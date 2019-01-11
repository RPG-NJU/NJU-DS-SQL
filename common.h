#pragma once

#include <iostream>
#include <fstream>
#include <assert.h>
#include <cstring>
#include <time.h>

using namespace std;

#define MAX_COL_SIZE 10
#define MAX_ATTR_LEN 30
#define MAX_COMMAND_SEG 20
#define MAX_COMMAND_SEG_LEN 20


#pragma warning(disable:4996) // 由于在VS环境下编译，依照助教的指示，添加此条

class Record{
    static int attrc;
    static char attr_name[MAX_COL_SIZE][MAX_ATTR_LEN];

    public:
    char *attrv[MAX_COL_SIZE];
    //TODO 
    //realize get and set attr;
    static int getAttr(char attrs[][MAX_ATTR_LEN]); //get attribute per record
    static bool setAttr(int num_attr, const char attrs[][MAX_ATTR_LEN]); //set attribute for record before reading records
    Record();
    ~Record();
    friend ifstream & operator >> (ifstream &input, Record &record);
};

class Command{
    public:
    int argc;
    char *argv[MAX_COMMAND_SEG];
    Command();
    ~Command();
    friend ifstream & operator >> (ifstream &input, Command &command);
};

ifstream & operator >> (ifstream &input, Record &record);
ifstream & operator >> (ifstream &input, Command &command);

void INFO(const char* msg);
void helper(Command &command);
void loadData(char *datafile);