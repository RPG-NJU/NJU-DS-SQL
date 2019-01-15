#pragma once
#include "GRPVector.h" //引入Vector用于存储数据
#include "Define.h"
#include <fstream>
#include <sstream>
#include "AVL.h"
//#include "AVL.h"
#include "AVL_Data_Node.h"

struct Data;

ostream& operator<<(ostream &os, Data data);
std::ofstream& operator<<(std::ofstream &file, Data data);

struct Data //该类型用于存储每一条数据
{
	bool valid; //标志位，表示该条数据是否有效，用于[假删除]
	int id;
	string name;
	GRPVector<int> value;
	Data() : id(0), name(""), valid(true) {}
};

class Table
{
private:
	string table_name; //数据表的名称，从文件的第一行读入
	GRPVector<string> key; //每一个属性的名称
	GRPVector<Data> data; //数据表

	//搜索树结构，一共种类型的树，用于区分不同的基本类型
	AVL<AVL_Data_Node<int> > id_tree;
	AVL<AVL_Data_Node<string> > name_tree;
	GRPVector<AVL<AVL_Data_Node<int> > > value_tree;
	//搜索树结构END
public:
	Table(string table_name);
	Table();
	~Table() {}
	void Read_Table_Name(string table_name); //读取表名
	void Read_Key_List(string key_list); //读取文件的属性列表
	void Read_Data(std::ifstream &file); //读取所有需要的数据

	//下面需要维护搜索树的结构
	void AVL_Insert_Data(const Data &data, const int &index);
	void test1();
	void test2();
};