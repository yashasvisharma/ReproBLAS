#include <indexed.h>

/**
 * @brief  Add complex single precision to suitably indexed manually specified indexed complex single precision (Y += X)
 *
 * Performs the operation Y += X on an indexed type Y where the index of Y is larger than the index of X
 *
 * @note This routine was provided as a means of allowing the you to optimize your code. After you have called cicupdate() on Y with the maximum absolute value of any elements you wish to deposit in Y, you can call this method to deposit a maximum of SIENDURANCE elements into Y. After calling cicdeposit() on an indexed type, you must renormalize the indexed type with cirenorm().
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
void cicdeposit(const int fold, const void *X, float_complex_indexed *Y){
  cmcdeposit(fold, X, Y, 1);
}
