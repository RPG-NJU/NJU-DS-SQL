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

MyDatabase SQL; //定义全局变量，方便使用

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
	SQL.Read_Table_Name(1, get_data); //获取表名
	/*cout << get_data << endl;*/
	getline(data_file, get_data);
	SQL.Read_Key_List(1, get_data); //获取属性列表

	//get_data.clear();
	//getline(data_file, get_data);
	//while(!get_data.empty())
	//{
	//	//
	//	cout << get_data << endl;
	//	get_data.clear();
	//	getline(data_file, get_data);
	//}

	SQL.Read_Data(1, data_file);

}

int TEST_TYPE = 0; //根据不同的type进行不同的数据结构操作   [拟定]


int main(int argc, char const *argv[])
{
    /* code */
    Timer timer;
    timer.tic("All");

	//printf(LIGHT_BLUE "%s\n" NONE, "<GRP DS-SQL>");

    SingleTester single_tester("single.txt", "result_single.txt");
    /*SectionTester section_tester1("section1.txt", "result_section1.txt");
    SectionTester section_tester2("section2.txt", "result_section2.txt");
    SetTester set_tester("set.txt", "result_set.txt");*/
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
    //TEST_TYPE = 1;
    //loadData("data_section1.txt");
    //INFO("=====================================");
    //section_tester1.exec();
    //INFO("=====================================\n");

    ////区间测试2
    //TEST_TYPE = 2;
    //loadData("data_section2.txt");
    //INFO("=====================================");
    //section_tester2.exec();
    //INFO("=====================================\n");

    ////集合测试
    //TEST_TYPE = 3;
    //loadData("data_set1.txt");
    //loadData("data_set2.txt");
    //INFO("=====================================");
    //set_tester.exec();
    //INFO("=====================================\n");

    timer.toc();
    INFO("You are a genius!");
    
    return 0;
}



