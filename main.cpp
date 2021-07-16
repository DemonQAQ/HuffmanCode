#include "function.h"
int main()
{
	int select = 0, table_length = 0;
	int* result = NULL;
	char* string = NULL, * decode_string = NULL ,* codestring_in = NULL;
	btree* root = NULL;
	ftable* ftable = NULL, * temp = NULL;
	huffmancode* code = NULL;
	while (1)
	{
		system("cls");
		printf("\t赫夫曼编码/解码系统\n\n");
		printf("------------------------------------\n");
		printf("[提示]:请输入数字选择模式\n");
		printf("\t1.编码器\n\t2.解码器\n\t0.退出\n");
		printf("------------------------------------\n");
		scanf_num(&select, 2, 0);
		switch (select)
		{
		case 1://编码器
			while (1)
			{
				system("cls");
				printf("\t编码器 -- 输入待编码字符串\n\n");
				printf("------------------------------------\n");
				printf("[提示]:请输入非汉字字符串\n");
				printf("[提示]:请输入数字选择模式\n");
				printf("\t1.从键盘输入\n\t2.从文件读取\n\t0.退出到主系统\n");
				printf("------------------------------------\n");
				scanf_num(&select, 2, 0);
				switch (select)
				{
				case 1:
					printf("[提示]:请输入待编码字符串\n");
					string = string_input_keyboard();
					if (!string)
					{
						printf("[提示]:输入失败,请检查输入内容\n");
						system("pause");
						break;
					}
					else goto code_build;
				case 2:
					string = file_input_string();
					if (!string)
					{
						printf("[提示]:读取失败,请检查文件内容\n");
						system("pause");
						break;
					}
					else goto code_build;
				case 0:
					goto code_end;
				default:
					break;
				}
			}
		code_build://编码部分
			while (1)
			{
				system("cls");
				printf("\t编码器 -- 选择编码模式\n\n");
				printf("------------------------------------\n");
				printf("[提示]:请输入数字选择模式\n");
				printf("\t1.根据输入的字符串生成编码\n\t2.从文件读取编码\n\t3.从键盘输入编码\n\t0.退出到主系统\n");
				printf("------------------------------------\n");
				scanf_num(&select, 3, 0);
				switch (select)
				{
				case 1:
					temp = create_frequencytable(string, &table_length);
					if (!temp)
					{
						printf("[提示]:频度表创建失败\n");
						system("pause");
						break;
					}
					else
					{
						ftable = copy_ftable(temp);
						root = huffmantree(ftable, table_length);
						if (!root)
						{
							printf("[提示]:赫夫曼树创建失败\n");
							system("pause");
							break;
						}
						else
						{
							code = code_create_list(root, table_length);
							if (!code)
							{
								printf("[提示]:编码表创建失败\n");
								system("pause");
								break;
							}
							else
							{
								result = codestring(code, string, table_length);
								goto code_input;
							}
						}
					}
					break;
				case 2:
					code = input_code_list_file(&table_length);
					if (!code)
					{
						printf("[提示]:编码表读取失败,请检查文件\n");
						system("pause");
						break;
					}
					else
					{
						result = codestring(code, string, table_length);
						goto code_input;
					}
					break;
				case 3:
					code = input_code_list_keybroad(&table_length);
					if (!code)
					{
						printf("[提示]:编码表读取失败,请检查输入\n");
						system("pause");
						break;
					}
					else
					{
						result = codestring(code, string, table_length);
						goto code_input;
					}
					break;
				case 0:
					break;
				}
			}
		code_input:
			while (1)
			{
				system("cls");
				printf("\t编码器 -- 选择输出模式\n\n");
				printf("------------------------------------\n");
				printf("[提示]:请输入数字选择模式\n");
				printf("\t1.输出生成的编码到屏幕\n\t2.输出生成的编码表到屏幕\n\t3.显示当前赫夫曼树(仅按输入字符串生成编码模式可用)\n\t4.输出生成的编码到文件\n\t5.输出生成的编码表到文件\n\t0.退出到主系统\n");
				printf("------------------------------------\n");
				scanf_num(&select, 5, 0);
				switch (select)
				{
				case 1:
					display_codestring(result);
					system("pause");
					break;
				case 2:
					display_codelist(code, table_length);
					system("pause");
					break;
				case 3:
					if (!root)
					{
						printf("[提示]:无法输出赫夫曼树\n");
						system("pause");
						break;
					}
					else
					{
						tree_display(root, 0);
						system("pause");
						break;
					}
				case 4:
					file_codestring(result);
					break;
				case 5:
					file_codelist(code, table_length);
					break;
				case 0:
					goto code_end;
					break;
				}
			}
		code_end://退出编码器
			break;
		case 2://解码器
			while (1)
			{
				system("cls");
				printf("\t解码器 -- 输入待解码编码串\n\n");
				printf("------------------------------------\n");
				printf("[提示]:请输入由01组成的编码串\n");
				printf("[提示]:请输入数字选择模式\n");
				printf("\t1.从键盘输入\n\t2.从文件读取\n\t0.退出到主系统\n");
				printf("------------------------------------\n");
				scanf_num(&select, 2, 0);
				switch (select)
				{
				case 1:
					printf("[提示]:输入0 1之外的字符结束输入\n");
					codestring_in = decodestring_input_keyboard(codestring_in);
					if (codestring_in)goto decode;
					else break;
				case 2:
					codestring_in = file_input_decodestring();
					if (codestring_in)goto decode;
					else break;
				case 0:
					goto decode_end;
					break;
				}
			}
		decode:
			while (1)
			{
				system("cls");
				printf("\t解码器 -- 输入编码表\n\n");
				printf("------------------------------------\n");
				printf("[提示]:请输入赫夫曼编码表\n");
				printf("[提示]:请输入数字选择模式\n");
				printf("\t1.从键盘输入\n\t2.从文件读取\n\t0.退出到主系统\n");
				printf("------------------------------------\n");
				scanf_num(&select, 2, 0);
				switch (select)
				{
				case 1:
					code = input_code_list_keybroad(&table_length);
					if (!code)
					{
						printf("[提示]:编码表读取失败,请检查输入\n");
						system("pause");
						break;
					}
					else goto decode_input;
					break;
				case 2:
					code = input_code_list_file(&table_length);
					if (!code)
					{
						printf("[提示]:编码表读取失败,请检查文件\n");
						system("pause");
						break;
					}
					else goto decode_input;
				case 0:
					goto decode_end;
				default:
					break;
				}
			}
		decode_input:
				root = huffmamtree_rebuild(code, table_length);
				decode_string = huffmandecode(root, codestring_in);
			while (1)
			{
				system("cls");
				printf("\t解码器 -- 输出译码\n\n");
				printf("------------------------------------\n");
				printf("[提示]:请输入数字选择模式\n");
				printf("\t1.打印到屏幕\n\t2.输出到文件\n\t0.退出到主系统\n");
				printf("------------------------------------\n");
				if (!root)
				{
					printf("[提示]:重构赫夫曼树失败\n");
					system("pause");
					goto decode_end;
				}
				scanf_num(&select, 2, 0);
				switch (select)
				{
				case 1:
					display_decodestring(decode_string);
					break;
				case 2:
					file_decodestring(decode_string);
					break;
				case 0:
					goto decode_end;
				}
			}
		decode_end:
			break;
		case 0:
			goto end;
		default:
			break;
		}
	}
end:
	return 0;
}