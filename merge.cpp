#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 20 //�ļ��м�¼���������ֵ

typedef int KeyType; //����ؼ�������Ϊ��������
#define RADIX 10     //��������ʱ�Ļ���
typedef int Status;
//��¼����

typedef struct
{

    KeyType key; //ѧ�ţ���¼�Ĺؼ��֣�

    const char *name; //����

    const char *sex; //�Ա�

    int age; //����

} RecordType;

//��¼�������

typedef struct
{

    RecordType r[MAXSIZE + 1]; //r[0]���û��������ڱ�����Ԫ

    int length; //��¼�ĸ���

} RecordTable;

//��������ʱ����ĵ������㣨��¼������

typedef struct LNode
{

    RecordType rc;

    LNode *next; //ָ����һ������ָ�루�������ã�

} LNode;

//��������ʱ�������ʽ��¼������

typedef struct
{

    LNode *head[RADIX]; //������ͷָ������

    int length; //��������ļ�¼����

} RadixTable;

Status Merge(RecordTable &RT, int start, int mid, int end)
{
    //�������RT.r[start..mid]��RT.r[mid+1..end]�鲢Ϊ�����RT.r[start..end]
    int k = start;
    int i = start;
    int j = mid + 1;
    RecordTable RT1;
    //��RT�м�¼���ؼ�����С����鲢����ʱ��RT1��
    while (i <= mid && j <= end)
        if (RT.r[i].key <= RT.r[j].key)
            RT1.r[k++] = RT.r[i++];
        else
            RT1.r[k++] = RT.r[j++];
    while (i <= mid)
        RT1.r[k++] = RT.r[i++]; //��ʣ��RT.r[i..m]���Ƶ�RT1
    while (j <= end)
        RT1.r[k++] = RT.r[j++]; //��ʣ��RT.r[j..n]���Ƶ�RT1
    for (j = start; j <= end; j++)
        RT.r[j] = RT1.r[j]; //��RT1���ƻ�RT
    return OK;
}

Status MergeSort(RecordTable &RT, int start, int end)
{
    //��RT.r[start..end]��������ֱ����õݹ鷽ʽ�鲢����ΪRT.r[s..t]
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(RT, start, mid);
        MergeSort(RT, mid + 1, end);
        Merge(RT, start, mid, end);
    }
    return OK;
}

void OutRadixTable(RadixTable LT)
{

    for (int i = 0; i < LT.length; i++)
    {
        printf("Node %d:", i);
        LNode *index = LT.head[i];
        while (index)
        {
            printf("{%d,%d,%s,%s}->", index->rc.age, index->rc.key, index->rc.name, index->rc.sex);
            index = index->next;
        }
        printf("null\n");
    }

    return;
}
void OutRecordTable(RecordTable RT)
{
    printf("OutRecordTable:");
    for (int i = 1; i <= RT.length; i++)
    {
        printf("{%d,%d,%s,%s}, ", RT.r[i].age, RT.r[i].key, RT.r[i].name, RT.r[i].sex);
    }
    printf("\n");
    return;
}

Status RadixSort(RecordTable &RT, int n)
{ //nΪ���ؼ��ֵ�λ��
    RadixTable LT;
    LT.length=10;
    for (int k = 1; k <= n; k++)
    { //ִ��n�ιؼ��ֵ�"����"��"�ռ�"
        for (int i = 0; i < RADIX; i++)
            LT.head[i] = NULL; //ָ�������ʼ��
        //1. ����-��RT�еļ�¼���뵽��Ӧ�ĵ�������
        for (int i = 1; i <= RT.length; i++)
        {
            int key = RT.r[i].key;
            for (int j = 1; j < k; j++)
                key = key / RADIX; //��ȡ�ؼ��ֵ���iλ����ֵ
            key = key % RADIX;
            LNode *s = (LNode *)malloc(sizeof(LNode)); //����һ���������½��s
            s->rc = RT.r[i];
            s->next = NULL;
            if (!LT.head[key])
                LT.head[key] = s; //��β�巨��s������ָ��������
            else
            {
                LNode *r = LT.head[key];
                while (r->next)
                {
                    r = r->next;
                }
                r->next = s;
            }
        }
        printf("��%d�η���:\n", k);
        OutRadixTable(LT); //�����������ĸ�����������
        //2. �ռ�-һ�ν����������еļ�¼д��RT
        int j = 1;
        for (int i = 0; i < RADIX; i++)
        {
            LNode *r = LT.head[i];
            while (r)
            {
                RT.r[j++] = r->rc; //����¼д��RT
                LNode *s = r;
                r = r->next;
                free(s); //��¼д�غ��ͷŽ��ռ�
            }
        }
        printf("��%d���ռ�:\n", k);
        OutRecordTable(RT); //����ռ��ļ�¼������
    }
    return OK;
}

void CreateRecordTable(RecordTable &RT)
{
    RT.r[1].key = 56;
    RT.r[1].name = "Zhang";
    RT.r[1].sex = "F";
    RT.r[1].age = 19;
    RT.r[2].key = 19;
    RT.r[2].name = "Wang";
    RT.r[2].sex = "F";
    RT.r[2].age = 20;
    RT.r[3].key = 80;
    RT.r[3].name = "Zhou";
    RT.r[3].sex = "F";
    RT.r[3].age = 19;
    RT.r[4].key = 5;
    RT.r[4].name = "Huang";
    RT.r[4].sex = "M";
    RT.r[4].age = 20;
    RT.r[5].key = 21;
    RT.r[5].name = "Zheng";
    RT.r[5].sex = "M";
    RT.r[5].age = 20;
    RT.r[6].key = 64;
    RT.r[6].name = "Li";
    RT.r[6].sex = "M";
    RT.r[6].age = 19;
    RT.r[7].key = 88;
    RT.r[7].name = "Liu";
    RT.r[7].sex = "F";
    RT.r[7].age = 18;
    RT.r[8].key = 13;
    RT.r[8].name = "Qian";
    RT.r[8].sex = "F";
    RT.r[8].age = 19;
    RT.r[9].key = 37;
    RT.r[9].name = "Sun";
    RT.r[9].sex = "M";
    RT.r[9].age = 20;
    RT.r[10].key = 75;
    RT.r[10].name = "Zhao";
    RT.r[10].sex = "M";
    RT.r[10].age = 20;
    RT.r[11].key = 92;
    RT.r[11].name = "Chen";
    RT.r[11].sex = "M";
    RT.r[11].age = 20;
    RT.length=11;
}

int main()
{
    RecordTable RT1;
    CreateRecordTable(RT1);
    OutRecordTable(RT1);
    MergeSort(RT1,1,11);
    OutRecordTable(RT1);
    CreateRecordTable(RT1);
    RadixSort(RT1,2);
    //OutRecordTable(RT1);
    return 0;
}
