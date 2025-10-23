// Пример кода с реализацией «кучи Фибоначчи» на C++
#ifndef FIBONACCI_HEAP_ALT_HPP
#define FIBONACCI_HEAP_ALT_HPP

#include <vector>
#include <list>
#include <cmath>
#include <limits>
#include <stdexcept>

template<typename T>
class FibonacciHeap {
private:
    struct Node {
        T value;
        int degree;
        bool marked;
        Node* parent;
        Node* child;
        Node* left;
        Node* right;

        Node(T val) : value(val), degree(0), marked(false),
                     parent(nullptr), child(nullptr),
                     left(this), right(this) {}
    };

    Node* minRoot;
    int count;

    // Вспомогательные методы
    void linkTrees(Node* child, Node* parent) {
        // Удаляем child из списка корней
        child->left->right = child->right;
        child->right->left = child->left;

        // Делаем child дочерним для parent
        child->parent = parent;
        if (parent->child == nullptr) {
            parent->child = child;
            child->left = child;
            child->right = child;
        } else {
            child->left = parent->child;
            child->right = parent->child->right;
            parent->child->right->left = child;
            parent->child->right = child;
        }

        parent->degree++;
        child->marked = false;
    }

    void consolidate() {
        if (!minRoot) return;

        int maxDegree = static_cast<int>(std::log(count) / std::log(1.618)) + 1;
        std::vector<Node*> degreeTable(maxDegree + 1, nullptr);

        // Собираем все корни в список
        std::vector<Node*> roots;
        Node* current = minRoot;
        do {
            roots.push_back(current);
            current = current->right;
        } while (current != minRoot);

        for (Node* root : roots) {
            Node* x = root;
            int degree = x->degree;

            while (degreeTable[degree] != nullptr) {
                Node* y = degreeTable[degree];
                
                // Обеспечиваем, чтобы x был корнем с меньшим ключом
                if (x->value > y->value) {
                    std::swap(x, y);
                }

                linkTrees(y, x);
                degreeTable[degree] = nullptr;
                degree++;
            }
            degreeTable[degree] = x;
        }

        // Восстанавливаем список корней
        minRoot = nullptr;
        for (Node* node : degreeTable) {
            if (node != nullptr) {
                // Убираем связи родитель-потомок для корней
                node->parent = nullptr;
                
                if (minRoot == nullptr) {
                    minRoot = node;
                    node->left = node;
                    node->right = node;
                } else {
                    // Добавляем в список корней
                    node->left = minRoot->left;
                    node->right = minRoot;
                    minRoot->left->right = node;
                    minRoot->left = node;

                    if (node->value < minRoot->value) {
                        minRoot = node;
                    }
                }
            }
        }
    }

    void cutNode(Node* node, Node* parent) {
        // Удаляем node из списка детей parent
        if (node->right == node) {
            parent->child = nullptr;
        } else {
            node->left->right = node->right;
            node->right->left = node->left;
            if (parent->child == node) {
                parent->child = node->right;
            }
        }
        parent->degree--;

        // Добавляем node в список корней
        node->parent = nullptr;
        node->marked = false;
        
        if (minRoot == nullptr) {
            minRoot = node;
            node->left = node;
            node->right = node;
        } else {
            node->left = minRoot->left;
            node->right = minRoot;
            minRoot->left->right = node;
            minRoot->left = node;
        }
    }

    void cascadingCut(Node* node) {
        Node* parent = node->parent;
        if (parent != nullptr) {
            if (!node->marked) {
                node->marked = true;
            } else {
                cutNode(node, parent);
                cascadingCut(parent);
            }
        }
    }

    void clearRecursive(Node* node) {
        if (!node) return;
        
        Node* current = node;
        do {
            Node* next = current->right;
            clearRecursive(current->child);
            delete current;
            current = next;
        } while (current != node);
    }

public:
    FibonacciHeap() : minRoot(nullptr), count(0) {}

