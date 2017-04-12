#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ch[1000];	//存储从文件中读入的数据
char temp_str[100];		//存储一次读取的字符串
struct ch_str{		//存储识别的字符串
	int num;
	int add;
	char content[30];
}ch_str[100];
int ch_str_len = 0;
char ch_num[50][100];	//常数表
int ch_num_len = 0;
char ch_id[50][100];	//标识符表
int ch_id_len = 0;

char* keyword[] = { "标识符", "常数", "if", "then", "else", "while", "do", "begin", "end"};
int keyword_len = 9;

void getFileContent(){	//将文件内容读取到数组中
	char temp[100];
	FILE *fp = fopen("input.txt","r");
	if (!fp)
	{
		printf("can't open file\n");
	}
	do{
		fscanf(fp, "%s", &temp);	//逐行读入数据
		strcat(ch, temp);	//将一行的数据复制到ch字符串尾部
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

void resetStr(char* p){		//将字符串清零
	int i = 0;
	while (p[i++] != '\0')//判断不是空的话就让它为空
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
				for (ii = 0; ii < ch_id_len; ii++){	//判断字符串是否已经存在于标识符表中
					if (strcmp(temp_str, ch_id[ii]) == 0){
						flag = 1;
						break;
					}
				}
				if (flag == 0){		//如果字符串不存在于标识符表中则将其加入标识符表
					ch_str[ch_str_len].num = 1;
					strcpy(ch_str[ch_str_len].content, temp_str);
					strcpy(ch_id[ch_id_len], temp_str);
					ch_str[ch_str_len].add = (int)ch_id[ch_id_len];
					ch_str_len++;
					ch_id_len++;
				}
				else if (flag == 1){		//如果字符串存在于标识符表中则不加入
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
			for (ii = 0; ii < ch_num_len; ii++){	//判断常数是否已经存在于常数表中
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
		把词法分析结果写入ch_str.txt
	*/
	if (freopen("ch_str.txt", "a", stdout) == NULL)
		printf("error redirecting stdout");
	printf("类型\t单词\t自身值\t\n");
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
		把标识符表写入identify.txt
	*/
	if (freopen("identify.txt", "a", stdout) == NULL)
		printf("error redirecting stdout");
	printf("指针地址\t内容\t\n");
	for (int j = 0; j < ch_id_len; j++){
		printf("%d\t", ch_id[j]);
		printf("%s\t\n", ch_id[j]);
	}
	fclose(stdout);

	/*
		把常数表写入number.txt
	*/
	if (freopen("number.txt", "a", stdout) == NULL)
		printf("error redirecting stdout");
	printf("指针地址\t内容\t\n");
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