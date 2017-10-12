#define _CRT_SECURE_NO_WARNINGS //2012年以后版本的visual studio禁止使用fopen，除非添加这一宏定义
#include<iostream>
#include<vector> 
#include<set> 
#include<string>
#include<conio.h>
using namespace std;
int NUM;

class SUBJECT              
{
 public:
 int Sno;          
 char Sname[30];    
 char Scha[20];     
 int Sxf, Stime;
 char Sterm[20];
 char Stest[20];
}S;         

class STUDENT                                 
{
public:
	char Stu_name[10];    
	char Stu_sno[15];  
}Stu;           

vector <SUBJECT> Sub;                     
vector <STUDENT> Z;                       
set <int> T;                              
vector <set<int> > TT;                    
set <int> ::iterator s;                  

int Find(int no);  
void Display_sub_info(int i);
void Save(); 
void Output();
void Load_sub();
void Load_stu();
void Getsno1();
void Getsno2();
void Quit();
void Log_in();							  
void Menu();                              
void Search_Menu();                       
void Search_xf();                         
void Search_scha();                      
void Search_sterm();
void Search_stest();                          
void Add_sub_info();                         
void Add_stu_info();   
void Save_stu_info();
void Del_sub_info();
void XuanKeMenu();
void Xuanke();
         
int Find(int no)                           //查找课程编号
{
	for (int i = 0; i<Sub.size(); i++)
	if (Sub[i].Sno == no) return i;
}

void Display_sub_info(int i)              //显示已选课程信息
{
	printf("\t    %3d%12s%8s%4d%6d%8s%8s\n",Sub[i].Sno, Sub[i].Sname, Sub[i].Scha, Sub[i].Stime, Sub[i].Sxf, Sub[i].Sterm, Sub[i].Stest);
}

void Save()                               //保存已选课程信息
{
	FILE *fp;
	fp = fopen("C:\\subject.txt", "a");
	for (int i = 0; i<Sub.size(); i++)
		fprintf(fp, "%d %s %s %d %d %s %s\n", Sub[i].Sno, Sub[i].Sname,Sub[i].Scha, Sub[i].Sxf, Sub[i].Stime, Sub[i].Sterm, Sub[i].Stest);
	fprintf(fp, "%s %s\n", Stu.Stu_sno, Stu.Stu_name);
	fclose(fp);
}

void Output()                             //显示已选课程信息
{
	system("cls");
	int i = 0;
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t                   课程信息                 " << endl;
	cout << "                                                " << endl;
	cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
	for (s = TT[NUM].begin(); s != TT[NUM].end(); s++, i++)   
	{
		if (i && i % 10 == 0)
		{
			cout << "                                                " << endl;
			cout << "\t    按任意键查看下一页";
			getchar();
			system("cls");
			cout << endl << endl << endl << endl << endl;
			cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
			cout << "                                                " << endl;
			cout << "\t\t                   课程信息                 " << endl;
			cout << "                                                " << endl;
			cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
		}
	    Display_sub_info(Find(*s)); 
	}
	cout << endl << "\t    若继续查看请输入[Y]，否则输入[N]:";
	string s; 
	cin >> s;
	if (s[0] == 'Y' || s[0] == 'y') Output();
	else Menu();
}

void Load_sub()                         //载入全部课程信息
{
	FILE *fp1;
	bool f = 1;
	fp1 = fopen("C:\\subject.txt", "r");
	if (fp1 == NULL) f = 0;
	while (f&&!feof(fp1))  
	{
		fscanf(fp1, "%d%s%s%d%d%s%s", &S.Sno, S.Sname, S.Scha, &S.Sxf, &S.Stime, &S.Sterm, &S.Stest);
		Sub.push_back(S);
	}
	fclose(fp1);
}

