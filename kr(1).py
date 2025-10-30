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
