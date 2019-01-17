#pragma once

#include <iostream>

using std::ostream;

class ID_Index_Node;

bool operator>(const ID_Index_Node &x, const ID_Index_Node &y);
bool operator==(const ID_Index_Node &x, const ID_Index_Node &y);
bool operator>=(const ID_Index_Node &x, const ID_Index_Node &y);
bool operator<(const ID_Index_Node &x, const ID_Index_Node &y);
bool operator<=(const ID_Index_Node &x, const ID_Index_Node &y);
bool operator!=(const ID_Index_Node &x, const ID_Index_Node &y);
static ostream& operator<<(ostream &os, const ID_Index_Node &x);

class ID_Index_Node //因为没有了value，所以不需要使用模板类，但是仍然都在头文件中定义，保持自定义节点类的统一性
{
public:
	int id; //键值
	//T value; //value可能为name的string，所以使用模板类进行
	int index;
	//两个个数据组成了一个节点的数据组
	//大小的比较应该只与id有关，而与index无关

	ID_Index_Node(int id, int index) : id(id), index(index) {}
	ID_Index_Node() : ID_Index_Node(0, 0) {}
	friend bool operator>(const ID_Index_Node &x, const ID_Index_Node &y) { return x.id > y.id; }
	friend bool operator==(const ID_Index_Node &x, const ID_Index_Node &y) { return x.id == y.id; }
	friend bool operator>=(const ID_Index_Node &x, const ID_Index_Node &y) { return x == y || x > y; }
	friend bool operator<(const ID_Index_Node &x, const ID_Index_Node &y) { return (!(x == y)) && (!(x > y)); }
	friend bool operator<=(const ID_Index_Node &x, const ID_Index_Node &y) { return x == y || x < y; }
	friend bool operator!=(const ID_Index_Node &x, const ID_Index_Node &y) { return !(x == y); }

	friend ostream& operator<<(ostream &os, const ID_Index_Node &x);
};

static ostream& operator<<(ostream& os, const ID_Index_Node& x)
{
	os << "[" << x.id << " " << x.index << "]";
	return os;
}
