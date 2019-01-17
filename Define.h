#pragma once

#define GET_COMMAND_SHOW //捕获命令的展示输出
#define EVERY_STEP_SHOW //每个阶段的展示输出
//#define GET_DATAFILE_SHOW //输出读取文件的阶段
//#define GET_RAW_DATA_SHOW //原始数据的输出（直接从文件中getline的一行输出）
#define RUN_COMMAND_SHOW

//在这一段定义一些颜色输出，用于printf的使用
#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"
//END define word color

