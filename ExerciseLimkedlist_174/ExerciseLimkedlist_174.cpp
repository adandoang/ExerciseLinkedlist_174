#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode();
    bool search(int rollno, Node** iffat, Node** akhdan);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    cout << "\nAdding a new node" << endl;

    Node* newNode = new Node;
    cout << "Enter roll number: ";
    cin >> newNode->rollNumber;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newNode->name);

    if (listEmpty()) {
        newNode->next = newNode;
        LAST = newNode;
    }
    else {
        Node* akhdan = LAST->next;
        Node* iffat = NULL;

        while (akhdan->rollNumber < newNode->rollNumber && akhdan != LAST) {
            iffat = akhdan;
            akhdan = akhdan->next;
        }

        if (iffat == NULL) {
            newNode->next = akhdan;
            LAST->next = newNode;
        }
        else if (akhdan == LAST && akhdan->rollNumber < newNode->rollNumber) {
            newNode->next = akhdan->next;
            akhdan->next = newNode;
            LAST = newNode;
        }
        else {
            iffat->next = newNode;
            newNode->next = akhdan;
        }
    }
    cout << "Added" << endl;
}

bool CircularLinkedList::search(int rollno, Node** iffat, Node** akhdan) {
    *iffat = LAST->next;
    *akhdan = LAST->next;

    while (*akhdan != LAST) {
        if (rollno == (*akhdan)->rollNumber) {
            return true;
        }

        *iffat = *akhdan;
        *akhdan = (*akhdan)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    if (listEmpty()) {
        cout << "\nList is empty. Deletion not possible." << endl;
        return false;
    }

    int rollno;
    cout << "\nEnter the roll number to delete: ";
    cin >> rollno;

    Node* iffat = NULL;
    Node* akhdan = NULL;

    if (!search(rollno, &iffat, &akhdan)) {
        cout << "Node with roll number " << rollno << " not found. Deletion not possible" << endl;
        return false;
    }

    if (iffat == NULL && akhdan->next == akhdan) {
        delete akhdan;
        LAST = NULL;
        cout << "Node with roll number " << rollno << " deleted" << endl;
        return true;
    }
    else if (iffat == NULL) {
        LAST->next = akhdan->next;
        delete akhdan;
        cout << "Node with roll number " << rollno << " deleted" << endl;
        return true;
    }
    else if (akhdan == LAST) {
        iffat->next = LAST->next;
        LAST = iffat;
        delete akhdan;
        cout << "Node with roll number " << rollno << " deleted" << endl;
        return true;
    }
    else {
        iffat->next = akhdan->next;
        delete akhdan;
        cout << "Node with roll number " << rollno << " deleted" << endl;
        return true;
    }
}


void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* currentNode = LAST->next;
        while (currentNode != LAST) {
            cout << currentNode->rollNumber << " " << currentNode->name << endl;
            currentNode = currentNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;
    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-4): ";
            char ch;
            cin >> ch;

            switch (ch) {
            case '1':
                obj.addNode();
                break;
            case '2':
                obj.delNode();
                break;
            case '3':
                obj.traverse();
                break;
            case '4':
                return 0;
            default:
                cout << "Invalid option" << endl;
                break;
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}