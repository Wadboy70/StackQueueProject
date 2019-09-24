#pragma once
#include <iostream>

using namespace std;

template <typename T>

class ABQ {
public:
	ABQ();
	ABQ(int capacity);
	ABQ(const ABQ &d);
	ABQ &operator=(const ABQ &d);
	~ABQ();
	void enqueue(T myData);
	T dequeue();
	T peek();
	unsigned int getSize();
	unsigned int getMaxCapacity();
	T* getData();

private:
	unsigned int capacity;
	unsigned int count;
	int sFactor;
	T* data = nullptr;

};
template <typename T>
ABQ<T>::ABQ() {
	capacity = 1;
	count = 0;
	data = new T[capacity];
	sFactor = 2.0f;
}
template <typename T>
ABQ<T>::ABQ(int capacity1) {
	capacity = capacity1;
	count = 0;
	data = new T[capacity];
	sFactor = 2.0f;
}
template <typename T>
ABQ<T>::ABQ(const ABQ &d) {
	this->capacity = d.capacity;
	this->data = d.data;
	this->count = d.count;
	this->data = new T[capacity];
	for (unsigned int i = 0; i < d.count; i++) {
		//copying values from one array to another
		this->push(d.data[i]);
	}

}
template <typename T>
ABQ<T>::~ABQ() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}
template <typename T>
ABQ<T> &ABQ<T>::operator=(const ABQ &rhs) {
	this->capacity = rhs.capacity;
	this->data = rhs.data;
	this->count = rhs.count;
	this->data = new T[capacity];
	for (unsigned int i = 0; i < rhs.count; i++) {
		//copying values from one array to another
		this->data[i] = rhs.data[i];
		this->push(rhs.data[i]);
	}
	return *this;
}

template <typename T>
void ABQ<T>::enqueue(T myData) {
	//runs if the size needs to be enlarged
	if (capacity == count) {

		capacity *= 2;
		T* array = new T[capacity];
		//array copying
		for (unsigned int i = 0; i < count; ++i) {
			array[i] = this->data[i];
		}
		delete[] this->data;
		this->data = array;
	}
	this->data[count] = myData;
	count++;
}

template <typename T>
T ABQ<T>::dequeue() {
	if (count == 0) {
		throw runtime_error("An error has occurred.");
	}
	T popped = data[0];
	T* array = new T[capacity];
	//only iterates staring from  i+1 because queue removes values from the front
	for (unsigned int i = 1; i < count; i++) {
		array[i - 1] = data[i];
	}
	delete[] data;
	data = array;

	if ((float)(count - 1) / (float)capacity < 1.0f / sFactor) {
		capacity /= sFactor;
	}
	count--;
	return popped;

}
template <typename T>
T ABQ<T>::peek() {
	if (count == 0) {
		throw runtime_error("An error has occurred.");
	}
	return data[0];
}
//Getters
template <typename T>
unsigned int ABQ<T>::getMaxCapacity() {
	return capacity;
}

template <typename T>
T* ABQ<T>::getData() {
	return data;
}

template <typename T>
unsigned int ABQ<T> ::getSize() {
	return count;
}