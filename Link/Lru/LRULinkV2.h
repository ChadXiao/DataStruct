//
// Created by Chad.xiao on 2019/1/3 0003.
// LRU缓存淘汰算法
//

#ifndef LINK_LRULINK_H
#define LINK_LRULINK_H
#define DEFAULT_CAPACITY  100
#include <iostream>

using namespace std;

template <class T>
class Node{
private:
	T value;
	Node<T> *next;
public:
	int getValue();
	void setValue(int);
	Node<T>* getNext();
	void setNext(Node<T> *);
};


template <class T>
class LRULink{
public:
	LRULink();
	LRULink(int capacity);
	~LRULink();

	/**
	* 输出所有的值
	*/
	void printAll();

	/**
	* 添加数据，如果表里有，则删除原有数据，并添加到表头
	* @param data
	*/
	void add(T data, bool(*comp)(T a, T b));

private:
	int length = 0;                 //长度
	int capacity = 0;               //容量
	Node<T> *head;                //表头

	/**
	* 删除最后面的元素
	*/
	bool deleteElementAtEnd();

	/**
	* 删除下一个元素
	*/
	void deleteNext(Node<T> *element);

	/**
	* 在表头插入
	* @param data 要插入的数据
	*/
	void insertAtHead(T data);

	/**
	* 查找前一个元素
	* @param value 要查找的值
	* @return 前一个元素
	*/
	Node<T>* findPreNodeByValue(T value, bool(*comp)(T a, T b));

	/**
	* 查找数据
	* @param data
	*/
	Node<T>* find(T data, bool(*comp)(T a, T b));

};


template <class T>
LRULink<T>::LRULink() {
	head = new Node<T>();
	capacity = DEFAULT_CAPACITY;
}

template <class T>
LRULink<T>::LRULink(int capacity) {
	head = new Node<T>();
	this->capacity = capacity;
}

template <class T>
LRULink<T>::~LRULink() {
	bool deleteResult;
	do{
		deleteResult = deleteElementAtEnd();
	} while (deleteResult);
	delete(head);
}

template <class T>
Node<T> * LRULink<T>::findPreNodeByValue(T value, bool(*comp)(T a, T b)) {
	if (length <= 0){
		return nullptr;
	}
	Node<T>* node = head;
	while (node->getNext() != nullptr){
		if (comp(node->getNext()->getValue(), value)){
			return node;
		}
		node = node->getNext();
	}
	return nullptr;
}

template <class T>
void LRULink<T>::deleteNext(Node<T> *node) {

	if (node == nullptr || node->getNext() == nullptr){
		return;
	}

	Node* temp = node->getNext();
	node->setNext(temp->getNext());
	delete(temp);
	temp = nullptr;
	length--;
	return;
}

template <class T>
bool LRULink<T>::deleteElementAtEnd() {

	if (length <= 0){
		//没有多余元素
		return false;
	}

	Node<T>* node = head;
	while (node->getNext() != nullptr && node->getNext()->getNext() != nullptr){
		node = node->getNext();
	}

	Node<T>* temp = node->getNext();
	node->setNext(nullptr);
	if (temp != nullptr){
		delete(temp);
		temp = nullptr;
	}
	length--;
	return true;
}

template <class T>
Node<T>* LRULink<T>::find(T data, bool(*comp)(T a, T b)) {

	Node<T>* preNode = findPreNodeByValue(data, comp);
	if (preNode != nullptr){
		Node<T>* temp = preNode->getNext();
		preNode->setNext(temp->getNext());
		temp->setNext(head->getNext());
		head->setNext(temp);
		return temp;
	}
	return nullptr;
}

template <class T>
void LRULink<T>::add(T data, bool(*comp)(T a, T b)) {

	if (findPreNodeByValue(data, comp) != nullptr){
		find(data, comp);
	}
	else{
		//超出容量，删掉最后的元素
		if (length >= capacity){
			deleteElementAtEnd();
		}
		insertAtHead(data);
	}

}

template <class T>
void LRULink<T>::insertAtHead(T data) {

	Node<T>* node = new Node<T>;
	node->setValue(data);
	node->setNext(head->getNext());
	head->setNext(node);
	length++;
	return;

}

template <class T>
void LRULink<T>::printAll() {
	Node<T>* node = head;
	cout << "LRULink : ";
	while (node->getNext() != nullptr){
		node = node->getNext();
		cout << node->getValue();
	}
	cout << endl;
}

template <class T>
int Node<T>::getValue() {
	return value;
}

template <class T>
void Node<T>::setValue(int value) {
	this->value = value;
	return;
}

template <class T>
Node<T>* Node<T>::getNext() {
	return next;
}

template <class T>
void Node<T>::setNext(Node *next) {
	this->next = next;
	return;
}

#endif //LINK_LRULINK_H


