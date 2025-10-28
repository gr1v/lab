#include <iostream>
#include <vector>

int interpolationSearch(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // Вычисляем позицию с помощью интерполяционной формулы
        int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);

        std::cout << "Проверяем позицию " << pos << " (значение: " << arr[pos] << ")" << std::endl;

        if (arr[pos] == target) {
            return pos;  // Элемент найден
        }

        if (arr[pos] < target) {
            low = pos + 1;  // Ищем в правой части
        } else {
            high = pos - 1; // Ищем в левой части
        }
    }

    return -1;  // Элемент не найден
}

int main() {
    std::vector<int> arr = {10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
    int target = 18;

    std::cout << "Массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Ищем элемент: " << target << std::endl << std::endl;

    int result = interpolationSearch(arr, target);

    if (result != -1) {
        std::cout << std::endl << "Элемент найден на позиции: " << result << std::endl;
    } else {
        std::cout << std::endl << "Элемент не найден" << std::endl;
    }

    return 0;
}