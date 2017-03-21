#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct Node
{
    char name[30];
    int tim;
};//模拟申请类型

queue<Node>q;//stl队列
int turn=0;//执行是否被占用

void *rr(void *arg)//轮转模拟
{
    while(true)
    {
        if(turn==0)//无正在执行
        {
            if(!q.empty())//队列不为空即有就绪作业
            {
                turn=1;//占用
                Node temp=q.front();//获取队首元素
                q.pop();//弹出队首元素
                printf("* %s * begin...\n",temp.name);
                if(temp.tim<=1000)//如该时间片内可完成
                {
                    Sleep(temp.tim);//模拟执行所剩时间
                    printf("* %s * end...%d ms\n",temp.name,temp.tim);
                }
                else//如不可完成
                {
                    temp.tim-=1000;//所需时间扣除一个时间片的时间
                    Sleep(1000);//模拟执行一个时间片
                    q.push(temp);//压入队尾
                    printf("* %s * ... 1000 ms\n",temp.name);
                }
                turn=0;//释放
                Sleep(50);
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
        Node te=t;

        q.push(te);//压入队列
        printf("%s * sq.........%d ms\n",t.name,t.tim);

        Sleep(1000);
    }
}

int main()
{
    pthread_t t1,t2;
    while(!q.empty())
        q.pop();//清空队列

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,rr,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
