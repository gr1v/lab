// Пример кода с реализацией хеш-таблицы на C++
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>

template<typename Key, typename Value>
class HashMap {
private:
    struct Entry {
        Key key;
        Value value;
        Entry(const Key& k, const Value& v) : key(k), value(v) {}
    };

    std::vector<std::list<Entry>> buckets;
    size_t itemCount;
    double loadFactorThreshold;

    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % buckets.size();
    }

    void rehash() {
        if (loadFactor() < loadFactorThreshold) return;

        size_t newSize = buckets.size() * 2;
        std::vector<std::list<Entry>> newBuckets(newSize);

        for (const auto& bucket : buckets) {
            for (const auto& entry : bucket) {
                size_t newIndex = std::hash<Key>{}(entry.key) % newSize;
                newBuckets[newIndex].push_back(entry);
            }
        }

        buckets = std::move(newBuckets);
    }

public:
    HashMap(size_t initialSize = 16, double maxLoadFactor = 0.75) 
        : buckets(initialSize), itemCount(0), loadFactorThreshold(maxLoadFactor) {}

    // Вставка или обновление значения
    void put(const Key& key, const Value& value) {
        if (loadFactor() >= loadFactorThreshold) {
            rehash();
        }

        size_t index = hash(key);
        auto& bucket = buckets[index];

        // Проверяем, существует ли уже ключ
        for (auto& entry : bucket) {
            if (entry.key == key) {
                entry.value = value; // Обновляем значение
                return;
            }
        }

        // Добавляем новую запись
        bucket.emplace_back(key, value);
        itemCount++;
    }

    // Получение значения по ключу
    Value& get(const Key& key) {
        size_t index = hash(key);
        auto& bucket = buckets[index];

        for (auto& entry : bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }

        throw std::out_of_range("Key not found");
    }

    // Константная версия получения значения
    const Value& get(const Key& key) const {
        size_t index = hash(key);
        const auto& bucket = buckets[index];

        for (const auto& entry : bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }

        throw std::out_of_range("Key not found");
    }

    // Безопасное получение значения (возвращает nullptr если ключ не найден)
    Value* find(const Key& key) {
        size_t index = hash(key);
        auto& bucket = buckets[index];

        for (auto& entry : bucket) {
            if (entry.key == key) {
                return &entry.value;
            }
        }

        return nullptr;
    }

    // Проверка существования ключа
    bool contains(const Key& key) const {
        size_t index = hash(key);
        const auto& bucket = buckets[index];

        for (const auto& entry : bucket) {
            if (entry.key == key) {
                return true;
            }
        }

        return false;
    }

    // Удаление элемента
    bool remove(const Key& key) {
        size_t index = hash(key);
        auto& bucket = buckets[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                itemCount--;
                return true;
            }
        }

        return false;
    }

    // Оператор [] для удобного доступа
    Value& operator[](const Key& key) {
        size_t index = hash(key);
        auto& bucket = buckets[index];

        for (auto& entry : bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }

        // Если ключ не найден, создаем новую запись
        bucket.emplace_back(key, Value{});
        itemCount++;
        return bucket.back().value;
    }

    // Размер хеш-таблицы
    size_t size() const {
        return itemCount;
    }

    // Емкость хеш-таблицы
    size_t capacity() const {
        return buckets.size();
    }

    // Коэффициент загрузки
    double loadFactor() const {
        return static_cast<double>(itemCount) / buckets.size();
    }

    // Проверка на пустоту
    bool empty() const {
        return itemCount == 0;
    }

    // Очистка таблицы
    void clear() {
        for (auto& bucket : buckets) {
            bucket.clear();
        }
        itemCount = 0;
    }

    // Итератор для обхода всех элементов
    class Iterator {
    private:
        const HashMap* map;
        size_t bucketIndex;
        typename std::list<Entry>::const_iterator listIt;

        void findNext() {
            while (bucketIndex < map->buckets.size()) {
                if (listIt != map->buckets[bucketIndex].end()) {
                    return;
                }
                bucketIndex++;
                if (bucketIndex < map->buckets.size()) {
                    listIt = map->buckets[bucketIndex].begin();
                }
            }
        }

    public:
        Iterator(const HashMap* m, size_t index, typename std::list<Entry>::const_iterator it)
            : map(m), bucketIndex(index), listIt(it) {
            findNext();
        }

        const Entry& operator*() const {
            return *listIt;
        }

        const Entry* operator->() const {
            return &(*listIt);
        }

        Iterator& operator++() {
            ++listIt;
            findNext();
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return bucketIndex != other.bucketIndex || listIt != other.listIt;
        }
    };

    Iterator begin() const {
        return Iterator(this, 0, buckets[0].begin());
    }

    Iterator end() const {
        return Iterator(this, buckets.size(), buckets.back().end());
    }

    // Вывод статистики
    void printStats() const {
        std::cout << "Hash Table Statistics:\n";
        std::cout << "Size: " << size() << "\n";
        std::cout << "Capacity: " << capacity() << "\n";
        std::cout << "Load Factor: " << loadFactor() << "\n";
        
        size_t maxBucketSize = 0;
        size_t emptyBuckets = 0;
        
        for (const auto& bucket : buckets) {
            if (bucket.empty()) {
                emptyBuckets++;
            }
            if (bucket.size() > maxBucketSize) {
                maxBucketSize = bucket.size();
            }
        }
        
        std::cout << "Max Bucket Size: " << maxBucketSize << "\n";
        std::cout << "Empty Buckets: " << emptyBuckets << "\n";
    }
};

// Пример использования
int main() {
    HashMap<std::string, int> map;

    // Вставка элементов
    map.put("apple", 10);
    map.put("banana", 20);
    map.put("orange", 30);
    map.put("grape", 40);

    // Доступ через оператор []
    std::cout << "apple: " << map["apple"] << std::endl;
    
    // Обновление через оператор []
    map["banana"] = 25;
    std::cout << "banana: " << map["banana"] << std::endl;

    // Доступ через get()
    try {
        std::cout << "orange: " << map.get("orange") << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    // Проверка существования
    std::cout << "Contains 'grape': " << map.contains("grape") << std::endl;
    std::cout << "Contains 'melon': " << map.contains("melon") << std::endl;

    // Удаление
    map.remove("orange");
    std::cout << "Contains 'orange' after removal: " << map.contains("orange") << std::endl;

    // Итерация по всем элементам
    std::cout << "\nAll elements:\n";
    for (const auto& entry : map) {
        std::cout << entry.key << ": " << entry.value << std::endl;
    }

    // Статистика
    std::cout << "\n";
    map.printStats();

    // Демонстрация рехеширования
    HashMap<int, std::string> smallMap(4, 0.5);
    for (int i = 0; i < 10; ++i) {
        smallMap.put(i, "Value_" + std::to_string(i));
    }
    
    std::cout << "\nAfter adding 10 elements:\n";
    smallMap.printStats();

    return 0;
}