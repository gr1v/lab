// Пример кода для реализации биномиальной кучи на C++
#include <iostream>
#include <cstdlib>
using namespace std;

/*
 * Node Declaration
 */
struct Node
{
    int value;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;
};

/*
 * Class Declaration
 */
class BinomialHeap
{
    private:
    Node* mainHeap;
    Node* tempHeap;
    int counter;
    
    public:
    Node* InitializeHeap();
    int LinkNodes(Node*, Node*);
    Node* CreateNode(int);
    Node* Union(Node*, Node*);
    Node* Insert(Node*, Node*);
    Node* Merge(Node*, Node*);
    Node* ExtractMin(Node*);
    int ReverseList(Node*);
    int Display(Node*);
    Node* Search(Node*, int);
    int DecreaseKey(Node*, int, int);
    int Delete(Node*, int);
    
    BinomialHeap()
    {
        mainHeap = InitializeHeap();
        tempHeap = InitializeHeap();
        counter = 1;
    }
};

/*
 * Initialize Heap
 */
Node* BinomialHeap::InitializeHeap()
{
    Node* newNode;
    newNode = NULL;
    return newNode;
}

/*
 * Linking nodes in Binomial Heap
 */
int BinomialHeap::LinkNodes(Node* node1, Node* node2)
{
    node1->parent = node2;
    node1->sibling = node2->child;
    node2->child = node1;
    node2->degree = node2->degree + 1;
}

/*
 * Create Nodes in Binomial Heap
 */
Node* BinomialHeap::CreateNode(int key)
{
    Node* newNode = new Node;
    newNode->value = key;
    return newNode;
}

/*
 * Insert Nodes in Binomial Heap
 */
Node* BinomialHeap::Insert(Node* heap, Node* newNode)
{
    Node* newHeap = InitializeHeap();
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->degree = 0;
    newHeap = newNode;
    heap = Union(heap, newHeap);
    return heap;
}

/*
 * Union Nodes in Binomial Heap
 */
Node* BinomialHeap::Union(Node* heap1, Node* heap2)
{
    Node* resultHeap = InitializeHeap();
    resultHeap = Merge(heap1, heap2);
    
    if (resultHeap == NULL)
        return resultHeap;
        
    Node* prevNode;
    Node* nextNode;
    Node* currentNode;
    
    prevNode = NULL;
    currentNode = resultHeap;
    nextNode = currentNode->sibling;
    
    while (nextNode != NULL)
    {
        if ((currentNode->degree != nextNode->degree) || 
            ((nextNode->sibling != NULL) && 
             (nextNode->sibling)->degree == currentNode->degree))
        {
            prevNode = currentNode;
            currentNode = nextNode;
        }
        else
        {
            if (currentNode->value <= nextNode->value)
            {
                currentNode->sibling = nextNode->sibling;
                LinkNodes(nextNode, currentNode);
            }
            else
            {
                if (prevNode == NULL)
                    resultHeap = nextNode;
                else
                    prevNode->sibling = nextNode;
                LinkNodes(currentNode, nextNode);
                currentNode = nextNode;
            }
        }
        nextNode = currentNode->sibling;
    }
    return resultHeap;
}

/*
 * Merge Nodes in Binomial Heap
 */
Node* BinomialHeap::Merge(Node* heap1, Node* heap2)
{
    Node* resultHeap = InitializeHeap();
    Node* node1;
    Node* node2;
    Node* temp1;
    Node* temp2;
    
    node1 = heap1;
    node2 = heap2;
    
    if (node1 != NULL)
    {
        if (node2 != NULL)
        {
            if (node1->degree <= node2->degree)
                resultHeap = node1;
            else if (node1->degree > node2->degree)
                resultHeap = node2;
        }
        else
            resultHeap = node1;
    }
    else
        resultHeap = node2;
        
    while (node1 != NULL && node2 != NULL)
    {
        if (node1->degree < node2->degree)
        {
            node1 = node1->sibling;
        }
        else if (node1->degree == node2->degree)
        {
            temp1 = node1->sibling;
            node1->sibling = node2;
            node1 = temp1;
        }
        else
        {
            temp2 = node2->sibling;
            node2->sibling = node1;
            node2 = temp2;
        }
    }
    return resultHeap;
}

/*
 * Display Binomial Heap
 */
int BinomialHeap::Display(Node* heap)
{
    if (heap == NULL)
    {
        cout << "Heap is empty" << endl;
        return 0;
    }
    cout << "Root nodes: " << endl;
    Node* currentNode;
    currentNode = heap;
    
    while (currentNode != NULL)
    {
        cout << currentNode->value;
        if (currentNode->sibling != NULL)
            cout << "-->";
        currentNode = currentNode->sibling;
    }
    cout << endl;
}

/*
 * Extract Minimum
 */
