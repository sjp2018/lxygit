#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PASSWORD "Aplane007"
#define NUM 200
#define ROW 50

char password[20];       //密码
char name[20];           //姓名
char ID[20];             //身份证号
char inf[40]=" ";        //用户登陆信息
int selection;           //标志身份


struct airplane {
	int num;              //航班号
	char end[20];         //目的地
	char btime[20];       //起飞时间
	char etime[20];       //落地时间
	int count;            //剩余机票数
	char seat[ROW][6][40];//座位
	double price;         //票价
	int flag=0;           //标志是否录入航班信息
}plane[NUM];


int main();              //主函数
void home();             //主菜单（选择身份）
void login(int x);       //登陆函数
void administer();       //管理人员菜单
void user();             //用户菜单
void input();            //录入函数
void change();           //修改函数
void del();              //删除函数
void scan();             //预览函数
void sch();              //搜索函数（缩小目标航班范围）
void book();             //订票函数
void quit();             //退票函数
int schbynum(int x);     //通过航班号找数组下标
void seat(int x);        //打印座位信息
void assure();           //查询用户已定机票函数
void save();             //保存函数
void read();             //读取函数



int main()
{
	read();
	home();
	save();
	system("PAUSE");
    return 0;
}

void home()
{
	printf("========您好 ！票务人员请按 1 ，旅客请按 2 , 退出请按 0 .=========");
	scanf_s("%d",&selection);
	if (selection != 0 && selection != 1 && selection != 2)
	{
		printf("输入错误！请按要求输入 0 或 1 或 2 ");
		scanf_s("%d",&selection);
	}
	switch (selection)
	{
	case 1:login(1);
		break;
	case 2:login(2);
		break;
	default:break;
	}
}

void login(int x)
{
	int i,j;
	char blank[] = " ";
	if (x == 1)
	{
		printf("> > > > 请输入管理员密码：");
		scanf_s("%s", &password);
		if (strcmp(password,PASSWORD)==0)
			administer();
		else
		{
			for(j=1;j<3;j++)
			{
			    printf("* * * 密 码 错 误 ！* * *\n");
			    printf("重新输入密码，请输入 1(三次错误将退出程序） ；返回上级菜单，请输入 2 .\t");
			    scanf_s("%d",&i);
				if (i == 1)
				{
					printf("你还有%d次机会，", 3 - j);
					printf("请输入管理员密码：");
					scanf_s("%s", &password);
					if (strcmp(password, PASSWORD) == 0)
					{
						administer();
						break;
					}
				}
				else
				{
					home();
					break;
				}
			}
		}
	}
	else
	{
		do {
			printf("> > > > 请输入姓名：");
			scanf_s("%s", &name);
			printf("> > > > 请输入身份证号：");
			scanf_s("%d", &ID);
			printf("请再次确认姓名：%s, 身份证号：%d\n若无误，请输入1；若有误，请输入0.", name, ID);
			scanf_s("%d", i);
		} while (i == 1);
		strcpy(inf, name);
		strcat(inf, blank);
		strcat(inf, ID);
		user();
	}
}

void administer()
{
	int i;
	printf("\n\t\t^o^o^o^o^o^o^o^o^ 1.录入航班信息  ^o^o^o^o^o^o^o^o^\n");
	printf("\t\t^o^o^o^o^o^o^o^o^ 2.删除航班信息  ^o^o^o^o^o^o^o^o^\n");
	printf("\t\t^o^o^o^o^o^o^o^o^ 3.修改航班信息  ^o^o^o^o^o^o^o^o^\n");
	printf("\t\t^o^o^o^o^o^o^o^o^ 4.预览航班信息  ^o^o^o^o^o^o^o^o^\n\n");
	printf("\t\t^o^o^o^o^o^o^o^o^ 0.退出          ^o^o^o^o^o^o^o^o^\n\n");
	printf("请在0~4之间选择您要进行的操作 ");
	scanf_s("%d", &i);
	if (i >= 0 && i <= 4)
		switch (i)
		{
		case  0: break;
		case  1:input();   break;
		case  2:del();     break;
		case  3:change();    break;
		case  4:scan();     break;
		}
	else
	{
		printf("\n输入错误！！\n\n\n");
	}
}

