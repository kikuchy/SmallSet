#ifndef SET_H
#define SET_H

#include <stdint.h>

struct set
{
  uint64_t _val;
};

struct set_iterator
{
  int _count;
  struct set *_s;
};

struct set set_construct_from_array(int elems[], int length);
struct set set_empty();
struct set set_add(struct set s, int x);
struct set set_discard(struct set s, int x);
int set_size(struct set s);
int set_in(struct set s, int x);
struct set set_union(struct set s, struct set t);
struct set set_intersection(struct set s, struct set t);
struct set set_difference(struct set s, struct set t);
int set_issubset(struct set s, struct set t);
int set_issuperset(struct set s, struct set t);
struct set_iterator set_begin(struct set *s);
struct set_iterator set_rbegin(struct set *s);
int set_iterator_get(struct set_iterator *itl);
int set_iterator_isend(struct set_iterator *itl);
int set_iterator_isrend(struct set_iterator *itl);
int set_iterator_next(struct set_iterator *itl);
int set_iterator_rnext(struct set_iterator *itl);
#endif
