#include "vector.h"
#include "contact.h"
#include <iostream>

using namespace std;

template<typename T> MyVector<T>::MyVector() : data(new T[0]), v_size(0), v_capacity(0) {} //creates empty vector with default capacity of 0

template<typename T> MyVector<T>::MyVector(int cap) : data(new T[cap]), v_capacity(cap), v_size(0) {} //constructor for vector with capacity of cap 

template<typename T> MyVector<T>::~MyVector() //destructor to avoid memory leak
{
	delete[] data; 
}
//=======================================================================
template <typename T> void MyVector<T>::push_back(T element) //adds element to the end
{
	if (capacity() <=  size()) //just in case adding new element exceeds capacity
	{
		T* myvector;
		if (v_capacity != 0) 
		{
			myvector = new T[2 * v_capacity]; //double the size
			v_capacity = 2 * v_capacity; 
		}
		else //dealing with special case where capacity is 0
		{
			myvector = new T[1]; //create a new vector with size 1
			v_capacity = 1;
		}
		for (int i = 0; i < v_size; i++)
		{
			myvector[i] = data[i]; //shift all elements to the new larger vector
		}

		if (data != NULL)
		{
			delete[] data; 
		}
		data = myvector; //assigning the reference to data so that we can continue using that name
	}

	data[v_size] = element; //push element to the end
	v_size += 1; //increment size
}
//=======================================================================
template<typename T> void MyVector<T>::insert(int index, T element) //insert at a particular index
{
	if (index > v_size - 1)
	{
		throw out_of_range("Index out of range"); //ensuring the index input is valid
	}
	else
	{
		if (capacity() <= size()) //check to see if vector full
		{
			//same as push_back
			T* myvector;
			if (v_capacity != 0)
			{
				myvector = new T[2 * v_capacity];
				v_capacity = 2 * v_capacity;
			}
			else
			{
				myvector = new T[1];
				v_capacity = 1;
			}
			for (int i = 0; i < v_size; i++)
			{
				myvector[i] = data[i];
			}

			if (data != NULL)
			{
				delete[] data;
			}
			data = myvector;
		}
	}
	//shift all elements after the index to the right to accomodate new element
	for (int j = v_size -1; j >= index; j--)
	{
		data[j + 1] = data[j]; 
	}

	data[index] = element; //add element to the index
	v_size += 1;

}
//=======================================================================
template<typename T> void MyVector<T>::erase(int index) //removes element at index
{
	if (index < 0) //ensuring index input is correct
	{
		throw out_of_range("Index out of range");
	}
	else if (index > v_size - 1)
	{
		throw out_of_range("Index out of range");
	}
	
	for (int j = index; j < v_size - 1; j++) //overwriting the element at index and shifting all further elements to the left
	{
		data[j] = data[j + 1];
	}

	v_size -= 1;
}
//=======================================================================
template<typename T> T& MyVector<T>::at(int index)
{
	if (index >= 0 && index <= v_capacity)
	{
		if (index < v_size) //checking to see if the index added is not after the last element
		{
			return data[index];
		}
		else
		{
			throw out_of_range("Empty index location");
		}
	}
	else
	{
		throw out_of_range("Index out of range"); 
	}
}
//=======================================================================
template<typename T> const T& MyVector<T>::front() //returns front
{
	if (v_size != 0) //makes sure the vector is not of size 0 i.e is empty
	{
		return data[0];
	}
	else
	{
		throw out_of_range("No elements stored");
	}
}
//=======================================================================
template<typename T> const T& MyVector<T>::back() //returns back
{
	if (v_size != 0) //same as front
	{
		return data[v_size - 1];
	}
	else
	{
		throw out_of_range("No elements stored");
	}
}
//=======================================================================
template<typename T> int MyVector<T>::size() const
{
	return v_size; //returns the number of elements in a vector
}
//=======================================================================
template<typename T> int MyVector<T>::capacity() const
{
	return v_capacity; //returns the capcity of vector
}
//=======================================================================
template<typename T> bool MyVector<T>::empty() const
{
	if (v_size == 0) //if there are no elements in the vector then the vector is empty
	{
		return true; 
	}
	else
	{
		return false; 
	}
}

//=======================================================================
template class MyVector<Contact>;