#pragma once
#include "common.h"

class Timer
{
public:
	char test_name[20];
	double used_time;
	clock_t start, end;
	void tic(char t[]);
	void toc();
};

class Tester 
{
public:
	char test_name[20];
	ifstream fin;
	ofstream fout;
	Tester(const char *test_file, const char *result_file);
	~Tester();
	void exec();
};


//所有的Tester结尾的类均是由Tester派生而来的
class SingleTester :public Tester {
public:
	SingleTester(const char *test_file, const char *result_file);
};

class SectionTester :public Tester {
public:
	SectionTester(const char *test_file, const char *result_file);
};

class SetTester :public Tester {
public:
	SetTester(const char *test_file, const char *result_file);
};


