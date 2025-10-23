# Реализация бинарной кучи с помощью модуля heapq
import heapq 

numbers = [8, 3, 5, 1, 6, 2, 4, 7]  # создание списка с исходными данными для кучи 
heapq.heapify(numbers) # превращение списка в кучу 
heapq.heappush(numbers, 0) # добавление нового элемента в кучу 
min_value = heapq.heappop(numbers) # извлечение минимального элемента из кучи 
print(numbers) # вывод программы

# Реализация бинарной кучи в виде собственного класса
class BinaryHeap:
    def __init__(self): 
        self.heap = [0]  # нулевой элемент для упрощения индексации
        self.size = 0
    
    def insert(self, key): 
        self.heap.append(key)
        self.size += 1
        self._heapify_up(self.size)
    
    def _heapify_up(self, index):
        while index // 2 > 0:
            if self.heap[index] < self.heap[index // 2]:
                self.heap[index], self.heap[index // 2] = self.heap[index // 2], self.heap[index]
            index = index // 2
    
    def delete_min(self): 
        if self.size == 0:
            return None
        min_val = self.heap[1]
        self.heap[1] = self.heap[self.size]
        self.size -= 1
        self.heap.pop()
        self._heapify_down(1)
        return min_val
    
    def _heapify_down(self, index):
        while (index * 2) <= self.size:
            min_child = self._min_child(index)
            if self.heap[index] > self.heap[min_child]:
                self.heap[index], self.heap[min_child] = self.heap[min_child], self.heap[index]
            index = min_child
    
    def _min_child(self, index):
        if index * 2 + 1 > self.size:
            return index * 2
        else:
            if self.heap[index * 2] < self.heap[index * 2 + 1]:
                return index * 2
            else:
                return index * 2 + 1
    
    def get_min(self): 
        if self.is_empty(): 
            return None 
        return self.heap[1]
    
    def is_empty(self): 
        return self.size == 0

# Тестирование бинарной кучи
heap = BinaryHeap()
heap.insert(5)
heap.insert(3)
heap.insert(8)
heap.insert(1)
print("Минимальный элемент:", heap.get_min())
print("Извлеченный минимум:", heap.delete_min())
print("Новый минимум:", heap.get_min())

# Реализация программы для печати ряда Фибоначчи до заданного количества элементов
def fibonacci_iterative(n): 
    a, b = 0, 1 
    for _ in range(n): 
        print(a, end=' ') 
        a, b = b, a + b 
    print()

print("Первые 10 чисел Фибоначчи:")
fibonacci_iterative(10)

# Алгоритм для рекурсивного вычисления n-го числа ряда Фибоначчи
def fibonacci_recursive(n): 
    if n <= 1: 
        return n 
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)

print("10-е число Фибоначчи:", fibonacci_recursive(10))

# Реализация с использованием словаря (dict) как хэш-таблицы
class SimpleHashTable: 
    def __init__(self, size): 
        self.size = size 
        self.table = [None] * size

    def _hash(self, key): 
        return hash(key) % self.size
     
    def set(self, key, value): 
        hash_index = self._hash(key) 
        self.table[hash_index] = (key, value) 

    def get(self, key): 
        hash_index = self._hash(key) 
        if self.table[hash_index] is not None and self.table[hash_index][0] == key: 
            return self.table[hash_index][1] 
        raise KeyError(f'Key {key} not found')
     
    def remove(self, key): 
        hash_index = self._hash(key) 
        if self.table[hash_index] is not None and self.table[hash_index][0] == key: 
            self.table[hash_index] = None 
        else: 
            raise KeyError(f'Key {key} not found')

# Создание хэш-таблицы размера 10 
simple_hash_table = SimpleHashTable(10) 
# Добавление пар ключ-значение 
simple_hash_table.set('Alice', 'January') 
simple_hash_table.set('Bob', 'May') 
# Получение значения 
print("Значение для 'Alice':", simple_hash_table.get('Alice'))
# Удаление пары ключ-значение 
simple_hash_table.remove('Bob') 
# Это вызовет KeyError, так как 'Bob' был удален 
try:
    print(simple_hash_table.get('Bob'))
except KeyError as e:
    print("Ошибка:", e)

# Реализация хэш-таблицы с цепочками для разрешения коллизий
class ChainedHashTable:
    def __init__(self, size=10):
        """
        Инициализирует хеш-таблицу с заданным размером.
        Внутренний массив будет хранить списки (цепочки) для разрешения коллизий.
        """
        self.array_size = size
        self.array = [[] for _ in range(self.array_size)]

    def hash_function(self, key):
        """
        Генерирует хеш-код для ключа.
        """
        return hash(key) % self.array_size

    def put(self, key, value):
        """
        Вставляет пару ключ-значение в таблицу.
        Если ключ уже существует, его значение обновляется.
        """
        index = self.hash_function(key)
        bucket = self.array[index]
        
        # Проверяем, существует ли уже такой ключ в цепочке
        for i, (existing_key, _) in enumerate(bucket):
            if existing_key == key:
                # Если ключ найден, обновляем значение и выходим
                bucket[i] = (key, value)
                return
        
        # Если ключ не найден, добавляем новую пару (ключ, значение) в цепочку
        bucket.append((key, value))

    def get(self, key):
        """
        Находит и возвращает значение по ключу.
        Если ключ не найден, вызывает исключение KeyError.
        """
        index = self.hash_function(key)
        bucket = self.array[index]
        
        # Ищем ключ в цепочке
        for existing_key, value in bucket:
            if existing_key == key:
                return value
        
        # Если ключ не был найден в цепочке
        raise KeyError(f"Ключ '{key}' не найден.")

    def remove(self, key):
        """
        Удаляет пару ключ-значение по ключу.
        Если ключ не найден, вызывает исключение KeyError.
        """
        index = self.hash_function(key)
        bucket = self.array[index]

        # Ищем ключ в цепочке, чтобы удалить его
        for i, (existing_key, _) in enumerate(bucket):
            if existing_key == key:
                # Удаляем элемент из списка по его индексу
                del bucket[i]
                return
        
        # Если ключ не был найден в цепочке
        raise KeyError(f"Ключ '{key}' не найден.")

    def contains(self, key):
        """
        Проверяет, содержится ли ключ в таблице.
        """
        try:
            self.get(key)
            return True
        except KeyError:
            return False

# --- Пример использования ---

# Создаем экземпляр хеш-таблицы
chained_hash_table = ChainedHashTable(10)

# Добавляем элементы
chained_hash_table.put("Alice", "Engineer")
chained_hash_table.put("Bob", "Designer")
chained_hash_table.put("Charlie", "Manager")

# Получаем значение по ключу
print("Должность Alice:", chained_hash_table.get("Alice"))

# Проверяем наличие ключа
print("Есть ли Bob в таблице:", chained_hash_table.contains("Bob"))

# Удаляем элемент
chained_hash_table.remove("Bob")
print("Bob удален из таблицы")

# Пытаемся получить удаленный элемент
try:
    print(chained_hash_table.get("Bob"))
except KeyError as e:
    print("Ошибка при получении Bob:", e)

# Демонстрация коллизий
chained_hash_table.put("key1", "value1")
chained_hash_table.put("key2", "value2")  # возможна коллизия
print("key1:", chained_hash_table.get("key1"))
print("key2:", chained_hash_table.get("key2"))