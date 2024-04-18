def merge(arr, left, mid, right, temp):
    i = left
    j = mid + 1
    k = left

    while i <= mid and j <= right:
        if arr[i] <= arr[j]:
            temp[k] = arr[i]
            i += 1
        else:
            temp[k] = arr[j]
            j += 1
        k += 1

    while i <= mid:
        temp[k] = arr[i]
        i += 1
        k += 1

    while j <= right:
        temp[k] = arr[j]
        j += 1
        k += 1

    for i in range(left, right + 1):
        arr[i] = temp[i]


def insertion_sort(arr, left, right):
    for i in range(left + 1, right + 1):
        key = arr[i]
        j = i - 1

        while j >= left and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1

        arr[j + 1] = key


def tim_sort(arr):
    min_run = 32
    n = len(arr)
    temp = [0] * n

    for i in range(0, n, min_run):
        insertion_sort(arr, i, min(i + min_run - 1, n - 1))

    size = min_run
    while size < n:
        for left in range(0, n, 2 * size):
            mid = left + size - 1
            right = min(left + 2 * size - 1, n - 1)
            merge(arr, left, mid, right, temp)
        size *= 2


def print_array(arr):
    for num in arr:
        print(num, end=" ")
    print()


def main():
    try:
        # Open the input file
        with open("input.txt", "r") as file:
            # Read the size of the array from the file
            n = int(file.readline())

            # Read the elements of the array from the file
            arr = list(map(int, file.readline().split()))

        print("Original array:", end=" ")
        print_array(arr)

        # Sort the array using Timsort
        tim_sort(arr)

        print("Sorted array:", end=" ")
        print_array(arr)

    except FileNotFoundError:
        print("Error: input file not found")


if __name__ == "__main__":
    main()
