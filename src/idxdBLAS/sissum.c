#include "idxdBLAS.h"

/**
 * @brief Add to indexed single precision Y the sum of single precision vector X
 *
 * Add to Y the indexed sum of X.
 *
 * @param fold the fold of the indexed types
 * @param N vector length
 * @param X single precision vector
 * @param incX X vector stride (use every incX'th element)
 * @param Y indexed scalar Y
 *
 * @author Peter Ahrens
 * @date   15 Jan 2016
 */
void idxdBLAS_sissum(const int fold, const int N, const float *X, const int incX, float_indexed *Y){
  idxdBLAS_smssum(fold, N, X, incX, Y, 1, Y + fold, 1);
}
