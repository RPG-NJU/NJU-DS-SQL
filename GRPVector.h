//#pragma once
#ifndef GRP_VECTOR
#define GRP_VECTOR

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;



#define GRP_VECTOR_DEFAULTSIZE 1 //将默认长度更改为1，模改

template <typename T>
class GRPVector
{
protected:
	T *data;
	size_t max_size;
	size_t real_size;
public:
	GRPVector();
	GRPVector(const GRPVector &x);
	~GRPVector();

	void push_back(const T &input);
	void pop_back();
	size_t size() const;
	bool empty() const;
	void clear();

	const T front();
	T& back();
	T& operator[](int i);
	const T& operator[](int i) const;

	void insert(int i, const T &add);
	void erase(int i);

	int find(T which) const;//寻找某元素，返回它的索引

	GRPVector& operator=(const GRPVector& copy);
};

template <typename T>
GRPVector<T>::GRPVector() : data(new T[GRP_VECTOR_DEFAULTSIZE]), max_size(GRP_VECTOR_DEFAULTSIZE), real_size(0) {}

template <typename T>
GRPVector<T>::~GRPVector()
{
	delete[] data;//将动态数组归还
	//更正，动态数组会自动归还
}


template <typename T>
size_t GRPVector<T>::size() const
{
	return real_size;
}

template <typename T>
bool GRPVector<T>::empty() const
{
	return real_size == 0;
}

template <typename T>
void GRPVector<T>::clear()
{
	real_size = 0;
	return;
}



template <typename T>
void GRPVector<T>::push_back(const T &input)
{
	if (real_size == max_size)
	{
		T *old = data;
		data = new T[2 * max_size];//开一个扩容一倍的数组
		for (size_t i(0); i < max_size; ++i)
		{
			data[i] = old[i];
		}
		max_size *= 2;//将扩容反馈
		//cout << old[0] << endl;
		delete[] old; //新增加，将旧空间归还		
	}
	//无论需不需要扩容，后续的过程是一样的
	data[real_size] = input;
	++real_size;
	return;
}

template <typename T>
void GRPVector<T>::pop_back()
{
	//现如今没有打算完成可以自动减少长度的功能
	--real_size;//直接将最后的标识向前即可，这样子就可以避免访问
	return;
}

template <typename T>
T& GRPVector<T>::operator[](int i)
{
	//cout << -static_cast<int>(real_size) << endl;
	//cout << (i >= -static_cast<int>(real_size)) << endl;
	if ((i < static_cast<int>(real_size)) && (i >= -static_cast<int>(real_size)))
	{
		if (i >= 0)
			return data[i];
		else
			return data[this->size() + i];
	}

	else
	{
		cout << "This GRPVector's size is " << real_size << endl;
		cout << "You should not read the place [" << i << "]" << endl;
		exit(-1);
	}
}

template <typename T>
const T& GRPVector<T>::operator[](int i) const
{
	if ((i < static_cast<int>(real_size)) && (i >= -static_cast<int>(real_size)))
	{
		if (i >= 0)
			return data[i];
		else
			return data[this->size() + i];
	}

	else
	{
		cout << "This GRPVector's size is " << real_size << endl;
		cout << "You should not read the place [" << i << "]" << endl;
		exit(-1);
	}
}


template <typename T>
const T GRPVector<T>::front()
{
	T x = data[0];
	//return (*this)[0];
	return x;
}

template <typename T>
T& GRPVector<T>::back()
{
	return (*this)[this->size() - 1];
}

template <typename T>
void GRPVector<T>::insert(int i, const T& add)
{
	if (i < real_size)
	{
		this->push_back(this->back());//将最后一位的数据在填充一次，供扩展
		//++real_size;
		for (int j(i); j < real_size - 1; ++j)
		{
			(*this)[j + 1] = (*this)[j];
		}
		(*this)[i] = add;
	}
	else
	{
		cout << "GRPVector的总长度为" << real_size << "，不能在[" << i << "]处插入元素" << endl;
	}
	return;
}

template <typename T>
void GRPVector<T>::erase(int i)
{
	if (i < real_size)
	{
		for (int j(i); j < real_size - 1; ++j)
		{
			//(*this)[j] = (*this)[j + 1];
			data[j] = data[j + 1]; //2019.1.16 UPDATE 减少函数的调用可以加快一定的运行速度，但是复杂化了代码
		}
		this->pop_back();
		//--real_size; //2019.1.16 DEBUG 此处应该更改大小，同步
	}
	else
	{
		cout << "GRPVector的总长度为" << real_size << "，不能在删除[" << i << "]元素" << endl;
	}
	return;
}


template <typename T>
int GRPVector<T>::find(T which) const
{
	for (int i(0); i < real_size; ++i)
	{
		if (data[i] == which)
			return i;
	}
	return -1;//作为无此元素的标志
}



template <typename T>
GRPVector<T>& GRPVector<T>::operator=(const GRPVector& copy)
{
	this->clear();
	this->data = new T[copy.max_size];
	for (int i(0); i < copy.size(); ++i)
	{
		//this->push_back(copy[i]);
		this->data[i] = copy.data[i];
	}
	this->real_size = copy.real_size;
	this->max_size = copy.max_size;
	return *this;
}

template <typename T>
GRPVector<T>::GRPVector(const GRPVector& x)
{
	/*this->clear();
	for (int i(0); i < x.size(); ++i)
	{
		this->push_back(x[i]);
	}*/
	this->data = new T[x.max_size];
	for (int i(0); i < x.size(); ++i)
	{
		//this->push_back(copy[i]);
		this->data[i] = x.data[i];
	}
	this->real_size = x.real_size;
	this->max_size = x.max_size;
	//return *this;
	//return *this;
}

#endif
