#pragma once
#include "GRPVector.h" //引入Vector用于存储数据
#include "Define.h"
#include <fstream>
#include <sstream>
#include "AVL.h"
#include "common.h"
//#include "AVL.h"
#include "AVL_Data_Node.h"
#include <algorithm>

using std::sort;
using std::stable_sort;

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
	friend class MyDatabase;
public:
	string table_name; //数据表的名称，从文件的第一行读入
	GRPVector<string> key; //每一个属性的名称
	GRPVector<Data> data; //数据表

	//搜索树结构，一共种类型的树，用于区分不同的基本类型
	AVL<AVL_Data_Node<int> > id_tree;
	AVL<AVL_Data_Node<string> > name_tree;
	GRPVector<AVL<AVL_Data_Node<int> > > value_tree;
	//搜索树结构END

	Data ERROR; //代表获取data失败
public:
	Table(string table_name);
	Table();
	~Table() {}
	void Read_Table_Name(string table_name); //读取表名
	void Read_Key_List(string key_list); //读取文件的属性列表
	void Read_Data(std::ifstream &file); //读取所有需要的数据

	//一部分功能函数定义在这里
	Data& Get_Data_By_ID(const int &id);
	int Get_Key_Index(const string &key_name);
	//void printf
	void Equal_Data(BinNode<AVL_Data_Node<int> > *&find_result, ofstream &file);
	void After_Data(BinNode<AVL_Data_Node<int> > *begin_node, ofstream &file/*, const int &value_index*/);
	void Before_Data(BinNode<AVL_Data_Node<int> > *begin_node, BinNode<AVL_Data_Node<int> > *end_node, ofstream &file/*, const int &value_index*/);
	void Equal_Data_Section(BinNode<AVL_Data_Node<int> > *&find_result, ofstream &file, int l, int r);
	void After_Data_Section(BinNode<AVL_Data_Node<int> > *begin_node, ofstream &file, int l, int r);
	void Before_Data_Section(BinNode<AVL_Data_Node<int> > *begin_node, BinNode<AVL_Data_Node<int> > *end_node, ofstream &file, int l, int r);
	//END


	void Insert_Data(Command &command);
	void Delete_Data(Command &command);
	void Set_Data(Command &command);
	void Add_Data(Command &command);
	void Query_Data(Command &command, ofstream &file);
	void Sum_Data(Command &command, ofstream &file);

	

	//下面需要维护搜索树的结构
	void AVL_Insert_Data(const Data &data, const int &index);
	void AVL_Reset_Data(/*const */Data &data, const int &new_value, const int &value_index); //对于value树，有些时候需要重设节点的位置，比如SET操作
	void test1();
	void test2();

	string Name() { return table_name; }
};