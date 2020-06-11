#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK         1
#define ERROR      0
#define TRUE       1
#define FALSE      0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define MAXSIZE 20         //�ļ��м�¼���������ֵ
// git测试2
typedef int Status;
typedef int  KeyType;          //����ؼ�������Ϊ��������

//��¼����
typedef struct  {
        KeyType  key;             //ѧ�ţ���¼�Ĺؼ��֣�
        const char *name;     //����
        char sex;         //�Ա� 
        int  age;                     //���� 
} RecordType;                     

//��¼��������
typedef struct{
          RecordType  r[MAXSIZE+1];      //r[0]���û��������ڱ�����Ԫ
          int length;                                  //��¼�ĸ���
}RecordTable;          

int ccount,mcount;
//����
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

// ��� 
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
 
//��������
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

//ϣ������
Status ShellSort(RecordTable &RT)
{
	int d,i,j;
	d=RT.length/2;
	ccount=0;
 	mcount=0;
        while(d>=1) {
          	for(i=d+1; i<=RT.length; i++)  
			{  
	        //�ӵ�d+1��Ԫ�ؿ�ʼ,������Ԫ�����������Ӧ������
	        RT.r[0]=RT. r[i];      //�����i��Ԫ��
      	    j=i-d;                    //��ǰ�Ҳ���λ��
      	    while( RT.r[0].key < RT.r[j].key && j>0) 
			{   //�Ҳ���λ�ò�����
      		  RT.r[j+d]=RT.r[j];      //����
		      j=j-d;   		 //������ǰ����
		      mcount++;
		      ccount++;
	        }//while
	        if(j>0)ccount++;
      	    RT.r[j+d]=RT.r[0];        //�����i��Ԫ��
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
	printf("ԭʼ����\n"); 
	CreateRecordTable(RT);
	OutRecordTable(RT);
	InsertSort(RT);
	printf("�򵥲�������\n"); 
	OutRecordTable(RT);
	printf("�ؼ��ֱȽϴ��� %d   ��¼�Ƚϴ��� %d\n",ccount,mcount);
	CreateRecordTable(Rt);
	printf("ϣ�������\n");
	ShellSort(Rt);
	//OutRecordTable(Rt);
	printf("�ؼ��ֱȽϴ��� %d   ��¼�Ƚϴ��� %d\n",ccount,mcount);
	return OK;
 } 
