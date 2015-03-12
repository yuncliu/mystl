#ifndef _MY_MOVE_
#define _MY_MOVE_

namespace my {

/**
 *    *  @addtogroup utilities
 *    *  @{
 *    */

/**
*  @brief Swaps two values.
*  @param  __a  A thing of arbitrary type.
*  @param  __b  Another thing of arbitrary type.
*  @return   Nothing.
*/
template<typename _Tp>
inline void
swap(_Tp& _a, _Tp& _b)
{
  _Tp _tmp = _a;
  _a = _b;
  _b = _tmp;
}


}

#endif //_MY_MOVE_
