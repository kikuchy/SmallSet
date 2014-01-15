#Small Set Library

[![Build Status](https://travis-ci.org/kikuchy/SmallSet.png?branch=master)](https://travis-ci.org/kikuchy/SmallSet)

Small, simple and fast mathematics set library written in C language.

##Feature

- Small (Range and size)
    - Support small range
    - Only ``0`` - ``63`` unsigned integer can be elements of a set.
    - You need only 2 files.
- Simple (API)
    - Set object is immutable
    - Enumerate using iterator
    - Mathematics set operations
        - union of ``s`` and ``t``
        - intersection of ``s`` and ``t``
        - difference of `` s`` and ``t``
        - ``s`` is subset of ``t``
        - ``s`` is superset of ``t``
        - ``x`` is in ``s``
- Fast (Operation)
    - Inplemented using bit operations

##How to use

###Write a code

    #include "set.h"

    struct set s = set_empty();
    s = set_add(s, 1);
    s = set_add(s, 2);
    s = set_add(s, 3);                      // <- (1, 2, 3)

    int elements[] = { 0, 2, 4 };
    struct set t = set_construct_from_array(elements, 3);
                                            // <- (0, 2, 4)

    struct set union = set_union(s, t);     // <- (0, 1, 2, 3, 4)

    struct set is = set_intersection(s, t)  // <- (2)

    struct set diff = set_difference(s, t)  // <- (1, 3)

    struct set_iterator itl = set_begin(&s);
    for(; !set_iterator_isend(&itl); set_iterator_next(&itl))
    {
        printf("%d, ", set_iterator_get(&itl));
    }
    // printed: 1, 2, 3

###Build

    cc -c set.c
    cc -c your_program.c
    cc set.o your_grogram.o
    ./a.out
