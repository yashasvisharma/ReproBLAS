#include <indexed.h>

/**
 * @internal
 * @brief rescale manually specified indexed single precision sum of squares
 *
 * Rescale an indexed single precision sum of squares Y to Y' such that Y / (scaleY * scaleY) == Y' / (X * X) and #smindex(Y) == #sindex(1.0)
 *
 * Note that Y is assumed to have an index smaller than the index of 1.0, and that X >= scaleY
 *
 * @param fold the fold of the indexed types
 * @param X Y's new scaleY (X == #sscale(Y) for some @c float Y) (X >= scaleY)
 * @param scaleY Y's current scaleY (scaleY == #sscale(Y) for some @c float Y) (X >= scaleY)
 * @param manY Y's mantissa vector (#smindex(Y) >= #sindex(1.0))
 * @param incmanY stride within Y's mantissa vector (use every incmanY'th element)
 * @param carY Y's carry vector
 * @param inccarY stride within Y's carry vector (use every inccarY'th element)
 *
 * @author Peter Ahrens
 * @date   1 Jun 2015
 */
void smsrescale(const int fold, const float X, const float scaleY, float *manY, const int incmanY, float *carY, const int inccarY){
  int i;
  float rescaleY;

  if(X == scaleY){
    return;
  }

  rescaleY = X/scaleY;
  rescaleY *= rescaleY;
  for(i = 0; i < fold; i++){
    manY[i * incmanY] /= rescaleY;
    if(manY[i * incmanY] == 0.0){
      smsupdate(fold - i, 0.0, manY + i * incmanY, incmanY, carY + i * inccarY, inccarY);
      break;
    }
  }
}
