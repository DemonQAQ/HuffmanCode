/*----------------------------------------------------------------
// 版权所有
//
// 文件名：fnormal.cpp
// 文件功能描述：基础函数
// 作者：Demon
// 时间：2021.6.19
//----------------------------------------------------------------*/
#include "function.h"

//刷新缓冲区
void flash()
{
	scanf("%*[^\n]"); //清空缓冲区中最后一个\n前的所有数据，再读取走最后一个\n
	scanf("%*c");
}

//按区间读取整数
int scanf_num(TYPE_INPUT_NUM* num, TYPE_INPUT_NUM max, TYPE_INPUT_NUM min)//范围为闭区间
{
	int flag = -1, max_t = 0, min_t = 0;
	long double num_temp = 0;
	if (min >= max)
	{
		min_t = NORMAL_MIN;
		max_t = NORMAL_MAX;
	}
	else
	{
		min_t = min;
		max_t = max;
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

//生成文件名 格式- data_%Y%m%d_%H%M%S.txt
char* file_name(char* name)
{
	struct tm* newtime;
	char* str = { name };
	char outfile[NORMAL_NUM];
	time_t t1;
	t1 = time(NULL);
	newtime = localtime(&t1);
	strftime(outfile, 128, " - data_%Y%m%d_%H%M%S.txt", newtime);
	strcat(str, outfile);
	return str;
}

//检查字符串长度，大于TRIGGER_NUM对字符串进行截断，截断长度为FRAGEMNT_LENGTH
char* string_check(char* string)
{
	if (!string)return string;
	int i = 0, j = 0, length = TRIGGER_NUM + 1, num = 0;
	char* string_new = NULL;
	while (string[num] != '\0')num++;
	if (num < TRIGGER_NUM)return string;
	else
	{
		string_new = (char*)malloc((num / (FRAGEMNT_LENGTH - 1)) * sizeof(char));
		if (!string_new)exit(-1);
		while (length > TRIGGER_NUM)
		{
			for (i = 0; i < num; i = i + TRIGGER_NUM)
			{
				strcpy(&string_new[j], &string[i]);
				j++;
				length = j;
			}
		}
		return string_new;
	}
}

//检查字符串内是否有汉字
int char_check(char* string)
{
	if (!string)return -2;
	int i = 0;
	while (string[i] != '\0')
	{
		if (string[i] < 0)return -1;//汉字ascii码小于0
		else i++;
	}
	return 0;
}

//拷贝频度表
ftable* copy_ftable(ftable* head)
{
	if (!head)return NULL;
	ftable* head_new = NULL;
	ftable* temp_new = NULL;
	ftable* rear = NULL;
	ftable* p = head->next;
	while (p)
	{
		if (!head_new)
		{
			head_new = (ftable*)malloc(sizeof(ftable));
			if (!head_new)exit(-1);
			head_new->c = p->c;
			head_new->index = p->index;
			head_new->next = NULL;
			rear = head_new;
		}
		else
		{
			temp_new = (ftable*)malloc(sizeof(ftable));
			if (!temp_new)exit(-1);
			temp_new->c = p->c;
			temp_new->index = p->index;
			temp_new->next = NULL;
			rear->next = temp_new;
			rear = temp_new;
		}
		p = p->next;
	}
	return head_new;
}

//打印二叉树
int vec_left[NORMAL_NUM];
void tree_display(btree* root, int ident)
{
	if (ident > 0)
	{
		for (int i = 0; i < ident - 1; ++i)
		{
			printf(vec_left[i] ? "│   " : "    ");
		}
		printf(vec_left[ident - 1] ? "├── " : "└── ");
	}

	if (!root)
	{
		printf("(null)\n");
		return;
	}
	if (!root->left && !root->right)printf("%c\n", root->c);
	else if (ident == 0)printf("root\n");
	else if (root->index == -1)printf("X\n");
	else printf("%c\n", root->c);
	if (!root->left && !root->right)
	{
		return;
	}
	vec_left[ident] = 1;
	tree_display(root->left, ident + 1);
	vec_left[ident] = 0;
	tree_display(root->right, ident + 1);
}

//用于编码表检查函数中判断是否有相同编码
void check_judge(int* judge, int index, bool* flag)
{
	int i = 0, j = 0;
	for (i = index; i > 0; i--)
	{
		if (judge[i] == 1)j++;
	}
	if (j == index)*flag = true;
	else *flag = false;
}

//检查编码表是否符合要求
int check_code_list(huffmancode* code, int num)
{
	int i = 0, j = 0, index = 0;
	bool flag = false;
	char temp = 0;
	if (num == 1)goto next_check;
	else
	{
		for (i = 0; i < num - 1; i++)//比较是否有相同字符
		{
			temp = code[i].c;
			for (j = i + 1; j < num; j++)
			{
				if (temp == code[j].c)return 0;
			}
		}
	}
next_check:
	for (i = 0; i < num; i++)//比较是否由非01的编码或空编码
	{
		j = 0;
		if (j == 0 && code[i].string[j] < 0)return 0;
		while (code[i].string[j] >= 0)
		{
			if (code[i].string[j] == 0 || code[i].string[j] == 1)j++;
			else return 0;
		}
	}
	if (num == 1)return 1;
	else
	{
		int string_temp[CHAR_MAX_NUM];
		int judge[CHAR_MAX_NUM];
		for (i = 0; i < num; i++)//检查是否有相同编码
		{
			index = 0;
			write_to_result_code(string_temp, code[i].string, &index);
			for (j = i + 1; j < num; j++)
			{
				for (i = 0; i < CHAR_MAX_NUM; i++)judge[i] = 0;
				index = 0;
				while (code[j].string[index] >= 0)
				{
					if (code[j].string[index] == string_temp[index])
						judge[index] = 1;
					else
						flag = false;
					index++;
				}
				check_judge(judge, index, &flag);
				if (flag)return 0;
			}
		}
	}
	return 1;
}

//从键盘读入赫夫曼编码
huffmancode* input_code_list_keybroad(int* table_length)
{
	int num = 0, i = 0, j = 0, flag = 0, temp = 0;
	huffmancode* code = NULL;
	printf("请输入编码表长\n");
	scanf_num(&num, 32767, 0);
	code = (huffmancode*)malloc(num * sizeof(huffmancode));
	if (!code)exit(-1);
	for (i = 0; i < num; i++)
	{
		j = 0;
		flash();
		printf("[提示]:请输入单个字符，输入字符串仅读取第一个字符\n");
		scanf("%c", &code[i].c);
		printf("[提示]:请输入正序输入由01组成的编码,每次输入一位编码，输入-1结束输入\n");
		flash();
		do
		{
			scanf("%d", &flag);
			if (flag == -1)break;
			else code[i].string[j++] = flag;
		} while (1);
	}
	if (check_code_list(code, num))
	{
		*table_length = num;
		printf("[提示]:读取成功\n");
		system("pause");
		return code;
	}
	else
	{
		*table_length = 0;
		printf("[提示]:读取失败，请检查编码表\n");
		system("pause");
		return NULL;
	}
}

//检查输入的待译串是否合规
int check_codestring_input(char* string)
{
	int i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '0' || string[i] == '1')i++;
		else return 0;
	}
	return 1;
}

