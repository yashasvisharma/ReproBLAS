#include <math.h>

#include <indexed.h>

/**
 * @internal
 * @brief Convert manually specified indexed double precision to double precision (X -> Y)
 *
 * @param fold the fold of the indexed types
 * @param manX X's mantissa vector
 * @param incmanX stride within X's mantissa vector (use every incmanX'th element)
 * @param carX X's carry vector
 * @param inccarX stride within X's carry vector (use every inccarX'th element)
 * @return scalar Y
 *
 * @author Hong Diep Nguyen
 * @author Peter Ahrens
 * @date   27 Apr 2015
 */
double ddmconv(const int fold, const double* manX, const int incmanX, const double* carX, const int inccarX) {
  int i = 0;
  long double Y = 0.0;
  double M;

  if (isinf(manX[0]) || isnan(manX[0]))
    return manX[0];

  if (manX[0] == 0.0) {
    return 0.0;
  }

  if(dmindex0(manX)){
    M = ufp(manX[i * incmanX]);
    Y += (carX[i * inccarX] * 0.25 * M + (manX[i * incmanX] - 1.5 * M)) * DMEXPANSION;
    i = 1;
  }

  for (; i < fold; i++) {
    M = ufp(manX[i * incmanX]);
    Y += carX[i * inccarX] * 0.25 * M + (manX[i * incmanX] - 1.5 * M);
  }

  return Y;
}
