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

typedef int Status;
typedef int  KeyType;          //����ؼ�������Ϊ��������

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

int ccount,mcount;
//ѡ������
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
 
 //������
 int ccount1=1;
 int mcount1=0;
 Status HeapAdjust(RecordTable &H, int i, int m) { 
       //���ݴ󶥶�����������H.r[i]��H.r[i..m]�е�λ��
       int j;
       H.r[0]=H.r[i];       //����H.r[i]
       for(j=2*i; j<=m; j*=2) {  //���ݶ������ṹ�ҽ��i����(2*i)��(2*i+1)���ӽ��
              if (j<m && H.r[j].key<H.r[j+1].key)
			  {
			  	j++;  //�Ƚ����Һ���key�Ĵ�С��ȡ��������i�Ƚ�
			  } 
			  /*if(j<m)*/ ccount1++;
              if (H.r[0].key>=H.r[j].key)  
			  {
			  	break;  // �����i��С�ں��ӽ�㣬�����ѭ��
			  }
			  ccount1++;
              H.r[i]=H.r[j];   i=j;		  //�����ӽ���ֵ��i����ֵ����
              mcount1++;
        } 
        if(H.r[i].key!=H.r[0].key)
		{
		  H.r[i]=H.r[0];  //�ָ�i����ֵ 
	    }
        return OK;
}

Status HeapSort(RecordTable &H) 
{
	//�Դ������H���ж�����
	RecordType temp;
	int i;
    for(i=H.length/2; i>0; i--) 
           HeapAdjust(H, i, H.length);     //����H����һ���󶥶�
           printf("�����󶥶Ѻ�\n");
           OutRecordTable(H);
    for(i=H.length; i>1; i--){
			temp=H.r[1];
			H.r[1]=H.r[i];
			H.r[i]=temp;    //���Ѷ���¼�����������һ����¼����
			mcount1++; 
            HeapAdjust(H,1,i-1);	//��H.r[1..i-1]���µ���Ϊ�󶥶�
            printf("��%d�ε����Ѷ�Ԫ��\n",H.length-i+1);
            OutRecordTable(H);
    }
        return OK;
}

int main()
{
	RecordTable RT,H;
	printf("ԭʼ����\n"); 
	CreateRecordTable(RT);
	CreateRecordTable(H);
	OutRecordTable(RT);
	printf("ѡ������\n");
	SelectSort(RT);
	OutRecordTable(RT);
	printf("�ؼ��ֱȽϴ��� %d  ��¼�������� %d\n",ccount,mcount);
	printf("������\n");
	HeapSort(H);
	printf("�ؼ��ֱȽϴ��� %d  ��¼�������� %d",ccount1,mcount1);
	return OK;
}