    ~FibonacciHeap() {
        clear();
    }

    // Запрещаем копирование и присваивание
    FibonacciHeap(const FibonacciHeap&) = delete;
    FibonacciHeap& operator=(const FibonacciHeap&) = delete;

    bool isEmpty() const {
        return minRoot == nullptr;
    }

    int size() const {
        return count;
    }

    Node* insert(T value) {
        Node* newNode = new Node(value);
        
        if (minRoot == nullptr) {
            minRoot = newNode;
        } else {
            // Вставляем новый узел в список корней
            newNode->left = minRoot->left;
            newNode->right = minRoot;
            minRoot->left->right = newNode;
            minRoot->left = newNode;

            if (value < minRoot->value) {
                minRoot = newNode;
            }
        }
        
        count++;
        return newNode;
    }

    T getMinimum() const {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }
        return minRoot->value;
    }

    T extractMinimum() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }

        Node* minNode = minRoot;
        T minValue = minNode->value;

        // Добавляем всех детей minNode в список корней
        if (minNode->child != nullptr) {
            Node* child = minNode->child;
            do {
                Node* nextChild = child->right;
                
                // Добавляем ребенка в список корней
                child->parent = nullptr;
                if (minRoot == nullptr) {
                    minRoot = child;
                    child->left = child;
                    child->right = child;
                } else {
                    child->left = minRoot->left;
                    child->right = minRoot;
                    minRoot->left->right = child;
                    minRoot->left = child;
                }
                
                child = nextChild;
            } while (child != minNode->child);
        }

        // Удаляем minNode из списка корней
        if (minNode->right == minNode) {
            minRoot = nullptr;
        } else {
            minNode->left->right = minNode->right;
            minNode->right->left = minNode->left;
            minRoot = minNode->right;
            consolidate();
        }

        delete minNode;
        count--;
        return minValue;
    }

    void decreaseKey(Node* node, T newValue) {
        if (newValue > node->value) {
            throw std::invalid_argument("New value is greater than current value");
        }

        node->value = newValue;
        Node* parent = node->parent;

        if (parent != nullptr && node->value < parent->value) {
            cutNode(node, parent);
            cascadingCut(parent);
        }

        if (node->value < minRoot->value) {
            minRoot = node;
        }
    }

    void deleteNode(Node* node) {
        decreaseKey(node, std::numeric_limits<T>::lowest());
        extractMinimum();
    }

    void merge(FibonacciHeap& other) {
        if (other.isEmpty()) return;

        if (isEmpty()) {
            minRoot = other.minRoot;
            count = other.count;
        } else {
            // Объединяем два циклических списка
            Node* thisLeft = minRoot->left;
            Node* otherRight = other.minRoot->right;

            minRoot->left = other.minRoot;
            other.minRoot->right = minRoot;
            thisLeft->right = otherRight;
            otherRight->left = thisLeft;

            if (other.minRoot->value < minRoot->value) {
                minRoot = other.minRoot;
            }

            count += other.count;
        }

        other.minRoot = nullptr;
        other.count = 0;
    }

    void clear() {
        if (minRoot) {
            clearRecursive(minRoot);
            minRoot = nullptr;
            count = 0;
        }
    }

    // Метод для отладки - печать структуры кучи
    void printStructure() const {
        if (isEmpty()) {
            std::cout << "Heap is empty" << std::endl;
            return;
        }

        std::cout << "Fibonacci Heap structure:" << std::endl;
        std::cout << "Total nodes: " << count << std::endl;
        std::cout << "Minimum: " << minRoot->value << std::endl;
        
        Node* current = minRoot;
        int rootCount = 0;
        do {
            std::cout << "Root " << ++rootCount << ": value=" << current->value 
                     << ", degree=" << current->degree << std::endl;
            current = current->right;
        } while (current != minRoot);
    }
};

#endif // FIBONACCI_HEAP_ALT_HPP