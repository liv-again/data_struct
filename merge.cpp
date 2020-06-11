#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 20 //文件中记录个数的最大值

typedef int KeyType; //定义关键字类型为整数类型
#define RADIX 10     //基数排序时的基数
typedef int Status;
//记录类型

typedef struct
{

    KeyType key; //学号（记录的关键字）

    const char *name; //姓名

    const char *sex; //性别

    int age; //年龄

} RecordType;

//记录表的类型

typedef struct
{

    RecordType r[MAXSIZE + 1]; //r[0]闲置或用作“哨兵”单元

    int length; //记录的个数

} RecordTable;

//基数排序时分组的单链表结点（记录）类型

typedef struct LNode
{

    RecordType rc;

    LNode *next; //指向下一个结点的指针（表排序用）

} LNode;

//基数排序时分组的链式记录表类型

typedef struct
{

    LNode *head[RADIX]; //单链表头指针数组

    int length; //基数排序的记录个数

} RadixTable;

Status Merge(RecordTable &RT, int start, int mid, int end)
{
    //将有序表RT.r[start..mid]和RT.r[mid+1..end]归并为有序表RT.r[start..end]
    int k = start;
    int i = start;
    int j = mid + 1;
    RecordTable RT1;
    //将RT中记录按关键字由小到大归并到临时表RT1中
    while (i <= mid && j <= end)
        if (RT.r[i].key <= RT.r[j].key)
            RT1.r[k++] = RT.r[i++];
        else
            RT1.r[k++] = RT.r[j++];
    while (i <= mid)
        RT1.r[k++] = RT.r[i++]; //将剩余RT.r[i..m]复制到RT1
    while (j <= end)
        RT1.r[k++] = RT.r[j++]; //将剩余RT.r[j..n]复制到RT1
    for (j = start; j <= end; j++)
        RT.r[j] = RT1.r[j]; //将RT1复制回RT
    return OK;
}

Status MergeSort(RecordTable &RT, int start, int end)
{
    //将RT.r[start..end]拆成两个字表，采用递归方式归并排序为RT.r[s..t]
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
{ //n为最大关键字的位数
    RadixTable LT;
    for (int k = 1; k <= n; k++)
    { //执行n次关键字的"分组"与"收集"
        for (int i = 0; i < RADIX; i++)
            LT.head[i] = NULL; //指针数组初始化
        //1. 分组-将RT中的记录插入到相应的单链表中
        for (int i = 1; i <= RT.length; i++)
        {
            int key = RT.r[i].key;
            for (int j = 1; j < k; j++)
                key = key / RADIX; //获取关键字倒数i位的数值
            key = key % RADIX;
            LNode *s = (LNode *)malloc(sizeof(LNode)); //申请一个单链表新结点s
            s->rc = RT.r[i];
            s->next = NULL;
            if (!LT.head[key])
                LT.head[key] = s; //用尾插法将s结点插入指定单链表
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
        printf("第%d次分组:\n", k);
        OutRadixTable(LT); //输出基数排序的各单链表数据
        //2. 收集-一次将各单链表中的记录写回RT
        int j = 1;
        for (int i = 0; i < RADIX; i++)
        {
            LNode *r = LT.head[i];
            while (r)
            {
                RT.r[j++] = r->rc; //结点记录写回RT
                LNode *s = r;
                r = r->next;
                free(s); //记录写回后释放结点空间
            }
        }
        printf("第%d次收集:\n", k);
        OutRecordTable(RT); //输出收集的记录表内容
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
    return 0;
}
