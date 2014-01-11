#include "set.h"

#define IS_IN_RANGE(x)    ((x) >= 0 && (x) < 64)

struct set set_construct()
{
  struct set s;
  s._val = 0;
  return s;
}

struct set set_add(struct set s, int x)
{
  if(IS_IN_RANGE(x))
  {
    uint64_t flag = (uint64_t)1 << x;
    s._val |= flag;
  }
  return s;
}

struct set set_discard(struct set s, int x)
{
  if(IS_IN_RANGE(x))
  {
    uint64_t flag = ~((uint64_t)1 << x);
    s._val &= flag;
  }
  return s;
}

static int count_bit(uint64_t v)
{
  uint64_t count = (v & 0x5555555555555555) + ((v >> 1) & 0x5555555555555555);
  count = (count & 0x3333333333333333) + ((count >> 2) & 0x3333333333333333);
  count = (count & 0x0f0f0f0f0f0f0f0f) + ((count >> 4) & 0x0f0f0f0f0f0f0f0f);
  count = (count & 0x00ff00ff00ff00ff) + ((count >> 8) & 0x00ff00ff00ff00ff);
  count = (count & 0x0000ffff0000ffff) + ((count >> 16) & 0x0000ffff0000ffff);
  return (int)((count & 0x00000000ffffffff) + ((count >> 32) & 0x00000000ffffffff));
}

int set_size(struct set s)
{
  return count_bit(s._val);
}

int set_in(struct set s, int x)
{
  return IS_IN_RANGE(x) ? s._val & (1 << x) : 0;
}


struct set set_union(struct set s, struct set t)
{
  s._val |= t._val;
  return s;
}

struct set set_intersection(struct set s, struct set t)
{
  s._val &= t._val;
  return s;
}

struct set set_difference(struct set s, struct set t)
{
  s._val &= ~t._val;
  return s;
}

int set_issubset(struct set s, struct set t)
{
  struct set inter = set_intersection(s, t);
  return inter._val == s._val;
}

int set_issuperset(struct set s, struct set t)
{
  struct set inter = set_intersection(s, t);
  return inter._val == t._val;
}

static int lsb(uint64_t x)
{
  x |= (x << 1);
  x |= (x << 2);
  x |= (x << 4);
  x |= (x << 8);
  x |= (x << 16);
  x |= (x << 32);
  return 64 - count_bit(x);
}

static int msb(uint64_t x)
{
  x |= (x >> 1);
  x |= (x >> 2);
  x |= (x >> 4);
  x |= (x >> 8);
  x |= (x >> 16);
  x |= (x >> 32);
  return count_bit(x) - 1;
}

struct set_iterator set_begin(struct set *s)
{
  struct set_iterator itl;
  itl._count = lsb(s->_val);
  itl._s = s;
  return itl;
}

struct set_iterator set_rbegin(struct set *s)
{
  struct set_iterator itl;
  itl._count = msb(s->_val);
  itl._s = s;
  return itl;
}

int set_iterator_get(struct set_iterator *itl)
{
  return itl->_count;
}

int set_iterator_isend(struct set_iterator *itl)
{
  return itl->_count > 63;
}

int set_iterator_isrend(struct set_iterator *itl)
{
  return itl->_count < 0;
}

int set_iterator_next(struct set_iterator *itl)
{
  if(itl->_count == 64) return 0;
  uint64_t mask = (itl->_count >= 63) ? 0 : (~(uint64_t)0) << (itl->_count + 1);
  uint64_t filtered = itl->_s->_val & mask;
  itl->_count = (filtered == 0) ? 64 : lsb(filtered);
  return 1;
}

int set_iterator_rnext(struct set_iterator *itl)
{
  if(itl->_count == -1) return 0;
  uint64_t mask = (itl->_count <= 0) ? 0 : (~(uint64_t)0) >> (64 - itl->_count);
  uint64_t filtered = itl->_s->_val & mask;
  itl->_count = (filtered == 0) ? -1 : msb(filtered);
  return 1;
}