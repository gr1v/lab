# Мультисписок
#include <iostream>
using namespace std;

// Структура узла двусвязного списка
struct Node {
    int data;
    Node* prev;
    Node* next;
    
    Node(int val) {
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    
public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    
    // Добавление в конец
    void append(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    // Удаление с начала
    void removeFront() {
        if (!head) return;
        
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
    }
    
    // Вывод списка
    void display() {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

void multiset_cpp_example() {
    cout << "=== ДВУСВЯЗНЫЙ СПИСОК (C++) ===" << endl;
    DoublyLinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);
    
    cout << "Список: ";
    list.display();
    
    list.removeFront();
    cout << "После удаления первого элемента: ";
    list.display();
}

# Очередь и Дек
#include <iostream>
#include <queue>
#include <deque>
using namespace std;

void queue_cpp_example() {
    cout << "\n=== ОЧЕРЕДЬ (C++) ===" << endl;
    
    // Очередь
    queue<string> q;
    q.push("Tom");
    q.push("Bob");
    q.push("Sam");
    
    cout << "Первый элемент: " << q.front() << endl;
    cout << "Последний элемент: " << q.back() << endl;
    
    cout << "Все элементы в порядке FIFO:" << endl;
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

void deque_cpp_example() {
    cout << "\n=== ДВУСТОРОННЯЯ ОЧЕРЕДЬ (C++) ===" << endl;
    
    // Дек
    deque<int> d = {1, 2, 3};
    d.push_front(0);  // Добавление в начало
    d.push_back(4);   // Добавление в конец
    
    cout << "Элементы дека: ";
    for (int num : d) {
        cout << num << " ";
    }
    cout << endl;
}





# Приоритетная очередь
#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Пользовательская структура для приоритетной очереди
struct Task {
    string name;
    int priority;
    
    // Перегрузка оператора для сравнения по приоритету
    bool operator<(const Task& other) const {
        return priority < other.priority;  // Максимальный приоритет первый
    }
};

void priority_queue_cpp_example() {
    cout << "\n=== ПРИОРИТЕТНАЯ ОЧЕРЕДЬ (C++) ===" << endl;
    
    // С примитивными типами
    priority_queue<int> pq;
    pq.push(10);
    pq.push(20);
    pq.push(15);
    
    cout << "Элементы с наивысшим приоритетом: ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
    
    // С пользовательскими структурами
    priority_queue<Task> taskQueue;
    taskQueue.push({"Task 1", 2});
    taskQueue.push({"Task 2", 1});
    taskQueue.push({"Task 3", 3});
    
    cout << "Обработка задач по приоритету:" << endl;
    while (!taskQueue.empty()) {
        Task task = taskQueue.top();
        cout << "Processing: " << task.name << " (приоритет: " << task.priority << ")" << endl;
        taskQueue.pop();
    }
}

// Главная функция для C++
int main() {
    multiset_cpp_example();
    queue_cpp_example();
    deque_cpp_example();
    priority_queue_cpp_example();
    return 0;
}
