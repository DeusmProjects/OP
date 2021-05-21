#include <iostream> 

//using namespace std;

struct Item
{
    int id;
    char name[10];
};

struct Node {
    struct Item* item = nullptr;
    struct Node* next = nullptr;
    struct Node* prev = nullptr;
};

struct List {
    unsigned int size = 0;
    struct Node* head = nullptr;
    struct Node* tail = nullptr;
};

Node* getNode(List* list, int index) {
    if (index >= list->size) {
        exit(5);
    }

    int halfSize = list->size / 2;
    int i;
    Node* current;

    if (index < halfSize) {
        i = 0;
        current = list->head;

        while (current != nullptr && i < index) {
            current = current->next;
            i++;
        }
    }
    else {
        i = list->size - 1;
        current = list->tail;

        while (current != nullptr && i > index) {
            current = current->prev;
            i--;
        }
    }

    return current;
}

void insertNodeBefore(List* list, Item* item, int index) {
    Node* newNode = new Node;
    newNode->item = item;

    Node* element = getNode(list, index);
    if (element == nullptr) {
        exit(7);
    }

    newNode->next = element;
    newNode->prev = element->prev;

    if (element->prev != nullptr) {
        element->prev->next = newNode;
    }

    element->prev = newNode;

    if (newNode->prev == nullptr) {
        list->head = newNode;
    }

    list->size++;
}

void insertNodeAfter(List* list, Item* item, int index) {
    Node* newNode = new Node;
    newNode->item = item;

    Node* element = getNode(list, index);
    if (element == nullptr) {
        exit(6);
    }

    newNode->prev = element;
    newNode->next = element->next;

    if (element->next != nullptr) {
        element->next->prev = newNode;
    }

    element->next = newNode;

    if (newNode->next == nullptr) {
        list->tail = newNode;
    }

    list->size++;
}

void addNode(List* list, Item* item)
{
    if (list->size == 0)
    {
        Node* newNode = new Node;
        newNode->item = item;
        list->head = newNode;
        list->tail = newNode;
        list->size++;
    }
    else
    {
        insertNodeAfter(list, item, list->size - 1);
    }
}

void sortedInsert(List* list, Item* item) {
    Node* newNode = new Node;
    newNode->item = item;
    Node* current;

    if (list->size == 0) {
        addNode(list, item);
    }
    else {
        int index = -1;
        current = list->head;

        /*bool conditionInt = current->item->id < item->id;
        bool conditionStr = strcmp(current->item->name, item->name);*/

        if (strcmp(current->item->name, item->name) >= 0) {
            insertNodeBefore(list, item, 0);
            return;
        }

        if (strcmp(list->tail->item->name, item->name) == -1) {
            insertNodeAfter(list, item, list->size - 1);
            return;
        }

        while (current != nullptr && strcmp(current->item->name, item->name) == -1) {
            current = current->next;
            index++;
        }

        insertNodeAfter(list, item, index);
    }
}

void printList(List* list)
{
    Node* tmp = list->head;
    for (int i = 0; i < list->size; ++i)
    {
        printf("item %d - name: %s\n", tmp->item->id, tmp->item->name);
        tmp = tmp->next;
    }
}

int main()
{
    List* list = new List;

    sortedInsert(list, new Item{ 1, "ertt" });
    sortedInsert(list, new Item{ 3, "adwaw" });
    sortedInsert(list, new Item{ 2, "cxccc" });

    /*addNode(list, new Item{1, "aaa"});
    addNode(list, new Item{2, "bbb"});
    addNode(list, new Item{3, "ccc"});
    addNode(list, new Item{4, "ddd"});
    insertNodeBefore(list, new Item{ 123, "awdawdaw" }, 0);
    insertNodeAfter(list, new Item{5, "eee"}, 1);*/
    //insertNodeBefore(list, new Item{6, "fff"}, 4);
    //insertNodeBefore(list, new Item{7, "ffdaff"}, 5);
    //insertNodeAfter(list, new Item{11, "fawdaff"}, 3);

    printList(list);

    return 0;
}