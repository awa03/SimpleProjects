#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

class unsorted_vector {
private:
    std::vector<int> data;

public:
    // Constructor
    unsorted_vector(std::vector<int> data) : data(data) {}

    // Copy constructor
    unsorted_vector(const unsorted_vector& copy) : data(copy.data) {}

    // Copy assignment operator
    unsorted_vector& operator=(const unsorted_vector& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    void add(int val) {
        data.push_back(val);
    }

    std::vector<int> stalin_sort() {
        int j = 0;
        for (int i = 1; i < data.size();) {
            if (data[j] > data[i]) {
                data.erase(data.begin() + i);
            } else {
                i++;
                j++;
            }
        }
        return data;
    }

    std::vector<int> bubbleSort() {
        bool isUnsorted;
        do {
            isUnsorted = false;
            for (int i = 0; i < (data.size() - 1); i++) {
                if (data[i] > data[i + 1]) {
                    isUnsorted = true;
                    std::swap(data[i], data[i + 1]);
                }
            }
        } while (isUnsorted);
        return data;
    }

    void radix() {
        // Find the maximum element in the vector
        int maxElement = *std::max_element(data.begin(), data.end());

        // Perform counting sort for every digit
        for (int exp = 1; maxElement / exp > 0; exp *= 10) {
            countingSort(exp);
        }
    }

    void countingSort(int exp) {
        int n = data.size();
        std::vector<int> output(n);
        std::vector<int> count(10, 0);

        // Count the occurrences of each digit
        for (int i = 0; i < n; i++) {
            count[(data[i] / exp) % 10]++;
        }

        // Calculate the cumulative count
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build the output array
        for (int i = n - 1; i >= 0; i--) {
            output[count[(data[i] / exp) % 10] - 1] = data[i];
            count[(data[i] / exp) % 10]--;
        }

        // Copy the sorted elements back to the original vector
        for (int i = 0; i < n; i++) {
            data[i] = output[i];
        }
    }

    void quickSort() {
        this->quickSortHelper(0, data.size() - 1);
    }

    void quickSortHelper(int low, int high) {
        if (low < high) {
            int pivotIndex = partition(low, high);
            quickSortHelper(low, pivotIndex - 1);
            quickSortHelper(pivotIndex + 1, high);
        }
    }

    int partition(int low, int high) {
        int pivot = data[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (data[j] < pivot) {
                i++;
                std::swap(data[i], data[j]);
            }
        }

        std::swap(data[i + 1], data[high]);
        return i + 1;
    }

    void GnomeSort() {
        int index = 0;
        while (index < data.size()) {
            if (index == 0) {
                index++;
            }
            if (data[index] >= data[index - 1]) {
                index++;
            } else {
                std::swap(data[index], data[index - 1]);
                index--;
            }
        }
    }

    // selection sort
    void selectionSort() {
        int minIndex;
        for (int i = 0; i < data.size() - 1; i++) {
            minIndex = i;
            for (int j = i + 1; j < data.size(); j++) {
                if (data[j] < data[minIndex]) {
                    minIndex = j;
                }
            }
            std::swap(data[minIndex], data[i]);
        }
    }

    // insertion sort
    void insertionSort() {
        int j;
        for (int i = 1; i < data.size(); i++) {
            j = i;
            while (j > 0 && data[j] < data[j - 1]) {
                std::swap(data[j], data[j - 1]);
                j--;
            }
        }
    }

    // merge sort
    void mergeSort() {
        this->mergeSortHelper(0, data.size() - 1);
    }

    // merge helper
    void mergeSortHelper(int low, int high) {
        if (low < high) {
            int mid = (low + high) / 2;
            mergeSortHelper(low, mid);
            mergeSortHelper(mid + 1, high);
            merge(low, mid, high);
        }
    }

    // merge
    void merge(int low, int mid, int high) {
        int n1 = mid - low + 1;
        int n2 = high - mid;

        std::vector<int> left(n1);
        std::vector<int> right(n2);

        for (int i = 0; i < n1; i++) {
            left[i] = data[low + i];
        }
        for (int j = 0; j < n2; j++) {
            right[j] = data[mid + 1 + j];
        }

        int i = 0;
        int j = 0;
        int k = low;

        while (i < n1 && j < n2) {
            if (left[i] <= right[j]) {
                data[k] = left[i];
                i++;
            } else {
                data[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            data[k] = left[i];
            i++;
            k++;
        }

        while (j < n2) {
            data[k] = right[j];
            j++;
            k++;
        }
    }

    // heap sort
    void heapSort() {
        int n = data.size();

        // Build heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(n, i);
        }

        // Extract elements from heap
        for (int i = n - 1; i >= 0; i--) {
            std::swap(data[0], data[i]);
            heapify(i, 0);
        }
    }

    // heapify
    void heapify(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // If left child is larger than root
        if (left < n && data[left] > data[largest]) {
            largest = left;
        }

        // If right child is larger than largest so far
        if (right < n && data[right] > data[largest]) {
            largest = right;
        }

        // If largest is not root
        if (largest != i) {
            std::swap(data[i], data[largest]);
            heapify(n, largest);
        }
    }

    // shell sort
    void shellSort() {
        int n = data.size();

        // Start with a big gap, then reduce the gap
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // Do a gapped insertion sort for this gap size.
            // The first gap elements a[0..gap-1] are already in gapped order
            // keep adding one more element until the entire array is gap sorted
            for (int i = gap; i < n; i += 1) {
                // add a[i] to the elements that have been gap sorted
                // save a[i] in temp and make a hole at position i
                int temp = data[i];

                // shift earlier gap-sorted elements up until the correct location for a[i] is found
                int j;
                for (j = i; j >= gap && data[j - gap] > temp; j -= gap) {
                    data[j] = data[j - gap];
                }

                // put temp (the original a[i]) in its correct location
                data[j] = temp;
            }
        }
    }

    // comb sort
    void combSort() {
        int n = data.size();

        // Initialize gap
        int gap = n;

        // Initialize swapped as true to make sure that loop runs
        bool swapped = true;

        // Keep running while gap is more than 1 and last iteration caused a swap
        while (gap != 1 || swapped == true) {
            // Find next gap
            gap = getNextGap(gap);

            // Initialize swapped as false so that we can check if swap happened or not
            swapped = false;

            // Compare all elements with current gap
            for (int i = 0; i < n - gap; i++) {
                if (data[i] > data[i + gap]) {
                    std::swap(data[i], data[i + gap]);
                    swapped = true;
                }
            }
        }
    }

    // getNextGap
    int getNextGap(int gap) {
        // Shrink gap by Shrink factor
        gap = (gap * 10) / 13;

        if (gap < 1) {
            return 1;
        }
        return gap;
    }

    void isSorted() {
        // Check if data is sorted
        for (int i = 0; i < data.size() - 1; i++) {
            if (data[i] > data[i + 1]) {
                std::cout << "Not sorted" << std::endl;
                return;
            }
        }
        std::cout << "Sorted" << std::endl;
    }

    std::vector<int> getData() {
        return data;
    }

    void print() {
        for (int i = 0; i < data.size(); i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

void menu(){
    std::cout << std::setw(2) << "Which sorting algorithm would you like to use?" << std::endl;
    std::cout << std::setw(2) << "1. Stalin Sort" << std::endl;
    std::cout << std::setw(2) << "2. Bubble Sort" << std::endl;
    std::cout << std::setw(2) << "3. Radix Sort" << std::endl;
    std::cout << std::setw(2) << "4. Quick Sort" << std::endl;
    std::cout << std::setw(2) << "5. Gnome Sort" << std::endl;
    std::cout << std::setw(2) << "6. Selection Sort" << std::endl;
    std::cout << std::setw(2) << "7. Insertion Sort" << std::endl;
    std::cout << std::setw(2) << "8. Merge Sort" << std::endl;
    std::cout << std::setw(2) << "9. Heap Sort" << std::endl;
    std::cout << std::setw(2) << "10. Shell Sort" << std::endl;
    std::cout << std::setw(2) << "11. Comb Sort" << std::endl;
    std::cout << std::setw(2) << "12. Quit" << std::endl;
    
}

int main(int argc, char* argv[]) {
    std::vector<int> data;

    std::ifstream file;
    file.open(argv[1]);
    if (!file) {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    int num;
    while (file >> num) {
        data.push_back(num);
    }

    unsorted_vector vector(data);
    // give the user option of which sorting algorithm to use

    menu();

    int sortType;
    while (sortType != 13) {
        std::cin >> sortType;
        switch (sortType) {
            case 1: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.stalin_sort();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Stalin Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 2: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.bubbleSort();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Bubble Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 3: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.radix();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Radix Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 4: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.quickSort();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Quick Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 5: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.GnomeSort();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Gnome Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 6: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.selectionSort();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Selection Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 7: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.insertionSort();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Insertion Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 8: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.mergeSort();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Merge Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 9: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.heapSort();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << std::endl;
                std::cout << "Heap Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 10: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.shellSort();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << std::endl;
                std::cout << "Shell Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 11: {
                auto start = std::chrono::high_resolution_clock::now();
                vector.combSort();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << std::endl;
                std::cout << "Comb Sort: " << elapsed.count() << " seconds" << std::endl;
                break;
            }
            case 12: {
                std::cout << "Quitting" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid input" << std::endl;
                break;
            }
    }
    


    

   

    // time complexity
    // stalin sort: O(n)
    // bubble sort: O(n^2)
    // radix sort: O(nk)
    // quick sort: O(nlogn)
    // gnome sort: O(n^2)
    // selection sort: O(n^2)
    // insertion sort: O(n^2)
    // merge sort: O(nlogn)
    // heap sort: O(nlogn)
    // shell sort: O(nlogn)


    }

    return 0;
}
