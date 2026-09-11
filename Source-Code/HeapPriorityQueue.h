#pragma once

#include <stdexcept>
#include "PriorityQueue.h"
#include "MinHeap.h"
#include "KVPair.h"
#include "Tiquete.h"

using std::runtime_error;

template <typename E>
class HeapPriorityQueue : public PriorityQueue<E>
{
private:
	MinHeap<KVPair<int, E>>* pairs;
	int priorities;

public:

	HeapPriorityQueue(int priorities, int max = DEFAULT_MAX_SIZE) {
		pairs = new MinHeap<KVPair<int, E>>(max);
		this->priorities = priorities;
	}
	~HeapPriorityQueue() {
		delete pairs;
	}

	void insert(E element, int priority) {
		if (priority < 0 || priority >= priorities)
			throw runtime_error("Invalid priority.");
		KVPair<int, E> p(priority, element);
		pairs->insert(p);
	}

	E min() {
		KVPair<int, E> p = pairs->first();
		return p.value;
	}
	E removeMin() {
		KVPair<int, E> p = pairs->removeFirst();
		return p.value;
	}
	void clear() {
		pairs->clear();
	}
	int getSize() {
		return pairs->getSize();
	}
	bool isEmpty() {
		return pairs->isEmpty();
	}
	void printTiquetes() {
		cout << "[";
		for (int i = 0; i < pairs->getSize(); ++i) {
			KVPair<int, E> p = pairs->getElement(i);
			Tiquete* tiquete = &p.value;
			if (i > 0) {
				cout << ", ";
			}
			cout << tiquete->getCodigo();
		}
		cout << "]" << endl;
	}
	void print() {
		pairs->print();
	}
};