void user()   //用户菜单
{
	int j;
	printf("\n\t\t<><><><><><><><><><> 1.订票 <><><><><><><><><><>\n");
	printf("\t\t<><><><><><><><><><> 2.退票 <><><><><><><><><><>\n");
	printf("\t\t<><><><><><><><><><> 3.预览<><><><><><><><><><>\n");
	printf("\t\t<><><><><><><><><><> 4.查询 <><><><><><><><><><>\n");
	printf("\t\t<><><><><><><><><><> 0.退出 <><><><><><><><><><>\n\n");
	printf("请在0~5之间选择您要进行的操作");
	scanf_s("%d\n\n", &j);
	if (j >= 0 && j <= 4)
		switch (j)
		{
		case 0: break;
		case 1:book();    break;
		case 2:quit();  break;
		case 3:change();    break;
		case 4:assure();    break;
		}
	else
	{
		printf("\n输入错误！！\n\n\n");
	}
}

void input()   //录入
{
	int i, m, j, k;
	printf("请问要输入几个航班信息: ");
	scanf_s("%d", &m);
	printf("\n\n******************************************************************\n\n");
	for (i = 0; i<m; i++)
	{
		printf("请输入航班号(不能为0):\n");
		scanf_s("%d", &plane[i].num);
		printf("请输入降落地点:\n");
		scanf_s("%s", &plane[i].end, sizeof(plane[i].end));
		printf("请输入起飞时间:\n");
		scanf_s("%s", &plane[i].btime, sizeof(plane[i].btime));
		printf("请输入票价:\n");
		scanf_s("%lf", &plane[i].price);
		printf("请输入机票数:\n");
		scanf_s("%d", &plane[i].count);
		for (j = 0; j < ROW; j++)
		{
			k = 0;
			do {
				strcpy_s(plane[i].seat[j][k], 0);
				k++;
			} while (k >= 6);
		}
	}
	getchar();
	administer();
}

void change()   //修改
{
	int m, i, j, k;
	system("cls");
	printf("请输入航班号：");
	scanf_s("d", &m);
	i = schbynum(m);
	printf("\n\n%d\t%s\t%s\t%s\t%lf\t%d\n", plane[i].num, plane[i].end, plane[i].btime, plane[i].etime, plane[i].price, plane[i].count);
	printf("请选择需要修改的项目");
	printf("\n\t\t<><><><><><><><><><> 1.航班号 <><><><><><><><><><>\n");
	printf("\t\t<><><><><><><><><><> 2.目的地 <><><><><><><><><><>\n");
	printf("\t\t<><><><><><><><><><> 3.起飞时间<><><><><><><><><><>\n");
	printf("\t\t<><><><><><><><><><> 4.落地时间<><><><><><><><><><>\n");
	printf("\t\t<><><><><><><><><><> 5.票价 <><><><><><><><><><>\n\n");
	printf("\t\t<><><><><><><><><><> 6.剩余机票数 <><><><><><><><><><>\n\n");
	printf("\t\t<><><><><><><><><><> 0.退出 <><><><><><><><><><>\n\n");
	printf("请在0~6之间选择您要进行的操作");
	scanf_s("%d\n\n", &j);
	if (j == 0)
		administer();
	if (j == 1)
		printf("请输入修改后的航班号：");
	scanf_s("%d", &plane[i].num);
	if (j == 2)
		printf("请输入修改后的目的地：");
	scanf_s("%s", &plane[i].end);
	if (j == 3)
		printf("请输入修改后的起飞时间");
	scanf_s("%s", &plane[i].btime);
	if (j == 4)
		printf("请输入修改后的落地时间");
	scanf_s("%s", &plane[i].etime);
	if (j == 5)
		printf("请输入修改后的票价");
	scanf_s("%g", &plane[i].price);
	if (j == 6)
		printf("请输入修改后的剩余机票数");
	scanf_s("%d", &plane[i].count);
	printf("\n\t\t<><><><><><><><><><>修改完成！<><><><><><><><><><>\n");
	printf("\t\t<><><><><><><><><><> 1.继续修改 <><><><><><><><><><>\n");
	printf("\t\t<><><><><><><><><><> 0.退出<><><><><><><><><><>\n");
	scanf_s("d", &k);
	switch (k)
	{
	case 1:change(); break;
	case 0:administer(); break;
	}
}

void del()   //删除
{
	int i, q, w, m, n = 0;
	system("cls");
	printf("请输入航班号：");
	scanf_s("d", &m);
	for (i = 0; i < 200; i++)
		if (plane[i].num == m)
			n++;
	q = i;
	printf("\n\n%d\t%s\t%s\t%s\t%lf\t%d\n", plane[i].num, plane[i].end, plane[i].btime, plane[i].etime, plane[i].price, plane[i].count);
	if (n = 0)
		printf("没有找到此航班,无法删除!");
	else
	{
		printf("确定删除请按 1 否则请按 0：\n\n");
		scanf_s("%d", &w);
		if (w == 1)
		{
			plane[q].num = 0;
			strcpy_s(plane[q].btime, 0);
			strcpy_s(plane[q].etime, 0);
			strcpy_s(plane[q].end, 0);
			strcpy_s(plane[q].seat[ROW][6], 0);
			plane[i].count = 0;
			plane[i].price = 0;
			printf("%d号航班已删除！", q);
		}
		getchar();
		getchar();
		administer();
	}
}

