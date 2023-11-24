#pragma once

#include <algorithm>
#include <vector>

using namespace std;

// Сортировка вставками
void insertionSort(vector<int> &arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int j = i;
        while (j > left && arr[j - 1] > arr[j]) {
            swap(arr[j - 1], arr[j]);
            --j;
        }
    }
}

// Merge
void merge(vector<int> &arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);
    for (int i = 0; i < n1; ++i) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; ++i) {
        rightArr[i] = arr[middle + 1 + i];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < n1) {
        arr[k++] = leftArr[i++];
    }

    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
}

// Стандартная версия MERGE SORT с выделением дополнительной памяти
void mergeSort(vector<int> &arr, int left, int right) {
    if (left >= right) {
        return;
    }
    auto middle = left + (right - left) / 2;
    mergeSort(arr, left, middle);
    mergeSort(arr, middle + 1, right);
    merge(arr, left, middle, right);
}

// Гибридная версия MERGE SORT с INSERTION SORT для малых массивов
void mergeSortHybrid(vector<int> &arr, int left, int right, int minSize) {
    if (left >= right) {
        return;
    }
    if (right - left + 1 <= minSize) {
        insertionSort(arr, left, right);
        return;
    }
    auto middle = left + (right - left) / 2;
    mergeSortHybrid(arr, left, middle, minSize);
    mergeSortHybrid(arr, middle + 1, right, minSize);
    merge(arr, left, middle, right);
}