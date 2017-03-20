#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct Node
{
    char name[30];
    int tim;
};//ģ����������

queue<Node>q;//stl����
int turn=0;//ִ���Ƿ�ռ��

void *fcfs(void *arg)//�����ȷ���ģ��
{
    while(true)
    {
        if(turn==0)//������ִ��
        {
            if(!q.empty())//���в�Ϊ�ռ��о�����ҵ
            {
                turn=1;//ռ��
                Node temp=q.front();//��ȡ����Ԫ��
                q.pop();//��������
                cout<<"* "<<temp.name<<" * begin..."<<endl;
                Sleep(temp.tim);//ģ��ִ��ʱ��
                cout<<"* "<<temp.name<<" * end..."<<temp.tim<<"ms"<<endl;
                turn=0;//�ͷ�
            }
        }
    }
}

void *sq(void *arg)//�����ģ������
{
    while(true)
    {
        Node t;
        memset(t.name,0,sizeof t.name);//������ٳ�ʼ��Ϊ0
        int x=rand();//��ȡ�����

        for(int i=0; i<x%5+1; i++)
            t.name[i]='x';//�������ȡ����
        t.tim=(x+1000)%3000;//�������ȡʱ��
        cout<<t.name<<" sq..............."<<t.tim<<" ms"<<endl;
        q.push(t);//ѹ�����
        Sleep(500);
    }
}

int main()
{
    pthread_t t1,t2;
    while(!q.empty())
        q.pop();//��ն���

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,fcfs,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
