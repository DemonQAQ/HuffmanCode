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
		printf("\t�շ�������/����ϵͳ\n\n");
		printf("------------------------------------\n");
		printf("[��ʾ]:����������ѡ��ģʽ\n");
		printf("\t1.������\n\t2.������\n\t0.�˳�\n");
		printf("------------------------------------\n");
		scanf_num(&select, 2, 0);
		switch (select)
		{
		case 1://������
			while (1)
			{
				system("cls");
				printf("\t������ -- ����������ַ���\n\n");
				printf("------------------------------------\n");
				printf("[��ʾ]:������Ǻ����ַ���\n");
				printf("[��ʾ]:����������ѡ��ģʽ\n");
				printf("\t1.�Ӽ�������\n\t2.���ļ���ȡ\n\t0.�˳�����ϵͳ\n");
				printf("------------------------------------\n");
				scanf_num(&select, 2, 0);
				switch (select)
				{
				case 1:
					printf("[��ʾ]:������������ַ���\n");
					string = string_input_keyboard();
					if (!string)
					{
						printf("[��ʾ]:����ʧ��,������������\n");
						system("pause");
						break;
					}
					else goto code_build;
				case 2:
					string = file_input_string();
					if (!string)
					{
						printf("[��ʾ]:��ȡʧ��,�����ļ�����\n");
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
		code_build://���벿��
			while (1)
			{
				system("cls");
				printf("\t������ -- ѡ�����ģʽ\n\n");
				printf("------------------------------------\n");
				printf("[��ʾ]:����������ѡ��ģʽ\n");
				printf("\t1.����������ַ������ɱ���\n\t2.���ļ���ȡ����\n\t3.�Ӽ����������\n\t0.�˳�����ϵͳ\n");
				printf("------------------------------------\n");
				scanf_num(&select, 3, 0);
				switch (select)
				{
				case 1:
					temp = create_frequencytable(string, &table_length);
					if (!temp)
					{
						printf("[��ʾ]:Ƶ�ȱ���ʧ��\n");
						system("pause");
						break;
					}
					else
					{
						ftable = copy_ftable(temp);
						root = huffmantree(ftable, table_length);
						if (!root)
						{
							printf("[��ʾ]:�շ���������ʧ��\n");
							system("pause");
							break;
						}
						else
						{
							code = code_create_list(root, table_length);
							if (!code)
							{
								printf("[��ʾ]:�������ʧ��\n");
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
						printf("[��ʾ]:������ȡʧ��,�����ļ�\n");
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
						printf("[��ʾ]:������ȡʧ��,��������\n");
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
				printf("\t������ -- ѡ�����ģʽ\n\n");
				printf("------------------------------------\n");
				printf("[��ʾ]:����������ѡ��ģʽ\n");
				printf("\t1.������ɵı��뵽��Ļ\n\t2.������ɵı������Ļ\n\t3.��ʾ��ǰ�շ�����(���������ַ������ɱ���ģʽ����)\n\t4.������ɵı��뵽�ļ�\n\t5.������ɵı�����ļ�\n\t0.�˳�����ϵͳ\n");
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
						printf("[��ʾ]:�޷�����շ�����\n");
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
		code_end://�˳�������
			break;
		case 2://������
			while (1)
			{
				system("cls");
				printf("\t������ -- �����������봮\n\n");
				printf("------------------------------------\n");
				printf("[��ʾ]:��������01��ɵı��봮\n");
				printf("[��ʾ]:����������ѡ��ģʽ\n");
				printf("\t1.�Ӽ�������\n\t2.���ļ���ȡ\n\t0.�˳�����ϵͳ\n");
				printf("------------------------------------\n");
				scanf_num(&select, 2, 0);
				switch (select)
				{
				case 1:
					printf("[��ʾ]:����0 1֮����ַ���������\n");
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
				printf("\t������ -- ��������\n\n");
				printf("------------------------------------\n");
				printf("[��ʾ]:������շ��������\n");
				printf("[��ʾ]:����������ѡ��ģʽ\n");
				printf("\t1.�Ӽ�������\n\t2.���ļ���ȡ\n\t0.�˳�����ϵͳ\n");
				printf("------------------------------------\n");
				scanf_num(&select, 2, 0);
				switch (select)
				{
				case 1:
					code = input_code_list_keybroad(&table_length);
					if (!code)
					{
						printf("[��ʾ]:������ȡʧ��,��������\n");
						system("pause");
						break;
					}
					else goto decode_input;
					break;
				case 2:
					code = input_code_list_file(&table_length);
					if (!code)
					{
						printf("[��ʾ]:������ȡʧ��,�����ļ�\n");
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
				printf("\t������ -- �������\n\n");
				printf("------------------------------------\n");
				printf("[��ʾ]:����������ѡ��ģʽ\n");
				printf("\t1.��ӡ����Ļ\n\t2.������ļ�\n\t0.�˳�����ϵͳ\n");
				printf("------------------------------------\n");
				if (!root)
				{
					printf("[��ʾ]:�ع��շ�����ʧ��\n");
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