#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class StringGenerator {
private:
    string alphabet;
    mt19937 rng;
public:
    StringGenerator() : alphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-"),
                        rng(random_device{}()) {}

    string generateRandomString(int length) {
        uniform_int_distribution<int> dist(0, static_cast<int>(alphabet.size()) - 1);
        string result;
        result.reserve(length);
        for (int i = 0; i < length; ++i) {
            result += alphabet[dist(rng)];
        }
        return result;
    }

    vector<string> generateRandomStrings(int numStrings, int minLength, int maxLength) {
        uniform_int_distribution<int> lengthDist(minLength, maxLength);
        vector<string> strings;
        strings.reserve(numStrings);
        for (int i = 0; i < numStrings; ++i) {
            int length = lengthDist(rng);
            strings.push_back(generateRandomString(length));
        }
        return strings;
    }

    vector<string> generateReverseSortedStrings(int numStrings, int minLength, int maxLength) {
        auto strings = generateRandomStrings(numStrings, minLength, maxLength);
        sort(strings.rbegin(), strings.rend());
        return strings;
    }

    vector<string> generateAlmostSortedStrings(int numStrings, int minLength, int maxLength) {
        auto strings = generateRandomStrings(numStrings, minLength, maxLength);
        sort(strings.begin(), strings.end());
        // Меняем местами небольшое количество пар строк
        uniform_int_distribution<int> indexDist(0, numStrings - 2);
        for (int i = 0; i < numStrings / 10; ++i) {
            int idx1 = indexDist(rng);
            int idx2 = indexDist(rng);
            swap(strings[idx1], strings[idx2]);
        }
        return strings;
    }
};

class String {
public:
    string value;
    mutable long long comparisons = 0;

    explicit String() = default;

    explicit String(string str) : value(std::move(str)) {}

    int length() const {
        return static_cast<int>(value.length());
    }

    int size() const {
        return static_cast<int>(value.size());
    }

    String substr(int pos, int len) const {
        return String(value.substr(pos, len));
    }

    char &operator[](int index) {
        return value[index];
    }

    const char &operator[](int index) const {
        return value[index];
    }


    bool operator<(const String &other) const {
        int len1 = static_cast<int>(value.length());
        int len2 = static_cast<int>(other.value.length());
        int minLen = min(len1, len2);
        for (int i = 0; i < minLen; ++i) {
            ++comparisons;
            if (value[i] != other.value[i]) {
                return value[i] < other.value[i];
            }
        }
        comparisons += abs(len1 - len2); // Additional comparisons for strings of different lengths
        return len1 < len2;
    }

    bool operator<=(const String &other) const {
        int len1 = static_cast<int>(value.length());
        int len2 = static_cast<int>(other.value.length());
        int minLen = min(len1, len2);
        for (int i = 0; i < minLen; ++i) {
            ++comparisons;
            if (value[i] != other.value[i]) {
                return value[i] <= other.value[i];
            }
        }
        comparisons += abs(len1 - len2); // Additional comparisons for strings of different lengths
        return len1 <= len2;
    }


};

class SortingBenchmark {
public:
    // STD Sorts

    using Stats = pair<long long, long long>;

    static Stats stdQuicksort(vector<String> &strings) {
        auto start = chrono::high_resolution_clock::now();
        sort(strings.begin(), strings.end());
        auto end = chrono::high_resolution_clock::now();
        long long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long comparisons = 0;
        for (const auto &str: strings) {
            comparisons += str.comparisons;
        }
        return {duration, comparisons};
    }

    static Stats stdMergesort(vector<String> &strings) {
        auto start = chrono::high_resolution_clock::now();
        stable_sort(strings.begin(), strings.end());
        auto end = chrono::high_resolution_clock::now();
        long long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long comparisons = 0;
        for (const auto &str: strings) {
            comparisons += str.comparisons;
        }
        return {duration, comparisons};
    }

    // String sorts

    static Stats stringQuicksort(vector<String> &strings, int prefixLength = 0) {
        auto start = chrono::high_resolution_clock::now();
        stringQuicksortRecursive(strings, 0, strings.size() - 1, prefixLength);
        auto end = chrono::high_resolution_clock::now();
        long long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long comparisons = 0;
        for (const auto &str: strings) {
            comparisons += str.comparisons;
        }
        return {duration, comparisons};
    }

