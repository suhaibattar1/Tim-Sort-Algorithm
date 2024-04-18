#include <stdio.h>
#include <stdlib.h>

#define MIN_MERGE 32

// Function to merge two sorted subarrays
void merge(int arr[], int left, int mid, int right, int temp[]) {
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
void insertionSort(int arr[], int left, int right) {
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
void timSort(int arr[], int n) {
    int minRun = MIN_MERGE;
    int *temp = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i += minRun) {
        insertionSort(arr, i, (i + minRun - 1 < n - 1) ? i + minRun - 1 : n - 1);
    }

    for (int size = minRun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? left + 2 * size - 1 : n - 1;

            merge(arr, left, mid, right, temp);
        }
    }

    free(temp);
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Open the input file
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the size of the array from the file
    int n;
    fscanf(file, "%d", &n);

    // Allocate memory for the array
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Read the elements of the array from the file
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    // Close the file
    fclose(file);

    printf("Original array: ");
    printArray(arr, n);

    // Sort the array using Timsort
    timSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    // Free the allocated memory
    free(arr);

    return 0;
}
