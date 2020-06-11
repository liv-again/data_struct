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
// git test 
//记录类型
typedef struct  {
        KeyType  key;             //学号（记录的关键字）
        const char *name;     //姓名
        char sex;         //性别 
        int  age;                     //年龄 
} RecordType;                     

//记录表的类型
typedef struct{
          RecordType  r[MAXSIZE+1];      //r[0]闲置或用作“哨兵”单元
          int length;                                  //记录的个数
}RecordTable;          

int ccount,mcount;
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
 
//插入排序
Status InsertSort(RecordTable &RT) 
{
 	int i,j;
 	ccount=0;
 	mcount=0;
 	for(i=2;i<=RT.length;++i)
 	{
 		RT.r[0].key=RT.r[i].key;
 		for(j=i-1;RT.r[j].key>RT.r[0].key;j--)
 		{
 			mcount++;
 			 RT.r[j+1].key=RT.r[j].key;
		 }
		 ccount=mcount+1;
		 if(j<i-1)  RT.r[j+1].key=RT.r[0].key;
	 }
	 return OK;
}

//希尔排序
Status ShellSort(RecordTable &RT)
{
	int d,i,j;
	d=RT.length/2;
	ccount=0;
 	mcount=0;
        while(d>=1) {
          	for(i=d+1; i<=RT.length; i++)  
			{  
	        //从第d+1个元素开始,将所有元素有序插入相应分组中
	        RT.r[0]=RT. r[i];      //保存第i个元素
      	    j=i-d;                    //向前找插入位置
      	    while( RT.r[0].key < RT.r[j].key && j>0) 
			{   //找插入位置并后移
      		  RT.r[j+d]=RT.r[j];      //后移
		      j=j-d;   		 //继续向前查找
		      mcount++;
		      ccount++;
	        }//while
	        if(j>0)ccount++;
      	    RT.r[j+d]=RT.r[0];        //插入第i个元素
    	    }// for
    	    printf("d=%d\n",d);
    	    OutRecordTable(RT);
    	    d=d/2;
        }//while
        return OK;
 } 
 
Status main()
{
	RecordTable RT,Rt;
	printf("原始数据\n"); 
	CreateRecordTable(RT);
	OutRecordTable(RT);
	InsertSort(RT);
	printf("简单插入排序\n"); 
	OutRecordTable(RT);
	printf("关键字比较次数 %d   记录比较次数 %d\n",ccount,mcount);
	CreateRecordTable(Rt);
	printf("希尔排序后\n");
	ShellSort(Rt);
	//OutRecordTable(Rt);
	printf("关键字比较次数 %d   记录比较次数 %d\n",ccount,mcount);
	return OK;
 } 
