//
// Created by mpampis on 1/5/2017.
//

#ifndef HARRY_POTTER_ARRAYLIST_H
#define HARRY_POTTER_ARRAYLIST_H

#include <iostream>
#include <sstream>
#include "../Errors/IndexOutOfBoundsException.h"
#define DEFAULT_CAPACITY 4

template <class Item>
class ArrayList {
public:

	ArrayList() {
		arr = new Item[DEFAULT_CAPACITY];
		capacity = DEFAULT_CAPACITY;
		size = 0;
	}

	~ArrayList() {
		delete[] arr;
	}

	void add(Item item) {
		if (size == capacity) {
			resizeCapacity(capacity * 2);
		}

		arr[size++] = item;
	}

	void add(int index, Item item) {
		rangeCheck(index);

		if (size == capacity) {
			resizeCapacity(capacity * 2);
		}

		shiftRight(index, size - 1);
		set(index, item);
		size++;
	}

	void clear() {
		delete[] arr;
		arr = new Item[DEFAULT_CAPACITY];
	}

	Item& get(int index) {
		rangeCheck(index);
		return arr[index];
	}

	Item& operator[](int index) {
		return get(index);
	}

	int indexOf(const Item& item) {
		for (int i = 0; i < size; i++) {
			if (item == arr[i]) {
				return  i;
			}
		}

		return -1;
	}

	bool isEmpty() {
		return size == 0;
	}

	Item remove(int index) {
		rangeCheck(index);

		Item oldValue = arr[index];

		shiftLeft(index + 1, size - 1);

		size--;

		if (size > 0 && size == capacity / 4) {
			resizeCapacity(capacity / 4);
		}

		return oldValue;
	}


	void set(int index, Item item) {
		rangeCheck(index);

		arr[index] = item;
	}

	int getSize() {
		return size;
	}

	Item* toArray() {
		Item* newArr = new Item[size];
		copy(arr, 0, newArr, 0, size);

		return newArr;
	}

	std::string toString() {
		std::ostringstream str;
		str << '[';
		for (int i = 0; i < size - 1; i++) {
			str << arr[i] << ", ";
		}

		str << arr[size - 1] << ']';

		return str.str();
	}
	
	
	ArrayList<Item>* clone() {
		ArrayList<Item>* newList = new ArrayList<Item>();
		for (int i = 0; i < size; i++) {
			newList->add(arr[i]);
		}

		return newList;
	}

private:

	void resizeCapacity(int newCapacity) {
		Item* newArr = new Item[newCapacity];
		copy(arr, 0, newArr, 0, size);
		delete[] arr;
		arr = newArr;
		capacity = newCapacity;
	}

	void shiftLeft(int indexLow, int indexHigh) {
		if (indexLow == 0) {
			return;
		}

		for (int i = indexLow; i <= indexHigh; i++) {
			arr[i - 1] = arr[i];
		}
	}

	void shiftRight(int indexLow, int indexHigh) {
		if (capacity == size) {
			resizeCapacity(capacity * 2);
		}

		for (int i = indexHigh; i >= indexLow; i--) {
			arr[i + 1] = arr[i];
		}
	}

	void rangeCheck(int index) {
		if (index < 0 || index >= size) {
			throw makeOutOfIndexException(index, size);
		}
	}

	IndexOutOfBoundsException makeOutOfIndexException(int index, int size) {
		std::ostringstream str;
		str << "IndexOutOfBoundsException: Index: " << index << ", Size: " << size;

		return IndexOutOfBoundsException(str.str());
	}

	template<class T>
	void copy(T* src, int srcPos, T* dest, int destPos, int length) {
		for (int i = 0; i < length; i++) {
			dest[destPos++] = src[srcPos++];
		}
	}

	Item* arr;
	int capacity;
	int size;
};

#endif //HARRY_POTTER_ARRAYLIST_H
