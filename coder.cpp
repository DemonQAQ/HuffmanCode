/*----------------------------------------------------------------
// ��Ȩ����
//
// �ļ�����coder.cpp
// �ļ�����������������
// ���ߣ�Demon
// ʱ�䣺2021.6.19
//----------------------------------------------------------------*/
#include "function.h"
//����Ƶ�ȱ�ɨ���ַ����ִ���
ftable* create_frequencytable(char* string, int* table_length)
{
	if (!string || !table_length)return NULL;
	char temp_c = 0;
	int i = 0;
	ftable* p_head = NULL;//��ͷ
	ftable* p_new = NULL; //����½ڵ�
	ftable* head = (ftable*)malloc(sizeof(ftable));
	if (!head)exit(-1);
	ftable* rear = head;  //��Ϊָ��
	head->index = 0701;   //��ͷ���
	head->next = NULL;
	temp_c = string[i];
	while (temp_c != '\0')//�����ַ�����������ĸ���Ӧindex++�������½�
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
			if (!head->next)//��������Ԫ��
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
	while (p_head)//�������ȥ��ͷ���ֵ
	{
		p_head = p_head->next;
		i++;
	}
	*table_length = i - 1;
	return head;
}

//����Ƶ�ȱ�����Сֵ
ftable* delect(ftable** head, ftable* min)
{
	if (!*head)return NULL;
	ftable* head_temp = *head;
	if (!head_temp->next)
	{
		*head = NULL;
		return head_temp;
	}
	min = head_temp;//Ĭ����Сֵ��ͷ
	ftable* p_temp = head_temp;
	while (p_temp)
	{
		if (p_temp->index < min->index)
			min = p_temp;
		p_temp = p_temp->next;
	}
	if (min->c == head_temp->c) //ɾ��ͷ���
	{
		head_temp = head_temp->next;
		min->next = NULL;
		*head = head_temp;
	}
	else//ɾ���ڵ�
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

//���������д���һ���ǿ�ָ��ʱ����δ��������������1����ѭ��
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

//���Ҷ�������Сֵ���±�
int find_queue_min(btree** queue, int length)
{
	int i = 0, min_index = -1;
	for (i = 0; i < length; i++)
	{
		if (!queue[i])continue;
		if (queue[i] && min_index == -1)min_index = i;//ѡ�е�һ���ǿ�ָ����Ϊmin_index�ĳ�ʼֵ
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

//�����շ�����
btree* huffmantree(ftable* head, int length)
{
	ftable* min_temp = NULL;//���Ƶ�ȱ���Сֵ
	btree* root = (btree*)malloc(sizeof(btree));//�շ�������
	btree* root_temp = NULL;//��ʱ���ڵ�
	int min_index = 0;//��Ŷ��в��ҵ����±�
	if (!root)exit(-1);
	root->index = -1;
	root->left = NULL;
	root->right = NULL;

	int ftable_length = 0, qhead = 0, qrear = 0, i = 0;//��ͷ,��β,��ʼ��
	ftable* p_temp = head;
	ftable_length = length;//Ƶ�ȱ�
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

		while (head)//��Ƶ�ȱ����нڵ����
		{
			min_temp = delect(&head, min_temp);
			root_temp = (btree*)malloc(sizeof(btree));
			root_temp->c = min_temp->c;
			root_temp->index = min_temp->index;
			root_temp->left = NULL;
			root_temp->right = NULL;
			queue[qrear++] = root_temp;
		}
		root->left = queue[qhead]; //�ϲ���ʼ���ڵ㲢���
		queue[qhead++] = NULL;
		root->right = queue[qhead];
		queue[qhead++] = NULL;
		if (!root->left && !root->right)exit(-1);
		else root->index = root->left->index + root->right->index;
		queue[qrear++] = root;
		while (check_queue(queue, ftable_length))//�ӿ�ʱ�˳�
		{
			root_temp = (btree*)malloc(sizeof(btree));
			if (!root_temp)exit(-1);
			else
			{
				//���β�����Сֵ�ֱ�ֵ����ʱ�������Һ���
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
		//ȡ�����������һ��Ԫ�أ���Ԫ�ؼ�Ϊ���ɵ�����
		min_index = find_queue_min(queue, ftable_length);
		root = queue[min_index];
	}
	return root;
}

//�����շ��������
huffmancode* code_create_list(btree* root, int length)
{
	btree* root_temp = root;
	huffmancode* code = NULL;
	int i = 0, j = 0, c_flag = -1;//code������Ԫ��code��string�ı�����Ԫ������������ϵı�־��Ԫ
	if (length <= 0)return NULL;
	code = (huffmancode*)malloc(length * sizeof(huffmancode));
	if (!code)exit(-1);
	if (length == 1)//����ֻ��һ��Ԫ��ʱ
	{
		code->c = root->c;
		code->string[0] = 0;
	}
	else//������������
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
�Զ��������ɱ���ĵݹ��㷨
c_flagΪ����������c_flagΪ1ʱ�����˴α�����������ϣ��˳����еݹ�
flagΪ�������ʱ�ǣ��������ʺ�����ҷ�����Ҫ���±����ֵ
*/
btree* coding(btree** root_, huffmancode** code_, int* i, int* j, int* c_flag)
{
	btree* root = *root_;
	bool flag = false;
	if (!root)return NULL;
	else
	{
		huffmancode* code = *code_;
		if (!root->left && !root->right)//����Ҷ�ӽڵ�
		{
			code[*i].c = root->c;
			root->index = 0;
			*c_flag = 1;
			goto end;
		}
		if (root->left->index == -1)//����ʷ�Ҷ�ӽڵ�
		{
			code[*i].string[(*j)++] = 0;
			coding(&root->left, code_, i, j, c_flag);
			flag = true;
			if (c_flag)goto end;
		}
		if (root->left->index > 0)//������Ҷ��
		{
			code[*i].string[(*j)++] = 0;
			coding(&root->left, code_, i, j, c_flag);
			if (c_flag)goto end;
		}
		if (root->right->index == -1)//�ҷ��ʷ�Ҷ�ӽڵ�
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
		if (root->right->index > 0)//������Ҷ��
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

//������д������
int* write_to_result_code(int* result_code, int* string, int* r_index)
{
	int i = 0;
	while (string[i] == 0 || string[i] == 1)
	{
		result_code[(*r_index)++] = string[i++];
	}
	return result_code;
}

//���ַ������룬ƥ���ַ��ͱ�����е��ַ�������Ӧ����д��������
int* codestring(huffmancode* code, char* string, int length)
{
	int i = 0, num = 0, j = 0, result_index = 0;//result_indexΪ��һ��д���������еı����±�
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

