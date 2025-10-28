def shell_sort(arr):
    n = len(arr)
    # Начинаем с большого шага, затем уменьшаем
    gap = n // 2
    
    while gap > 0:
        # Выполняем сортировку вставками для этого шага
        for i in range(gap, n):
            temp = arr[i]
            j = i
            # Сдвигаем элементы, пока не найдем правильную позицию
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = temp
        # Уменьшаем шаг
        gap //= 2
    
    return arr

# Пример использования
arr = [64, 34, 25, 12, 22, 11, 90, 5]
print("Исходный массив:", arr)
sorted_arr = shell_sort(arr.copy())
print("Отсортированный массив:", sorted_arr)
