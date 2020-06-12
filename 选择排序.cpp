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
        char sex;         //性别 
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

int ccount,mcount;
//选择排序
Status SelectSort(RecordTable &RT)
{
	int i,j,min;
	ccount=mcount=0;
	for(i=1;i<=RT.length;i++)
	{
		min=i;
		for(j=i+1;j<=RT.length;j++)
		{
			if(RT.r[j].key<RT.r[min].key) min=j;
			ccount++;
		}
		if(min!=i)
		{
			RT.r[0]=RT.r[i];
            RT.r[i]=RT.r[min];
            RT.r[min]=RT.r[0];
			mcount++;
		}
	}
	return OK; 
 } 
 
 //堆排序
 int ccount1=1;
 int mcount1=0;
 Status HeapAdjust(RecordTable &H, int i, int m) { 
       //根据大顶堆特征，调整H.r[i]在H.r[i..m]中的位置
       int j;
       H.r[0]=H.r[i];       //保存H.r[i]
       for(j=2*i; j<=m; j*=2) {  //根据二叉树结构找结点i的左(2*i)右(2*i+1)孩子结点
              if (j<m && H.r[j].key<H.r[j+1].key)
			  {
			  	j++;  //比较左右孩子key的大小，取大者与结点i比较
			  } 
			  /*if(j<m)*/ ccount1++;
              if (H.r[0].key>=H.r[j].key)  
			  {
			  	break;  // 若结点i不小于孩子结点，则结束循环
			  }
			  ccount1++;
              H.r[i]=H.r[j];   i=j;		  //将孩子结点的值与i结点的值互换
              mcount1++;
        } 
        if(H.r[i].key!=H.r[0].key)
		{
		  H.r[i]=H.r[0];  //恢复i结点的值 
	    }
        return OK;
}

Status HeapSort(RecordTable &H) 
{
	//对待排序表H进行堆排序
	RecordType temp;
	int i;
    for(i=H.length/2; i>0; i--) 
           HeapAdjust(H, i, H.length);     //将表H建成一个大顶堆
           printf("建立大顶堆后\n");
           OutRecordTable(H);
    for(i=H.length; i>1; i--){
			temp=H.r[1];
			H.r[1]=H.r[i];
			H.r[i]=temp;    //将堆顶记录与待排序的最后一个记录互换
			mcount1++; 
            HeapAdjust(H,1,i-1);	//将H.r[1..i-1]重新调整为大顶堆
            printf("第%d次调整堆顶元素\n",H.length-i+1);
            OutRecordTable(H);
    }
        return OK;
}

int main()
{
	RecordTable RT,H;
	printf("原始数据\n"); 
	CreateRecordTable(RT);
	CreateRecordTable(H);
	OutRecordTable(RT);
	printf("选择排序\n");
	SelectSort(RT);
	OutRecordTable(RT);
	printf("关键字比较次数 %d  记录交换次数 %d\n",ccount,mcount);
	printf("堆排序\n");
	HeapSort(H);
	printf("关键字比较次数 %d  记录交换次数 %d",ccount1,mcount1);
	return OK;
}
