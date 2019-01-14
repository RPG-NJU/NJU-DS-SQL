#include "database.h"


//class MyDatabase{
//    //TODO
//    //do what you want to.
//    int haha;
//};

//定义转至头文件中

void MyDatabase::Read_Key_List(int i, string key_list)
{
	switch (i)
	{
	case 1:table1.Read_Key_List(key_list); break;
	case 2:table2.Read_Key_List(key_list); break;
	default:break;
	}
	return;
}

void MyDatabase::Read_Data(int i, ifstream& file)
{
	switch (i)
	{
	case 1:table1.Read_Data(file); break;
	case 2:table2.Read_Data(file); break;
	default:break;
	}
}

void MyDatabase::Read_Table_Name(int i, string table_name)
{
	switch (i)
	{
	case 1:table1.Read_Table_Name(table_name); break;
	case 2:table2.Read_Table_Name(table_name); break;
	default:break;
	}
}


