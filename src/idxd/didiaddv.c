#include <idxd.h>

/**
 * @brief  Add indexed double precision vectors (Y += X)
 *
 * Performs the operation Y += X
 *
 * @param fold the fold of the indexed types
 * @param N vector length
 * @param X indexed vector X
 * @param incX X vector stride (use every incX'th element)
 * @param Y indexed vector Y
 * @param incY Y vector stride (use every incY'th element)
 *
 * @author Peter Ahrens
 * @date   25 Jun 2015
 */
void idxd_didiaddv(const int fold, const int N, const double_indexed *X, const int incX, double_indexed *Y, const int incY){
  int i;
  for(i = 0; i < N; i++, X += incX * idxd_dinum(fold), Y += incY * idxd_dinum(fold)){
    idxd_dmdmadd(fold, X, 1, X + fold, 1, Y, 1, Y + fold, 1);
  }
}
