#include "common.h"
#include "test.h"
#include "database.h"


/*
 * 本实验使用Visual Studio环境进行编写
 * 实验开始时间，2019.1.11
 * 文件中的框架代码由助教提供
 * 从文件中读入数据和操作指令
 * 
 * 相关要求以及答疑：
 * 1.文件不用回写
 * 
 */

void helper(Command &command){
    //TODO
    //recognize and execute command
    INFO("hehe");
}

void loadData(const char *file){
    //TODO
    //load data file
}

int TEST_TYPE = 0;


int main(int argc, char const *argv[])
{
    /* code */
    Timer timer;
    timer.tic("All");

    /*SingleTester single_tester("single.txt", "result_single.txt");
    SectionTester section_tester1("section1.txt", "result_section1.txt");
    SectionTester section_tester2("section2.txt", "result_section2.txt");
    SetTester set_tester("set.txt", "result_set.txt");*/
    //
    ////单点测试
    //TEST_TYPE = 0;
    //loadData("data_single.txt");
    //INFO("=====================================");
    //single_tester.exec();
    //INFO("=====================================\n");

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



