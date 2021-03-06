#include <reproBLAS.h>

#include "../../config.h"

/**
 * @brief Compute the reproducible conjugated dot product of complex double precision vectors X and Y
 *
 * Return the sum of the pairwise products of X and conjugated Y.
 *
 * The reproducible dot product is computed with indexed types of default fold using #idxdBLAS_zizdotc()
 *
 * @param N vector length
 * @param X complex double precision vector
 * @param incX X vector stride (use every incX'th element)
 * @param Y complex double precision vector
 * @param incY Y vector stride (use every incY'th element)
 * @param dotc scalar return
 *
 * @author Peter Ahrens
 * @date   15 Jan 2016
 */
void reproBLAS_zdotc_sub(const int N, const void* X, const int incX, const void *Y, const int incY, void *dotc) {
  reproBLAS_rzdotc_sub(DIDEFAULTFOLD, N, X, incX, Y, incY, dotc);
}
