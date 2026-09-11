#pragma once

#define DEFAULT_MAX_SIZE 200

#include <stdexcept>
#include <iostream>
#include "List.h"

using std::runtime_error;
using std::cout;
using std::endl;


template <typename E>
class ArrayList : public List<E> {
protected: // cuando una subclase debe accederlos
	E* elements;
	int max;
	int size;
	int pos;

	void expand() {
		max *= 2;
		E* temp = new E[max];
		for (int i = 0; i < size; i++) {
			temp[i] = elements[i];
		}
		delete[] elements;
		elements = temp;
	}

public:
	ArrayList(int max = DEFAULT_MAX_SIZE) {
		elements = new E[max];
		this->max = max;
		size = pos = 0;
	}
	~ArrayList() {
		delete[] elements;
	}
	void insert(E element) {
		if (size == max)
			expand();
		for (int i = size; i > pos; i--)
			elements[i] = elements[i - 1];
		elements[pos] = element;
		size++;
	}
	void append(E element) {
		if (size == max)
			expand();
		elements[size] = element; // elements[size++] = element;
		size++;
	}
	void set(E element) { // sustituye el elemento que esté en pos
		if (pos == size) // si pos está apuntando al final o al inicio de la lista, donde no hay ningún elemento
			throw runtime_error("No current element");
		elements[pos] = element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty");
		if (pos == size)
			throw runtime_error("No current element");
		E result = elements[pos];
		for (int i = pos; i < size-1; i++)
			elements[i] = elements[i + 1];
		size--;
		return result;
	}
	void clear() {
		size = pos = 0;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty");
		if (pos == size)
			throw runtime_error("No current element");
		return elements[pos];
	}
	void goToStart() {
		pos = 0;
	}
	void goToEnd() {
		pos = size;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out of bounds.");
		this->pos = pos;
	}
	void next() {
		if (pos < size)
			pos++;
	}
	void previous() {
		if (pos > 0)
			pos--;
	}
	bool atStart() {
		return pos == 0;
	}
	bool atEnd() {
		return pos == size;
	}
	int getSize() {
		return size;
	}
	int getPos() {
		return pos;
	}
	int indexOf(E element) {
		int tempPos = 0;
		while (tempPos <= size) {
			if (element == elements[tempPos])
				return tempPos;
			tempPos++;
		}
		return -1;
	}
	bool contains(E element) {
		return indexOf(element) != -1;
	}
	void print() {
		cout << "[ ";
		for (int i = 0; i < size; i++)
			cout << elements[i] << " ";
		cout << "]" << endl;
	}
 };
