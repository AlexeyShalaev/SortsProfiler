#pragma once

#include <algorithm>
#include <random>
#include <vector>

using namespace std;

// Массивы, которые заполнены случайными значениями в некотором диапазоне.
vector<int> generateRandomArray(int size, int left, int right) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(left, right);
    for (auto &element: arr) {
        element = dist(gen);
    }
    return arr;
}

// Массивы, которые отсортированы в обратном порядке по невозрастанию.
vector<int> generateRandomReversedSortedArray(int size, int left, int right) {
    auto arr = generateRandomArray(size, left, right);
    sort(arr.begin(), arr.end(), greater<int>());
    return arr;
}

// Массивы, которые «почти» отсортированы.
vector<int> generatePartiallySortedArray(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, size - 1);

    auto swaps = max(size / 2, size / 100);

    for (size_t i = 0; i < swaps; ++i) {
        auto index1 = dist(gen);
        auto index2 = dist(gen);
        swap(arr[index1], arr[index2]);
    }
    return arr;
}