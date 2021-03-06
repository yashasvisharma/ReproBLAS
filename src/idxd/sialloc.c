#include <idxd.h>

/**
 * @brief indexed single precision allocation
 *
 * @param fold the fold of the indexed type
 * @return a freshly allocated indexed type. (free with @c free())
 *
 * @author Peter Ahrens
 * @date   27 Apr 2015
 */
float_indexed *idxd_sialloc(const int fold){
  return (float_indexed*)malloc(idxd_sisize(fold));
}
