#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ch[1000];	//�洢���ļ��ж��������
char temp_str[100];		//�洢һ�ζ�ȡ���ַ���
struct ch_str{		//�洢ʶ����ַ���
	int num;
	int add;
	char content[30];
}ch_str[100];
int ch_str_len = 0;
char ch_num[50][100];	//������
int ch_num_len = 0;
char ch_id[50][100];	//��ʶ����
int ch_id_len = 0;

char* keyword[] = { "��ʶ��", "����", "if", "then", "else", "while", "do", "begin", "end"};
int keyword_len = 9;

void getFileContent(){	//���ļ����ݶ�ȡ��������
	char temp[100];
	FILE *fp = fopen("input.txt","r");
	if (!fp)
	{
		printf("can't open file\n");
	}
	do{
		fscanf(fp, "%s", &temp);	//���ж�������
		strcat(ch, temp);	//��һ�е����ݸ��Ƶ�ch�ַ���β��
	} while (!feof(fp));
}

int isLetter(char p){
	if ((p >= 'A'&&p <= 'Z') || (p >= 'a'&&p <= 'z'))
		return 1;
	else
		return 0;
}

int isNumber(char p){
	if (p >= '0'&&p <= '9')
		return 1;
	else
		return 0;
}

void resetStr(char* p){		//���ַ�������
	int i = 0;
	while (p[i++] != '\0')//�жϲ��ǿյĻ�������Ϊ��
		p[i - 1] = '\0';
}

void push(char* p, char a){
	int p_len = strlen(p);
	p[p_len] = a;
}

int isKeyword(char* p){
	for (int i = 0; i < keyword_len; i++){
		if (strcmp(p, keyword[i]) == 0){
			return i + 3;
		}
	}
	return 0;
}

