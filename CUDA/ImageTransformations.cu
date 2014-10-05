#include <stdio.h>
#include <helper_timer.h>
#include <helper_image.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void imageKernel(const float *a, float *b, int im_width, int im_height, int pitch) {
  int ix = threadIdx.x + blockDim.x * blockIdx.x;
  int iy = threadIdx.y + blockDim.y * blockIdx.y;
  float sum = 0.0f;
  int oxx, oyy;

  for (int xx = ix - 2; xx < ix + 2; ++xx) {
    for (int yy = iy - 2; yy < iy + 2; ++yy) {
      oxx = xx;
      oyy = yy;

      if (xx < 0) oxx = 0;
      if (yy < 0) oyy = 0;

      if (xx >= im_width) oxx = im_width - 1;
      if (yy >= im_height) oyy = im_height - 1;

      sum += a[oyy * (pitch / sizeof(float)) + oxx];
    }
  }

  if (ix < im_width && iy < im_height) {
    int idx = iy * (pitch / sizeof(float)) + ix;
    b[idx] = sum / 25;

    if (b[idx] > 1.0f) {
      b[idx] = 1.0f;
    }

    if (b[idx] < 0.0f) {
      b[idx] = 0.0f;
    }
  }
}

void blurPixel(const float* a, float* b, int ix, int iy, int im_width, int im_height) {
  float sum = 0.0f;
  int oxx, oyy;

  for (int xx = ix - 2; xx < ix + 2; ++xx) {
    for (int yy = iy - 2; yy < iy + 2; ++yy) {
      oxx = xx;
      oyy = yy;

      if (xx < 0) oxx = 0;
      if (yy < 0) oyy = 0;

      if (xx >= im_width) oxx = im_width - 1;
      if (yy >= im_height) oyy = im_height - 1;

      sum += a[oyy * im_width + oxx];
    }
  }

  if (ix < im_width && iy < im_height) {
    int idx = iy * im_width + ix;
    b[idx] = sum / 25;

    if (b[idx] > 1.0f) {
      b[idx] = 1.0f;
    }

    if (b[idx] < 0.0f) {
      b[idx] = 0.0f;
    }
  }
}

void task4() {
  int blockSizeX = 0, blockSizeY = 0;
  int size = 0;
  int blockX = 0, blockY = 0;

  float *b = 0;
  float *c = 0;
  float *d = 0;

  size_t pitch = 0;
  size_t pitch1 = 0;

    float *aOnDevice = 0;
    float *bOnDevice = 0;

  unsigned int im_width, im_height;
  float* im_data = NULL;

  sdkLoadPGM("lena.pgm", &im_data, &im_width, &im_height);
  size = im_width * im_height;

  printf("Type size of block X: ");
  scanf("%d", &blockSizeX);

  printf("\nType size of Y block: ");
  scanf("%d", &blockSizeY);

  if (im_width % blockSizeX == 0) {
    blockX = im_width / blockSizeX;
  } else {
    blockX = im_width / blockSizeX + 1;
  }

  if (im_height % blockSizeY == 0) {
    blockY = im_height / blockSizeY;
  } else {
    blockY = im_height / blockSizeY + 1;
  }

  b = (float*)malloc(sizeof(float) * size);
  c = (float*)malloc(sizeof(float) * size);
  d = (float*)malloc(sizeof(float) * size);

  cudaSetDevice(0);
  cudaMallocPitch((void**)&aOnDevice, &pitch, im_width * sizeof(float), im_height);
  cudaMallocPitch((void**)&bOnDevice, &pitch1, im_width * sizeof(float), im_height);

  cudaMemcpy2D(aOnDevice, pitch, im_data, im_width * sizeof(float), im_width * sizeof(float), im_height, cudaMemcpyHostToDevice);
  cudaMemcpy2D(bOnDevice, pitch1, im_data, im_width * sizeof(float), im_width * sizeof(float), im_height, cudaMemcpyHostToDevice);

  dim3 gridDims = dim3(blockX, blockY, 1);
  dim3 blockDims = dim3(blockSizeX, blockSizeY, 1);

  StopWatchInterface* hTimer;
  sdkCreateTimer(&hTimer);
  sdkResetTimer(&hTimer);

  cudaDeviceSynchronize();

  sdkStartTimer(&hTimer);

  for(int i = 0; i < 100; ++i) {
    imageKernel<<<gridDims,blockDims>>>(aOnDevice, bOnDevice, im_width, im_height, pitch);
  }

  cudaDeviceSynchronize();
  sdkStopTimer(&hTimer);

  float time1 = sdkGetTimerValue(&hTimer) / 100;

  cudaMemcpy2D(c, im_width * sizeof(float), bOnDevice, pitch1, im_width * sizeof(float), im_height, cudaMemcpyDeviceToHost);
  sdkSavePGM("lena_out_gpu.pgm", c, im_width, im_height);

  cudaFree(aOnDevice);
  cudaFree(bOnDevice);

  sdkResetTimer(&hTimer);

  sdkStartTimer(&hTimer);

  for(int x = 0; x < im_width; ++x) {
    for(int y = 0; y  < im_height; ++y) {
      blurPixel(im_data, d, x, y, im_width, im_height);
    }
  }

  sdkStopTimer(&hTimer);
  float time2 = sdkGetTimerValue(&hTimer);

  printf("CUDA: %f, CPU: %f \n", time1, time2);
  sdkSavePGM("lena_out_cpu.pgm", d, im_width, im_height);

  sdkResetTimer(&hTimer);
  cudaDeviceReset();

  free(b);
  free(c);
  free(d);
}