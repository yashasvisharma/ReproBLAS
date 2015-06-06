#include <math.h>

#include <indexed.h>

#include "../common/common.h"

/**
 * @internal
 * @brief  Add complex double precision to suitably indexed manually specified indexed complex double precision (Y += X)
 *
 * Performs the operation Y += X on an indexed type Y where the index of Y is larger than the index of X
 *
 * @note This routine was provided as a means of allowing the you to optimize your code. After you have called zmzupdate() on Y with the maximum absolute value of any elements you wish to deposit in Y, you can call this method to deposit a maximum of DIENDURANCE elements into Y. After calling zmzdeposit() on an indexed type, you must renormalize the indexed type with zmrenorm().
 *
 * @param fold the fold of the indexed types
 * @param X scalar X
 * @param manY Y's mantissa vector
 * @param incmanY stride within Y's mantissa vector (use every incmanY'th element)
 *
 * @author Hong Diep Nguyen
 * @author Peter Ahrens
 * @date   27 Apr 2015
 */
void zmzdeposit(const int fold, const void *X, double *manY, const int incmanY){
  double MR, MI;
  long_double qR, qI;
  int i;
  double xR = ((double*)X)[0];
  double xI = ((double*)X)[1];

  if (isinf(xR) || isnan(xR) || isinf(manY[0]) || isnan(manY[0])) {
    manY[0] += xR;
    dmddeposit(fold, xI, manY + 1, 2 * incmanY);
    return;
  }
  if (isinf(xI) || isnan(xI) || isinf(manY[1]) || isnan(manY[1])) {
    manY[1] += xI;
    dmddeposit(fold, xR, manY, 2 * incmanY);
    return;
  }

  if(dmindex0(manY) || dmindex0(manY + 1)){
    dmddeposit(fold, xR, manY, 2 * incmanY);
    dmddeposit(fold, xI, manY + 1, 2 * incmanY);
    return;
  }

  for (i = 0; i < fold - 1; i++) {
    MR = manY[i * 2 * incmanY];
    MI = manY[i * 2 * incmanY + 1];
    qR.d = xR;
    qI.d = xI;
    qR.l |= 1;
    qI.l |= 1;
    qR.d += MR;
    qI.d += MI;
    manY[i * 2 * incmanY] = qR.d;
    manY[i * 2 * incmanY + 1] = qI.d;
    MR -= qR.d;
    MI -= qI.d;
    xR += MR;
    xI += MI;
  }
  qR.d = xR;
  qI.d = xI;
  qR.l |= 1;
  qI.l |= 1;
  manY[i * 2 * incmanY] += qR.d;
  manY[i * 2 * incmanY + 1] += qI.d;
}