void Load_stu()                          //载入全部学生信息
{
	FILE *fp;
	fp = fopen("C:\\student.txt", "r");
	while (!feof(fp))
	{
		int x;
		fscanf(fp, "%s%s", Stu.Stu_sno, &Stu.Stu_name);
		Z.push_back(Stu); T.clear();
		fscanf(fp, "%d", &x), T.insert(x);
		TT.push_back(T);
	}
	fclose(fp);
}

void Getsno1(char *str)                 //获取所选课程的编号
{
	string t = "";
	int i = 0, cont = 0;
	while (str[i])
	{
		if (isalnum(str[i]))  
			t += str[i]; 
		else
		{
			int tmp = atoi(t.c_str()); 
			if (TT[NUM].find(tmp) != TT[NUM].end())
			{
				t = ""; i++; continue;
			}
			TT[NUM].insert(tmp); t = "";
			cont++;
		}
		i++;
	}
	int tmp = atoi(t.c_str());
	if (TT[NUM].find(tmp) == TT[NUM].end())
	{
		cont++;
		TT[NUM].insert(tmp);
	}
}

void Getsno2(char *str)                   //获取要删除课程的编号
{
	string t = "";
	int i = 0, cont = 0;
	while (str[i])
	{
		if (isalnum(str[i]))
			t += str[i];
		else
		{
			int tmp = atoi(t.c_str());
			set<int>::iterator _t = TT[NUM].find(tmp); 
			if (_t != TT[NUM].end())
			{
				t = "";
				TT[NUM].erase(_t);
			}
		}
		i++;
	}
	int tmp = atoi(t.c_str());
	set<int>::iterator _t = TT[NUM].find(tmp);
	if (_t != TT[NUM].end())
	{
		t = "";
		TT[NUM].erase(_t);
	}
}

void Quit()
{
	exit(1);
}

void Log_in()                                             
{
	int f;
	char stuno[25];
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t                             退出请输入[hhh]" << endl;
	cout << "                                                " << endl;
	cout << "\t\t  请输入您的学号:";
	cin >> stuno;
	if (!strcmp(stuno, "hhh")) Quit();
	{for (unsigned int i = 0; i < Z.size(); i++)
	if (!strcmp(stuno, Z[i].Stu_sno)){f = 0; NUM = i; Menu(); break;}
	else{f = 1;}}
	if (f != 0)
	{cout << "                                                " << endl;
	 cout << "                                                " << endl;
	 cout << "                                                " << endl;
	 cout << "\t\t  无此信息,请通过[Y/N]决定是否添加该学生信息:";
	 char sx;
	 cin >> sx;
	 if (sx == 'Y' || sx == 'y') Add_stu_info();
	 Log_in();}
}

void Menu()                                      
{
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t                          当前用户名: " << Z[NUM].Stu_name << endl;
	cout << "                                                " << endl;
	cout << "\t\t  当前功能:                                 " << endl;
	cout << "                                                " << endl;
	cout << "\t\t    [1]学生课程信息  [2]添加课程信息(教务处)" << endl;
	cout << "\t\t    [3]查询课程信息  [4]更改课程信息(学生)  " << endl;
	cout << "\t\t    [5]退        出  [6]待定功能预留        " << endl;
	cout << "                                                " << endl;
	cout << "\t\t  请选择[1-5]:";
	int choice;
	cin >> choice;
	if (choice >= 1 && choice <= 5)
	{
		if (choice == 1) Output();
		if (choice == 2) Add_sub_info();
		if (choice == 3) Search_Menu();
		if (choice == 4) XuanKeMenu();
		if (choice == 5) Log_in();
	}
	else  Menu();
}

void Search_Menu()                         //查询主菜单函数
{
	system("cls"); 
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t  请选择查询方式:                           " << endl;
	cout << "                                                " << endl;
	cout << "                  [1]学分查询 [2]课程性质查询 [3]开课学期查询 " << endl;
	cout << "\t\t  [4]考试形式查询 [5]退        出           " << endl;
	cout << "                                                " << endl;
	cout << "\t\t  请选择[1-5]：";
	int choice;
	cin >> choice;
	if (choice >= 1 && choice <= 5)
	{
		if (choice == 1) Search_xf();     //按学分来查询
		if (choice == 2) Search_scha();   //按课程性质查询
		if (choice == 3) Search_sterm();  //按开课学期查询
		if (choice == 4) Search_stest();  //按考试形式查询
		if (choice == 5) Menu();
	}
	else  Search_Menu();
}

