#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <functional>

class MergeSort {
public:
    void Sort(std::vector<int>& arr) {
        if (arr.size() <= 1) return;
        std::vector<int> left(arr.begin(), arr.begin() + arr.size() / 2);
        std::vector<int> right(arr.begin() + arr.size() / 2, arr.end());
        Sort(left);
        Sort(right);
        Merge(arr, left, right);
    }

private:
    void Merge(std::vector<int>& result, std::vector<int>& left, std::vector<int>& right) {
        auto it = result.begin();
        auto it_left = left.begin();
        auto it_right = right.begin();
        while (it_left != left.end() && it_right != right.end()) {
            if (*it_left <= *it_right) {
                *it++ = *it_left++;
            }
            else {
                *it++ = *it_right++;
            }
        }
        while (it_left != left.end()) {
            *it++ = *it_left++;
        }
        while (it_right != right.end()) {
            *it++ = *it_right++;
        }
    }
};

int main() {
    // Установка кодировки консоли на UTF-8
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> arr;
    std::cout << u8"Введите 10 чисел: ";
    for (int i = 0; i < 10; ++i) {
        int num;
        std::cin >> num;
        arr.push_back(num);
    }

    MergeSort sorter;

    std::thread mergeSortThread([&sorter, &arr]() {
        sorter.Sort(arr);
        });

    mergeSortThread.join();

    std::cout << u8"Отсортированный массив: ";
    for (const int& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
