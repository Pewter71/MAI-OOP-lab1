#include <gtest/gtest.h>
#include <cstddef>
#include "array_ops.h"

TEST(Array, Create)
{
    int* arr{array_create(3)};
    EXPECT_NE(arr, nullptr);
    EXPECT_EQ(arr[0], 0);
    array_delete(arr);
}

TEST(Array, Delete)
{
    int* arr{array_create(3)};
    array_delete(arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(Array, ResizeGrow)
{
    int* arr{array_create(1)};
    arr[0] = 7;
    arr = array_resize(arr, 1, 3);
    EXPECT_EQ(arr[0], 7);
    EXPECT_EQ(arr[2], 0);
    array_delete(arr);
}

TEST(Array, ResizeShrink)
{
    int* arr{array_create(3)};
    arr[0] = 7;
    arr = array_resize(arr, 3, 1);
    EXPECT_EQ(arr[0], 7);
    array_delete(arr);
}

TEST(Array, InsertMiddle)
{
    std::size_t size{2};
    int* arr{array_create(size)};
    arr[0] = 1;
    arr[1] = 3;
    arr = array_insert(arr, size, 1, 2);
    EXPECT_EQ(size, 3U);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    array_delete(arr);
}

TEST(Array, InsertEmpty)
{
    std::size_t size{0};
    int* arr{array_create(size)};
    arr = array_insert(arr, size, 0, 5);
    EXPECT_EQ(size, 1U);
    EXPECT_EQ(arr[0], 5);
    array_delete(arr);
}

TEST(Array, RemoveMiddle)
{
    std::size_t size{3};
    int* arr{array_create(size)};
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr = array_remove(arr, size, 1);
    EXPECT_EQ(size, 2U);
    EXPECT_EQ(arr[1], 3);
    array_delete(arr);
}

TEST(Array, RemoveEmpty)
{
    std::size_t size{0};
    int* arr{array_create(size)};
    arr = array_remove(arr, size, 0);
    EXPECT_EQ(size, 0U);
    array_delete(arr);
}

TEST(Search, Found)
{
    const int arr[]{5, 3, 1, 4, 2};
    std::size_t index{};
    EXPECT_TRUE(array_search(arr, 5, 4, index));
    EXPECT_EQ(index, 3U);
}

TEST(Search, NotFound)
{
    const int arr[]{5, 3, 1, 4, 2};
    std::size_t index{};
    EXPECT_FALSE(array_search(arr, 5, 7, index));
}

TEST(Search, Empty)
{
    std::size_t index{};
    EXPECT_FALSE(array_search(nullptr, 0, 1, index));
}

TEST(Variant, MergeSort)
{
    int arr[]{5, 3, 1, 4, 2};
    array_merge_sort(arr, 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[4], 5);
}

TEST(Variant, Median)
{
    const int arr[]{5, 3, 1, 4, 2};
    EXPECT_EQ(array_median(arr, 5), 3);
}

TEST(Variant, MedianEmpty)
{
    EXPECT_EQ(array_median(nullptr, 0), 0);
}