    static Stats stringMergesort(vector<String> &strings) {
        auto start = chrono::high_resolution_clock::now();
        stringMergesortRecursive(strings, 0, strings.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        long long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long comparisons = 0;
        for (const auto &str: strings) {
            comparisons += str.comparisons;
        }
        return {duration, comparisons};
    }

    static Stats msdRadixSort(vector<String> &strings, int prefixLength = 0) {
        auto start = chrono::high_resolution_clock::now();
        msdRadixSortRecursive(strings, 0, strings.size() - 1, prefixLength);
        auto end = chrono::high_resolution_clock::now();
        long long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long comparisons = 0;
        for (const auto &str: strings) {
            comparisons += str.comparisons;
        }
        return {duration, comparisons};
    }

    static Stats msdRadixSortSwitch(vector<String> &strings, int prefixLength = 0) {
        auto start = chrono::high_resolution_clock::now();
        msdRadixSortRecursiveSwitch(strings, 0, strings.size() - 1, prefixLength);
        auto end = chrono::high_resolution_clock::now();
        long long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long comparisons = 0;
        for (const auto &str: strings) {
            comparisons += str.comparisons;
        }
        return {duration, comparisons};
    }

private:
    static void stringQuicksortRecursive(vector<String> &strings, int left, int right, int prefixLength) {
        if (left >= right) return;

        int pivotIndex = partition(strings, left, right, prefixLength);
        stringQuicksortRecursive(strings, left, pivotIndex - 1, prefixLength);
        stringQuicksortRecursive(strings, pivotIndex + 1, right, prefixLength);
    }

    static int partition(vector<String> &strings, int left, int right, int prefixLength) {
        auto pivot = strings[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (strings[j].substr(0, prefixLength) <= pivot.substr(0, prefixLength)) {
                ++i;
                swap(strings[i], strings[j]);
            }
        }
        swap(strings[i + 1], strings[right]);
        return i + 1;
    }

    static void stringMergesortRecursive(vector<String> &strings, int left, int right) {
        if (left >= right) return;

        int mid = (left + right) / 2;
        stringMergesortRecursive(strings, left, mid);
        stringMergesortRecursive(strings, mid + 1, right);
        merge(strings, left, mid, right);
    }

    static void merge(vector<String> &strings, int left, int mid, int right) {
        vector<String> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right) {
            if (strings[i] <= strings[j]) {
                temp[k++] = strings[i++];
            } else {
                temp[k++] = strings[j++];
            }
        }
        while (i <= mid) temp[k++] = strings[i++];
        while (j <= right) temp[k++] = strings[j++];
        for (int p = 0; p < temp.size(); ++p) {
            strings[left + p] = temp[p];
        }
    }

    static void msdRadixSortRecursive(vector<String> &strings, int left, int right, int prefixLength) {
        if (left >= right) return;

        vector<vector<String>> buckets(256);
        for (int i = left; i <= right; ++i) {
            if (prefixLength < strings[i].size()) {
                int index = static_cast<unsigned char>(strings[i][prefixLength]);
                buckets[index].push_back(strings[i]);
            } else {
                buckets[0].push_back(strings[i]);
            }
        }

        int current = left;
        for (int i = 0; i < 256; ++i) {
            msdRadixSortRecursive(buckets[i], 0, buckets[i].size() - 1, prefixLength + 1);
            for (const auto &str: buckets[i]) {
                strings[current++] = str;
            }
        }
    }

    static void msdRadixSortRecursiveSwitch(vector<String> &strings, int left, int right, int prefixLength) {
        if (left >= right) return;

        if (right - left + 1 <= 10) {
            stringQuicksortRecursive(strings, left, right, prefixLength);
            return;
        }

        vector<vector<String>> buckets(256);
        for (int i = left; i <= right; ++i) {
            if (prefixLength < strings[i].size()) {
                int index = static_cast<unsigned char>(strings[i][prefixLength]);
                buckets[index].push_back(strings[i]);
            } else {
                buckets[0].push_back(strings[i]);
            }
        }

        int current = left;
        for (int i = 0; i < 256; ++i) {
            msdRadixSortRecursiveSwitch(buckets[i], 0, buckets[i].size() - 1, prefixLength + 1);
            for (const auto &str: buckets[i]) {
                strings[current++] = str;
            }
        }
    }

};