void scan()      //浏览  
{
	int i, j, k, m = 0, num, row, col, n;
	printf("\n\n航班号\t起飞地点\t降落地点\t起飞时间\t票价\t机票数\n\n");
	for (i = 0; i <= NUM-1; i++)
	{
		if (plane[i].flag == 1)
		{
			m++;
			printf("\n\n%d\t%s\t%s\t%s\t%lf\n", plane[i].num, plane[i].end, plane[i].btime, plane[i].etime, plane[i].price);
		}
	}
	if (m == 0)
		printf("无航班信息！");
	if (selection == 1)
	{
		printf("是否需要查询座位情况? 查询座位已定与未定，请输 1 ；查询具体座位身份信息，请输 2 ；无需查询，请输 0 .");
		scanf_s("%d", &j);
		for (m = 0; m != 1;)
		{
		    printf("请输入查询的航班号：");
			scanf_s("%d", &num);
			i = schbynum(num);
			if (plane[i].flag == 1)
				break;
			else
			{
				printf("无此航班。是否继续查询航班号？是请输1,否请输0返回上一菜单.");
				scanf_s("%d", m);
			}
		}
		if (m == 0)
		{
			administer();
		}
		if (j == 1)
		{
			seat(schbynum(num));
		}
		if (j == 2)
		{

			printf("请输入座位的航班号：");
			scanf_s("%d", &num);
			i = schbynum(num);
			for (k = 0; k != 1;)
			{
			    printf("请输入座位的行号：");
			    scanf_s("%d",&row);
			    printf("请输入座位的列号：");
			    scanf_s("%d",&col);
				if (row > 0 && row < ROW + 1 && col>0 && col < 7)
				{
					k++;
					printf("姓名与身份证号为：%s",plane[i].seat[row][col]);
				}
				else
				{
					printf("%d号航班不存在该座位号为%d行%d列的座位\n", num, row, col);
					printf("退出查找请按 0 返回上一菜单，继续查找请按 1 .");
					scanf_s("%d", &n);
					if (n == 0)
						administer();
				}	    
			}

		}
	}
}

void sch()  //查询模块  
{
	int i, c, e, j = 0, z = 0;
	struct airplane a;
	struct airplane result[20];
	struct airplane copy;
	printf("\n\n请输入降落地点:");
	scanf_s("%s", &a.end, sizeof(a.end));
	printf("\n\n请输入起飞时间:");
	scanf_s("%s", &a.btime, sizeof(a.btime));
	printf("\n\n请输入降落时间:");
	scanf_s("%s", &a.etime, sizeof(a.etime));

	printf("请选择排序方式（ 1：按航班号升序；2：按票价升序）");
	scanf_s("%d", &c);
	printf("\n\n航班号\t起飞地点\t起飞时间\t降落时间\t票价\t剩余座位\n\n");
	for (i = 0; i <= 2014; i++)
	{
		if (plane[i].btime == a.btime && strcmp(plane[i].etime, a.etime) == 0 && strcmp(plane[i].end, a.end) == 0)
		{
			result[j] = plane[i];
			j++;
		}
	}
	if (j == 0)
		printf("抱歉，暂时没有该条件的航班!");
	else
	{
		if (c == 1)
		{
			for (e = 0; e < (j - 1); e++)
				for (i = 0; i < (j - 1 - e); i++)
					if (result[i].num > result[i + 1].num)
					{
						copy = result[i];
						result[i] = result[i + 1];
						result[i + 1] = copy;
					}
		}
		if (c == 2)
		{
			for (e = 0; e < (j - 1); e++)
				for (i = 0; i < (j - 1 - e); i++)
					if (result[i].price > result[i + 1].price)
					{
						copy = result[i];
						result[i] = result[i + 1];
						result[i + 1] = copy;
					}
		}

		for (i = 1; i <= j; i++)
		{
			printf("\n\n%d\t%s\t%s\t%s\t%lf\t%d\n", result[i].num, result[i].end, result[i].btime, result[i].etime, result[i].price, result[i].count);
		}
	}
}

