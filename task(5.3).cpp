#include <iostream>
#include <vector>

void insertionSortWithSteps(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        std::cout << "Шаг " << i << ": key = " << key << std::endl;
        std::cout << "До вставки: ";
        for (int k = 0; k <= i; k++) {
            std::cout << arr[k] << " ";
        }
        std::cout << std::endl;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
        
        std::cout << "После вставки: ";
        for (int k = 0; k <= i; k++) {
            std::cout << arr[k] << " ";
        }
        std::cout << std::endl << std::endl;
    }
}

int main() {
    std::vector<int> arr = {4, 3, 2, 10, 12, 1, 5, 6};
    
    std::cout << "Исходный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;
    
    insertionSortWithSteps(arr);
    
    std::cout << "Финальный отсортированный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}