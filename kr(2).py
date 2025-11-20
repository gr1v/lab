import random

def aco_knapsack(weights, values, W, n_ants, n_iter, evaporation_rate=0.5, alpha=1.0, beta=2.0):
    n = len(weights)
    pheromone = [[1.0 for _ in range(n)] for _ in range(n)]
    best_value = 0
    best_items = []
    
    value_per_weight = [values[i] / weights[i] if weights[i] > 0 else 0 for i in range(n)]
    
    for iter in range(n_iter):
        all_solutions = []
        
        for ant in range(n_ants):
            solution = []
            total_weight = 0
            available = set(range(n))
            
            while True:
                feasible_items = []
                for i in available:
                    if total_weight + weights[i] <= W:
                        feasible_items.append(i)
                
                if not feasible_items:
                    break
                
                probabilities = []
                for i in feasible_items:
                    if not solution:
                        avg_pheromone = sum(pheromone[i][j] for j in range(n)) / n
                    else:
                        last_item = solution[-1]
                        avg_pheromone = pheromone[last_item][i]
                    
                    prob = (avg_pheromone ** alpha) * (value_per_weight[i] ** beta)
                    probabilities.append(prob)
                
                total_prob = sum(probabilities)
                if total_prob > 0:
                    probabilities = [p / total_prob for p in probabilities]
                else:
                    probabilities = [1.0 / len(feasible_items)] * len(feasible_items)
                
                r = random.random()
                cumulative_prob = 0
                selected_item = None
                
                for i, prob in enumerate(probabilities):
                    cumulative_prob += prob
                    if r <= cumulative_prob:
                        selected_item = feasible_items[i]
                        break
                
                if selected_item is None:
                    selected_item = feasible_items[-1]
                
                solution.append(selected_item)
                total_weight += weights[selected_item]
                available.remove(selected_item)
            
            solution_value = sum(values[i] for i in solution)
            all_solutions.append((solution, solution_value, total_weight))
        
        for i in range(n):
            for j in range(n):
                pheromone[i][j] *= (1.0 - evaporation_rate)
        
        all_solutions.sort(key=lambda x: x[1], reverse=True)
        
        for rank, (solution, value, weight) in enumerate(all_solutions[:3]):
            if value > 0:
                reinforcement = (3 - rank) * value / best_value if best_value > 0 else value / 100
                
                for k in range(len(solution) - 1):
                    i = solution[k]
                    j = solution[k + 1]
                    pheromone[i][j] += reinforcement
        
        current_best_solution, current_best_value, _ = all_solutions[0]
        if current_best_value > best_value:
            best_value = current_best_value
            best_items = current_best_solution.copy()
        
        if iter % 10 == 0:
            print(f"Итерация {iter}: лучшая ценность = {best_value}")
    
    return best_items, best_value

def manual_input():
    print("=== Ручной ввод данных для задачи о рюкзаке ===")
    
    while True:
        try:
            n = int(input("Введите количество предметов: "))
            if n > 0:
                break
            else:
                print("Количество предметов должно быть положительным числом.")
        except ValueError:
            print("Пожалуйста, введите целое число.")
    
    weights = []
    values = []
    
    print("\nВведите данные для каждого предмета:")
    for i in range(n):
        print(f"\nПредмет {i+1}:")
        while True:
            try:
                weight = float(input("  Вес предмета: "))
                if weight > 0:
                    break
                else:
                    print("  Вес должен быть положительным числом.")
            except ValueError:
                print("  Пожалуйста, введите число.")
        
        while True:
            try:
                value = float(input("  Ценность предмета: "))
                if value >= 0:
                    break
                else:
                    print("  Ценность должна быть неотрицательным числом.")
            except ValueError:
                print("  Пожалуйста, введите число.")
        
        weights.append(weight)
        values.append(value)
    
    while True:
        try:
            W = float(input("\nВведите вместимость рюкзака: "))
            if W > 0:
                break
            else:
                print("Вместимость должна быть положительным числом.")
        except ValueError:
            print("Пожалуйста, введите число.")
    
    while True:
        try:
            n_ants = int(input("Введите количество муравьёв: "))
            if n_ants > 0:
                break
            else:
                print("Количество муравьёв должно быть положительным числом.")
        except ValueError:
            print("Пожалуйста, введите целое число.")
    
    while True:
        try:
            n_iter = int(input("Введите количество итераций: "))
            if n_iter > 0:
                break
            else:
                print("Количество итераций должно быть положительным числом.")
        except ValueError:
            print("Пожалуйста, введите целое число.")
    
    return weights, values, W, n_ants, n_iter

