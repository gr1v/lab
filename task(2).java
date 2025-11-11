# Двусвязный список
class Node {
    int data;
    Node prev;
    Node next;
    
    public Node(int data) {
        this.data = data;
        this.prev = null;
        this.next = null;
    }
}

class DoublyLinkedList {
    Node head;
    Node tail;
    
    public DoublyLinkedList() {
        this.head = null;
        this.tail = null;
    }
    
    public void append(int data) {
        Node newNode = new Node(data);
        if (head == null) {
            head = tail = newNode;
        } else {
            tail.next = newNode;
            newNode.prev = tail;
            tail = newNode;
        }
    }
    
    public void display() {
        Node current = head;
        while (current != null) {
            System.out.print(current.data + " ");
            current = current.next;
        }
        System.out.println();
    }
}

public class JavaStructures {
    public static void multisetJavaExample() {
        System.out.println("=== ДВУСВЯЗНЫЙ СПИСОК (Java) ===");
        DoublyLinkedList list = new DoublyLinkedList();
        list.append(1);
        list.append(2);
        list.append(3);
        
        System.out.print("Список: ");
        list.display();
    }

  
  # Очередь и Дек
  public static void queueJavaExample() {
        System.out.println("\n=== ОЧЕРЕДЬ (Java) ===");
        
        java.util.Queue<String> queue = new java.util.LinkedList<>();
        queue.add("банан");
        queue.add("яблоко");
        queue.add("ананас");
        
        System.out.println("Элементы в порядке FIFO:");
        while (!queue.isEmpty()) {
            System.out.println(queue.poll());
        }
    }
    
    public static void dequeJavaExample() {
        System.out.println("\n=== ДВУНАПРАВЛЕННАЯ ОЧЕРЕДЬ (Java) ===");
        
        java.util.Deque<Integer> stack = new java.util.ArrayDeque<>();
        stack.push(1);
        stack.push(2);
        stack.push(3);
        
        System.out.println("Элементы в порядке LIFO (как стек):");
        while (!stack.isEmpty()) {
            System.out.println(stack.pop());
        }
    }


  # Приоритетная очередь
  public static void priorityQueueJavaExample() {
        System.out.println("\n=== ПРИОРИТЕТНАЯ ОЧЕРЕДЬ (Java) ===");
        
        // С естественным порядком (min-heap)
        java.util.PriorityQueue<Integer> minHeap = new java.util.PriorityQueue<>();
        minHeap.offer(10);
        minHeap.offer(5);
        minHeap.offer(15);
        minHeap.offer(2);
        
        System.out.println("Элементы в порядке возрастания:");
        while (!minHeap.isEmpty()) {
            System.out.println(minHeap.poll());
        }
        
        // С компаратором для пользовательских объектов
        class Task {
            int id;
            String name;
            int priority;
            
            Task(int id, String name, int priority) {
                this.id = id;
                this.name = name;
                this.priority = priority;
            }
            
            public int id() { return id; }
            public String toString() { return "Task{id=" + id + ", name='" + name + "', priority=" + priority + "}"; }
        }
        
        java.util.Comparator<Task> idComparator = java.util.Comparator.comparing(Task::id);
        java.util.PriorityQueue<Task> taskQueue = new java.util.PriorityQueue<>(idComparator);
        
        taskQueue.add(new Task(10003, "Task 3", 10));
        taskQueue.add(new Task(10001, "Task 1", 5));
        taskQueue.add(new Task(10002, "Task 2", 1));
        
        System.out.println("\nЗадачи, отсортированные по ID:");
        while (!taskQueue.isEmpty()) {
            System.out.println(taskQueue.poll());
        }
    }
    
    public static void main(String[] args) {
        multisetJavaExample();
        queueJavaExample();
        dequeJavaExample();
        priorityQueueJavaExample();
    }
}
