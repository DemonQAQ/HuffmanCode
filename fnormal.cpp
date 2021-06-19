/*----------------------------------------------------------------
// 版权所有
//
// 文件名：fnormal.cpp
// 文件功能描述：基础函数
// 作者：Demon
// 时间：2021.6.19
//----------------------------------------------------------------*/
#include "function.h"

void flash()
{
	scanf("%*[^\n]%*c");
}

int scanf_num(TYPE_INPUT_NUM* num, TYPE_INPUT_NUM max, TYPE_INPUT_NUM min)//范围为闭区间
{
	int flag = -1, max_t = 0,min_t=0;
	long double num_temp = 0;
	if (min >= max) 
	{
		min_t = NORMAL_MIN;
		max_t = NORMAL_MAX;
	}
	printf("[提示]:请输入在区间[%d - %d]内的数值\n", min_t, max_t);
	do
	{
		if (flag != -1)flash();
		flag = scanf("%lf", &num_temp);
		if (!flag)
			printf("[提示]:输入数据类型错误,请重新输入\n");
		if (num_temp > max_t || num_temp < min_t)
			printf("[提示]:请输入区间[%d - %d]内的数据\n", min_t, max_t);
	} while (!flag || num_temp > max_t || num_temp < min_t);
	*num = (TYPE_INPUT_NUM)num_temp;
	return 1;
}

char* file_name(char* name)
{
	struct tm* newtime;
	char* str = { name };
	char outfile[NORMAL_NUM];
	time_t t1;
	t1 = time(NULL);
	newtime = localtime(&t1);
	strftime(outfile, 128, " - data_%Y%m%d_%H%M%S.log", newtime);
	strcat(str, outfile);
	return str;
}