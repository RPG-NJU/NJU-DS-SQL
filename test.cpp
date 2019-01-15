#include "common.h"
#include "test.h"
//#include "Table.h"

#include "Define.h"



void Timer::tic(char t[]) //输出传入的字符串，并且开启计时
{
    strcpy(test_name, t);
    cout << test_name << " test begin." << endl;
    start = clock(); //获取当前时间

}

void Timer::toc(){
    end = clock();
    used_time = double(end - start) / CLOCKS_PER_SEC;
    cout << test_name << " test done. Use time: " << used_time << endl;
}


Tester::Tester(const char *test_file, const char *result_file)
//构造函数打开两个文件，首先是命令文件，其次是结果文件
{
    fin.open(test_file);
    fout.open(result_file);

#ifdef EVERY_STEP_SHOW
	if (fin && fout)
		printf(LIGHT_GREEN "<OPEN THE FILE>  " NONE "%s %s\n", test_file, result_file);
	if (!fin)
		printf(LIGHT_RED "<FILE OPEN FAIL>  " NONE "%s\n", test_file);
	if (!fout)
		printf(LIGHT_RED "<FILE OPEN FAIL>  " NONE "%s\n", result_file);
#endif

    assert((fin && fout) || (INFO("open file failed!"), 0));
}

Tester::~Tester()
{
    fin.close();
    fout.close();
}

void Tester::exec()
{
    Command command; //命令类，其中重载了操作符>>，所以fin>>不是简单的读入，已经分割完成
    Timer timer;
    timer.tic(test_name);
    while (fin >> command) //不断捕获命令，并且对命令进行执行，通过helper函数
	{
        helper(command, fout);
    }
    timer.toc();
}

SingleTester::SingleTester(const char *test_file, const char *result_file):Tester(test_file, result_file)
{
    strcpy(test_name, "Single");   
}

SectionTester::SectionTester(const char *test_file, const char *result_file):Tester(test_file, result_file)
{
    strcpy(test_name, "Section");
}

SetTester::SetTester(const char *test_file, const char *result_file):Tester(test_file, result_file)
{
    strcpy(test_name, "Set");
}