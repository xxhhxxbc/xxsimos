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

void *fcfs(void *arg)//先来先服务模拟
{
    while(true)
    {
        if(turn==0)//无正在执行
        {
            if(!q.empty())//队列不为空即有就绪作业
            {
                turn=1;//占用
                Node temp=q.front();//获取队首元素
                q.pop();//弹出队首
                cout<<"* "<<temp.name<<" * begin..."<<endl;
                Sleep(temp.tim);//模拟执行时间
                cout<<"* "<<temp.name<<" * end..."<<temp.tim<<"ms"<<endl;
                turn=0;//释放
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
        t.tim=(x+1000)%3000;//随机数获取时间
        cout<<t.name<<" sq..............."<<t.tim<<" ms"<<endl;
        q.push(t);//压入队列
        Sleep(500);
    }
}

int main()
{
    pthread_t t1,t2;
    while(!q.empty())
        q.pop();//清空队列

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,fcfs,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
