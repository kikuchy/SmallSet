#include <gtest/gtest.h>
extern "C"
{
#include "set.h"
}

TEST(SetConstructTest, ConstructFromArray)
{
    int array[] = {-1, 0, 2, 3, 63, 64};
    struct set s = set_construct_from_array(array, 6);
    uint64_t ext = (uint64_t)1 << 0;
    ext |= (uint64_t)1 << 2;
    ext |= (uint64_t)1 << 3;
    ext |= (uint64_t)1 << 63;
    EXPECT_EQ(ext, s._val);
}

TEST(SetEmptyTest, EmptySet)
{
    struct set s = set_empty();
    EXPECT_EQ(0, s._val);
}

TEST(SetAddTest, AddInsideOfRange)
{
    struct set s = set_empty();
    s = set_add(s, 0);
    uint64_t exp = (uint64_t)1 << 0;
    EXPECT_EQ(exp, s._val);
    s = set_add(s, 63);
    exp |= (uint64_t)1 << 63;
    EXPECT_EQ(exp, s._val);
 }

TEST(SetAddTest, AddOutOfRange)
{
    struct set s = set_empty();
    s = set_add(s, 64);
    EXPECT_EQ(0, s._val);
    s = set_add(s, -1);
    EXPECT_EQ(0, s._val);
}

TEST(SetDiscardTest, DiscardContains)
{
    struct set s = set_empty();
    s = set_add(s, 1);
    s = set_add(s, 10);
    s = set_discard(s, 1);
    EXPECT_EQ((uint64_t)1 << 10, s._val);
}

TEST(SetDiscardTest, DiscardNotContains)
{
    struct set s = set_empty();
    s = set_add(s, 3);
    s = set_discard(s, 5);
    EXPECT_EQ((uint64_t)1 << 3, s._val);
}

TEST(SetSizeTest, GetSize)
{
    struct set s = set_empty();
    EXPECT_EQ(0, set_size(s));
    s = set_add(s, 1);
    EXPECT_EQ(1, set_size(s));
    s = set_add(s, 1);
    EXPECT_EQ(1, set_size(s));
}

TEST(SetInTest, InContains)
{
    struct set s = set_empty();
    EXPECT_FALSE(set_in(s, -1));
    EXPECT_FALSE(set_in(s, 0));
    s = set_add(s, 0);
    EXPECT_TRUE(set_in(s, 0));
}

TEST(SetUnionTest, Union)
{
    struct set s = set_empty(), t = set_empty();
    s = set_add(s, 0);
    s = set_add(s, 1);
    s = set_add(s, 2);
    t = set_add(t, 0);
    t = set_add(t, 2);
    t = set_add(t, 4);
    s = set_union(s, t);
    uint64_t exp = (uint64_t)1 |
                    (uint64_t)1 << 1 | 
                    (uint64_t)1 << 2 |
                    (uint64_t)1 << 4;
    EXPECT_EQ(exp, s._val);
}

TEST(SetIntersectionTest, Intersection)
{
    struct set s = set_empty(), t = set_empty();
    s = set_add(s, 0);
    s = set_add(s, 1);
    s = set_add(s, 2);
    t = set_add(t, 0);
    t = set_add(t, 2);
    t = set_add(t, 4);
    s = set_intersection(s, t);
    uint64_t exp = (uint64_t)1 |
                    (uint64_t)1 << 2;
    EXPECT_EQ(exp, s._val);
}

TEST(SetDifferenceTest, Difference)
{
    struct set s = set_empty(), t = set_empty();
    s = set_add(s, 0);
    s = set_add(s, 1);
    s = set_add(s, 2);
    s = set_add(s, 3);
    t = set_add(t, 1);
    t = set_add(t, 2);
    s = set_difference(s, t);
    uint64_t exp = (uint64_t)1 |
                    (uint64_t)1 << 3;
    EXPECT_EQ(exp, s._val);
}

TEST(SetIsSubsetTest, IsSubset)
{
    struct set s = set_empty(), t = set_empty();
    s = set_add(s, 0);
    s = set_add(s, 1);
    s = set_add(s, 2);
    s = set_add(s, 3);
    t = set_add(t, 0);
    t = set_add(t, 2);
    t = set_add(t, 3);
    EXPECT_TRUE(set_issubset(t, s));
}

TEST(SetIsSupersetTest, IsSuperset)
{
    struct set s = set_empty(), t = set_empty();
    s = set_add(s, 0);
    s = set_add(s, 1);
    s = set_add(s, 2);
    s = set_add(s, 3);
    t = set_add(t, 0);
    t = set_add(t, 2);
    t = set_add(t, 3);
    EXPECT_TRUE(set_issuperset(s, t));
}

TEST(SetEnumerateTest, GetIterator)
{
    struct set s = set_empty();
    s = set_add(s, 0);
    s = set_add(s, 1);
    s = set_add(s, 3);
    s = set_add(s, 5);
    s = set_add(s, 7);
    s = set_add(s, 63);
    struct set_iterator itl = set_begin(&s);
    EXPECT_EQ(&s, itl._s);
    EXPECT_EQ(0, itl._count);
    EXPECT_TRUE(set_iterator_next(&itl));
    EXPECT_EQ(1, set_iterator_get(&itl));
    EXPECT_TRUE(set_iterator_next(&itl));
    EXPECT_TRUE(set_iterator_next(&itl));
    EXPECT_TRUE(set_iterator_next(&itl));
    EXPECT_TRUE(set_iterator_next(&itl));
    EXPECT_EQ(63, set_iterator_get(&itl));
    EXPECT_FALSE(set_iterator_isend(&itl));
    EXPECT_TRUE(set_iterator_next(&itl));
    EXPECT_TRUE(set_iterator_isend(&itl)) << itl._count << ", " << (itl._s->_val & (~(uint64_t)0 << (itl._count + 1)));
    EXPECT_FALSE(set_iterator_next(&itl));
}

TEST(SetEnumerateTest, ForLoop)
{
    struct set s = set_empty();
    s = set_add(s, 0);
    s = set_add(s, 1);
    s = set_add(s, 3);
    s = set_add(s, 5);
    s = set_add(s, 7);
    s = set_add(s, 63);
    struct set_iterator itl = set_begin(&s);
    int count = 0;
    for(;!set_iterator_isend(&itl); set_iterator_next(&itl))
    {
        count++;
    }
    EXPECT_EQ(6, count);
    itl = set_rbegin(&s);
    for(count = 0; !set_iterator_isrend(&itl); set_iterator_rnext(&itl))
    {
        count++;
        //std::cout << set_iterator_get(&itl);
    }
    EXPECT_EQ(6, count);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
