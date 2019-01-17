#include "common.h"
#include "test.h"
#include "database.h"

#include "Define.h"
#include "Table.h"
#include "AVL.h"
#include "Value_ID_Index_Node.h"
#include "ID_Index_Node.h"
#include "AVL_Data_Node.h"


/*
 * 本实验使用Visual Studio环境进行编写
 * 实验开始时间，2019.1.11
 * 文件中的框架代码由助教提供
 * 从文件中读入数据和操作指令
 *
 * 相关要求以及答疑：
 * 1.文件不用回写
 * 2.只需要填写文件中的TODO部分，而其余部分可以不做修改
 *
 */

MyDatabase SQL4;
MyDatabase SQL3;
MyDatabase SQL2;
MyDatabase SQL1;
MyDatabase SQL0; //定义全局变量，方便使用

const int one = 1;
const int two = 2;
template <typename T>
void cout_T(T data)
{
	cout << data << endl;
}

void helper(Command &command, ofstream &file)
{
	//TODO
	//recognize and execute command 识别并且执行命令
	//INFO("hehe");
	if (TEST_TYPE == 0)
	{
		const string first_command_word(command.argv[0]);
		if (first_command_word == "INSERT")
			SQL0.Insert(1, command);
		else if (first_command_word == "DELETE")
			SQL0.Delete(1, command);
		else if (first_command_word == "SET")
			SQL0.Set(1, command);
		else if (first_command_word == "ADD")
			SQL0.Add(1, command);
		else if (first_command_word == "QUERY")
			SQL0.Query(1, command, file);
		else
			printf(LIGHT_RED "<CANNOT DO THIS COMMAND>\n" NONE);
	}
	else if (TEST_TYPE == 1)
	{
		const string first_command_word(command.argv[0]);
		if (first_command_word == "INSERT")
			SQL1.Insert(1, command);
		else if (first_command_word == "DELETE")
			SQL1.Delete(1, command);
		else if (first_command_word == "SET")
			SQL1.Set(1, command);
		else if (first_command_word == "ADD")
			SQL1.Add(1, command);
		else if (first_command_word == "QUERY")
			SQL1.Query(1, command, file);
		else if (first_command_word == "SUM")
			SQL1.SUM(1, command, file);
		else
			printf(LIGHT_RED "<CANNOT DO THIS COMMAND>\n" NONE);
	}
	else if (TEST_TYPE == 2)
	{
		const string first_command_word(command.argv[0]);
		if (first_command_word == "INSERT")
			SQL2.Insert(1, command);
		else if (first_command_word == "DELETE")
			SQL2.Delete(1, command);
		else if (first_command_word == "SET")
			SQL2.Set(1, command);
		else if (first_command_word == "ADD")
			SQL2.Add(1, command);
		else if (first_command_word == "QUERY")
			SQL2.Query(1, command, file);
		else if (first_command_word == "SUM")
			SQL2.SUM(1, command, file);
		else
			printf(LIGHT_RED "<CANNOT DO THIS COMMAND>\n" NONE);
	}
	else if (TEST_TYPE == 3)
	{
		const string first_command_word(command.argv[0]);
		if (first_command_word == "INSERT")
			SQL3.Insert(1, command);
		else if (first_command_word == "DELETE")
			SQL3.Delete(1, command);
		else if (first_command_word == "SET")
			SQL3.Set(1, command);
		else if (first_command_word == "ADD")
			SQL3.Add(1, command);
		else if (first_command_word == "QUERY")
			SQL3.Query(1, command, file);
		else if (first_command_word == "SUM")
			SQL3.SUM(1, command, file);
		else if (first_command_word == "INTER")
		{
			/*SQL3.Inter(command, file);*/
			const string x1(command.argv[1]);
			const string x2(command.argv[2]);

			if (x1 == SQL3.table1.Name())
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
				//cout << SQL3.table1.data.size() << endl;
				for (int i(0); i < SQL3.table1.data.size(); ++i)
				{


					const string name = SQL3.table1.data[i].name; //获取名字
					AVL_Data_Node<string> name_node(name, 0, 0);
					if (SQL3.table1.name_tree.search(name_node)->data._index[0].index == i)
					{
						if (SQL4.table1.name_tree.search(name_node))
							file << SQL3.table1.data[i].name << endl;
					}
					//cout << "?" << endl;
				}
			}
			else
			{
				for (int i(0); i < SQL4.table1.data.size(); ++i)
				{

					const string name = SQL4.table1.data[i].name; //获取名字
					AVL_Data_Node<string> name_node(name, 0, 0);
					if (SQL4.table1.name_tree.search(name_node)->data._index[0].index == i)
					{
						if (SQL3.table1.name_tree.search(name_node))
							file << SQL4.table1.data[i].name << endl;
					}


				}
			}
#ifdef RUN_COMMAND_SHOW
			printf(LIGHT_BLUE "<INTER> OVER\n" NONE);
#endif
		}
		else if (first_command_word == "UNION")
		{
			const string x1(command.argv[1]);
			const string x2(command.argv[2]);

			if (x1 == SQL3.table1.Name())
			{
				//cout << SQL3.table1.data.size() << endl;
				for (int i(0); i < SQL3.table1.data.size(); ++i)
				{
					const string name = SQL3.table1.data[i].name; //获取名字
					AVL_Data_Node<string> name_node(name, 0, 0);
					if (SQL3.table1.name_tree.search(name_node)->data._index[0].index == i)
					{
						file << SQL3.table1.data[i].name << endl;
					}
				}
				for (int i(0); i < SQL4.table1.data.size(); ++i)
				{
					const string name = SQL4.table1.data[i].name; //获取名字
					AVL_Data_Node<string> name_node(name, 0, 0);
					if (SQL4.table1.name_tree.search(name_node)->data._index[0].index == i && SQL3.table1.name_tree.search(name_node) == nullptr)
					{
						file << SQL4.table1.data[i].name << endl;
					}
				}
			}
			else
			{
				for (int i(0); i < SQL4.table1.data.size(); ++i)
				{
					const string name = SQL4.table1.data[i].name; //获取名字
					AVL_Data_Node<string> name_node(name, 0, 0);
					if (SQL4.table1.name_tree.search(name_node)->data._index[0].index == i)
					{
						file << SQL4.table1.data[i].name << endl;
					}
				}
				for (int i(0); i < SQL3.table1.data.size(); ++i)
				{
					const string name = SQL3.table1.data[i].name; //获取名字
					AVL_Data_Node<string> name_node(name, 0, 0);
					if (SQL3.table1.name_tree.search(name_node)->data._index[0].index == i && SQL4.table1.name_tree.search(name_node) == nullptr)
					{
						file << SQL3.table1.data[i].name << endl;
					}
				}
			}
#ifdef RUN_COMMAND_SHOW
			printf(LIGHT_BLUE "<UNION> OVER\n" NONE);
#endif
		}
		else
			printf(LIGHT_RED "<CANNOT DO THIS COMMAND>\n" NONE);
	}
}

