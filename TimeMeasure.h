#pragma once

#include <vector>
#include <iostream>
#include "TimeCount.h"
#include "Searching.h"
#include "Sorting.h"
#include "Array.h"


using namespace std;
using namespace TimeCount;

namespace TimeMeasure {

    void run() {
        vector<size_t> sizes = { 1'000, 10'000, 100'000, 1'000'000, 10'000'000, 100'000'000 };
        vector<size_t> durationsize = { 0, 0, 0, 0, 0, 0 };

        const int repeats = 1'000;
        int j = 0;
        for (auto size : sizes) {
            int duration = 0;
            cout << "Array size: " << size << endl;

            
            int* arr = random_array_sorted<int>(size, 0, 1'000'000'000);
            mt19937 gen(random_device{}());
            uniform_int_distribution<int> dist(0, 1'000'000'000);

            for (int i = 0; i < repeats; ++i) {
                int target = dist(gen);
                duration += measure_time([&]() {
                    sequential_search1(arr, size, target);
                    });
            }
            durationsize[j] = duration / repeats;
            j += 1;
            delete[] arr;
        }
        for (size_t i = 0; i < 6; ++i) {
            cout << durationsize[i] << " " << endl;
        }

    }
}
