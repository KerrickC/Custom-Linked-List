//
// Created by Kerrick Cavanaugh on 2/23/21.
//

#pragma once
#include <iostream>
#include <vector>
using namespace std;
template <typename T>

class LinkedList {
public:

    struct Node{
        //data
        T data;
        //pointer next node
        LinkedList::Node* next;
        //pointer prev node
        LinkedList::Node* prev;
    };

    //head node pointer
    LinkedList::Node* head;

    //tail node pointer
    LinkedList::Node* tail;
    //# of nodes
    int numNodes;

    LinkedList();

    void AddHead(const T& data);

    void Clear();

    void PrintForward() const;

    void AddTail(const T& data);

    void AddNodesHead(const T* data, unsigned int count);

    void AddNodesTail(const T* data, unsigned int count);

    int NodeCount();

    void PrintReverse() const;

    void PrintForwardRecursive(Node* start);

    void PrintReverseRecursive(Node* start);

    Node* Head();

    const Node* Head() const;

    Node* Tail();

    const Node* Tail() const;

    Node* GetNode(unsigned int index);

    const Node* GetNode(unsigned int index) const;

    T& operator[](unsigned int index);

    const T& operator[](unsigned int index) const;

    Node* Find(const T& data);

    const Node* Find(const T& data) const;

    void FindAll(vector<Node*>& outData, const T& value) const;

    void InsertAfter(Node* node, const T& data);

    void InsertBefore(Node* node, const T& data);

    void InsertAt(const T& data, unsigned int index);

    bool operator==(const LinkedList<T>& rhs) const;

    bool RemoveHead();

    bool RemoveTail();

    unsigned int Remove(const T& data);

    bool RemoveAt(unsigned int index);

    LinkedList<T>& operator=(const LinkedList<T>& rhs); //copy assignment operator

    LinkedList<T>(const LinkedList<T>& rhs); //copy constructor

    ~LinkedList(); //destructor
};

template<typename T>
void LinkedList<T>::AddHead(const T &data) {
    Node* curhead = head;
    if(numNodes == 0){
        head = new Node;
        head->data = data;
        head->next = curhead;
        tail = head;
        tail->prev = curhead;
    }else{
        head = new Node;
        head->data = data;
        head->next = curhead;
        curhead->prev = head;
    }
    numNodes ++;
    //delete curhead;
}

template<typename T>
void LinkedList<T>::AddTail(const T &data) {
    Node* curhead = tail;
    if(numNodes == 0){
        tail = nullptr;
        head = nullptr;
        tail = new Node;
        head = new Node;
        head->prev = nullptr;
        tail->next= nullptr;
        head->data = data;
        tail->prev = head;
        head->next = tail;
        tail->next= nullptr;
    }else if(numNodes == 1){
        //tail = nullptr;
        tail->data = data;
    }else{
        //delete tail;
        tail = new Node;
        tail->data = data;
        tail->prev = curhead;
        curhead->next = tail;
        tail->next= nullptr;
        //delete curhead;
    }
    numNodes ++;
}

template<typename T>
void LinkedList<T>::PrintForward() const {

    Node* curNode = head;

    while(curNode != nullptr){
        cout << curNode->data << endl;
        curNode = curNode->next;
    }
}

template<typename T>
void LinkedList<T>::PrintReverse() const {
    Node* curNode = tail;

    while(curNode != nullptr){
        cout << curNode->data << endl;
        curNode = curNode->prev;
    }
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
    for(unsigned int i = 0; i < count; ++i){
        AddTail(data[i]);
    }
    numNodes += count;
}


template<typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {
    for(int i = count ; i > 0; --i){
        AddHead(data[i-1]);
    }
    tail->next = nullptr;
    head->prev = nullptr;
//    numNodes += count;
}


template<typename T>
int LinkedList<T>::NodeCount() {
    return numNodes;
}


