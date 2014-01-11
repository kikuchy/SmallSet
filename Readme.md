#Small Set Library

Small, simple and fast mathematics set library written in C language.

##Feature

- Fast (Operation)
    - Inplemented using bit operations
- Small (Range and size)
    - Support small range
    - Only ``0`` - ``63`` unsigned integer can be elements of a set.
    - You need only 2 files.
- Mathematics set operations
    - union of ``s`` and ``t``
    - intersection of ``s`` and ``t``
    - difference of `` s`` and ``t``
    - ``s`` is subset of ``t``
    - ``s`` is superset of ``t``
    - ``x`` is in ``s``
- Simple (API)
    - Set object is unbreakable
    - Enumerate using iterator

##How to use

###Write a code

    #include "set.h"

    struct set s = set_construct();
    s = set_add(s, 1);
    s = set_add(s, 2);
    s = set_add(s, 3);

    struct set t = set_construct();
    t = set_add(t, 0);
    t = set_add(t, 2);
    t = set_add(t, 4);

    struct set union = set_union(s, t);     // <- (0, 1, 2, 3, 4)

    struct set is = set_intersection(s, t)  // <- (2)

    struct set diff = set_difference(s, t)  // <- (1, 3)

    struct set_iterator itl = set_begin(&s);
    for(; !set_iterator_isend(&itl); set_iterator_next(&itl))
    {
        printf("%d, ", set_iterator_get(&itl));
    }
    // printed: 1, 2, 3
