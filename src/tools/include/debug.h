#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <cassert>
#include <cstdio>
#include <cstdlib>

// If DEBUG undefined, debug mode is disable.
#define DEBUG

#ifdef DEBUG

#undef NDEBUG

#define ASSERT_MSG(cond, msg)                                            \
  do {                                                                   \
    if (!(cond)) {                                                       \
      fprintf(stderr,                                                    \
              "[ASSERT FAILED] %s:%d\n  Condition: %s\n  Message: %s\n", \
              __FILE__, __LINE__, #cond, msg);                           \
      assert(false);                                                     \
    }                                                                    \
  } while (0)
#else
#endif

#endif