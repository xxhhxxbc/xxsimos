#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int lat[1010];//分区大小数组
int total;//分区总数
bool sign[1010];//保证修改数据不冲突
bool turn=false;//保证打印不冲突

struct Node
{
    char name[30];
    int tim,siz,la;//时间、大小、传参时所用标号
};//模拟申请类型

queue<Node>q;//STL队列

void *ru(void *arg)//模拟作业执行占用空间
{
    Node temp1 = *(Node *)arg;//获取参数
    while(turn);
    turn=true;
    printf("* %s * in %d...\n",temp1.name,temp1.la+1);
    turn=false;
    Sleep(temp1.tim);//模拟执行时间

    while(sign[temp1.la]);

    sign[temp1.la]=true;
    lat[temp1.la]+=temp1.siz;//执行完毕释放所占空间
    sign[temp1.la]=false;

    while(turn);
    turn=true;
    printf("* %s * end...%d ms\n",temp1.name,temp1.tim);
    turn=false;
}

void *ff(void *arg)//首次适应算法模拟
{
    while(true)
    {
        if(!q.empty())//队列不为空即有就绪作业
        {
            while(turn);
            turn=true;
            printf("\n");
            for(int i=0; i<3; i++)//打印当前空间剩余情况
                printf("$$$$$ %d\n",lat[i]);
            printf("\n");
            turn=false;

            Node temp=q.front();//获取队首元素
            q.pop();//弹出队首

            int tte=-1;
            for(int i=0; i<total; i++)//从头开始寻找第一个合适的空间
            {
                if(temp.siz<=lat[i])
                {
                    tte=i;
                    break;
                }
            }
            if(tte==-1)//若没找到
            {
                Sleep(500);
                q.push(temp);//分配失败压回队列
                while(turn);
                turn=true;
                printf("error\n");
                turn=false;
            }
            else//若寻找成功
            {
                temp.la=tte;
                while(sign[temp.la]);
                sign[temp.la]=true;
                lat[tte]-=temp.siz;//分配成功减去分配掉的空间大小
                sign[temp.la]=false;
                pthread_t tq;
                int ttq=pthread_create(&tq,NULL,ru,&temp);//模拟空间占用
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
        while(turn);
        turn=true;
        printf("%s sq......... size = %d time = %d ms\n",t.name,t.siz,t.tim);
        turn=false;
        q.push(t);//压入队列
        Sleep(500);
    }
}

int main()
{
    pthread_t t1,t2;
    while(!q.empty())
        q.pop();//清空队列
    memset(lat,0,sizeof lat);
    memset(sign,0,sizeof sign);//快速初始化数组

    printf("请输入分区总数：\n");
    scanf("%d",&total);
    for(int i=0; i<total; i++)
    {
        printf("请输入第%d区的大小：\n",i+1);
        scanf("%d",&lat[i]);
    }

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,ff,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
