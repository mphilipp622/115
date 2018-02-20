#pragma once
#include "Node.h"

template<typename T>
class List
{
public:
	List<T>();
	~List<T>();

	void Insert(int position, T value);
	void InsertFront(T value);
	void InsertBack(T value);
	void DeleteFront();
	void DeleteBack();
	void Delete(int position);
	T GetFront();
	T GetBack();
	T Get(int index);

private:
	Node<T> *head, *tail;
	Node<T>* CreateNode(T value);

};

template<typename T>
List<T>::List()
{
	head = NULL;
	tail = NULL;
}

template<typename T>
List<T>::~List()
{
}

template<typename T>
void List<T>::Insert(int position, T value)
{
	// insert value into list at specific position

	Node<T>* temp = head;
	for (int i = 0; i < position; i++)
	{
		// find node at position
		temp = temp->GetNext();
	}

	if (!temp)
	{
		cout << "Index out of Bounds" << endl;
		return;
	}

	Node<T>* newNode = CreateNode(value);
	newNode->SetPrev(temp->GetPrev());
	newNode->SetNext(temp);
	temp->SetPrev(newNode);
	temp->GetPrev()->SetNext(newNode);
}

template<typename T>
void List<T>::InsertFront(T value)
{
	// insert new node into front of list
	Node<T>* newNode = CreateNode(value);

	if (head)
		head->SetPrev(newNode);

	Node<T>* temp = head;
	newNode->SetNext(temp);
	newNode->SetPrev(nullptr);

	head = newNode;
	if (!tail)
		tail = newNode; // set the tail if nothing exists in the list yet
}

template<typename T>
void List<T>::InsertBack(T value)
{
	// insert new node into back of list
	Node<T>* newNode = CreateNode(value);

	if (tail)
		tail->SetNext(newNode);

	Node<T>* temp = tail;
	newNode->SetNext(nullptr);
	newNode->SetPrev(temp);
	tail = newNode;

	if (!head)
		head = newNode;
}

template<typename T>
void List<T>::DeleteFront()
{
	// delete node at front of list
	head = head->GetNext();
	delete head->GetPrev();
	head->SetPrev(nullptr);
}

template<typename T>
void List<T>::DeleteBack()
{
	// delete node at back of list
	tail = tail->GetPrev();
	delete tail->GetNext();
	tail->SetNext(nullptr);
}

template<typename T>
void List<T>::Delete(int position)
{
}

template<typename T>
T List<T>::GetFront()
{
	return head->GetData();
}

template<typename T>
T List<T>::GetBack()
{
	return tail->GetData();
}

template<typename T>
T List<T>::Get(int index)
{
	// traverse list and return the data at specified index

	Node<T>* temp = head;
	for (int i = 0; i < index; i++)
	{
		temp = temp->GetNext();
	}

	if (!temp)
	{
		cout << "Index out of Bounds" << endl;
		return NULL;
	}
	return temp->GetData();
}

template<typename T>
Node<T>* List<T>::CreateNode(T value)
{
	return new Node<T>(value);
}