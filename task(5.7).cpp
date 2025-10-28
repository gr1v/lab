#include <iostream>
#include <vector>

// Восстановление свойства кучи для поддерева с корнем в узле i
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;        // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1;   // Левый потомок
    int right = 2 * i + 2;  // Правый потомок

    // Если левый потомок больше корня
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Если правый потомок больше наибольшего элемента
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если наибольший элемент не корень
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        // Рекурсивно восстанавливаем кучу для затронутого поддерева
        heapify(arr, n, largest);
    }
}

// Основная функция пирамидальной сортировки
void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // Построение max-heap (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i > 0; i--) {
        // Перемещаем текущий корень в конец
        std::swap(arr[0], arr[i]);
        // Вызываем heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    std::cout << "Исходный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    heapSort(arr);

    std::cout << "Отсортированный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
