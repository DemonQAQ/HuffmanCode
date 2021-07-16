/*----------------------------------------------------------------
// ��Ȩ����
//
// �ļ�����fnormal.cpp
// �ļ�������������������
// ���ߣ�Demon
// ʱ�䣺2021.6.19
//----------------------------------------------------------------*/
#include "function.h"

//ˢ�»�����
void flash()
{
	scanf("%*[^\n]"); //��ջ����������һ��\nǰ���������ݣ��ٶ�ȡ�����һ��\n
	scanf("%*c");
}

//�������ȡ����
int scanf_num(TYPE_INPUT_NUM* num, TYPE_INPUT_NUM max, TYPE_INPUT_NUM min)//��ΧΪ������
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
	printf("[��ʾ]:������������[%d - %d]�ڵ���ֵ\n", min_t, max_t);
	do
	{
		if (flag != -1)flash();
		flag = scanf("%lf", &num_temp);
		if (!flag)
			printf("[��ʾ]:�����������ʹ���,����������\n");
		if (num_temp > max_t || num_temp < min_t)
			printf("[��ʾ]:����������[%d - %d]�ڵ�����\n", min_t, max_t);
	} while (!flag || num_temp > max_t || num_temp < min_t);
	*num = (TYPE_INPUT_NUM)num_temp;
	return 1;
}

//�����ļ��� ��ʽ- data_%Y%m%d_%H%M%S.txt
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

//����ַ������ȣ�����TRIGGER_NUM���ַ������нضϣ��ضϳ���ΪFRAGEMNT_LENGTH
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

//����ַ������Ƿ��к���
int char_check(char* string)
{
	if (!string)return -2;
	int i = 0;
	while (string[i] != '\0')
	{
		if (string[i] < 0)return -1;//����ascii��С��0
		else i++;
	}
	return 0;
}

//����Ƶ�ȱ�
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

