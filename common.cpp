#include "common.h"
#include <cstring>
#include <assert.h>

#include "Define.h"


void INFO(const char* msg) // 封装cout endl
{
	cout << msg << endl;
}


int Record::attrc = 0;
char Record::attr_name[MAX_COL_SIZE][MAX_ATTR_LEN] = { '\0' };

Record::Record() { attrc = 0; }

Record::~Record() {
	for (int i = 0; i < attrc; i++) {
		delete[] attrv[i];
	}
}

ifstream & operator >> (ifstream &input, Record &record) {
	assert(record.attrc > 0 || (INFO("attributes should be set first."), 0));

	char tmp[MAX_ATTR_LEN * MAX_COL_SIZE], *p;
	const char * dlim = " ,:";
	int i = 0;
	input.getline(tmp, MAX_ATTR_LEN*MAX_COL_SIZE);
	p = strtok(tmp, dlim);
	while (p) 
	{
		record.attrv[i] = new char[MAX_ATTR_LEN];
		strcpy(record.attrv[i++], p);
		p = strtok(NULL, dlim);
	}

	assert(i == record.attrc || (INFO("attributes per record should be equal."), 0));
	return input;
}


Command::Command() { argc = 0; }

Command::~Command() {
	for (int i = 0; i < argc; i++) {
		delete[] argv[i];
	}
}

ifstream & operator >> (ifstream &input, Command &command) //Command类重载>>操作符
{
	if (command.argc > 0) //如果存储有指令，则进行清除
	{
		for (int i = 0; i < command.argc; i++)
		{
			delete[] command.argv[i];
		}
		command.argc = 0;
	}

	assert(command.argc == 0); //进行读入的时候，指令存储必须为空

	char tmp[MAX_ATTR_LEN * MAX_COL_SIZE], *p;
	const char * dlim = " ,:()\t"; //括号和制表符是后续自己添加的
	input.getline(tmp, MAX_COMMAND_SEG * MAX_COMMAND_SEG_LEN);
	p = strtok(tmp, dlim);
	int i = 0;
	while (p)
	{
		command.argv[i] = new char[MAX_COMMAND_SEG_LEN];
		strcpy(command.argv[i++], p);
		p = strtok(NULL, dlim);
	}
	command.argc = i;

#ifdef GET_COMMAND_SHOW //用于输出捕获的命令，
	printf(LIGHT_GREEN "<GET COMMAND>  " NONE);
	for (int command_show_i(0); command_show_i < command.argc; ++command_show_i)
		cout << command.argv[command_show_i] << " ";
	cout << endl;
#endif
	return input;
}

//温馨提示：如果在VS编译采用strcpy、strtok无法通过，建议在头文件处增加#pragma warning(disable:4996)