//输出编码表
void display_codelist(huffmancode* code, int length)
{
	int i = 0, j = 0;
	printf("编码表:\n[提示]:格式为 字母  --  对应编码\n");
	for (i = 0; i < length; i++)
	{
		j = 0;
		printf("%c  --  ", code[i].c);
		while (code[i].string[j] == 0 || code[i].string[j] == 1)
		{
			printf("%d", code[i].string[j++]);
		}
		printf("\n");
	}
}

//输出编码串
void display_codestring(int* string)
{
	int i = 0;
	printf("由字符串转换成的编码为:\n");
	while (string[i] == 0 || string[i] == 1)printf("%d", string[i++]);
	printf("\n");
}

//输出译码
void display_decodestring(char* string)
{
	printf("由编码翻译出的字符串为:\n");
	printf("%s", string);
	system("pause");
}

//输出编码表到文件
void file_codelist(huffmancode* code, int length)
{
	FILE* fp;
	char temp[STRING_MAX_NUM] = { "code" };
	char* name = temp;
	//name = file_name(temp);
	if ((fp = fopen(name, "wb+")) == NULL)
	{
		puts("[提示]:无法创建文件\n");
		system("pause");
		exit(-1);
	}
	fwrite(code, sizeof(struct huffmancode), length, fp);
	fclose(fp);
	printf("[提示]:已输出到 code.txt\n");
	system("pause");
}