//��ӡ������
int vec_left[NORMAL_NUM];
void tree_display(btree* root, int ident)
{
	if (ident > 0)
	{
		for (int i = 0; i < ident - 1; ++i)
		{
			printf(vec_left[i] ? "��   " : "    ");
		}
		printf(vec_left[ident - 1] ? "������ " : "������ ");
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

//���ڱ�����麯�����ж��Ƿ�����ͬ����
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

//��������Ƿ����Ҫ��
int check_code_list(huffmancode* code, int num)
{
	int i = 0, j = 0, index = 0;
	bool flag = false;
	char temp = 0;
	if (num == 1)goto next_check;
	else
	{
		for (i = 0; i < num - 1; i++)//�Ƚ��Ƿ�����ͬ�ַ�
		{
			temp = code[i].c;
			for (j = i + 1; j < num; j++)
			{
				if (temp == code[j].c)return 0;
			}
		}
	}
next_check:
	for (i = 0; i < num; i++)//�Ƚ��Ƿ��ɷ�01�ı����ձ���
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
		for (i = 0; i < num; i++)//����Ƿ�����ͬ����
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

//�Ӽ��̶���շ�������
huffmancode* input_code_list_keybroad(int* table_length)
{
	int num = 0, i = 0, j = 0, flag = 0, temp = 0;
	huffmancode* code = NULL;
	printf("����������\n");
	scanf_num(&num, 32767, 0);
	code = (huffmancode*)malloc(num * sizeof(huffmancode));
	if (!code)exit(-1);
	for (i = 0; i < num; i++)
	{
		j = 0;
		flash();
		printf("[��ʾ]:�����뵥���ַ��������ַ�������ȡ��һ���ַ�\n");
		scanf("%c", &code[i].c);
		printf("[��ʾ]:����������������01��ɵı���,ÿ������һλ���룬����-1��������\n");
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
		printf("[��ʾ]:��ȡ�ɹ�\n");
		system("pause");
		return code;
	}
	else
	{
		*table_length = 0;
		printf("[��ʾ]:��ȡʧ�ܣ���������\n");
		system("pause");
		return NULL;
	}
}

//�������Ĵ��봮�Ƿ�Ϲ�
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

//��������
void display_codelist(huffmancode* code, int length)
{
	int i = 0, j = 0;
	printf("�����:\n[��ʾ]:��ʽΪ ��ĸ  --  ��Ӧ����\n");
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

//������봮
void display_codestring(int* string)
{
	int i = 0;
	printf("���ַ���ת���ɵı���Ϊ:\n");
	while (string[i] == 0 || string[i] == 1)printf("%d", string[i++]);
	printf("\n");
}

//�������
void display_decodestring(char* string)
{
	printf("�ɱ��뷭������ַ���Ϊ:\n");
	printf("%s", string);
	system("pause");
}

//���������ļ�
void file_codelist(huffmancode* code, int length)
{
	FILE* fp;
	char temp[STRING_MAX_NUM] = { "code" };
	char* name = temp;
	//name = file_name(temp);
	if ((fp = fopen(name, "wb+")) == NULL)
	{
		puts("[��ʾ]:�޷������ļ�\n");
		system("pause");
		exit(-1);
	}
	fwrite(code, sizeof(struct huffmancode), length, fp);
	fclose(fp);
	printf("[��ʾ]:������� code.txt\n");
	system("pause");
}

//������봮���ļ�
void file_codestring(int* string)
{
	int i = 0;
	FILE* fp;
	char temp[STRING_MAX_NUM] = { "code_string" };
	char* name = temp;
	//name = file_name(temp);
	if ((fp = fopen(name, "w+")) == NULL)
	{
		puts("�޷������ļ�\n");
		system("pause");
		exit(-1);
	}
	while (1)
	{
		if (string[i] == 0 || string[i] == 1)fprintf(fp, "%d", string[i++]);
		else break;
	}
	fclose(fp);
	printf("[��ʾ]:������� code_string.txt\n");
	system("pause");
}

//������봮���ļ�
void file_decodestring(char* string)
{
	FILE* fp;
	char temp[STRING_MAX_NUM] = { "decode_string" };
	char* name = temp;
	name = file_name(temp);
	if ((fp = fopen(name, "w+")) == NULL)
	{
		puts("�޷������ļ�\n");
		system("pause");
		exit(-1);
	}
	fputs(string, fp);
	fclose(fp);
	printf("[��ʾ]:������� decode_string.txt\n");
	system("pause");
}

//���ļ�����շ��������
huffmancode* input_code_list_file(int* table_length)
{
	int num = 0, i = 0;
	huffmancode* code = NULL;
	FILE* fp;
	char name[CHAR_MAX] = { '\0' };
	flash();
	printf("[��ʾ]:���������׺���ļ���������code.log\n");
	scanf("%s", name);
	flash();
	if ((fp = fopen(name, "rb+")) == NULL)
	{
		printf("[��ʾ]:���ļ�ʧ�ܣ������ļ���\n");
		system("pause");
		return NULL;
	}
	printf("[��ʾ]:����������\n");
	scanf_num(&num, 32767, 0);
	code = (huffmancode*)malloc(num * sizeof(huffmancode));
	if (!code)exit(-1);
	fread(code, sizeof(struct huffmancode), num, fp);
	if (check_code_list(code, num))
	{
		*table_length = num;
		printf("[��ʾ]:��ȡ�ɹ�\n");
		system("pause");
		return code;
	}
	else
	{
		*table_length = 0;
		printf("[��ʾ]:��ȡʧ�ܣ���������\n");
		system("pause");
		return NULL;
	}
	fclose(fp);
}

//���ļ������ַ���
char* file_input_string()
{
	char* string = NULL;
	FILE* fp;
	int num = 0, i = 0;
	char name[CHAR_MAX] = { '\0' };
	flash();
	printf("[��ʾ]:���������׺���ļ���������string.log\n");
	scanf("%s", name);
	flash();
	if ((fp = fopen(name, "r+")) == NULL)
	{
		printf("[��ʾ]:���ļ�ʧ�ܣ������ļ���\n");
		system("pause");
		return NULL;
	}
	printf("[��ʾ]:���������ȡ���ַ����ĳ���\n");
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
		printf("[��ʾ]:��ȡ�ɹ�\n");
		return string;
	}
	else return NULL;
}

//���ļ���������봮
char* file_input_decodestring()
{
	int num = 0, i = 0;
	char* decode_string = NULL;
	char name[CHAR_MAX] = { '\0' };
	FILE* fp;
	flash();
	printf("[��ʾ]:���������׺���ļ���������string.log\n");
	scanf("%s", name);
	flash();
	if ((fp = fopen(name, "r+")) == NULL)
	{
		printf("[��ʾ]:���ļ�ʧ�ܣ������ļ���\n");
		system("pause");
		return NULL;
	}
	printf("[��ʾ]:���������ȡ���ַ����ĳ���\n");
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

//�Ӽ��̶�ȡ�ַ���
char* string_input_keyboard()
{
	char s[STRING_MAX_NUM];
	char* temp = s;
	do
	{
		flash();
		gets_s(s, STRING_MAX_NUM);
		if (char_check(s) == -1)printf("[��ʾ]:�������뺺�֣�����������\n");
		else break;
	} while (1);
	temp = string_check(s);
	return temp;
}

//�Ӽ�������������
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