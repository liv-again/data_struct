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

#define MAXSIZE 20         //�ļ��м�¼���������ֵ

typedef int KeyType;          //����ؼ�������Ϊ��������
typedef int Status;

//��¼����
typedef struct  {
        KeyType  key;             //ѧ�ţ���¼�Ĺؼ��֣�
        const char *name;     //����
        char sex;         //�Ա� 
        int  age;                     //���� 
} RecordType;                     

//��¼�������
typedef struct{
          RecordType  r[MAXSIZE+1];      //r[0]���û��������ڱ�����Ԫ
          int length;                                  //��¼�ĸ���
}RecordTable;                                     

int ccount,mcount;         //ȫ�ֱ�����ccount�ؼ��ֱȽϴ�����mcount��¼�Ƶ�����

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

//��� 
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
 
//ð������
Status BubbleSort(RecordTable &RT)
{
	int i,j,done;
	 i=1;  done=1;
	 ccount=mcount=0;
        while(i<=RT.length && done)  {
            	//������length��ð�ݣ���û�з������������
   	        done=0;
   	        for(j=1; j<=RT.length-i; j++)
   	        {
   	        	if (RT.r[j+1].key<RT.r[j].key) {   //������¼�������������
      		      RT.r[0] = RT.r[j];	    //����������¼λ��
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
 
 //��������
int ccount1=0;
int mcount1=0;
Status Partition (RecordTable &RT, int low, int high) {  //һ�˿��������㷨
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
	    
	  //mcount1++;      //������¼����λ��
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
	  mcount1++;        //������¼����λ��
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
    	printf("��%d�ο�������\n",pcount);
    	OutRecordTable(RT);
	    QuickSort(RT, low, pivotloc-1);     //�ԵͶ��ӱ�ݹ���ñ�����
    	QuickSort(RT, pivotloc+1, high);   //�Ը߶��ӱ�ݹ���ñ�����
     }
	return OK;
 } 
 
 Status main()
 {
 	RecordTable RT,Rt;
 	printf("ԭʼ����\n"); 
	CreateRecordTable(RT);
	OutRecordTable(RT);
	BubbleSort(RT);
	printf("ð�������\n");
	OutRecordTable(RT);
	printf("�ؼ��ֱȽϴ��� %d   ��¼�Ƚϴ��� %d\n",ccount,mcount);
	CreateRecordTable(Rt);
	printf("���������\n");
	QuickSort(Rt,1,Rt.length);
	//OutRecordTable(Rt);
	printf("�ؼ��ֱȽϴ��� %d   ��¼�Ƚϴ��� %d\n",ccount1,mcount1);
	return OK;
 }
