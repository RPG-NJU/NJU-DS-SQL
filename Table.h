#pragma once
#include "GRPVector.h" //引入Vector用于存储数据
#include "Define.h"
#include <fstream>
#include <sstream>


struct Data //该类型用于存储每一条数据
{
	int id;
	string name;
	GRPVector<int> value;
	Data() : id(0), name("") {}
};

class Table
{
private:
	string table_name; //数据表的名称，从文件的第一行读入
	GRPVector<string> key; //每一个属性的名称
	GRPVector<Data> data; //数据表
public:
	Table(string table_name);
	Table();
	~Table() {}
	void Read_Table_Name(string table_name); //读取表名
	void Read_Key_List(string key_list); //读取文件的属性列表
	void Read_Data(std::ifstream &file); //读取所有需要的数据

};