template<typename T0, typename... Ts>
void CSVImpl(std::ostream &out, const T0 &v0, const Ts &... vs) {
    using namespace literals;
    out << v0;
    if constexpr (sizeof...(vs) != 0) {
        out << ";"sv;
        CSVImpl(out, vs...);
    }
}

template<typename... Tn>
string CSV(const Tn &... vn) {
    ostringstream os;
    if constexpr (sizeof...(vn) != 0) {
        CSVImpl(os, vn...);
    }
    return os.str();
}

class Research {
public:
    explicit Research(int numStrings = 3000, int minLength = 10, int maxLength = 200, StringGenerator generator = {})
            : generator(std::move(generator)) {
        generate(numStrings, minLength, maxLength);
    }

    void operator()(ostream &out = cout) const {
        /*
         * arrayType;sortMethod;arraySize;duration;comparisons;
         *
         * arrayTypes: unsorted / reversed_sorted / almost_sorted
         * sortMethods: std_quicksort / std_mergesort / string_quicksort / string_mergesort /  msd_radix_sort / msd_radix_sort_switch
         * arraySize: 100 200 ... 3000
         * duration - microseconds
         * comparisons - count
         */
        auto header = CSV("arrayType", "sortMethod", "arraySize", "duration", "comparisons");
        vector<string> dataset = {header};
        benchmark("unsorted", unsortedStrings, dataset);
        benchmark("reversed_sorted", reverseSortedStrings, dataset);
        benchmark("almost_sorted", almostSortedStrings, dataset);
        for (const auto &it: dataset) {
            out << it << endl;
        }
    }

private:
    StringGenerator generator;
    vector<String> unsortedStrings;
    vector<String> reverseSortedStrings;
    vector<String> almostSortedStrings;

    void generate(int numStrings, int minLength, int maxLength) {
        // Генерация тестовых данных
        for (const auto &str: generator.generateRandomStrings(numStrings, minLength, maxLength)) {
            unsortedStrings.emplace_back(str);
        }
        for (const auto &str: generator.generateReverseSortedStrings(numStrings, minLength, maxLength)) {
            reverseSortedStrings.emplace_back(str);
        }
        for (const auto &str: generator.generateAlmostSortedStrings(numStrings, minLength, maxLength)) {
            almostSortedStrings.emplace_back(str);
        }
    }

    static void benchmark(const string &name, const vector<String> &array, vector<string> &result) {
        SortingBenchmark::Stats stats;
        for (int array_size = 100; array_size <= array.size(); array_size += 100) {
            vector<String> part(array.begin(), array.begin() + array_size);

            // std_quicksort
            stats = SortingBenchmark::stdQuicksort(part);
            result.push_back(CSV(name, "std_quicksort", array_size, stats.first, stats.second));

            // std_mergesort
            stats = SortingBenchmark::stdMergesort(part);
            result.push_back(CSV(name, "std_mergesort", array_size, stats.first, stats.second));

            // string_quicksort
            stats = SortingBenchmark::stringQuicksort(part);
            result.push_back(CSV(name, "string_quicksort", array_size, stats.first, stats.second));

            // string_mergesort
            stats = SortingBenchmark::stringMergesort(part);
            result.push_back(CSV(name, "string_mergesort", array_size, stats.first, stats.second));

            // msd_radix_sort
            stats = SortingBenchmark::msdRadixSort(part);
            result.push_back(CSV(name, "msd_radix_sort", array_size, stats.first, stats.second));

            // msd_radix_sort_switch
            stats = SortingBenchmark::msdRadixSortSwitch(part);
            result.push_back(CSV(name, "msd_radix_sort_switch", array_size, stats.first, stats.second));
        }
    }

};

int main() {
    ofstream out("dataset.csv");
    Research research;
    research(out);
    return 0;
}
