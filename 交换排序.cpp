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

#define MAXSIZE 20         //文件中记录个数的最大值

typedef int KeyType;          //定义关键字类型为整数类型
typedef int Status;

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

int ccount,mcount;         //全局变量，ccount关键字比较次数，mcount记录移到次数

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

//输出 
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
 
//冒泡排序
Status BubbleSort(RecordTable &RT)
{
	int i,j,done;
	 i=1;  done=1;
	 ccount=mcount=0;
        while(i<=RT.length && done)  {
            	//最多进行length次冒泡，如没有发生交换则结束
   	        done=0;
   	        for(j=1; j<=RT.length-i; j++)
   	        {
   	        	if (RT.r[j+1].key<RT.r[j].key) {   //两个记录不符合排序规则
      		      RT.r[0] = RT.r[j];	    //交换两个记录位置
	 	          RT.r[j] = RT.r[j+1];
          		  RT. r[j+1] = RT.r[0];
		          done=1;
		          mcount++;
		        }//if
	            ccount++;
				} 
    	i++;
         }//while
         return OK;
 } 
 
 //快速排序
int ccount1=0;
int mcount1=0;
Status Partition (RecordTable &RT, int low, int high) {  //一趟快速排序算法
    int pivotkey,t;
    pivotkey = RT.r[low].key;
    while (low < high) 
	{
	  while (low < high  && RT.r[high].key >= pivotkey)  
	  {
	  	--high;
	  	ccount1++;
	  }
	  if(low <high)
	  {
	  t=RT.r[low].key;
	  RT.r[low].key=RT.r[high].key;
	  RT.r[high].key=t;	
	  }
	    
	  //mcount1++;      //两个记录互换位置
	  while (low < high  && RT.r[low].key <= pivotkey) 
	  {
	  	++low;
	  	ccount1++;
	   } 
	  ccount1++;
	  if(low <high)
	  {
	  t=RT.r[low].key;
	  RT.r[low].key=RT.r[high].key;
	  RT.r[high].key=t;	
	  }
	  mcount1++;        //两个记录互换位置
    }
      return low;
}// Partition 
int pcount=0; 
Status QuickSort(RecordTable &RT, int low, int high)
{
	int pivotloc;
       if (low < high) { 
    	pivotloc = Partition(RT, low, high);
		pcount++;
    	printf("第%d次快速排序\n",pcount);
    	OutRecordTable(RT);
	    QuickSort(RT, low, pivotloc-1);     //对低端子表递归调用本函数
    	QuickSort(RT, pivotloc+1, high);   //对高端子表递归调用本函数
     }
	return OK;
 } 
 
 Status main()
 {
 	RecordTable RT,Rt;
 	printf("原始数据\n"); 
	CreateRecordTable(RT);
	OutRecordTable(RT);
	BubbleSort(RT);
	printf("冒泡排序后\n");
	OutRecordTable(RT);
	printf("关键字比较次数 %d   记录比较次数 %d\n",ccount,mcount);
	CreateRecordTable(Rt);
	printf("快速排序后\n");
	QuickSort(Rt,1,Rt.length);
	//OutRecordTable(Rt);
	printf("关键字比较次数 %d   记录比较次数 %d\n",ccount1,mcount1);
	return OK;
 }
