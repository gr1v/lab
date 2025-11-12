class TreeNode:
    def __init__(self, value):
        self.value = value      # Данные узла
        self.children = []      # Дочерние узлы
    
    def add_child(self, child_node):
        # Добавляем узел в список детей
        self.children.append(child_node)
    
    def remove_child(self, child_node):
        # Удаляем указанный дочерний узел
        self.children = [child for child in self.children if child != child_node]
    
    def traverse(self):
        # Обходим дерево в глубину (DFS)
        nodes = [self]
        while nodes:
            current_node = nodes.pop()
            print(current_node.value)
            # Добавляем детей в обратном порядке для правильного обхода
            nodes.extend(current_node.children[::-1])

# Бинарное дерево
class BinaryTreeNode:
    def __init__(self, value):
        self.value = value      # Данные узла
        self.left = None        # Левый ребенок
        self.right = None       # Правый ребенок
        self.parent = None      # Ссылка на родителя
    
    def insert_left(self, value):
        # Создаем и возвращаем левого потомка
        self.left = BinaryTreeNode(value)
        self.left.parent = self
        return self.left
    
    def insert_right(self, value):
        # Создаем и возвращаем правого потомка
        self.right = BinaryTreeNode(value)
        self.right.parent = self
        return self.right