Node* BinomialHeap::ExtractMin(Node* heap)
{
    tempHeap = NULL;
    Node* minPrev = NULL;
    Node* minNode = heap;
    
    if (minNode == NULL)
    {
        cout << "Nothing to Extract" << endl;
        return minNode;
    }
    
    int minValue = minNode->value;
    Node* currentNode = minNode;
    
    while (currentNode->sibling != NULL)
    {
        if ((currentNode->sibling)->value < minValue)
        {
            minValue = (currentNode->sibling)->value;
            minPrev = currentNode;
            minNode = currentNode->sibling;
        }
        currentNode = currentNode->sibling;
    }
    
    if (minPrev == NULL && minNode->sibling == NULL)
        heap = NULL;
    else if (minPrev == NULL)
        heap = minNode->sibling;
    else if (minPrev->sibling == NULL)
        minPrev = NULL;
    else
        minPrev->sibling = minNode->sibling;
        
    if (minNode->child != NULL)
    {
        ReverseList(minNode->child);
        (minNode->child)->sibling = NULL;
    }
    
    mainHeap = Union(heap, tempHeap);
    return minNode;
}

/*
 * Reverse List
 */
int BinomialHeap::ReverseList(Node* node)
{
    if (node->sibling != NULL)
    {
        ReverseList(node->sibling);
        (node->sibling)->sibling = node;
    }
    else
    {
        tempHeap = node;
    }
}

/*
 * Search Nodes in Binomial Heap
 */
Node* BinomialHeap::Search(Node* heap, int key)
{
    Node* currentNode = heap;
    Node* foundNode = NULL;
    
    if (currentNode->value == key)
    {
        foundNode = currentNode;
        return foundNode;
    }
    
    if (currentNode->child != NULL && foundNode == NULL)
        foundNode = Search(currentNode->child, key);
        
    if (currentNode->sibling != NULL && foundNode == NULL)
        foundNode = Search(currentNode->sibling, key);
        
    return foundNode;
}

/*
 * Decrease key of a node
 */
int BinomialHeap::DecreaseKey(Node* heap, int oldKey, int newKey)
{
    int tempValue;
    Node* targetNode;
    Node* node1;
    Node* node2;
    
    targetNode = Search(heap, oldKey);
    
    if (targetNode == NULL)
    {
        cout << "Invalid key choice" << endl;
        return 0;
    }
    
    if (newKey > targetNode->value)
    {
        cout << "Error!! New key is greater than current key" << endl;
        return 0;
    }
    
    targetNode->value = newKey;
    node1 = targetNode;
    node2 = targetNode->parent;
    
    while (node2 != NULL && node1->value < node2->value)
    {
        tempValue = node1->value;
        node1->value = node2->value;
        node2->value = tempValue;
        node1 = node2;
        node2 = node2->parent;
    }
    cout << "Key successfully decreased" << endl;
}

/*
 * Delete Nodes in Binomial Heap
 */
int BinomialHeap::Delete(Node* heap, int key)
{
    Node* deleteNode;
    
    if (heap == NULL)
    {
        cout << "\nHEAP EMPTY!!!!!";
        return 0;
    }
    
    DecreaseKey(heap, key, -1000);
    deleteNode = ExtractMin(heap);
    
    if (deleteNode != NULL)
        cout << "Node successfully deleted" << endl;
}

/*
 * Main Contains Menu
 */
int main()
{
    int choice, value, oldValue, newValue;
    BinomialHeap heap;
    Node* newNode;
    Node* mainHeap;
    mainHeap = heap.InitializeHeap();
    
    while (1)
    {
        cout << "----------------------------" << endl;
        cout << "Binomial Heap Operations" << endl;
        cout << "----------------------------" << endl;
        cout << "1) Insert Element" << endl;
        cout << "2) Extract Minimum" << endl;
        cout << "3) Decrease Key" << endl;
        cout << "4) Delete Node" << endl;
        cout << "5) Display Heap" << endl;
        cout << "6) Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        
        switch(choice)
        {
            case 1:
                cout << "Enter element to insert: ";
                cin >> value;
                newNode = heap.CreateNode(value);
                mainHeap = heap.Insert(mainHeap, newNode);
                break;
            case 2:
                newNode = heap.ExtractMin(mainHeap);
                if (newNode != NULL)
                    cout << "Minimum key node: " << newNode->value << endl;
                else
                    cout << "Heap is empty" << endl;
                break;
            case 3:
                cout << "Enter key to decrease: ";
                cin >> oldValue;
                cout << "Enter new key value: ";
                cin >> newValue;
                heap.DecreaseKey(mainHeap, oldValue, newValue);
                break;
            case 4:
                cout << "Enter key to delete: ";
                cin >> value;
                heap.Delete(mainHeap, value);
                break;
            case 5:
                cout << "Heap contents: " << endl;
                heap.Display(mainHeap);
                break;
            case 6:
                exit(1);
            default:
                cout << "Wrong Choice";
        }
    }
    return 0;
}