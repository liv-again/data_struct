#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK         1
#define ERROR      0
#define TRUE       1
#define FALSE      0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define MAXSIZE 20         //文件中记录个数的最大值

typedef int Status;
typedef int  KeyType;          //定义关键字类型为整数类型

//记录类型
typedef struct  {
        KeyType  key;             //学号（记录的关键字）
        const char *name;     //姓名
        const char *sex;         //性别 
        int  age;                     //年龄 
} RecordType;                     

//记录表的类型
typedef struct{
          RecordType  r[MAXSIZE+1];      //r[0]闲置或用作“哨兵”单元
          int length;                                  //记录的个数
}RecordTable;   

//创建 
Status CreateRecordTable(RecordTable &RT)
{
	RecordType RT1[11]={56,"Zhang",'F',19,19,"Wang",'F',20,80,"Zhou",'F',19,5,"Huang",'M',20,
    21,"Zheng",'M',20,64,"Li",'M',19,88,"Liu",'F',18,13,"Qian",'F',19,37,"Sun",'M',20,
    75,"Zhao",'M',20,92,"Chen",'M',20};
    int i;
    for(i=1;i<=11;++i)
    {
    	RT.r[i].key=RT1[i-1].key;
    	RT.r[i].name=RT1[i-1].name;
    	RT.r[i].sex=RT1[i-1].sex;
    	RT.r[i].age=RT1[i-1].age;
	}
	RT.length=11;
	return OK;
}

// 输出 
Status OutRecordTable(RecordTable RT)
{
	int i;
	for(i=1;i<=RT.length;i++)
	{
        printf("%2d",RT.r[i].key);
	    printf("%6s",RT.r[i].name);
		printf("%3c",RT.r[i].sex);
		printf("%4d\n",RT.r[i].age);
	}
	return OK;
 } 
