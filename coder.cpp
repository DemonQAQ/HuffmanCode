/*----------------------------------------------------------------
// 版权所有
//
// 文件名：coder.cpp
// 文件功能描述：编码器
// 作者：Demon
// 时间：2021.6.19
//----------------------------------------------------------------*/
#include "function.h"
//创建频度表，扫描字符出现次数
ftable* create_frequencytable(char* string, int* table_length)
{
	if (!string || !table_length)return NULL;
	char temp_c = 0;
	int i = 0;
	ftable* p_head = NULL;//表头
	ftable* p_new = NULL; //存放新节点
	ftable* head = (ftable*)malloc(sizeof(ftable));
	if (!head)exit(-1);
	ftable* rear = head;  //表为指针
	head->index = 0701;   //表头标记
	head->next = NULL;
	temp_c = string[i];
	while (temp_c != '\0')//遍历字符串，已有字母则对应index++，否则新建
	{
		p_head = head;
		while (p_head)
		{
			if (temp_c == p_head->c)
				break;
			if (p_head)
				p_head = p_head->next;
		}
		if (!p_head)
		{
			p_new = (ftable*)malloc(sizeof(ftable));
			if (!p_new)exit(-1);
			p_new->index = 1;
			p_new->c = temp_c;
			if (!head->next)//链表中无元素
			{
				head->next = p_new;
				p_new->next = NULL;
				rear = p_new;
			}
			else
			{
				rear->next = p_new;
				p_new->next = NULL;
				rear = p_new;
			}
		}
		else
		{
			p_head->index++;
		}
		i++;
		temp_c = string[i];
	}
	i = 0;
	p_head = head;
	while (p_head)//计算表长，去除头结点值
	{
		p_head = p_head->next;
		i++;
	}
	*table_length = i - 1;
	return head;
}

//查找频度表中最小值
ftable* delect(ftable** head, ftable* min)
{
	if (!*head)return NULL;
	ftable* head_temp = *head;
	if (!head_temp->next)
	{
		*head = NULL;
		return head_temp;
	}
	min = head_temp;//默认最小值在头
	ftable* p_temp = head_temp;
	while (p_temp)
	{
		if (p_temp->index < min->index)
			min = p_temp;
		p_temp = p_temp->next;
	}
	if (min->c == head_temp->c) //删除头结点
	{
		head_temp = head_temp->next;
		min->next = NULL;
		*head = head_temp;
	}
	else//删除节点
	{
		p_temp = head_temp;
		while (p_temp && p_temp->next)
		{
			if (p_temp->next->c == min->c)
				break;
			p_temp = p_temp->next;
		}
		p_temp->next = min->next;
	}
	return min;
}

//当队列中有大于一个非空指针时表明未建立完树，返回1继续循序
int check_queue(btree** queue, int length)
{
	int i = 0, count = 0;
	for (i = 0; i < length; i++)
	{
		if (queue[i])count++;
		if (count > 1)return 1;
	}
	return 0;
}

//查找队列中最小值的下标
int find_queue_min(btree** queue, int length)
{
	int i = 0, min_index = -1;
	for (i = 0; i < length; i++)
	{
		if (!queue[i])continue;
		if (queue[i] && min_index == -1)min_index = i;//选中第一个非空指针作为min_index的初始值
		else
		{
			if (queue[i]->index < queue[min_index]->index)min_index = i;
		}
	}
	if (min_index == -1)return min_index;
	else
	{
		return min_index;
	}
}

//建立赫夫曼树
btree* huffmantree(ftable* head, int length)
{
	ftable* min_temp = NULL;//存放频度表最小值
	btree* root = (btree*)malloc(sizeof(btree));//赫夫曼树根
	btree* root_temp = NULL;//临时根节点
	int min_index = 0;//存放队列查找到的下标
	if (!root)exit(-1);
	root->index = -1;
	root->left = NULL;
	root->right = NULL;

	int ftable_length = 0, qhead = 0, qrear = 0, i = 0;//队头,队尾,初始点
	ftable* p_temp = head;
	ftable_length = length;//频度表长
	if (ftable_length < 0)return NULL;
	else if (ftable_length == 1)
	{
		root->c = head->c;
		root->left = NULL;
		root->right = NULL;
	}
	else
	{
		ftable_length = 2 * ftable_length;
		btree** queue = (btree**)malloc(ftable_length * sizeof(btree*));
		if (!queue)exit(-1);
		for (i = 0; i < ftable_length; i++)queue[i] = NULL;

		while (head)//将频度表所有节点入队
		{
			min_temp = delect(&head, min_temp);
			root_temp = (btree*)malloc(sizeof(btree));
			root_temp->c = min_temp->c;
			root_temp->index = min_temp->index;
			root_temp->left = NULL;
			root_temp->right = NULL;
			queue[qrear++] = root_temp;
		}
		root->left = queue[qhead]; //合并初始根节点并入队
		queue[qhead++] = NULL;
		root->right = queue[qhead];
		queue[qhead++] = NULL;
		if (!root->left && !root->right)exit(-1);
		else root->index = root->left->index + root->right->index;
		queue[qrear++] = root;
		while (check_queue(queue, ftable_length))//队空时退出
		{
			root_temp = (btree*)malloc(sizeof(btree));
			if (!root_temp)exit(-1);
			else
			{
				//两次查找最小值分别赋值给临时根的左右孩子
				min_index = find_queue_min(queue, ftable_length);
				if (min_index == -1)exit(-1);
				else
				{
					root_temp->left = queue[min_index];
					queue[min_index] = NULL;
				}
				min_index = find_queue_min(queue, ftable_length);
				if (min_index == -1)exit(-1);
				else
				{
					root_temp->right = queue[min_index];
					queue[min_index] = NULL;
				}

				root_temp->index = root_temp->left->index + root_temp->right->index;
				if (root_temp->left->left && root_temp->left->right)root_temp->left->index = -1;
				if (root_temp->right->left && root_temp->right->right)root_temp->right->index = -1;
				queue[qrear++] = root_temp;
			}
		}
		//取出队列中最后一个元素，该元素即为生成的树根
		min_index = find_queue_min(queue, ftable_length);
		root = queue[min_index];
	}
	return root;
}