void Search_xf()                          
{
	system("cls");  
	int Course_num = 0; 
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t  请输入要查询的学分：";
	int key;
	cin >> key;
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t                   课程信息                 " << endl;
	cout << "                                                " << endl;
	cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
	for (int i = 0; i<Sub.size(); i++)
	{
		if (Course_num && Course_num%10 == 0)
		{
			cout << "\t    按任意键查看下一页"; 
			getchar();
			system("cls");
			cout << endl << endl << endl << endl << endl;
			cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
			cout << "                                                " << endl;
			cout << "\t\t                   课程信息                 " << endl;
			cout << "                                                " << endl;
			cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
		}
		if (Sub[i].Sxf == key)
		{
			Course_num++;
			printf("\t    %3d%12s%8s%4d%6d%8s%8s\n",Sub[i].Sno, Sub[i].Sname, Sub[i].Scha, Sub[i].Sxf, Sub[i].Stime, Sub[i].Sterm, Sub[i].Stest);
		}
	}
	cout << endl << "\t  是否继续查询[Y/N]:";
	string s; 
	cin >> s;
	if (s[0] == 'Y' || s[0] == 'y') Search_xf();
	else Menu();
}

void Search_scha()                           
{
	system("cls");
	int Course_num = 0;
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t  请输入课程性质：";
	char key[20];
	cin >> key;
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t                   课程信息                 " << endl;
	cout << "                                                " << endl;
	cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
	for (int i = 0; i<Sub.size(); i++) 
	{
		if (Course_num && Course_num % 10 == 0)
		{
			cout << "\t\t   按任意键查看下一页"; 
			getchar();
			system("cls"); 
			cout << endl << endl << endl << endl << endl;
			cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
			cout << "                                                " << endl;
			cout << "\t\t                   课程信息                 " << endl;
			cout << "                                                " << endl;
			cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
		}
		if (!strcmp(Sub[i].Scha, key))
		{
			Course_num++;
			printf("\t    %3d%12s%8s%4d%6d%8s%8s\n",Sub[i].Sno, Sub[i].Sname, Sub[i].Scha, Sub[i].Sxf, Sub[i].Stime, Sub[i].Sterm, Sub[i].Stest);
		}
	}
	cout << endl << "\t\t  是否继续查询[Y/N]:";
	string s; 
	cin >> s;
	if (s[0] == 'Y' || s[0] == 'y') Search_scha();
	else Menu();
}

void Search_sterm()                           
{
	system("cls");
	int Course_num = 0;
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t  请输入开课学期：";
	char key[20];
	cin >> key;
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t                   课程信息                 " << endl;
	cout << "                                                " << endl;
	cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
	for (int i = 0; i<Sub.size(); i++) 
	{
		if (Course_num && Course_num % 10 == 0)
		{
			cout << "\t\t   按任意键查看下一页"; getchar();
			system("cls");
			cout << endl << endl << endl << endl << endl;
			cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
			cout << "                                                " << endl;
			cout << "\t\t                   课程信息                 " << endl;
			cout << "                                                " << endl;
			cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
		}
		if (!strcmp(Sub[i].Sterm, key))
		{
			Course_num++;
			printf("\t    %3d%12s%8s%4d%6d%8s%8s\n", Sub[i].Sno, Sub[i].Sname, Sub[i].Scha, Sub[i].Sxf, Sub[i].Stime, Sub[i].Sterm, Sub[i].Stest);
		}
	}
	cout << endl << "\t\t  是否继续查询[Y/N]:";
	string s; 
	cin >> s;
	if (s[0] == 'Y' || s[0] == 'y') Search_sterm();
	else Menu();
}

