// Список (vector)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    vector<string> list = {"a", "ab", "abc", "abcd"};
    
    // Удаляем элементы с длиной меньше 3
    list.erase(
        remove_if(list.begin(), list.end(), 
                 [](const string& s) { return s.length() < 3; }),
        list.end()
    );
    
    cout << "Результат: ";
    for (const auto& str : list) {
        cout << str << " ";
    }
    cout << endl;
    
    return 0;
}
