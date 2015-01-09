#include <rblas.h>
#include <IndexedFP.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../common/test_opt.h"
#include "../common/test_vec.h"
#include "../common/test_time.h"
#include "../common/test_perf.h"
#include <rblas.h>
#include <IndexedFP.h>

#include "vecvec_fill_bench_header.h"

#define FLOP_PER_N 8

extern const char* vecvec_fill_bench_name(int argc, char** argv){
  static char name_buffer[MAX_LINE];
  snprintf(name_buffer, MAX_LINE * sizeof(char), "Benchmark [camaxm]");
  return name_buffer;
}

extern int vecvec_fill_bench_test(int argc, char** argv, int N, int incx, int incy, int type, int perf_unit, int trials){
  int rc = 0;
  float complex res;
  I_float_Complex Ires;
  float complex *x = cvec_alloc(N, incx);
  float complex *y = cvec_alloc(N, incy);

  vec_random_seed();

  //fill empty space with random data to check increment
  cvec_fill(N * incx, x, 1, vec_fill_RAND, 1.0, 1.0);
  cvec_fill(N * incy, y, 1, vec_fill_RAND, 1.0, 1.0);

  //fill x
  cvec_fill(N, x, incx, type, 1.0, opt_read_float(argc, argv, "-c", 1.0));

  //fill y with -i where necessary
  cvec_fill(N, y, incy, vec_fill_CONSTANT, -_Complex_I, 1.0);

  time_tic();
  for(int i = 0; i < trials; i++){
    res = camaxm(N, x, incx, y, incy);
  }
  time_toc();

  printf("%e\n", perf_output(time_read(), N, trials, FLOP_PER_N, perf_unit, perf_prec_SINGLE));

  free(x);
  free(y);
  return rc;
}