void Search_stest()                           
{
	system("cls");
	int Course_num = 0;
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t  请输入考试形式：";
	char key[20];
	cin >> key;
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t                   课程信息                 " << endl;
	cout << "                                                " << endl;
	cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
	for (int i = 0; i<Sub.size(); i++) 
	{
		if (Course_num && Course_num % 10 == 0)
		{
			cout << "\t\t   按任意键查看下一页"; getchar();
			system("cls");
			cout << endl << endl << endl << endl << endl;
			cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
			cout << "                                                " << endl;
			cout << "\t\t                   课程信息                 " << endl;
			cout << "                                                " << endl;
			cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
		}
		if (!strcmp(Sub[i].Stest, key))
		{
			Course_num++;
			printf("\t    %3d%12s%8s%4d%6d%8s%8s\n", Sub[i].Sno, Sub[i].Sname, Sub[i].Scha, Sub[i].Sxf, Sub[i].Stime, Sub[i].Sterm, Sub[i].Stest);
		}
	}
	cout << endl << "\t\t  是否继续查询[Y/N]:";
	string s; 
	cin >> s;
	if (s[0] == 'Y' || s[0] == 'y') Search_stest();
	else Menu();
}

void Add_sub_info()                    //教务处添加课程信息
{
	int password = 0;
	system("cls");       
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t  请输入密码：";
	cin >> password;
	if (password == 666)
	{
	cout << "\t\t  请输入课程号:";
	cin >> S.Sno;
	cout << "\t\t  请输入课程名:";
	cin >> S.Sname;
	cout << "\t\t  请输入课程属性:";
	cin >> S.Scha;
	cout << "\t\t  请输入学分:";
	cin >> S.Sxf;
	cout << "\t\t  请输入课程总学时:";
	cin >> S.Stime;
	cout << "\t\t  请输入开课学期:";
	cin >> S.Sterm;
	cout << "\t\t  请输入考试形式:";
	cin >> S.Stest;
	Sub.push_back(S);
	Save(); 
	cout << endl << "\t\t  是否继续添加[Y/N]:";
	string s; cin >> s;
	if (s[0] == 'Y' || s[0] == 'y') Add_sub_info();
	else Menu();
	}
	else Menu();
}

void Add_stu_info()                  //添加学生信息         
{
	FILE *fp;    
    fp = fopen("C:\\student.txt", "a"); 
	fseek(fp, 0, 2);           
	system("cls");  
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t  请输入要添加的学号："; cin >> Stu.Stu_sno;
	cout << "\t\t  请输入要添加的姓名："; cin >> Stu.Stu_name;
	fprintf(fp, "%s %s\n", Stu.Stu_sno, Stu.Stu_name);
	Z.push_back(Stu);  
	T.clear(); 
	TT.push_back(T);   
	fclose(fp); 
}

void Save_stu_info()                    //保存学生信息
{
	FILE *fp;
	fp = fopen("C:\\student.txt", "a");
	for (unsigned int i = 0; i<Z.size(); i++)
	{
	 fprintf(fp, "%s %s", Z[i].Stu_sno, Z[i].Stu_name);
	 for (s = TT[i].begin(); s != TT[i].end(); s++)
	 fprintf(fp, " %d", *s);
	 fprintf(fp, "\n");
	}
	fclose(fp);
}

