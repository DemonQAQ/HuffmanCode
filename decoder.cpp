/*----------------------------------------------------------------
// ��Ȩ����
//
// �ļ�����decoder.cpp
// �ļ�����������������
// ���ߣ�Demon
// ʱ�䣺2021.6.19
//----------------------------------------------------------------*/
#include "function.h"

//��������ı�����ؽ��շ�����
btree* huffmamtree_rebuild(huffmancode* code, int length)
{
	int i = 0, j = 0;
	char temp = 0;
	btree* root = (btree*)malloc(sizeof(btree)), * root_temp = NULL;
	if (!root)exit(-1);
	root->left = NULL;
	root->right = NULL;
	for (i = 0; i < length; i++)
	{
		j = 0;
		temp = code[i].c;
		root_temp = root;
		while (1)
		{
			if (code[i].string[j] == 0 || code[i].string[j] == 1)
			{
				if (code[i].string[j] == 0) //���
				{
					if (root_temp->left)root_temp = root_temp->left;
					else
					{
						root_temp->left = (btree*)malloc(sizeof(btree));
						if (!root_temp->left)exit(-1);
						else
						{
							root_temp->left->index = -1;
							root_temp->left->left = NULL;
							root_temp->left->right = NULL;
							root_temp = root_temp->left;
						}
					}
				}
				else //�ҽ�
				{
					if (root_temp->right)root_temp = root_temp->right;
					else
					{
						root_temp->right = (btree*)malloc(sizeof(btree));
						if (!root_temp->right)exit(-1);
						else
						{
							root_temp->right->index = -1;
							root_temp->right->left = NULL;
							root_temp->right->right = NULL;
							root_temp = root_temp->right;
						}
					}
				}
				j++;
			}
			else
			{
				root_temp->c = temp;
				break;
			}
		}
	}
	return root;
}

//����
char* huffmandecode(btree* root, char* string)
{
	if (!root)return NULL;
	int i = 0, j = 0, length = 0;
	length = strlen(string);
	btree* temp_root = root;
	char* decode_string = (char*)malloc(sizeof(char));
	if (!decode_string)exit(-1);
	else
	{
		for (i = 0; i < length; i++)decode_string[i] = 0;
		for (i = 0; i < length; i++)
		{
			if (string[i] == '0')
			{
				if (temp_root->left)temp_root = temp_root->left;
				else 
				{
					printf("[����]:δ�ҵ������Ӧ�ַ�����������Ĵ��봮�ͱ����\n");
					exit(-2);
				}
				if (!temp_root->left && !temp_root->right) 
				{
					decode_string[j++] = temp_root->c;
					temp_root = root;
				}
			}
			if (string[i] == '1')
			{
				if (temp_root->right)temp_root = temp_root->right;
				else exit(-2);
				if (!temp_root->left && !temp_root->right)
				{
					decode_string[j++] = temp_root->c;
					temp_root = root;
				}
			}
		}
		return decode_string;
	}
}