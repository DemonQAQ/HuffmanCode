/*----------------------------------------------------------------
// 版权所有
//
// 文件名：decoder.cpp
// 文件功能描述：解码器
// 作者：Demon
// 时间：2021.6.19
//----------------------------------------------------------------*/
#include "function.h"

//根据输入的编码表重建赫夫曼树
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
				if (code[i].string[j] == 0) //左进
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
				else //右进
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

//译码
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
					printf("[错误]:未找到编码对应字符，请检查输入的待译串和编码表\n");
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