//输出编码串到文件
void file_codestring(int* string)
{
	int i = 0;
	FILE* fp;
	char temp[STRING_MAX_NUM] = { "code_string" };
	char* name = temp;
	//name = file_name(temp);
	if ((fp = fopen(name, "w+")) == NULL)
	{
		puts("无法创建文件\n");
		system("pause");
		exit(-1);
	}
	while (1)
	{
		if (string[i] == 0 || string[i] == 1)fprintf(fp, "%d", string[i++]);
		else break;
	}
	fclose(fp);
	printf("[提示]:已输出到 code_string.txt\n");
	system("pause");
}

//输出解码串到文件
void file_decodestring(char* string)
{
	FILE* fp;
	char temp[STRING_MAX_NUM] = { "decode_string" };
	char* name = temp;
	name = file_name(temp);
	if ((fp = fopen(name, "w+")) == NULL)
	{
		puts("无法创建文件\n");
		system("pause");
		exit(-1);
	}
	fputs(string, fp);
	fclose(fp);
	printf("[提示]:已输出到 decode_string.txt\n");
	system("pause");
}

//从文件读入赫夫曼编码表
huffmancode* input_code_list_file(int* table_length)
{
	int num = 0, i = 0;
	huffmancode* code = NULL;
	FILE* fp;
	char name[CHAR_MAX] = { '\0' };
	flash();
	printf("[提示]:请输入带后缀的文件名，例如code.log\n");
	scanf("%s", name);
	flash();
	if ((fp = fopen(name, "rb+")) == NULL)
	{
		printf("[提示]:打开文件失败，请检查文件名\n");
		system("pause");
		return NULL;
	}
	printf("[提示]:请输入编码表长\n");
	scanf_num(&num, 32767, 0);
	code = (huffmancode*)malloc(num * sizeof(huffmancode));
	if (!code)exit(-1);
	fread(code, sizeof(struct huffmancode), num, fp);
	if (check_code_list(code, num))
	{
		*table_length = num;
		printf("[提示]:读取成功\n");
		system("pause");
		return code;
	}
	else
	{
		*table_length = 0;
		printf("[提示]:读取失败，请检查编码表\n");
		system("pause");
		return NULL;
	}
	fclose(fp);
}

//从文件读入字符串
char* file_input_string()
{
	char* string = NULL;
	FILE* fp;
	int num = 0, i = 0;
	char name[CHAR_MAX] = { '\0' };
	flash();
	printf("[提示]:请输入带后缀的文件名，例如string.log\n");
	scanf("%s", name);
	flash();
	if ((fp = fopen(name, "r+")) == NULL)
	{
		printf("[提示]:打开文件失败，请检查文件名\n");
		system("pause");
		return NULL;
	}
	printf("[提示]:请输入待读取的字符串的长度\n");
	scanf_num(&num, 32767, 0);
	num++;
	string = (char*)malloc(num * sizeof(char));
	if (!string)exit(-1);
	else
	{
		for (i = 0; i < num; i++)string[i] = 0;
		fgets(string, num, fp);
	}
	if (char_check(string) == 0)
	{
		printf("[提示]:读取成功\n");
		return string;
	}
	else return NULL;
}

//从文件读入待解码串
char* file_input_decodestring()
{
	int num = 0, i = 0;
	char* decode_string = NULL;
	char name[CHAR_MAX] = { '\0' };
	FILE* fp;
	flash();
	printf("[提示]:请输入带后缀的文件名，例如string.log\n");
	scanf("%s", name);
	flash();
	if ((fp = fopen(name, "r+")) == NULL)
	{
		printf("[提示]:打开文件失败，请检查文件名\n");
		system("pause");
		return NULL;
	}
	printf("[提示]:请输入待读取的字符串的长度\n");
	scanf_num(&num, 32767, 0);
	num++;
	decode_string = (char*)malloc(num * sizeof(char));
	if (!decode_string)exit(-1);
	else
	{
		fscanf(fp, "%s", decode_string);
	}
	if (check_codestring_input(decode_string))return decode_string;
	else return NULL;
}

//从键盘读取字符串
char* string_input_keyboard()
{
	char s[STRING_MAX_NUM];
	char* temp = s;
	do
	{
		flash();
		gets_s(s, STRING_MAX_NUM);
		if (char_check(s) == -1)printf("[提示]:请勿输入汉字，请重新输入\n");
		else break;
	} while (1);
	temp = string_check(s);
	return temp;
}

//从键盘输入待译编码
char* decodestring_input_keyboard(char* codestring_in)
{
	int num = 0, i = 0;
	char codestring[STRING_MAX_NUM];
	scanf("%s", codestring);
	if (check_codestring_input(codestring))
	{
		codestring_in = codestring;
		return codestring_in;
	}
	else return NULL;
}