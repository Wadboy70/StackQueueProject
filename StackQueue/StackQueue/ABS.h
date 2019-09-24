#pragma once
#include <iostream>


using namespace std;

template <typename T>

class ABS {
public:

	ABS();
	ABS(int capacity);
	ABS(const ABS &d);
	~ABS();
	ABS &operator = (const ABS &d);
	void push(T data);
	T pop();
	T peek();
	unsigned int getSize();
	unsigned int getMaxCapacity();
	T* getData();

private:
	T * data = nullptr;
	unsigned int capacity;
	unsigned int count;
	float sFactor;

};
template <typename T>
ABS<T>::ABS() {
	capacity = 1;
	count = 0;
	data = new T[capacity];
	sFactor = 2.0f;
}
template <typename T>
ABS<T>::ABS(int capacity1) {
	capacity = capacity1;
	data = new T[capacity];
	count = 0;
	sFactor = 2.0f;
}

template <typename T>
ABS<T>::ABS(const ABS &rhs) {
	this->capacity = rhs.capacity;
	this->data = new T[capacity];

	// entering for loop
	//copying data from "this" to rhs
	for (unsigned int i = 0; i < rhs.count; i++) {
		this->push(rhs.data[i]);
	}
}
template <typename T>
//data is the only global pointer that has been allocated
ABS<T>::~ABS() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

template <typename T>
ABS<T> &ABS<T>::operator=(const ABS &rhs) {
	this->capacity = rhs.capacity;
	this->data = new T[capacity];
	for (unsigned int i = 0; i < rhs.count; i++) {
		this->push(rhs.data[i]);
	}
	return *this;
}

template <typename T>
void ABS<T>::push(T someData) {
	//This code should only occur when the array needs to be resized to make room for more elements
	if (capacity == count) {

		capacity *= 2;
		T* array = new T[capacity];
		//data is copied from one array to another
		for (unsigned int i = 0; i < count; ++i) {
			array[i] = data[i];
		}
		delete[] data;
		data = array;
	}
	//someData ia dded to the end of the arrray
	data[count] = someData;
	count++;
}

template <typename T>
T ABS<T>::pop() {
	if (count == 0) {
		throw runtime_error("An error has occurred.");
	}
	T popped = data[count - 1];
	T* array = new T[capacity];
	for (unsigned int i = 0; i < count - 1; i++) {
		array[i] = data[i];
		//cout << array[i];

	}
	delete[] data;
	data = array;
	//If the inverse of the load factor is more than the ratio of count to the array size then the array can be shrunk
	if ((float)(count - 1) / (float)capacity < 1.0f / sFactor) {
		capacity /= sFactor;
	}
	count--;

	return popped;

}

template <typename T>
T ABS<T>::peek() {
	if (count == 0) {
		throw runtime_error("An error has occurred.");
	}
	else {
		//Just taking a look at the top value in the stack
		return data[count - 1];
	}
}
//Getters
template <typename T>
unsigned int ABS <T> ::getSize() {
	return count;
}

template <typename T>
unsigned int ABS<T>::getMaxCapacity() {
	return capacity;
}

template <typename T>
T* ABS<T>::getData() {
	return data;
}