void identify(char* p){
	int i;
	int flag = 0;
	for (i = 0; p[i] != '\0'&&p[i] != '#'; i++){
		resetStr(temp_str);
		if (isLetter(p[i]) == 1){
			push(temp_str, p[i]);
			i++;
			for (i; p[i] != '\0'&&p[i] != '#'; i++){
				if (isLetter(p[i]) == 1||isNumber(p[i]) == 1){
					push(temp_str, p[i]);
				}
				else{
					i--;
					break;
				}
			}
			if (isKeyword(temp_str) != 0){
				ch_str[ch_str_len].num = isKeyword(temp_str);
				strcpy(ch_str[ch_str_len].content, temp_str);
				ch_str_len++;
			}
			else{
				flag = 0;
				int ii = 0;
				for (ii = 0; ii < ch_id_len; ii++){	//�ж��ַ����Ƿ��Ѿ������ڱ�ʶ������
					if (strcmp(temp_str, ch_id[ii]) == 0){
						flag = 1;
						break;
					}
				}
				if (flag == 0){		//����ַ����������ڱ�ʶ��������������ʶ����
					ch_str[ch_str_len].num = 1;
					strcpy(ch_str[ch_str_len].content, temp_str);
					strcpy(ch_id[ch_id_len], temp_str);
					ch_str[ch_str_len].add = (int)ch_id[ch_id_len];
					ch_str_len++;
					ch_id_len++;
				}
				else if (flag == 1){		//����ַ��������ڱ�ʶ�������򲻼���
					ch_str[ch_str_len].num = 1;
					strcpy(ch_str[ch_str_len].content, temp_str);
					ch_str[ch_str_len].add = (int)ch_id[ii];
					ch_str_len++;
				}

			}
			resetStr(temp_str);
		}
		else if (isNumber(p[i]) == 1){
			push(temp_str, p[i]);
			i++;
			for (i; p[i] != '\0'&&p[i] != '#'; i++){
				if (isNumber(p[i]) == 1){
					push(temp_str, p[i]);
				}
				else{
					i--;
					break;
				}
			}
			flag = 0;
			int ii = 0;
			for (ii = 0; ii < ch_num_len; ii++){	//�жϳ����Ƿ��Ѿ������ڳ�������
				if (strcmp(temp_str, ch_num[ii]) == 0){
					flag = 1;
					break;
				}
			}
			if (flag == 0){
				ch_str[ch_str_len].num = 2;
				strcpy(ch_str[ch_str_len].content, temp_str);
				strcpy(ch_num[ch_num_len], temp_str);
				ch_str[ch_str_len].add = (int)ch_num[ch_num_len];
				ch_str_len++;
				ch_num_len++;
			}
			else if (flag == 1){
				ch_str[ch_str_len].num = 2;
				strcpy(ch_str[ch_str_len].content, temp_str);
				ch_str[ch_str_len].add = (int)ch_num[ii];
				ch_str_len++;
			}
			resetStr(temp_str);
		}
		else{
			switch (p[i]){
			case '+':
				ch_str[ch_str_len].num = 31;
				ch_str[ch_str_len].content[0] = '+';
				ch_str_len++;
				break;
			case '-':
				ch_str[ch_str_len].num = 32;
				ch_str[ch_str_len].content[0] = '-';
				ch_str_len++;
				break;
			case '*':
				ch_str[ch_str_len].num = 33;
				ch_str[ch_str_len].content[0] = '*';
				ch_str_len++;
				break;
			case '/':
				ch_str[ch_str_len].num = 34;
				ch_str[ch_str_len].content[0] = '/';
				ch_str_len++;
				break;
			case '>':
				i++;
				if (p[i] == '='){
					ch_str[ch_str_len].num = 36;
					ch_str[ch_str_len].content[0] = '>';
					ch_str[ch_str_len].content[1] = '=';
					ch_str_len++;
				}
				else{
					i--;
					ch_str[ch_str_len].num = 35;
					ch_str[ch_str_len].content[0] = '>';
					ch_str_len++;
				}
				break;
			case '<':
				i++;
				if (p[i] == '='){
					ch_str[ch_str_len].num = 38;
					ch_str[ch_str_len].content[0] = '<';
					ch_str[ch_str_len].content[1] = '=';
					ch_str_len++;
				}
				else{
					i--;
					ch_str[ch_str_len].num = 37;
					ch_str[ch_str_len].content[0] = '<';
					ch_str_len++;
				}
				break;
			case '=':
				ch_str[ch_str_len].num = 39;
				ch_str[ch_str_len].content[0] = '=';
				ch_str_len++;
				break;
			case '(':
				ch_str[ch_str_len].num = 40;
				ch_str[ch_str_len].content[0] = '(';
				ch_str_len++;
				break;
			case ')':
				ch_str[ch_str_len].num = 41;
				ch_str[ch_str_len].content[0] = ')';
				ch_str_len++;
				break;
			case '{':
				ch_str[ch_str_len].num = 42;
				ch_str[ch_str_len].content[0] = '{';
				ch_str_len++;
				break;
			case '}':
				ch_str[ch_str_len].num = 43;
				ch_str[ch_str_len].content[0] = '}';
				ch_str_len++;
				break;
			case ';':
				ch_str[ch_str_len].num = 44;
				ch_str[ch_str_len].content[0] = ';';
				ch_str_len++;
				break;
			case ',':
				ch_str[ch_str_len].num = 45;
				ch_str[ch_str_len].content[0] = ',';
				ch_str_len++;
				break;
			case '#':
				break;
			}
		}
	}
}

void writeToFile(){
	/*
		�Ѵʷ��������д��ch_str.txt
	*/
	if (freopen("ch_str.txt", "a", stdout) == NULL)
		printf("error redirecting stdout");
	printf("����\t����\t����ֵ\t\n");
	for (int j = 0; j < ch_str_len; j++){
		printf("%d\t", ch_str[j].num);
		printf("%s\t", ch_str[j].content);
		if (ch_str[j].add == 0)
			printf("/\n");
		else{
			printf("%d\t\n", ch_str[j].add);
		}
	}
	fclose(stdout);

	/*
		�ѱ�ʶ����д��identify.txt
	*/
	if (freopen("identify.txt", "a", stdout) == NULL)
		printf("error redirecting stdout");
	printf("ָ���ַ\t����\t\n");
	for (int j = 0; j < ch_id_len; j++){
		printf("%d\t", ch_id[j]);
		printf("%s\t\n", ch_id[j]);
	}
	fclose(stdout);

	/*
		�ѳ�����д��number.txt
	*/
	if (freopen("number.txt", "a", stdout) == NULL)
		printf("error redirecting stdout");
	printf("ָ���ַ\t����\t\n");
	for (int j = 0; j < ch_num_len; j++){
		printf("%d\t", ch_num[j]);
		printf("%s\t\n", ch_num[j]);
	}
	fclose(stdout);
}

int main(void){
	getFileContent();
	printf("%s\n",ch);
	identify(ch);
	writeToFile();
	system("PAUSE");
	return 0;
}