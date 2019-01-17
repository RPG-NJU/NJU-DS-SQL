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
	case 3:table3.Read_Key_List(key_list); break;
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
	case 3:table3.Read_Data(file); break;
	default:break;
	}
}

void MyDatabase::Read_Table_Name(int i, string table_name)
{
	switch (i)
	{
	case 1:table1.Read_Table_Name(table_name); break;
	case 2:table2.Read_Table_Name(table_name); break;
	case 3:table3.Read_Table_Name(table_name); break;
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
	switch (i)
	{
	case 1:table1.Set_Data(command); break;
	case 2:table2.Set_Data(command); break;
	default:break;
	}
}

void MyDatabase::Add(int i, Command& command)
{
	switch (i)
	{
	case 1:table1.Add_Data(command); break;
	case 2:table2.Add_Data(command); break;
	default:break;
	}
}

void MyDatabase::Query(int i, Command& command, ofstream& file)
{
	switch (i)
	{
	case 1:table1.Query_Data(command, file); break;
	case 2:table2.Query_Data(command, file); break;
	default:break;
	}
}


void MyDatabase::SUM(int i, Command& command, ofstream& file)
{
	switch (i)
	{
	case 1:table1.Sum_Data(command, file); break;
	case 2:table2.Sum_Data(command, file); break;
	default:break;
	}
}

void MyDatabase::Inter(Command& command, ofstream& file)
{
	const string x1(command.argv[1]);
	const string x2(command.argv[2]);

	if (x1 == table1.Name())
	{
		/*const AVL_Data_Node<int> begin_data(INT32_MIN, 0, 0);
		const AVL_Data_Node<int> end_data(INT32_MAX, 0, 0);
		BinNode<AVL_Data_Node<int> > *begin_node = table1.id_tree.search(begin_data);
		if (begin_node == nullptr)
		{
			begin_node = table1.id_tree._hot;
			cout << table1.id_tree._hot << endl;
		}
		BinNode<AVL_Data_Node<int> > *end_node = table1.id_tree.search(end_data);
		if (end_node == nullptr)
		{
			end_node = table1.id_tree._hot;
		}*/
		cout << table1.data.size() << endl;
		for (int i(0); i < table1.data.size(); ++i)
		{


			const string name = table1.data[i].name; //获取名字
			AVL_Data_Node<string> name_node(name, 0, 0);
			if (table1.name_tree.search(name_node)->data._index[0].index == i)
			{
				if (table2.name_tree.search(name_node))
					file << table1.data[i].name << endl;
			}
			//cout << "?" << endl;
		}
	}
	else
	{
		for (int i(0); i < table2.data.size(); ++i)
		{

			const string name = table2.data[i].name; //获取名字
			AVL_Data_Node<string> name_node(name, 0, 0);
			if (table2.name_tree.search(name_node)->data._index[0].index == i)
			{
				if (table1.name_tree.search(name_node))
					file << table2.data[i].name << endl;
			}


		}
	}
#ifdef RUN_COMMAND_SHOW
	printf(LIGHT_BLUE "<INTER> OVER\n" NONE);
#endif
}
