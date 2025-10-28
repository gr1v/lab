#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int left, int mid, int right, int depth) {
    std::string indent(depth * 2, ' ');
    std::cout << indent << "Слияние [" << left << "-" << mid << "] и [" << (mid+1) << "-" << right << "]" << std::endl;
    
    // Размеры левого и правого подмассивов
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Создаем временные массивы
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);
    
    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    // Сливаем временные массивы обратно в основной
    int i = 0, j = 0, k = left;
    
    // Сравниваем и сливаем элементы
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    // Копируем оставшиеся элементы
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
    
    // Показываем результат слияния
    std::cout << indent << "Результат: ";
    for (int idx = left; idx <= right; idx++) {
        std::cout << arr[idx] << " ";
    }
    std::cout << std::endl;
}

void mergeSort(std::vector<int>& arr, int left, int right, int depth = 0) {
    std::string indent(depth * 2, ' ');
    std::cout << indent << "Сортировка [" << left << "-" << right << "]" << std::endl;
    
    // Базовый случай: массив из 0 или 1 элемента уже отсортирован
    if (left >= right) {
        return;
    }
    
    // Находим середину для разделения
    int mid = left + (right - left) / 2;
    
    // Рекурсивно сортируем левую и правую половины
    mergeSort(arr, left, mid, depth + 1);
    mergeSort(arr, mid + 1, right, depth + 1);
    
    // Сливаем отсортированные половины
    merge(arr, left, mid, right, depth);
}

int main() {
    std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    
    std::cout << "Исходный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;
    
    // Запускаем сортировку
    mergeSort(arr, 0, arr.size() - 1);
    
    std::cout << std::endl << "Финальный отсортированный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}