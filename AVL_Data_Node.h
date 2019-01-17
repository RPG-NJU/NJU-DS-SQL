#pragma once

#include <iostream>
#include "GRPVector.h"
#include "ID_Index_Node.h"
#include <cassert>

using std::ostream;

template <typename T>
class AVL_Data_Node;

template <typename T>
static bool operator< (const AVL_Data_Node<T> &x, const AVL_Data_Node<T> &y);
template <typename T>
static bool operator> (const AVL_Data_Node<T> &x, const AVL_Data_Node<T> &y);
template <typename T>
static bool operator== (const AVL_Data_Node<T> &x, const AVL_Data_Node<T> &y);
template <typename T>
static ostream& operator<< (ostream &os, const AVL_Data_Node<T> &x);
template <typename T>
class AVL_Data_Node
{
public:
	T value;
	GRPVector<ID_Index_Node> _index;

	//成员函数
	AVL_Data_Node(T value, ID_Index_Node a_index) : value(value) { _index.push_back(a_index); } //只有一个初始值的构造函数
	AVL_Data_Node(T value, int id, int index) : value(value) { const ID_Index_Node x(id, index); _index.push_back(x); /*cout << _index.size() << endl;*/ }

	void ReLoad(T value, int id, int index);

	void Add(ID_Index_Node x);

	friend bool operator> <T>(const AVL_Data_Node &x, const AVL_Data_Node &y);
	friend bool operator== <T>(const AVL_Data_Node &x, const AVL_Data_Node &y);
	//friend bool operator>= <T>(const AVL_Data_Node &x, const AVL_Data_Node &y) { return x == y || x > y; }
	friend bool operator< <T>(const AVL_Data_Node &x, const AVL_Data_Node &y);
	//friend bool operator<= <T>(const AVL_Data_Node &x, const AVL_Data_Node &y) { return x == y || x < y; }
	//friend bool operator!= <T>(const AVL_Data_Node &x, const AVL_Data_Node &y) { return !(x == y); }

	friend ostream& operator<< <T>(ostream &os, const AVL_Data_Node &x);
};


template <typename T>
bool operator>(const AVL_Data_Node<T> &x, const AVL_Data_Node<T> &y)
{
	return x.value > y.value;
}

template <typename T>
bool operator==(const AVL_Data_Node<T> &x, const AVL_Data_Node<T> &y)
{
	return x.value == y.value;
}

template <typename T>
bool operator< (const AVL_Data_Node<T> &x, const AVL_Data_Node<T> &y)
{
	return (!(x == y)) && (!(x > y));
}


template <typename T>
void AVL_Data_Node<T>::Add(const ID_Index_Node x)
{
	int i(_index.size() - 1);

	if (x > _index[i])
	{
		_index.push_back(x);
		return;
	}
	for (; i >= 0; --i)
	{
		if (x < _index[i])
		{
			_index.insert(i, x);
			return;
		}
		else if (x == _index[i])
		{
			return;
		}
	}
	//cout << _index[0] <<"-"<< _index[1] << endl;
	cout << "[" << x << " " << _index[0] <<"]"<< endl;
	assert(0);
}

template <typename T>
static ostream& operator<<(ostream &os, const AVL_Data_Node<T> &x)
{
	os << x.value << ":  ";
	for (int i(0); i < x._index.size(); ++i)
		os << "[" << x._index[i].id << " " << x._index[i].index << "] ";
	return os;
}

template <typename T>
void AVL_Data_Node<T>::ReLoad(T value, int id, int index)
{
	this->value = value;
	const ID_Index_Node x(id, index); 
	_index[0] = x;
	return;
}
