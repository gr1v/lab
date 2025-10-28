def sequential_search(arr, target):
    """
    Реализует последовательный поиск в списке.
    
    :param arr: Список элементов для поиска
    :param target: Искомое значение
    :return: Индекс искомого элемента, либо None, если элемент не найден
    """
    # Проходим по каждому элементу списка
    for index, value in enumerate(arr):
        # Если находим совпадение с целевым значением
        if value == target:
            # Возвращаем индекс найденного элемента
            return index
    # Если целевой элемент не найден, возвращаем None
    return None


# Пример использования
if __name__ == "__main__":
    my_list = [10, 20, 30, 40, 50, 60]
    search_value = 30
    result = sequential_search(my_list, search_value)

    if result is not None:
        print(f'Значение {search_value} найдено на индексе {result}')
    else:
        print(f'Значение {search_value} не найдено')