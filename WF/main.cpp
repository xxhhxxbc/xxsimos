#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int qqq;//分区总数
bool tur=false;//避免排序与查找冲突

struct Node
{
    char name[30];
    int tim,siz,la;//时间、大小、传参时所用标号
};//模拟申请类型

struct Spa
{
    int sig,si,sign;//编号，大小，占用标记
} lat[1010]; //模拟分区类型

int cmp(Spa a,Spa b)//自定义结构体排序方式
{
    if(a.si==b.si)
        return a.sig<b.sig;
    return a.si>b.si;
}

queue<Node>q;//STL队列

void *ru(void *arg)//模拟作业执行占用空间
{
    Node temp1 = *(Node *)arg;//获取参数
    printf("* %s * in %d ...\n",temp1.name,temp1.la+1);
    Sleep(temp1.tim);//模拟执行时间

    while(tur);
    tur = true;
    for(int i=0; i<qqq; i++)//根据编号查找空间
        if(temp1.la==lat[i].sig)
        {
            while(lat[i].sign);
            lat[i].sign=true;
            lat[i].si+=temp1.siz;//执行完毕释放所占空间
            lat[i].sign=false;
            break;
        }

    tur=false;

    printf("* %s * end... %d ms\n",temp1.name,temp1.tim);
}

void *wf(void *arg)//最坏适应模拟
{
    while(true)
    {
        if(!q.empty())//队列不为空即有就绪作业
        {
            Node temp=q.front();//获取队首元素
            q.pop();//弹出队首

            while(tur);
            tur = true;
            sort(lat,lat+qqq,cmp);//分区大小递减排序
            tur=false;

            printf("\n");
            for(int i=0; i<3; i++)//打印当前空间剩余情况
                printf("$$$$$ %d %d\n",lat[i].sig+1,lat[i].si);
            printf("\n");
            if(temp.siz<=lat[0].si)
            {
                temp.la=lat[0].sig;
                while(lat[0].sign);

                lat[0].sign=true;
                lat[0].si-=temp.siz;//分配成功减去分配掉的空间大小
                lat[0].sign=false;

                pthread_t tq;
                int ttq=pthread_create(&tq,NULL,ru,&temp);//模拟空间占用
            }
            else//若没找到
            {
                Sleep(500);
                q.push(temp);//分配失败压回队列
                printf("error\n");
            }
        }
    }
}

void *sq(void *arg)//随机数模拟申请
{
    while(true)
    {
        Node t;
        memset(t.name,0,sizeof t.name);//数组快速初始化为0
        int x=rand();//获取随机数
        for(int i=0; i<x%5+1; i++)
            t.name[i]='x';//随机数获取名字
        t.tim=(x+1000)%5000;//随机数获取时间
        t.siz=(x+499)%500;//随机数获取大小
        printf("%s sq.........size = %d time = %d ms\n",t.name,t.siz,t.tim);
        q.push(t);//压入队列
        Sleep(500);
    }
}

int main()
{
    pthread_t t1,t2;
    while(!q.empty())
        q.pop();//清空队列
    memset(lat,0,sizeof lat);//快速初始化数组

    printf("请输入分区总数：\n");
    cin>>qqq;
    for(int i=0; i<qqq; i++)
    {
        printf("请输入第%d区的大小：\n",i+1);
        lat[i].sig=i;
        cin>>lat[i].si;
    }

    sort(lat,lat+qqq,cmp);

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,wf,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