void loadData(const char *file)
{
	//TODO
	//load data file 加载数据文件
	ifstream data_file;
	data_file.open(file);
#ifdef EVERY_STEP_SHOW
	if (data_file)
		printf(LIGHT_GREEN "<OPEN DATA FILE>  " NONE "%s\n", file);
	else
	{
		printf(LIGHT_RED "<DATA FILE OPEN FAIL>  " NONE "%s\n", file);
		exit(-1);
	}
#endif
	//确定文件打开成功
	string get_data;
	getline(data_file, get_data);
	if (TEST_TYPE == 0)
	{
		SQL0.Read_Table_Name(1, get_data); //获取表名
		/*cout << get_data << endl;*/
		getline(data_file, get_data);
		SQL0.Read_Key_List(1, get_data); //获取属性列表

		SQL0.Read_Data(1, data_file);
	}
	if (TEST_TYPE == 1)
	{
		SQL1.Read_Table_Name(1, get_data); //获取表名
		/*cout << get_data << endl;*/
		getline(data_file, get_data);
		SQL1.Read_Key_List(1, get_data); //获取属性列表

		SQL1.Read_Data(1, data_file);
	}
	if (TEST_TYPE == 2)
	{
		SQL2.Read_Table_Name(1, get_data); //获取表名
		/*cout << get_data << endl;*/
		getline(data_file, get_data);
		SQL2.Read_Key_List(1, get_data); //获取属性列表

		SQL2.Read_Data(1, data_file);
	}
	if (TEST_TYPE == 3)
	{
		//cout << SQL3.now_table << endl;
		//cout << "?" << endl;
		if (SQL3.now_table == 1)
		{
			SQL3.Read_Table_Name(1, get_data); //获取表名
			getline(data_file, get_data);
			SQL3.Read_Key_List(1, get_data); //获取属性列表

			SQL3.Read_Data(1, data_file);
			//cout << "?" << endl;
		}
		else
		{
			SQL4.Read_Table_Name(1, get_data); //获取表名
			getline(data_file, get_data);
			SQL4.Read_Key_List(1, get_data); //获取属性列表

			SQL4.Read_Data(1, data_file);
			data_file.close();
		}
	}
}

int TEST_TYPE = 0; //根据不同的type进行不同的数据结构操作   [拟定]


int main(int argc, char const *argv[])
{
	/* code */
	Timer timer;
	timer.tic("All");

	//printf(LIGHT_BLUE "%s\n" NONE, "<GRP DS-SQL>");

	SingleTester single_tester("single.txt", "result_single.txt");
	SectionTester section_tester1("section1.txt", "result_section1.txt");

	SectionTester section_tester2("section2.txt", "result_section2.txt");
	SetTester set_tester("set.txt", "result_set.txt");
	//
	//单点测试
	TEST_TYPE = 0;
	loadData("data_single.txt");
	INFO("=====================================");
	single_tester.exec();
	INFO("=====================================\n");

	//AVL<AVL_Data_Node<int> > test;
	//AVL_Data_Node<int> a(64, 234,1);
	//AVL_Data_Node<int> b(64, 237, 2);
	//AVL_Data_Node<int> c(23, 256, 3);
	//AVL_Data_Node<int> d(75, 222, 4);
	//AVL_Data_Node<int> e(64, 236, 5);
	//

	////cout << "?" << endl;
	//test.insert(a);
	//test.insert(b);
	//test.insert(c);
	//test.insert(d);
	//test.insert(e);
	//
	//test.travIn(cout_T<AVL_Data_Node<int> >); cout << endl;
	//cout << "!" << endl;
	//cout<<test.search()
	//test.remove(27);
	//test.travIn(cout_T<int>); cout << endl;
	////区间测试1
	TEST_TYPE = 1;
	loadData("data_section1.txt");
	INFO("=====================================");
	section_tester1.exec();
	INFO("=====================================\n");

	////区间测试2
	TEST_TYPE = 2;
	loadData("data_section2.txt");
	INFO("=====================================");
	section_tester2.exec();
	INFO("=====================================\n");

	////集合测试
	TEST_TYPE = 3;
	loadData("data_set1.txt");
	SQL3.now_table = 2;
	loadData("data_set2.txt");
	INFO("=====================================");
	set_tester.exec();
	INFO("=====================================\n");

	timer.toc();
	INFO("You are a genius!");

	return 0;
}



