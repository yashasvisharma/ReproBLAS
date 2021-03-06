#include <math.h>

#include <idxd.h>

#include "../common/common.h"

/**
 * @internal
 * @brief  Add double precision to suitably indexed manually specified indexed double precision (Y += X)
 *
 * Performs the operation Y += X on an indexed type Y where the index of Y is larger than the index of X
 *
 * @note This routine was provided as a means of allowing the you to optimize your code. After you have called #idxd_dmdupdate() on Y with the maximum absolute value of all future elements you wish to deposit in Y, you can call #idxd_dmddeposit() to deposit a maximum of #idxd_DIENDURANCE elements into Y before renormalizing Y with #idxd_dmrenorm(). After any number of successive calls of #idxd_dmddeposit() on Y, you must renormalize Y with #idxd_dmrenorm() before using any other function on Y.
 *
 * @param fold the fold of the indexed types
 * @param X scalar X
 * @param priY Y's primary vector
 * @param incpriY stride within Y's primary vector (use every incpriY'th element)
 *
 * @author Hong Diep Nguyen
 * @author Peter Ahrens
 * @date   10 Jun 2015
 */
void idxd_dmddeposit(const int fold, const double X, double *priY, const int incpriY){
  double M;
  long_double q;
  int i;
  double x = X;

  if(ISNANINF(x) || ISNANINF(priY[0])){
    priY[0] += x;
    return;
  }

  if(idxd_dmindex0(priY)){
    M = priY[0];
    q.d = x * idxd_DMCOMPRESSION;
    q.l |= 1;
    q.d += M;
    priY[0] = q.d;
    M -= q.d;
    M *= idxd_DMEXPANSION * 0.5;
    x += M;
    x += M;
    for (i = 1; i < fold - 1; i++) {
      M = priY[i * incpriY];
      q.d = x;
      q.l |= 1;
      q.d += M;
      priY[i * incpriY] = q.d;
      M -= q.d;
      x += M;
    }
    q.d = x;
    q.l |= 1;
    priY[i * incpriY] += q.d;
  }else{
    for (i = 0; i < fold - 1; i++) {
      M = priY[i * incpriY];
      q.d = x;
      q.l |= 1;
      q.d += M;
      priY[i * incpriY] = q.d;
      M -= q.d;
      x += M;
    }
    q.d = x;
    q.l |= 1;
    priY[i * incpriY] += q.d;
  }
}
