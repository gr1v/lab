#include <iostream>
#include <vector>

void optimizedBubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // Если не было обменов, массив уже отсортирован
        if (!swapped) {
            break;
        }
    }
}

int main() {
    std::vector<int> arr = {5, 1, 4, 2, 8};
    
    std::cout << "Исходный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    optimizedBubbleSort(arr);
    
    std::cout << "Отсортированный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}