#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct Node
{
    char name[30];
    int pag;//页号
};//模拟申请类型

queue<Node>q;//页面申请队列
queue<int>te;//到来顺序
int turn=0;
int page[3];//模拟内存块

void sub(Node t1)
{
    Node t2=t1;
    int w=te.front();//获取当前最先到来
    te.pop();
    int v=-1;//临时变量存储块号
    for(int i=0; i<3; i++) //因数据量小，采取暴力查找块号
    {
        if(page[i]==w)//块内页面为当前最先到来页
        {
            v=i;
            break;
        }
    }
    page[v]=t2.pag;//块分配页号
    te.push(t2.pag);//压入到来队列尾
    cout<<"*** substitution "<<t2.name<<" * ..."<<v<<endl;
}

void wai(Node temp)
{
    Node t1=temp;
    int ff=-1;
    for(int i=0; i<3; i++)
        if(page[i]==-1)//存在空页面
            ff=i;

    if(ff!=-1)//直接压入
    {
        page[ff]=t1.pag;//块分配页号
        te.push(t1.pag);//压入到来队列尾
        cout<<"** press "<<t1.name<<" * ..."<<ff<<endl;
    }
    else//需置换
        sub(t1);
}

void *fifo(void *arg)//先进先出模拟
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

                for(int i=0; i<3; i++) //打印当前分配状况
                    cout<<"&&&       "<<page[i]<<endl;

                int flag=-1;//页面存在标记，空页面标记

                for(int i=0; i<3; i++)
                {
                    if(temp.pag==page[i])//申请页面已分配
                    {
                        flag=i;//获取块号
                        cout<<"* "<<temp.name<<" * in..."<<flag<<endl;
                        break;
                    }
                }

                if(flag==-1)//申请页面未分配
                    wai(temp);

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
        t.pag=(x+9)%10;//随机数获取页号
        cout<<t.name<<" sq..............."<<t.pag<<endl;
        q.push(t);//压入队列
        Sleep(100);
    }
}

int main()
{
    pthread_t t1,t2;
    memset(page,-1,sizeof page);
    while(!q.empty())
        q.pop();//清空队列
    while(!te.empty())
        te.pop();//清空队列

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,fifo,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
