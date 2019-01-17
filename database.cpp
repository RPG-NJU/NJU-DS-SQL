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

void MyDatabase::Insert(int i, Command& command)
{
	switch (i)
	{
	case 1:table1.Insert_Data(command); break;
	case 2:table2.Insert_Data(command); break;
	default:break;
	}
}

void MyDatabase::Delete(int i, Command& command)
{
	switch (i)
	{
	case 1:table1.Delete_Data(command); break;
	case 2:table2.Delete_Data(command); break;
	default:break;
	}
}

void MyDatabase::Set(int i, Command& command)
{
	switch(i)
	{
	case 1:table1.Set_Data(command); break;
	case 2:table2.Set_Data(command); break;
	default:break;
	}
}

void MyDatabase::Add(int i, Command& command)
{
	switch(i)
	{
	case 1:break;
	case 2:break;
	default:break;
	}
}


