/*----------------------------------------------------------------
// ��Ȩ����
//
// �ļ�����function.h
// �ļ���������������ͷ�ļ�
// ���ߣ�Demon
// ʱ�䣺2021.6.19
//----------------------------------------------------------------*/
#pragma once
#ifndef	FUNCTION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//-------------------DEFINE_START----------------------------------

#define CHAR_MAX_NUM 2				//�ڵ��ַ����ĳ���
#define FRAGEMNT_LENGTH 2
#define NORMAL_NUM 128
#define NORMAL_MAX 128
#define NORMAL_MIN 0
#define STRING_MAX_NUM 64
#define TRIGGER_NUM 10000
#define TYPE_INPUT_NUM int

//-------------------DEFINE_END------------------------------------

//-------------------STRUCT_START----------------------------------

struct btree						//������
{
	char c[CHAR_MAX_NUM];			//���涥���ַ�
	int index;						//����Ƿ�ΪҶ�ӽڵ�
	btree* left;
	btree* right;
};

struct  ftable						//�շ�����Ƶ������
{
	char c[CHAR_MAX_NUM];
	int index;						//ĳ�ַ����ִ���
	ftable* next;
};

struct huffmancode					//�շ�������ڵ�
{
	char c[CHAR_MAX_NUM];			//�ַ�
	char string[CHAR_MAX_NUM];		//��Ӧ�շ�������
};

//-------------------STRUCT_END----------------------------------

//-------------------FUNCTION_START------------------------------

int char_check(char* string);
int scanf_num(TYPE_INPUT_NUM* num, double max, double min);
char* string_check(char* string);
char* huffmamtree_rebuild(huffmancode* code);
char* codestring(huffmancode* code, char* string, ftable* head);
char* huffmandecode(btree* root, char* string);
char* file_name(char* name);
void display_tree();//����
void display_codelist();
void display_codestring();
void file_codelist();
void file_codestring();
void display_decodestring();
void file_decodestring();
void flash();
btree* coding(btree* root, huffmancode* code, int* i, int* j);
btree* huffmantree(ftable* head);
ftable* copy_ftable(ftable* head);
ftable* create_frequencytable(char* string, int* table_length);
huffmancode* build_huffmancode(char* string);
huffmancode* code_create_list(btree* root, int length);
huffmancode* input_code_list_keybroad();
huffmancode* input_code_list_file();

//-------------------FUNCTION_END--------------------------------
#endif
