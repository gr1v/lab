def quicksort(arr):
    if len(arr) <= 1:
        return arr  # Базовый случай рекурсии: пустой список или одиночный элемент уже отсортированы
    else:
        pivot = arr[len(arr)//2]  # Выбор опорного элемента (среднего элемента массива)
        left = [x for x in arr if x < pivot]  # Все элементы, меньшие опорного
        middle = [x for x in arr if x == pivot]  # Все элементы, равные опорному
        right = [x for x in arr if x > pivot]  # Все элементы, большие опорного
        return quicksort(left) + middle + quicksort(right)  # Рекурсивная сортировка левой и правой частей

# Пример использования:
if __name__ == "__main__":
    unsorted_array = [3, 6, 8, 10, 1, 2, 1]
    sorted_array = quicksort(unsorted_array)
    print("Отсортированный массив:", sorted_array)