void book()    //订票模块  
{
	int i, j, a, m, n;
	char blank[] = " ";
	struct airplane d;
	do {
		sch();
		printf("请输入您要订的航班号： ");
		scanf_s("%d", &d.num);
		j = schbynum(d.num);
		d.count = 0;
		printf("请输入您要订的机票数： ");
		scanf_s("%d", &d.count);
		while (d.count <= 0)
		{
			printf("请输入大于0的机票数！");
			printf("请输入您要订的机票数： ");
			scanf_s("%d", &d.count);
		}
		if (plane[j].count >= d.count)
		{
			void seat(int j);
			for (i = 0; i < d.count; i++) 
			{
				printf("请选择第%d个座位的行数：", i+1);
				scanf_s("%d", &m);
				printf("请选择第%d个座位的列数：", i+1);
				scanf_s("%d", &n);
				strcpy(plane[j].seat[m - 1][n - 1],inf);
			}
			plane[j].count = plane[j].count - d.count;
			printf("恭喜您订票成功！祝您旅途愉快！\n");
			break;
		}
		else
		{
			printf("此航班只剩下%d张票，订票失败", plane[j].count);
			break;
		}
		printf("\n\n继续订票请按 1 ，退出请按 0  ");
		scanf_s("%d", &a);
	} while (a == 1);
}

void assure()
{
	int i, j, k, m=0;
	printf("航班号\t落地点\t起飞时间\t降落时间\t座位行号\t座位列号\t");
	for(i=0;plane[i].flag!=0;i++)
		for(j=0;j<ROW;j++)
			for (k = 0; k < 6; k++)
			{
				if (plane[i].seat[j][k] == inf)
				{
					printf("%d\t%s\t%s\t%s\t%s\t%d\t", plane[i].num, plane[i].end, plane[i].btime, plane[i].etime, j, k);
					m++;
				}
			}
	if (m == 0)
		printf("姓名为：%s 身份证号为：%s 的用户没有已定机票. 请检查登陆信息。", name, ID);
}

void quit()   //退票模块  
{
	int i, a, m, n;
	struct airplane f;
    printf("您已定机票如下：");
	assure();
	do
	{
		printf("请输入您要退订的机票航班号： ");
		scanf_s("%d", &f.num);
		printf("请输入您要退订机票的座位行号： ");
		scanf_s("%d", &m);
		printf("请输入您要退订机票的座位列号： ");
		scanf_s("%d", &n);
		i = schbynum(f.num);
		if (strcmp(plane[i].seat[m][n], inf) == 0)
		{
			strcpy(plane[i].seat[m][n], "0");
			plane[i].count++;
			printf("恭喜您退票成功! \n");
		}
		else
			printf("抱歉，您输入的机票信息有误!");
		printf("\n\n继续订票请按 1 ，退出请按 0  ");
		scanf_s("%d", &a);
	} while (a == 1);
	printf("您已定机票如下：");
	assure();
}

int schbynum(int x)
{
	int i ;
	for (i = 0; i <= NUM - 1; i++)
	{
		if (plane[i].num == x)
			return i;
	}
	printf("航班号为%d的航班不存在！",x);
}

void seat(int x)
{
	int i, j;
	printf("第一列 第二列 第三列 第四列 第五列 第六列\n");
	for (j = 0; j < NUM; j++)
		for (i = 0; i < 6; i++)
		{
			if (plane[x].seat[j][i] != "0")
				printf("已定  ");
			else
				printf("未定  ");
			printf("\n");
		}
}

void read()  //读取模块  
{
	int i;
	FILE *fp;
	fp = fopen("D:\\资料\\VisualStudio\\PLANE\\PLANE.txt", "r");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
	}
	else
	{
		while (!feof(fp))
			for (i = 0; i <= 199; i++)
				fread(plane, sizeof(struct airplane), 1, fp);
	}
	fclose(fp);
	printf("------------欢 迎 进 入 A 航 空 公 司 票 务 系 统 ！------------\n");
}

void save()   //保存模块  
{
	int i, w=1;
	FILE *fp;
	fp = fopen("D:\\资料\\VisualStudio\\PLANE\\PLANE.txt", "w");
	if (fp == NULL)
	{
		printf("打开文件错误\n");
		exit(0);
	}
	for (i = 0; i <= 199; i++)
		if (fwrite(plane, sizeof(struct airplane), 1, fp) == 0)
		{
			printf("文件保存错误！\n");
			exit(0);
			w = 0;
		}
	if (w == 1)
		printf("> > > > > > > >成功退出A航空公司票务系统!< < < < < < < <\n");
	fclose(fp);
}
