#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <cassert>
#include <iostream>

// If DEBUG undefined, debug mode is disable.
#define DEBUG

#ifdef DEBUG

#undef NDEBUG

#define DEBUG_MSG(msg, ...)                                            \
  printf("DEBUG [%s:%d - %s] " msg "\n", __FILE__, __LINE__, __func__, \
         ##__VA_ARGS__);
#endif

#endif