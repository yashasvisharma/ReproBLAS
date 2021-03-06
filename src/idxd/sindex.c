#include <math.h>

#include <idxd.h>

#include "../common/common.h"

/**
 * @brief Get index of single precision
 *
 * The index of a non-indexed type is the smallest index an indexed type would need to have to sum it reproducibly. Higher indicies correspond to smaller bins.
 *
 * @param X scalar X
 * @return X's index
 *
 * @author Peter Ahrens
 * @author Hong Diep Nguyen
 * @date   19 Jun 2015
 */
int idxd_sindex(const float X){
  /*
  //reference version
  int exp;

  if(X == 0.0){
    return (FLT_MAX_EXP - FLT_MIN_EXP)/SIWIDTH;
  }else{
    frexpf(X, &exp);
    return (FLT_MAX_EXP - exp)/SIWIDTH;
  }
  */
  int exp = EXPF(X);
  if(exp == 0){
    if(X == 0.0){
      return idxd_SIMAXINDEX;
    }else{
      frexpf(X, &exp);
      return MIN((FLT_MAX_EXP - exp)/SIWIDTH, idxd_SIMAXINDEX);
    }
  }
  return ((FLT_MAX_EXP + EXPF_BIAS) - exp)/SIWIDTH;
}
