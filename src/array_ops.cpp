#include "array_ops.h"
#include <algorithm>
#include <iostream>

void copy_elements(const int* source, int* destination, std::size_t count) {
    for (std::size_t i{0}; i < count; ++i) {
        destination[i] = source[i];
    }
}

void merge_half(int* arr, std::size_t middle, std::size_t size) {
    int* merged{array_create(size)};
    std::size_t left{0};
    std::size_t right{middle};
    for (std::size_t i{0}; i < size; ++i) {
        if (right >= size || (left < middle && arr[left] <= arr[right])) {
            merged[i] = arr[left];
            ++left;
        } else {
            merged[i] = arr[right];
            ++right;
        }
    }
    copy_elements(merged, arr, size);
    array_delete(merged);
}
int* array_create(std::size_t size) {
    return new int[size]{};
}

void array_delete(int*& arr) {
    delete[] arr;
    arr = nullptr;
}

int* array_resize(int* arr, std::size_t size, std::size_t new_size) {
    int* resized{array_create(new_size)};
    copy_elements(arr, resized, std::min(size, new_size));
    array_delete(arr);
    return resized;
}

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value) {
    if (pos > size) {
        return arr;
    }
    int* result{array_create(size + 1)};
    copy_elements(arr, result, pos);
    result[pos] = value;
    copy_elements(arr + pos, result + pos + 1, size - pos);
    array_delete(arr);
    ++size;
    return result;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos) {
    if (pos >= size) {
        return arr;
    }
    int* result{array_create(size - 1)};
    copy_elements(arr, result, pos);
    copy_elements(arr + pos + 1, result + pos, size - pos - 1);
    array_delete(arr);
    --size;
    return result;
}

void array_print(const int* arr, std::size_t size) {
    for (std::size_t i{0}; i < size; ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << arr[i];
    }
    std::cout << "\n";
}

bool array_search(const int* arr, std::size_t size, int target, std::size_t& out_index) {
    for (std::size_t i{0}; i < size; ++i) {
        if (arr[i] == target) {
            out_index = i;
            return true;
        }
    }
    return false;
}

void array_merge_sort(int* arr, std::size_t size) {
    if (size < 2) {
        return;
    }
    const std::size_t middle{size / 2};
    array_merge_sort(arr, middle);
    array_merge_sort(arr + middle, size - middle);
    merge_half(arr, middle, size);
}

int array_median(const int* arr, std::size_t size) {
    if (size == 0) {
        return 0;
    }
    int* sorted{array_create(size)};
    copy_elements(arr, sorted, size);
    array_merge_sort(sorted, size);
    int median{sorted[(size - 1) / 2]};
    array_delete(sorted);
    return median;
}
