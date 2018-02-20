#pragma once

template <typename T>
class Node
{
public:
	Node();
	Node(T newValue);
	Node(T newData, Node<T>* newNext, Node<T>* newPrev);
	~Node();
	T GetData();
	Node* GetNext();
	Node* GetPrev();
	void SetNext(Node<T>* newNext);
	void SetPrev(Node<T>* newPrev);

private:
	T data;
	Node* next;
	Node* prev;
};

template<typename T>
Node<T>::Node()
{
	data = NULL;
	next = nullptr;
	prev = nullptr;
}

template<typename T>
Node<T>::Node(T newValue)
{
	data = newValue;
	next = nullptr;
	prev = nullptr;
}

template<typename T>
Node<T>::Node(T newData, Node<T>* newNext, Node<T>* newPrev)
{
	data = newData;
	next = newNext;
	prev = newPrev;
}

template<typename T>
Node<T>::~Node()
{

}

template<typename T>
T Node<T>::GetData()
{
	return data;
}

template<typename T>
Node<T>* Node<T>::GetNext()
{
	return next;
}

template<typename T>
Node<T>* Node<T>::GetPrev()
{
	return prev;
}

template<typename T>
void Node<T>::SetNext(Node<T>* newNext)
{
	this->next = newNext;
}

template<typename T>
void Node<T>::SetPrev(Node<T>* newPrev)
{
	this->prev = newPrev;
}
