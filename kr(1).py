def bucket_sort(arr):
    """
    Блочная сортировка - распределяет элементы по корзинам и сортирует каждую корзину отдельно
    """
    if len(arr) == 0:
        return arr
    
    # Определяем количество корзин
    num_buckets = len(arr)
    
    # Создаем корзины
    buckets = [[] for _ in range(num_buckets)]
    
    # Распределяем элементы по корзинам
    max_val = max(arr)
    for num in arr:
        index = int(num * num_buckets / (max_val + 1))  # Функция распределения
        buckets[index].append(num)
    
    # Сортируем каждую корзину (используем встроенную сортировку)
    for bucket in buckets:
        bucket.sort()
    
    # Объединяем корзины
    result = []
    for bucket in buckets:
        result.extend(bucket)
    
    return result

# Тестирование
if __name__ == "__main__":
    test_array = [0.42, 0.32, 0.33, 0.52, 0.37, 0.47, 0.51]
    print("Исходный массив:", test_array)
    sorted_array = bucket_sort(test_array)
    print("Отсортированный массив:", sorted_array)
  
  // Исходный массив: [0.42, 0.32, 0.33, 0.52, 0.37, 0.47, 0.51]
  // Отсортированный массив: [0.32, 0.33, 0.37, 0.42, 0.47, 0.51, 0.52]


def pancake_sort(arr):
    """
    Блинная сортировка - использует операцию переворота префикса массива
    """
    def flip(subarray, k):
        """Переворачивает первые k элементов подмассива"""
        i = 0
        while i < k // 2:
            subarray[i], subarray[k - i - 1] = subarray[k - i - 1], subarray[i]
            i += 1
    
    n = len(arr)
    
    # Постепенно уменьшаем размер неотсортированной части
    for curr_size in range(n, 1, -1):
        # Находим индекс максимального элемента в неотсортированной части
        max_index = arr.index(max(arr[:curr_size]))
        
        # Если максимальный элемент не на своем месте
        if max_index != curr_size - 1:
            # Переворачиваем до максимального элемента, чтобы он стал первым
            if max_index != 0:
                flip(arr, max_index + 1)
            
            # Переворачиваем всю неотсортированную часть
            flip(arr, curr_size)
    
    return arr

# Тестирование
if __name__ == "__main__":
    test_array = [3, 1, 4, 1, 5, 9, 2, 6]
    print("Исходный массив:", test_array)
    sorted_array = pancake_sort(test_array.copy())
    print("Отсортированный массив:", sorted_array)

//Исходный массив: [3, 1, 4, 1, 5, 9, 2, 6]
//Отсортированный массив: [1, 1, 2, 3, 4, 5, 6, 9]

def bead_sort(arr):
    """
    Сортировка бусинами - моделирует падение бусин под действием гравитации
    Работает только для неотрицательных целых чисел
    """
    if not arr:
        return arr
    
    # Находим максимальное значение для определения количества рядов
    max_val = max(arr)
    
    # Создаем "абак" - матрицу бусин
    beads = [[0] * len(arr) for _ in range(max_val)]
    
    # Расставляем бусины (1 - есть бусина, 0 - нет)
    for i, num in enumerate(arr):
        for j in range(num):
            beads[j][i] = 1
    
    # Моделируем падение бусин (гравитацию)
    for i in range(max_val):
        # Считаем количество бусин в каждом ряду
        bead_count = sum(beads[i])
        
        # "Сбрасываем" все бусины
        for j in range(len(arr)):
            beads[i][j] = 0
        
        # Бусины оседают вниз (справа)
        for j in range(len(arr) - bead_count, len(arr)):
            beads[i][j] = 1
    
    # Считываем результат снизу вверх
    result = [0] * len(arr)
    for i in range(len(arr)):
        for j in range(max_val):
            result[i] += beads[j][i]
    
    return result

# Тестирование
if __name__ == "__main__":
    test_array = [3, 1, 4, 1, 2]
    print("Исходный массив:", test_array)
    sorted_array = bead_sort(test_array)
    print("Отсортированный массив:", sorted_array)

//Исходный массив: [3, 1, 4, 1, 2]
//Отсортированный массив: [1, 1, 2, 3, 4]

import math

def jump_search(arr, target):
    """
    Поиск скачками - прыгает через блоки, затем выполняет линейный поиск в блоке
    """
    n = len(arr)
    
    # Определяем размер прыжка
    step = int(math.sqrt(n))
    
    # Поиск блока, где может находиться элемент
    prev = 0
    while arr[min(step, n) - 1] < target:
        prev = step
        step += int(math.sqrt(n))
        if prev >= n:
            return -1
    
    # Линейный поиск в найденном блоке
    for i in range(prev, min(step, n)):
        if arr[i] == target:
            return i
    
    return -1

# Тестирование
if __name__ == "__main__":
    sorted_array = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144]
    target = 34
    print(f"Массив: {sorted_array}")
    print(f"Поиск элемента {target}")
    result = jump_search(sorted_array, target)
    if result != -1:
        print(f"Элемент найден на позиции {result}")
    else:
        print("Элемент не найден")

//Массив: [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144]
//Поиск элемента 34
//Элемент найден на позиции 9

def binary_search(arr, left, right, target):
    """
    Вспомогательная функция бинарного поиска
    """
    while left <= right:
        mid = left + (right - left) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1

def exponential_search(arr, target):
    """
    Экспоненциальный поиск - экспоненциально увеличивает диапазон, затем бинарный поиск
    """
    n = len(arr)
    
    # Если элемент в начале массива
    if arr[0] == target:
        return 0
    
    # Экспоненциально увеличиваем диапазон
    i = 1
    while i < n and arr[i] <= target:
        i *= 2
    
    # Выполняем бинарный поиск в найденном диапазоне
    return binary_search(arr, i // 2, min(i, n - 1), target)

# Тестирование
if __name__ == "__main__":
    sorted_array = [2, 3, 4, 10, 15, 18, 20, 22, 24, 25, 30, 40, 50]
    target = 18
    print(f"Массив: {sorted_array}")
    print(f"Поиск элемента {target}")
    result = exponential_search(sorted_array, target)
    if result != -1:
        print(f"Элемент найден на позиции {result}")
    else:
        print("Элемент не найден")

//Массив: [2, 3, 4, 10, 15, 18, 20, 22, 24, 25, 30, 40, 50]
//Поиск элемента 18
//Элемент найден на позиции 5

def ternary_search(arr, target):
    """
    Тернарный поиск - делит массив на три части
    """
    def recursive_search(left, right):
        if left > right:
            return -1
        
        # Делим диапазон на три части
        mid1 = left + (right - left) // 3
        mid2 = right - (right - left) // 3
        
        # Проверяем граничные точки
        if arr[mid1] == target:
            return mid1
        if arr[mid2] == target:
            return mid2
        
        # Определяем, в какой трети продолжать поиск
        if target < arr[mid1]:
            return recursive_search(left, mid1 - 1)
        elif target > arr[mid2]:
            return recursive_search(mid2 + 1, right)
        else:
            return recursive_search(mid1 + 1, mid2 - 1)
    
    return recursive_search(0, len(arr) - 1)

# Тестирование
if __name__ == "__main__":
    sorted_array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
    target = 7
    print(f"Массив: {sorted_array}")
    print(f"Поиск элемента {target}")
    result = ternary_search(sorted_array, target)
    if result != -1:
        print(f"Элемент найден на позиции {result}")
    else:
        print("Элемент не найден")

//Массив: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
//Поиск элемента 7
//Элемент найден на позиции 6
