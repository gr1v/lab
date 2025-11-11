# Создание и работа с вложенными списками
def multiset_example():
    # Создание вложенного списка
    groups = [['Hong', 'Ryan'], ['Andry', 'Ross'], ['Mike', 'Smith']]
    print("Исходный вложенный список:", groups)
    
    # Преобразование в один список
    # Способ 1: с помощью циклов
    names = []
    for group in groups:
        for name in group:
            names.append(name)
    print("Преобразованный список (циклы):", names)
    
    # Способ 2: с помощью extend
    names = []
    for group in groups:
        names.extend(group)
    print("Преобразованный список (extend):", names)
    
    # Операции с вложенными списками
    nested_list = [[1, 2, 3], [4, 5, 6]]
    nested_list.append([7, 8, 9])
    print("После добавления:", nested_list)
    
    nested_list[0][1] = 99  # Изменение элемента
    print("После изменения:", nested_list)
    
    removed = nested_list.pop(1)  # Удаление элемента
    print("После удаления:", nested_list)
    print("Удаленный элемент:", removed)

multiset_example()

# очередь и дек
from queue import Queue
from collections import deque

def queue_example():
    print("\n=== ОЧЕРЕДЬ (Queue) ===")
    # Использование Queue
    q = Queue()
    q.put(1)
    q.put(2)
    q.put(3)
    
    print("Элементы в порядке FIFO:")
    while not q.empty():
        print(q.get())

def deque_example():
    print("\n=== ДВУНАПРАВЛЕННАЯ ОЧЕРЕДЬ (Deque) ===")
    # Использование deque
    tasks = deque()
    tasks.append("task1")
    tasks.append("task2")
    tasks.append("task3")
    
    print("Обработка задач в порядке FIFO:")
    while tasks:
        current_task = tasks.popleft()
        print(f"Выполняется: {current_task}")
    
    # Двунаправленные операции
    dq = deque([1, 2, 3])
    dq.appendleft(0)  # Добавление в начало
    dq.append(4)      # Добавление в конец
    print("Дек после операций:", list(dq))

queue_example()
deque_example()


# приоритетная очередь
import heapq
from queue import PriorityQueue

def priority_queue_example():
    print("\n=== ПРИОРИТЕТНАЯ ОЧЕРЕДЬ ===")
    
    # Способ 1: через PriorityQueue
    print("С использованием PriorityQueue:")
    q = PriorityQueue()
    q.put((2, 'mid-priority item'))
    q.put((1, 'high-priority item'))
    q.put((3, 'low-priority item'))
    
    while not q.empty():
        priority, item = q.get()
        print(f"Приоритет {priority}: {item}")
    
    # Способ 2: через heapq
    print("\nС использованием heapq:")
    customers = []
    heapq.heappush(customers, (2, "Harry"))
    heapq.heappush(customers, (3, "Charles"))
    heapq.heappush(customers, (1, "Riya"))
    heapq.heappush(customers, (4, "Stacy"))
    
    while customers:
        priority, name = heapq.heappop(customers)
        print(f"Приоритет {priority}: {name}")

priority_queue_example()
