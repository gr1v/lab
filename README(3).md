# Бинарная куча (Binary Heap)
### Описание: Полное бинарное дерево, удовлетворяющее свойству кучи: в min-куче родитель меньше потомков, в max-куче — больше.

Реализации:

Java: Класс BinaryHeap<T>

Поддерживает min/max режим через флаг isMax.

Методы: add(), pop(), getTop(), isEmpty().

Динамическое расширение массива через doubleTabSize().

Python: Класс BinaryHeap

Реализована min-куча.

Методы: insert(), delete_min(), get_min(), is_empty().

Вспомогательные методы: _heapify_up(), _heapify_down(), _min_child().

C++: Класс BinaryHeap

Реализована max-куча через вектор.

Методы: push(), pop(), peek(), empty().

Вспомогательные методы: heapifyUp(), heapifyDown().

# Биномиальная куча (Binomial Heap)
### Описание: Коллекция биномиальных деревьев, объединённых в список корней. Эффективно поддерживает слияние.

Реализации:

Java: Класс BinomialHeap

Вложенные классы HeapNode и HeapItem.

Методы: insert(), deleteMin(), decreaseKey(), delete(), meld().

Использует циклический список корней.

C++: Класс BinomialHeap

Структура Node с полями: value, degree, parent, child, sibling.

Методы: Insert(), ExtractMin(), DecreaseKey(), Delete(), Union(), Merge().

Поддерживает меню для интерактивной работы.

# Куча Фибоначчи (Fibonacci Heap)
### Описание: Коллекция деревьев, поддерживающая амортизировано эффективные операции, включая слияние и уменьшение ключа.

Реализации:

C++: Класс FibonacciHeap<T>

Структура Node с двусвязными циклическими списками.

Методы: insert(), extractMinimum(), decreaseKey(), deleteNode(), merge().

Поддержка каскадного разреза (cascading cut) и консолидации.

Используется логарифмическая оценка для размера таблицы степеней.

# Хеш-таблица (Hash Table)
### Описание: Структура для хранения пар «ключ-значение» с быстрым доступом.

Реализации:

Java:

Hashtable<String, Integer>: синхронизированная версия.

HashMap<String, Integer>: несинхронизированная, более производительная.

Методы: put(), get(), remove(), containsKey(), size().

Python:

Класс SimpleHashTable: простая реализация с одной парой на ячейку.

Класс ChainedHashTable: разрешение коллизий методом цепочек.

Методы: set(), get(), remove(), contains().

C++: Класс HashMap<Key, Value>

Использует вектор списков для цепочек.

Методы: put(), get(), remove(), contains(), operator[].

Поддержка рехеширования и итераторов.


