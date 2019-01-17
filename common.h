#pragma once

#include <iostream>
#include <fstream>
#include <assert.h>
#include <cstring>
#include <time.h>

//using namespace std;

#define MAX_COL_SIZE 10
#define MAX_ATTR_LEN 30
#define MAX_COMMAND_SEG 20
#define MAX_COMMAND_SEG_LEN 20

using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::string;
using std::endl;

#pragma warning(disable:4996) // 由于在VS环境下编译，依照助教的指示，添加此条

class Record //由于与自己的思想不是非常的契合，目前该类处于弃置状态
{
	static int attrc;
	static char attr_name[MAX_COL_SIZE][MAX_ATTR_LEN];

public:
	char *attrv[MAX_COL_SIZE];
	//TODO 
	//realize get and set attr; 实现get和set attr
	static int getAttr(char attrs[][MAX_ATTR_LEN]); //get attribute per record 获取每条记录的属性
	static bool setAttr(int num_attr, const char attrs[][MAX_ATTR_LEN]); //set attribute for record before reading records 在读取记录之前设置记录的属性
	Record();
	~Record();
	friend ifstream & operator >> (ifstream &input, Record &record);
};

class Command 
{
public:
	int argc; //指令词的个数
	char *argv[MAX_COMMAND_SEG]; //指令词的最大个数
	Command();
	~Command();
	friend ifstream & operator >> (ifstream &input, Command &command);
};

static ifstream & operator >> (ifstream &input, Record &record); //这段函数的重载意义与command的重载类似，但是代码中没有进行使用，而是自己进行拆分，具体在Table类中有定义
ifstream & operator >> (ifstream &input, Command &command); //在助教提供的框架代码中直接使用了这一段重载，故没有进行更改

void INFO(const char* msg);
void helper(Command &command, ofstream &file);
void loadData(char *datafile);