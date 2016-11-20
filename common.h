#pragma once

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

#define CAT_(x, y) x##y
#define CAT(x, y) CAT_(x, y)

#define OPAD(size) u8 CAT(_pad_, __COUNTER__)[size]
#define OSTRUCT(name, size)                                                    \
  struct name {                                                                \
    union {                                                                    \
      OPAD(size);
#define OSTRUCT_END                                                            \
  }                                                                            \
  ;                                                                            \
  }                                                                            \
  ;
#define OFIELD(off, field)                                                     \
  struct {                                                                     \
    OPAD(off);                                                                 \
    field;                                                                     \
  }

#define ASSERT_STRSIZE(struc, size)                                            \
  _Static_assert(sizeof(struc) == (size), "size of " #struc " != " #size)
#define ASSERT_STROFF(struc, member, offset)                                   \
  _Static_assert(offsetof(struc, member) == (offset),                          \
                 "offset of " #struc "." #member " != " #offset)