//创建赫夫曼编码表
huffmancode* code_create_list(btree* root, int length)
{
	btree* root_temp = root;
	huffmancode* code = NULL;
	int i = 0, j = 0, c_flag = -1;//code遍历单元，code的string的遍历单元，编码生成完毕的标志单元
	if (length <= 0)return NULL;
	code = (huffmancode*)malloc(length * sizeof(huffmancode));
	if (!code)exit(-1);
	if (length == 1)//表中只有一个元素时
	{
		code->c = root->c;
		code->string[0] = 0;
	}
	else//对树遍历编码
	{
		if (!code)exit(-1);
		for (i = 0; i < length; i++)
		{
			j = 0;
			c_flag = -1;
			coding(&root_temp, &code, &i, &j, &c_flag);
		}
	}
	return code;
}

/*
自顶向下生成编码的递归算法
c_flag为结束条件，c_flag为1时表明此次编码已生成完毕，退出所有递归
flag为完成左访问标记，完成左访问后进行右访问需要更新编码的值
*/
btree* coding(btree** root_, huffmancode** code_, int* i, int* j, int* c_flag)
{
	btree* root = *root_;
	bool flag = false;
	if (!root)return NULL;
	else
	{
		huffmancode* code = *code_;
		if (!root->left && !root->right)//访问叶子节点
		{
			code[*i].c = root->c;
			root->index = 0;
			*c_flag = 1;
			goto end;
		}
		if (root->left->index == -1)//左访问非叶子节点
		{
			code[*i].string[(*j)++] = 0;
			coding(&root->left, code_, i, j, c_flag);
			flag = true;
			if (c_flag)goto end;
		}
		if (root->left->index > 0)//访问左叶子
		{
			code[*i].string[(*j)++] = 0;
			coding(&root->left, code_, i, j, c_flag);
			if (c_flag)goto end;
		}
		if (root->right->index == -1)//右访问非叶子节点
		{
			if (flag)
			{
				(*j)--;
				code[*i].string[(*j)++] = 1;
			}
			else code[*i].string[(*j)++] = 1;
			coding(&root->right, code_, i, j, c_flag);
			if (c_flag)goto end;
		}
		if (root->right->index > 0)//访问右叶子
		{
			if (flag)
			{
				(*j)--;
				code[*i].string[(*j)++] = 1;
			}
			else code[*i].string[(*j)++] = 1;
			coding(&root->right, code_, i, j, c_flag);
			if (c_flag)goto end;
		}
	}
end:
	return root;
}

huffmancode* build_huffmancode(int* table_length)
{
	char string[NORMAL_NUM];
	ftable* table_head = NULL;
	ftable* table_temp = NULL;
	btree* root = NULL;
	huffmancode* code = NULL;
	do
	{
		scanf("%s", string);
		if (!(char_check(string)))flash();
	} while (char_check(string));
	table_head = create_frequencytable(string, table_length);
	table_temp = copy_ftable(table_head);
	root = huffmantree(table_temp, *table_length);
	code = code_create_list(root, *table_length);
	return code;
}

//将编码写入数组
int* write_to_result_code(int* result_code, int* string, int* r_index)
{
	int i = 0;
	while (string[i] == 0 || string[i] == 1)
	{
		result_code[(*r_index)++] = string[i++];
	}
	return result_code;
}

//对字符串编码，匹配字符和编码表中的字符，讲对应编码写入数组中
int* codestring(huffmancode* code, char* string, int length)
{
	int i = 0, num = 0, j = 0, result_index = 0;//result_index为下一次写入结果数组中的变量下标
	num = strlen(string);
	int* result_code = (int*)malloc(2 * num * sizeof(int));
	if (!result_code)exit(-1);
	if (length == 1)
	{
		for (i = 0; i < num; i++)
		{
			result_code[i] = code->string[0];
		}
	}
	else
	{
		char temp = string[0];
		for (i = 0; i < num; i++)
		{
			temp = string[i];
			for (j = 0; j < length; j++)
			{
				if (code[j].c == temp)
				{
					result_code = write_to_result_code(result_code, code[j].string, &result_index);
					break;
				}
			}
		}
	}
	return result_code;
}