if __name__ == "__main__":
    print("Решение задачи о рюкзаке методом муравьиной колонии (ACO)")
    print("=" * 60)
    
    while True:
        mode = input("\nВыберите режим ввода:\n1 - Ручной ввод\n2 - Использовать пример\nВаш выбор (1 или 2): ")
        if mode in ['1', '2']:
            break
        else:
            print("Пожалуйста, введите 1 или 2")
    
    if mode == '1':
        weights, values, W, n_ants, n_iter = manual_input()
    else:
        weights = [2, 3, 4, 5, 9, 7, 3, 6]
        values = [3, 4, 8, 8, 10, 13, 6, 11]
        W = 20
        n_ants = 15
        n_iter = 100
        print("\nИспользуются данные примера:")
        print(f"Веса: {weights}")
        print(f"Ценности: {values}")
        print(f"Вместимость рюкзака: {W}")
        print(f"Количество муравьёв: {n_ants}")
        print(f"Количество итераций: {n_iter}")
    
    print("\n" + "=" * 60)
    print("Введенные данные:")
    print(f"Количество предметов: {len(weights)}")
    print(f"Веса предметов: {weights}")
    print(f"Ценности предметов: {values}")
    print(f"Вместимость рюкзака: {W}")
    print(f"Количество муравьёв: {n_ants}")
    print(f"Количество итераций: {n_iter}")
    
    print("\nЗапуск алгоритма муравьиной колонии...")
    best_items, best_value = aco_knapsack(weights, values, W, n_ants, n_iter)
    
    print("\n" + "=" * 60)
    print("РЕЗУЛЬТАТЫ:")
    print(f"Выбранные предметы (индексы): {best_items}")
    print(f"Выбранные предметы (номера): {[i+1 for i in best_items]}")
    print(f"Общая ценность: {best_value}")
    print(f"Общий вес: {sum(weights[i] for i in best_items)}")
    print(f"Вместимость рюкзака: {W}")
    
    print("\nДетали выбранных предметов:")
    total_weight = 0
    total_value = 0
    for i in best_items:
        total_weight += weights[i]
        total_value += values[i]
        print(f"  Предмет {i+1}: вес = {weights[i]}, ценность = {values[i]}")
    
    print(f"\nИтог: вес = {total_weight}, ценность = {total_value}")




ВВОД ВЫВОД
Встроеный Пример 
Выберите режим ввода:
1 - Ручной ввод
2 - Использовать пример
Ваш выбор (1 или 2): 2

Используются данные примера:
Веса: [2, 3, 4, 5, 9, 7, 3, 6]
Ценности: [3, 4, 8, 8, 10, 13, 6, 11]
Вместимость рюкзака: 20
Количество муравьёв: 15
Количество итераций: 100

============================================================
Введенные данные:
Количество предметов: 8
Веса предметов: [2, 3, 4, 5, 9, 7, 3, 6]
Ценности предметов: [3, 4, 8, 8, 10, 13, 6, 11]
Вместимость рюкзака: 20
Количество муравьёв: 15
Количество итераций: 100

Запуск алгоритма муравьиной колонии...
Итерация 0: лучшая ценность = 38
Итерация 10: лучшая ценность = 38
Итерация 20: лучшая ценность = 38
Итерация 30: лучшая ценность = 38
Итерация 40: лучшая ценность = 38
Итерация 50: лучшая ценность = 38
Итерация 60: лучшая ценность = 38
Итерация 70: лучшая ценность = 38
Итерация 80: лучшая ценность = 38
Итерация 90: лучшая ценность = 38

============================================================
РЕЗУЛЬТАТЫ:
Выбранные предметы (индексы): [7, 2, 5, 6]
Выбранные предметы (номера): [8, 3, 6, 7]
Общая ценность: 38
Общий вес: 20
Вместимость рюкзака: 20

Детали выбранных предметов:
  Предмет 8: вес = 6, ценность = 11
  Предмет 3: вес = 4, ценность = 8
  Предмет 6: вес = 7, ценность = 13
  Предмет 7: вес = 3, ценность = 6

Итог: вес = 20, ценность = 38




Ручной Ввод 
Выберите режим ввода:
1 - Ручной ввод
2 - Использовать пример
Ваш выбор (1 или 2): 1
=== Ручной ввод данных для задачи о рюкзаке ===
Введите количество предметов: 4

Введите данные для каждого предмета:

Предмет 1:
  Вес предмета: 8
  Ценность предмета: 9 

Предмет 2:
  Вес предмета: 4
  Ценность предмета: 7

Предмет 3:
  Вес предмета: 3
  Ценность предмета: 1

Предмет 4:
  Вес предмета: 9
  Ценность предмета: 6

Введите вместимость рюкзака: 10
Введите количество муравьёв: 4
Введите количество итераций: 5

============================================================
Введенные данные:
Количество предметов: 4
Веса предметов: [8.0, 4.0, 3.0, 9.0]
Ценности предметов: [9.0, 7.0, 1.0, 6.0]
Вместимость рюкзака: 10.0
Количество муравьёв: 4
Количество итераций: 5

Запуск алгоритма муравьиной колонии...
Итерация 0: лучшая ценность = 9.0

============================================================
РЕЗУЛЬТАТЫ:
Выбранные предметы (индексы): [0]
Выбранные предметы (номера): [1]
Общая ценность: 9.0
Общий вес: 8.0
Вместимость рюкзака: 10.0

Детали выбранных предметов:
  Предмет 1: вес = 8.0, ценность = 9.0

Итог: вес = 8.0, ценность = 9.0

