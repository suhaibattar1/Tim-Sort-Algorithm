#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define MIN_MERGE 32

// Function to merge two sorted subarrays
void merge(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& temp) {
    int i = left;       // Starting index of left subarray
    int j = mid + 1;    // Starting index of right subarray
    int k = left;       // Starting index of merged array

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy the remaining elements of left subarray
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy the remaining elements of right subarray
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy the merged elements back to the original array
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

// Function to perform insertion sort on a subarray
void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Function to perform merge sort on the given array
void timSort(std::vector<int>& arr) {
    int minRun = MIN_MERGE;
    std::vector<int> temp(arr.size());

    for (size_t i = 0; i < arr.size(); i += minRun) {
        insertionSort(arr, i, std::min(static_cast<size_t>(i + minRun - 1), arr.size() - 1));
    }

    for (size_t size = minRun; size < arr.size(); size *= 2) {
        for (size_t left = 0; left < arr.size(); left += 2 * size) {
            size_t mid = left + size - 1;
            size_t right = std::min(left + 2 * size - 1, arr.size() - 1);

            merge(arr, left, mid, right, temp);
        }
    }
}

// Function to print the array
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    // Read the size of the array from the file
    int n;
    file >> n;

    // Read the elements of the array from the file
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        file >> arr[i];
    }

    file.close();

    std::cout << "Original array: ";
    printArray(arr);

    // Sort the array using Timsort
    timSort(arr);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}
