#include <idxdBLAS.h>
#include <idxd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../common/test_opt.h"
#include "../../config.h"
#include "wrap_saugsum.h"

#include "../common/test_vecvec_header.h"

static opt_option augsum_func;
static opt_option fold;
static opt_option norm;

static void validate_xblas_sdot_options_initialize(void){
  augsum_func._named.header.type       = opt_named;
  augsum_func._named.header.short_name = 'w';
  augsum_func._named.header.long_name  = "augsum_func";
  augsum_func._named.header.help       = "augmented summation function";
  augsum_func._named.required          = 0;
  augsum_func._named.n_names           = wrap_saugsum_func_n_names;
  augsum_func._named.names             = (char**)wrap_saugsum_func_names;
  augsum_func._named.descs             = (char**)wrap_saugsum_func_descs;
  augsum_func._named.value             = wrap_saugsum_RSDOT;

  fold._int.header.type       = opt_int;
  fold._int.header.short_name = 'k';
  fold._int.header.long_name  = "fold";
  fold._int.header.help       = "fold";
  fold._int.required          = 0;
  fold._int.min               = 2;
  fold._int.max               = idxd_SIMAXFOLD;
  fold._int.value             = SIDEFAULTFOLD;

  norm._int.header.type       = opt_int;
  norm._int.header.short_name = 'n';
  norm._int.header.long_name  = "norm";
  norm._int.header.help       = "-1 for close to underflow, 1 for close to overflow";
  norm._int.required          = 0;
  norm._int.min               = -1;
  norm._int.max               = 1;
  norm._int.value             = 0;
}

int validate_xblas_sdot(int fold, int N, float* X, int incX, float* Y, int incY, int func, float r, float ref) {
  // GENERATE DATA
  float res;
  float error;
  float bound;
  float_indexed *ires = idxd_sialloc(fold);

  idxd_sisconv(fold, r, ires);
  (wrap_siaugsum_func(func))(fold, N, X, incX, Y, incY, ires);
  res = idxd_ssiconv(fold, ires);
  error = fabsf(res - ref);
  bound = wrap_saugsum_bound(fold, N, func, X, incX, Y, incY, res, ref);
  if (!util_ssoftequals(res, ref, bound)) {
    //TODO these error messages need to go to stderr for all tests.
    printf("%s(X, Y) = %g != %g\n|%g - %g| = %g > %g\n", wrap_saugsum_func_names[func], res, ref, res, ref, error, bound);
    printf("\nres float_indexed:\n");
    idxd_siprint(fold, ires);
    printf("\n");
    return 1;
  }
  free(ires);
  return 0;
}

int vecvec_show_help(void){
  validate_xblas_sdot_options_initialize();

  opt_show_option(augsum_func);
  opt_show_option(fold);
  opt_show_option(norm);
  return 0;
}

const char* vecvec_name(int argc, char** argv){
  static char name_buffer[MAX_LINE];

  validate_xblas_sdot_options_initialize();

  opt_eval_option(argc, argv, &augsum_func);
  opt_eval_option(argc, argv, &fold);
  opt_eval_option(argc, argv, &norm);
  snprintf(name_buffer, MAX_LINE * sizeof(char), "Validate %s internally fold=%d", wrap_saugsum_func_names[augsum_func._named.value], fold._int.value);
  return name_buffer;
}

int vecvec_test(int argc, char** argv, int N, int incX, int incY){
  int rc = 0;
  float ref;
  float r;

  validate_xblas_sdot_options_initialize();

  util_random_seed();

  opt_eval_option(argc, argv, &augsum_func);
  opt_eval_option(argc, argv, &fold);
  opt_eval_option(argc, argv, &norm);

  float *X = util_svec_alloc(N, 4 * incX);
  float *Y = util_svec_alloc(N, 4 * incY);
  int *P;

  float *X_gen = util_svec_alloc(N, 1);
  float *Y_gen = util_svec_alloc(N, 1);
  float alpha = 1.0;
  float beta = 1.0;
  double ref_l;
  double ref_t;
  int seed = rand();
  util_xblas_sdot_fill(N, 0, 0, norm._int.value, 'n',
                  &alpha, 1, &beta, 1,
                  X_gen, Y_gen, &seed,
                  &r, &ref_l, &ref_t);
  ref = ref_l;
  util_svec_dotsplit_twins(N, X_gen, 1, X, incX);
  util_svec_dotsplit_couples(N, Y_gen, 1, Y, incY);
  free(X_gen);
  free(Y_gen);
  N *= 4;

  rc = validate_xblas_sdot(fold._int.value, N, X, incX, Y, incY, augsum_func._named.value, r, ref);
  if(rc != 0){
    return rc;
  }

  P = util_identity_permutation(N);
  util_svec_reverse(N, X, incX, P, 1);
  util_svec_permute(N, Y, incY, P, 1, NULL, 1);
  free(P);

  rc = validate_xblas_sdot(fold._int.value, N, X, incX, Y, incY, augsum_func._named.value, r, ref);
  if(rc != 0){
    return rc;
  }

  P = util_identity_permutation(N);
  util_svec_sort(N, X, incX, P, 1, util_Increasing);
  util_svec_permute(N, Y, incY, P, 1, NULL, 1);
  free(P);

  rc = validate_xblas_sdot(fold._int.value, N, X, incX, Y, incY, augsum_func._named.value, r, ref);
  if(rc != 0){
    return rc;
  }

  P = util_identity_permutation(N);
  util_svec_sort(N, X, incX, P, 1, util_Decreasing);
  util_svec_permute(N, Y, incY, P, 1, NULL, 1);
  free(P);

  rc = validate_xblas_sdot(fold._int.value, N, X, incX, Y, incY, augsum_func._named.value, r, ref);
  if(rc != 0){
    return rc;
  }

  P = util_identity_permutation(N);
  util_svec_sort(N, X, incX, P, 1, util_Increasing_Magnitude);
  util_svec_permute(N, Y, incY, P, 1, NULL, 1);
  free(P);

  rc = validate_xblas_sdot(fold._int.value, N, X, incX, Y, incY, augsum_func._named.value, r, ref);
  if(rc != 0){
    return rc;
  }

  P = util_identity_permutation(N);
  util_svec_sort(N, X, incX, P, 1, util_Decreasing_Magnitude);
  util_svec_permute(N, Y, incY, P, 1, NULL, 1);
  free(P);

  rc = validate_xblas_sdot(fold._int.value, N, X, incX, Y, incY, augsum_func._named.value, r, ref);
  if(rc != 0){
    return rc;
  }

  free(X);
  free(Y);

  return rc;
}
