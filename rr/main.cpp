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

void *rr(void *arg)//��תģ��
{
    while(true)
    {
        if(turn==0)//������ִ��
        {
            if(!q.empty())//���в�Ϊ�ռ��о�����ҵ
            {
                turn=1;//ռ��
                Node temp=q.front();//��ȡ����Ԫ��
                q.pop();//��������Ԫ��
                printf("* %s * begin...\n",temp.name);
                if(temp.tim<=1000)//���ʱ��Ƭ�ڿ����
                {
                    Sleep(temp.tim);//ģ��ִ����ʣʱ��
                    printf("* %s * end...%d ms\n",temp.name,temp.tim);
                }
                else//�粻�����
                {
                    temp.tim-=1000;//����ʱ��۳�һ��ʱ��Ƭ��ʱ��
                    Sleep(1000);//ģ��ִ��һ��ʱ��Ƭ
                    q.push(temp);//ѹ���β
                    printf("* %s * ... 1000 ms\n",temp.name);
                }
                turn=0;//�ͷ�
                Sleep(50);
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
        t.tim=(x+1000)%5000;//�������ȡʱ��
        Node te=t;

        q.push(te);//ѹ�����
        printf("%s * sq.........%d ms\n",t.name,t.tim);

        Sleep(1000);
    }
}

int main()
{
    pthread_t t1,t2;
    while(!q.empty())
        q.pop();//��ն���

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,rr,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
