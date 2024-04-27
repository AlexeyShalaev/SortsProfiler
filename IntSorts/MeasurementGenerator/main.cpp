#include "array_generators.h"
#include "array_sorters.h"

#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;
using namespace std::chrono;
using namespace std::literals;
using Clock = std::chrono::high_resolution_clock;

struct SortTimes {
    vector<long long> randomArray;
    vector<long long> randomReversedSortedArray;
    vector<long long> partiallySortedArray;

    explicit SortTimes(int size) {
        randomArray.resize(size);
        randomReversedSortedArray.resize(size);
        partiallySortedArray.resize(size);
    }
};

ostream &operator<<(ostream &output, const vector<long long> &arr) {
    for (auto &el: arr) {
        output << el << " ";
    }
    output << endl;
    return output;
}

ostream &operator<<(ostream &output, const SortTimes &sortTimes) {
    output << "RandomArray: " << sortTimes.randomArray;
    output << "RandomReversedSortedArray: " << sortTimes.randomReversedSortedArray;
    output << "PartiallySortedArray: " << sortTimes.partiallySortedArray;
    output << endl;
    return output;
}

void ProfileSorts(int begin, int end, int step, int left, int right) {
    auto randomArray = generateRandomArray(end, left, right);
    auto randomReversedSortedArray = generateRandomReversedSortedArray(end, left, right);
    auto partiallySortedArray = generatePartiallySortedArray(end);

    auto times_size = (end - begin) / step + 1;

    SortTimes mergeSortTimes(times_size);
    SortTimes mergeSortHybridTimes_5(times_size);
    SortTimes mergeSortHybridTimes_10(times_size);
    SortTimes mergeSortHybridTimes_20(times_size);
    SortTimes mergeSortHybridTimes_50(times_size);

    for (int i = begin; i <= end; i += step) {
        auto index = (i - begin) / step;

        // Merge sort
        {
            auto arr = randomArray;
            auto start = Clock::now();
            mergeSort(arr, 0, i - 1);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortTimes.randomArray[index] = dur;
        }
        {
            auto arr = randomReversedSortedArray;
            auto start = Clock::now();
            mergeSort(arr, 0, i - 1);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortTimes.randomReversedSortedArray[index] = dur;
        }
        {
            auto arr = partiallySortedArray;
            auto start = Clock::now();
            mergeSort(arr, 0, i - 1);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortTimes.partiallySortedArray[index] = dur;
        }

        // MERGE sort Hybrid 5
        {
            auto arr = randomArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 5);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_5.randomArray[index] = dur;
        }
        {
            auto arr = randomReversedSortedArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 5);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_5.randomReversedSortedArray[index] = dur;
        }
        {
            auto arr = partiallySortedArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 5);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_5.partiallySortedArray[index] = dur;
        }

        // MERGE sort Hybrid 10
        {
            auto arr = randomArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 10);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_10.randomArray[index] = dur;
        }
        {
            auto arr = randomReversedSortedArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 10);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_10.randomReversedSortedArray[index] = dur;
        }
        {
            auto arr = partiallySortedArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 10);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_10.partiallySortedArray[index] = dur;
        }

        // MERGE sort Hybrid 20
        {
            auto arr = randomArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 20);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_20.randomArray[index] = dur;
        }
        {
            auto arr = randomReversedSortedArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 20);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_20.randomReversedSortedArray[index] = dur;
        }
        {
            auto arr = partiallySortedArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 20);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_20.partiallySortedArray[index] = dur;
        }

        // MERGE sort Hybrid 50
        {
            auto arr = randomArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 50);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_50.randomArray[index] = dur;
        }
        {
            auto arr = randomReversedSortedArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 50);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_50.randomReversedSortedArray[index] = dur;
        }
        {
            auto arr = partiallySortedArray;
            auto start = Clock::now();
            mergeSortHybrid(arr, 0, i - 1, 50);
            auto dur = duration_cast<microseconds>(Clock::now() - start).count();
            mergeSortHybridTimes_50.partiallySortedArray[index] = dur;
        }
    }

    ofstream outMergeSortTimes("MergeSortTimes.txt");
    outMergeSortTimes << mergeSortTimes;

    ofstream outMergeSortHybridTimes_5("MergeSortHybridTimes_5.txt");
    outMergeSortHybridTimes_5 << mergeSortHybridTimes_5;

    ofstream outMergeSortHybridTimes_10("MergeSortHybridTimes_10.txt");
    outMergeSortHybridTimes_10 << mergeSortHybridTimes_10;

    ofstream outMergeSortHybridTimes_20("MergeSortHybridTimes_20.txt");
    outMergeSortHybridTimes_20 << mergeSortHybridTimes_20;

    ofstream outMergeSortHybridTimes_50("MergeSortHybridTimes_50.txt");
    outMergeSortHybridTimes_50 << mergeSortHybridTimes_50;
}


int main() {
    ProfileSorts(500, 4000, 100, 0, 3000);
}