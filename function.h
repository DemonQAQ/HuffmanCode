/*----------------------------------------------------------------
// 版权所有
//
// 文件名：function.h
// 文件功能描述：集成头文件
// 作者：Demon
// 时间：2021.6.19
//----------------------------------------------------------------*/
#pragma once
#ifndef	FUNCTION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//-------------------DEFINE_START----------------------------------

#define CHAR_MAX_NUM 64				//节点字符串的长度
#define FRAGEMNT_LENGTH 2
#define NORMAL_NUM 128
#define NORMAL_MAX 128
#define NORMAL_MIN 0
#define STRING_MAX_NUM 5000	
#define TRIGGER_NUM 4000
#define TYPE_INPUT_NUM int

//-------------------DEFINE_END------------------------------------

//-------------------STRUCT_START----------------------------------

struct btree						//二叉树
{
	char c;							//保存顶点字符
	int index;						//标记是否为叶子节点
	btree* left;
	btree* right;
};

struct  ftable						//赫夫曼树频度链表
{
	char c;
	int index;						//某字符出现次数
	ftable* next;
};

struct huffmancode					//赫夫曼编码节点
{
	char c;			//字符
	int string[CHAR_MAX_NUM];		//对应赫夫曼编码
};

//-------------------STRUCT_END----------------------------------

//-------------------FUNCTION_START------------------------------
int char_check(char* string);
int check_codestring_input(char* string);
int scanf_num(TYPE_INPUT_NUM* num, TYPE_INPUT_NUM max, TYPE_INPUT_NUM min);
int check_code_list(huffmancode* code, int num);
int* codestring(huffmancode* code, char* string, int length);
int* write_to_result_code(int* result_code, int* string, int* r_index);
char* decodestring_input_keyboard(char* codestring_in);
char* file_input_decodestring();
char* string_check(char* string);
char* file_input_string();
char* huffmandecode(btree* root, char* string);
char* file_name(char* name);
char* string_input_keyboard();
void display_codelist(huffmancode* code, int length);
void tree_display(btree* root, int ident);
void display_codestring(int* string);
void file_codelist(huffmancode* code, int length);
void file_codestring(int* string);
void display_decodestring(char* string);
void file_decodestring(char* string);
void coding(btree** root_, huffmancode** code_, int* i, int* j, int* c_flag);
void flash();
btree* huffmamtree_rebuild(huffmancode* code, int length);
btree* huffmantree(ftable* head, int length);
ftable* copy_ftable(ftable* head);
ftable* create_frequencytable(char* string, int* table_length);
huffmancode* code_create_list(btree* root, int length);
huffmancode* input_code_list_keybroad(int* table_length);
huffmancode* input_code_list_file(int* table_length);

//-------------------FUNCTION_END--------------------------------
#endif
