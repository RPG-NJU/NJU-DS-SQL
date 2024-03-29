#pragma once

#include "common.h"
#include "GRPVector.h" //引入模板，其中是vector的自我定义
#include <string>
//#include <fstream>

#include "Table.h"

//using std::ifstream;

//class MyDatabase;

extern int TEST_TYPE;
/*
 * 根据不同的TEST_TYPE指定选择不同的数据结构进行实现
 * TEST_TYPE = 0，
 */

class MyDatabase 
{
	//TODO
	//do what you want to.
	//int haha;
	//这里需要一些数据结构来完成整个数据库的构建
public:
	Table table1;
	Table table2;
	Table table3;

	
public:
	int now_table = 1;
	void Read_Key_List(int i, string key_list);
	void Read_Data(int i, ifstream &file);
	void Read_Table_Name(int i, string table_name);

	void Insert(int i, Command &command);
	void Delete(int i, Command &command);
	void Set(int i, Command &command);
	void Add(int i, Command &command);
	void Query(int i, Command &command, ofstream &file);
	void SUM(int i, Command &command, ofstream &file);
	void Inter(Command &command, ofstream &file);
	void Union(Command &command, ofstream &file);
};