template<typename T>
LinkedList<T>::LinkedList() {
    numNodes = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node* temp = head;
    while(temp != nullptr){
        Node* cur = temp->next;
        delete temp;
        temp = cur;
    }
    //delete tail->prev;
    head = nullptr;
    numNodes = 0;
    tail = nullptr;
    delete temp;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head(){
    return head;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>:: Head() const{
    const LinkedList<T>::Node* const_head = head;
    return const_head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail(){
    return tail;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>:: Tail() const{
    const LinkedList<T>::Node* const_tail = head;
    return const_tail;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index){
    if(index >= numNodes){
        throw out_of_range("Index is too high!");
    }else{
        Node* curNode = head;
        for(int i = 0; i <= index; i ++){
            if(i == index){
                return curNode;
            }
            curNode = curNode->next;
        }
    }
}

template<typename T>
const typename LinkedList<T>::Node*LinkedList<T>::GetNode(unsigned int index) const{
    if(index >= numNodes){
        throw out_of_range("Index is too high!");
    }else{
        const Node* curNode = head;
        for(int i = 0; i < index; i ++){
            curNode = curNode->next;
            if(i + 1 == index){
                return curNode;
            }
        }
    }

}

template<typename T>
void LinkedList<T>::Clear() {
    Node* cur = this->head;
    for(int i = 1; i < numNodes; i ++){
        Node* prev = cur-> prev;
        cur = cur -> next;
        delete prev;
    }
    this->head = nullptr;
    this->tail = nullptr;
    numNodes = 0;
}

template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> &rhs) {

    Clear();

    this->numNodes = 0;

    Node* temp = rhs.head;

    T* dataarr = new T[rhs.numNodes];

    for(int i = 0; i < rhs.numNodes; i ++){
        dataarr[i] = temp->data;
//            cout << "data: " << dataarr[i] << endl;
        temp = temp->next;
    }

    this->AddNodesHead(dataarr, rhs.numNodes);
    delete[] dataarr;

    return *this;
}



template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs){
    this->numNodes = 0;

    Node* temp = rhs.head;

    T* dataarr = new T[rhs.numNodes];

    for(int i = 0; i < rhs.numNodes; i ++){
        dataarr[i] = temp->data;
//            cout << "data: " << dataarr[i] << endl;
        temp = temp->next;
    }

    this->AddNodesHead(dataarr, rhs.numNodes);
    delete[] dataarr;
    //cout << "Tail: " << this->tail->data << endl;
}

template<typename T>
T &LinkedList<T>::operator[](unsigned int index) {
    Node* val = GetNode(index);
    return val->data;
}

template<typename T>
const T &LinkedList<T>::operator[](unsigned int index) const {
    Node* val = GetNode(index);
    return val->data;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) const {
    Node* temp = head;
    for(int i = 0; i < numNodes; i ++){
        if(temp->data == data){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;

}


template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) {
    Node* temp = head;
    for(int i = 0; i < numNodes; i ++){
        if(temp->data == data){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) const {
    vector<Node *> tempoutData;

    Node* temp = head;
    for(int i = 0; i < numNodes; i ++){
        if(temp->data == value){
            tempoutData.push_back(temp);
        }
        temp = temp->next;
    }
    outData = tempoutData;
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data){
    Node* newNode = new Node;
    newNode->data = data;

    Node* temp = this->head;
    for(int i = 0; i < numNodes; i ++){
        if(temp == node){
            if(i == numNodes){
                this->tail = newNode;
                newNode->prev = node;
                newNode->next = nullptr;
                node->next = newNode;
                numNodes++;
                break;
            }
            Node* afternode = node->next;
            //node->next->prev = newNode;
            node->next = newNode;
            newNode->prev = node;
            newNode->next = afternode;
            afternode->prev = newNode;
            numNodes ++;
            break;
        }
        temp = temp->next;
    }
}
template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data){
    Node* newNode = new Node;
    newNode->data = data;

    Node* temp = this->head;
    for(int i = 0; i < numNodes; i ++){
        if(temp == node) {
            if (i == 0) {
                this->head = newNode;
                newNode->next = node;
                newNode->prev = nullptr;
                node->prev = newNode;
                numNodes++;
                break;
            } else {
                Node *beforenode = node->prev;
                node->prev->next = newNode;
                node->prev = newNode;
                newNode->next = node;
                newNode->prev = beforenode;
                //node->next = newNode;
                numNodes++;
                break;
            }
        }
        temp = temp->next;
    }
    //delete newNode;
}

template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index){
    Node* temp = this->head;

    for( int i = 0; i <= numNodes;++i){
        if (unsigned(i) == index){
            if(index == unsigned(numNodes)){
                Node* prevtail = this->tail;
                Node* insertNode = new Node;
                insertNode->data = data;
                this->tail = insertNode;
                insertNode->prev = prevtail;
                prevtail->next=insertNode;
                numNodes++;
                break;
            }
            InsertBefore(temp,data);
            break;
        }
        temp = temp->next;
    }

}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    if(numNodes != rhs.numNodes){
        return false;
    }
    Node* rhsguy = rhs.head;
    Node* myguy = this->head;
    for(int i = 0; i < numNodes; i ++){
        if(rhsguy->data != myguy->data){
            return false;
        }
        rhsguy = rhsguy->next;
        myguy = myguy->next;
    }
    return true;

}

template<typename T>
bool LinkedList<T>::RemoveHead(){
    if(numNodes > 0){
        if(numNodes == 1){
            head->next = tail;
            tail -> prev = head;
            tail-> next = nullptr;
            head->prev = nullptr;
            numNodes = 0;
            return true;
        }
        Node* curhead = this->head->next;
        delete head;
        head = curhead;
        curhead ->prev = nullptr;
        numNodes --;
        return true;
    }else{
        delete head;
        //delete tail;
        return false;
    }
}

template<typename T>
bool LinkedList<T>::RemoveTail(){
    if(numNodes > 0){
        if(numNodes == 1){
            tail->prev = head;
            head -> next = tail;
            head-> prev = nullptr;
            tail->next = nullptr;
            numNodes = 0;
            return true;
        }
        Node* curtail = this->tail->prev;
        delete tail;
        tail = curtail;
        curtail ->next = nullptr;
        numNodes --;
        return true;
    }else{
        //delete head;
        return false;
    }
}


template<typename T>
unsigned int LinkedList<T>::Remove(const T& data){
    unsigned int retVal = 0;
    for(int i = 0; i < numNodes; i ++){
        if(Find(data) != nullptr){
            Node* removalNode = Find(data);
            if(i == 0){
//                Node* removalNextNode = removalNode->next;
//                removalNextNode = removalNode;
//                removalNextNode = nullptr;
            }else if(i == numNodes-1){
//                Node* removalPrevNode = removalNode->prev;
//                removalPrevNode = removalNode;
            }else{
                Node* removalNextNode = removalNode->next;
                Node* removalPrevNode = removalNode->prev;
                removalNode->prev->next = removalNextNode;
                removalNode->next->prev = removalPrevNode;
                this->numNodes--;
                retVal++;
                delete removalNode;
                removalNode = nullptr;
            }

        }

    }
    return retVal;

}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index){
    Node* temp = this->head;
    if(index > unsigned(numNodes)){
        return false;
    }
    for(int i = 0; i < numNodes; i ++){
        if(unsigned(i) == index){
            Node* removalNode = temp;
            if(removalNode->next != nullptr){
                Node* removalNextNode = removalNode->next;
                removalNode->prev->next = removalNextNode;
            }
            if(removalNode->prev != nullptr){
                Node* removalPrevNode = removalNode->prev;
                removalNode->next->prev = removalPrevNode;
            }
            this->numNodes--;
            delete removalNode;
            temp = nullptr;
            delete temp;
            return true;
        }

        temp = temp -> next;

    }
    delete temp;
    temp = nullptr;
    return false;
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(Node* start){
    if(start != nullptr){
        cout << start->data << endl;
        PrintForwardRecursive(start->next);
    }
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(Node* start){
    if(start != nullptr){
        cout << start->data << endl;
        PrintReverseRecursive(start->prev);
    }
}