void Del_sub_info()                      //删除已选课程信息
{
	int m, i = 0, k = 0;
	char str[200];
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t姓名:" << Z[NUM].Stu_name << "  学号:" << Z[NUM].Stu_sno << endl;
	cout << "                                                " << endl;
	cout << "\t     课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
	for (s = TT[NUM].begin(); s != TT[NUM].end(); s++, i++)
	{
		if (i && i%10 == 0)
		{
			cout << "\t\t  请输入要删除的课程的编号，按[0]退出："; 
			gets(str);
			if (strcmp(str, "")) Getsno2(str);
			system("cls");
			cout << endl << endl << endl << endl << endl;
			cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
			cout << "                                                " << endl;
			cout << "\t\t姓名:" << Z[NUM].Stu_name << "  学号:" << Z[NUM].Stu_sno << endl;
			cout << "                                                " << endl;
			cout << "\t     课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
		}
		Display_sub_info(Find(*s));
	}
	cout << "                                                " << endl;
	cout << "\t\t  请输入要删除的课程的编号，按[0]退出："; 
	gets(str);
	if (strcmp(str, "")) Getsno2(str);
	Save_stu_info();
	XuanKeMenu();
}

void XuanKeMenu()                  //选课主菜单
{
	system("cls");
	int choice, i = 0;
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t    国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t     姓名:" << Z[NUM].Stu_name << "  学号:" << Z[NUM].Stu_sno << endl;
	cout << "                                                " << endl;
	cout << "\t     已选课程信息:\n";
	cout << "                                                " << endl;
	cout << "\t     课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
	for (s = TT[NUM].begin(); s != TT[NUM].end(); s++, i++)  
	{
		if (i && i % 10 == 0)
		{
			cout << "\t     [1]开始选课 [2]删除已选课程 [3]下一页 [4]退  出:";
			cin >> choice;
			getchar();
			if (choice == 1) Xuanke();
			else if (choice == 2) Del_sub_info();
			else if (choice == 4) Menu();
			else if (choice == 3);
			else XuanKeMenu();
			system("cls");
			cout << endl << endl << endl << endl << endl;
			cout << "\t\t    国际关系学院2014级信息科技学院学生选课系统" << endl;
			cout << "                                                " << endl;
			cout << "\t     姓名:" << Z[NUM].Stu_name << "  学号:" << Z[NUM].Stu_sno << endl;
			cout << "                                                " << endl;
			cout << "\t     已选课程信息:\n";
			cout << "                                                " << endl;
			cout << "\t     课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
		}
		Display_sub_info(Find(*s)); 
	}
	cout << "                                                " << endl;
	cout << "\t     [1]开始选课 [2]删除已选课程 [3]下一页 [4]退  出:";
	cin >> choice;
	getchar();
	if (choice == 1) Xuanke();
	else if (choice == 2) Del_sub_info();
	else if (choice == 4) Menu();
	else XuanKeMenu();
}

void Xuanke()                            //具体的选课函数
{
	char str[200];
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
	cout << "                                                " << endl;
	cout << "\t\t                   课程信息                 " << endl;
	cout << "                                                " << endl;
	cout << "\t    课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
	for (int i = 0; i<Sub.size(); i++)
	{
		if (i && i % 10 == 0)
		{
			cout << endl << "\t    请输入所选课程编号，按[0]退出：";
			gets(str);
			if (strcmp(str, "")) Getsno1(str);
			system("cls");
			cout << endl << endl << endl << endl << endl;
			cout << "\t\t  国际关系学院2014级信息科技学院学生选课系统" << endl;
			cout << "                                                " << endl;
			cout << "\t\t                   课程信息                 " << endl;
			cout << "                                                " << endl;
			cout << "\t     课程号 课程名 课程属性 学分 课程总学时 开课学期 考试形式" << endl << endl;
		}
		printf("\t    %3d%12s%8s%4d%6d%8s%8s\n", Sub[i].Sno, Sub[i].Sname, Sub[i].Scha, Sub[i].Sxf, Sub[i].Stime, Sub[i].Sterm, Sub[i].Stest);
	}
	cout << endl << "\t    请输入所选课程编号，按[0]退出：";
	gets(str);
	if (strcmp(str, "")) Getsno1(str);
	Save_stu_info();
	XuanKeMenu();
}

void main()
{
	Load_stu();               
	Z.erase(Z.end() - 1);      
	Load_sub();
	Sub.erase(Sub.end() - 1);
	TT.erase(TT.end() - 1); 
	Log_in();
}
