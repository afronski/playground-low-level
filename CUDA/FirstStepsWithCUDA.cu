#include <stdio.h>
#include <helper_timer.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void addKernel(const int *a, const int *b, int *c, int size) {
  int i = threadIdx.x + blockDim.x * blockIdx.x;

  float _a = a[i];
  float _b = b[i];

  float sum = _a + _b * 2.0f;
  float mul = _a * (_a + _b);
  float val = (sum + mul) * 5.35f;
  float val2= (sum * 8.06f) + sqrtf(val) * (mul + 6.36f);

  c[i] = sqrt(val2) * 44.87f;
}

void task4() {
  const int VALUE = 100;
  int someConstant = 1024;
  int size = 0;
  int block = 0;

  int *a = 0;
  int *b = 0;
  int *c = 0;

  int i = 0;
  int j = 0;

  int sum = 0;
  int sum2 = 0;

  int *aOnDevice = 0;
  int *bOnDevice = 0;
  int *cOnDevice = 0;

  do {
    printf("Type vector size: ");
    scanf("%d", &size);

    if (size <= 0) break;

    printf("\nType size of block: ");
    scanf("%d", &someConstant);

    if (size % someConstant == 0) {
      block = size / someConstant;
    } else {
      block = size / someConstant + 1;
    }

    a = (int*)malloc(sizeof(int) * size);
    b = (int*)malloc(sizeof(int) * size);
    c = (int*)malloc(sizeof(int) * size);

    for(i = 0; i < size; ++i) {
      a[i] = 1;
      b[i] = 1;
    }

    cudaSetDevice(0);

    cudaMalloc((void**)&aOnDevice, size * sizeof(int));
    cudaMalloc((void**)&bOnDevice, size * sizeof(int));
    cudaMalloc((void**)&cOnDevice, size * sizeof(int));

    cudaMemcpy(aOnDevice, a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(bOnDevice, b, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(cOnDevice, c, size * sizeof(int), cudaMemcpyHostToDevice);

    dim3 gridDims = dim3(block, 1, 1);
    dim3 blockDims = dim3(someConstant, 1, 1);

    StopWatchInterface* hTimer;
    sdkCreateTimer(&hTimer);
    sdkResetTimer(&hTimer);

    cudaDeviceSynchronize();
    addKernel<<<gridDims,blockDims>>>(aOnDevice, bOnDevice, cOnDevice, size);

    sdkStartTimer(&hTimer);
    for(i = 0; i < VALUE; ++i) {
      addKernel<<<gridDims,blockDims>>>(aOnDevice, bOnDevice, cOnDevice, size);
    }
    cudaDeviceSynchronize();
    sdkStopTimer(&hTimer);

    cudaMemcpy(c, cOnDevice, size * sizeof(int), cudaMemcpyDeviceToHost);
    float time1 = sdkGetTimerValue(&hTimer) / VALUE;

    sdkResetTimer(&hTimer);

    cudaFree(aOnDevice);
    cudaFree(bOnDevice);

    sum = c[0];
    for(i = 1; i < size; ++i) {
      sum += c[i];
    }

    sdkStartTimer(&hTimer);

    for(i = 0; i < size; ++i)
    {
      float _a = a[i];
      float _b = b[i];
      float sum = _a + _b * 2.0f;
      float mul = _a * (_a + _b);
      float val = (sum + mul) * 5.35f;
      float val2 = (sum * 8.06f) + sqrtf(val) * (mul + 6.36f);
      c[i] = sqrt(val2) * 44.87f;
    }

    sdkStopTimer(&hTimer);
    float time2 = sdkGetTimerValue(&hTimer);

    sum2 = 0;

    for(i = 0; i < size; ++i) {
      sum2 += c[i];
    }

    if (sum == sum2) {
      printf("OK!\n");
    }

    printf("CUDA: %f, CPU: %f \n", time1, time2);

    sdkResetTimer(&hTimer);
    cudaDeviceReset();

    free(a);
    free(b);
    free(c);
  } while(size > 0);
}