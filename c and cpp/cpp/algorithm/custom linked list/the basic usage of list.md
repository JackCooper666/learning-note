# Single direction list
```cpp
// Definition for singly-linked list.
struct ListNode {
int val;
ListNode *next;
ListNode() : val(0), next(nullptr) {}
ListNode(int x) : val(x), next(nullptr) {}
ListNode(int x, ListNode *next) : val(x), next(next) {}
};
```

initialization of list
simple version:
```cpp
ListNode* node1 = new ListNode(1);
ListNode* node2 = new ListNode(2);
ListNode* node3 = new ListNode(3);
ListNode* node4 = new ListNode(4);
node1->next = node2;
node2->next = node3;
node3->next = node4;
```
advanced version:
```cpp
// Function to create a linked list from a vector of values
ListNode* createList(const std::vector<int>& values) {
    ListNode* dummy = new ListNode(); // Dummy node to simplify insertion
    ListNode* tail = dummy; // Tail pointer to track the end

    for (int val : values) {
        tail->next = new ListNode(val); // Append new node
        tail = tail->next; // Move tail forward
    }

    ListNode* head = dummy->next; // Actual head is after dummy
    delete dummy; // Free dummy node
    return head;
}
```

how to count the length of a list in cpp
```cpp
int getLength(ListNode* head) {
    int count = 0;
    ListNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}
```
```cpp
int getLengthRecursive(ListNode* head) {
    if (head == nullptr) return 0;
    return 1 + getLengthRecursive(head->next);
}
```

# bio-direct list
```cpp
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};
```