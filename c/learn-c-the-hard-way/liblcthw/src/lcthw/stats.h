#ifndef _lcthw_stats_h_
#define _lcthw_stats_h_

typedef struct Stats {
  double sum;
  double sumsq;
  unsigned long n;
  double min;
  double max;
} Stats;

Stats* Stats_recreate(double sum, double sumq, unsigned long n, double min, double max);
Stats* Stats_create();

double Stats_mean(Stats* st);
double Stats_stddev(Stats* st);

void Stats_sample(Stats* st, double s);
void Stats_dump(Stats* st);

#endif
