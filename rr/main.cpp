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
int tur=0;//*��ע��˲�����Ϊ�˴�ӡ�ÿ�����

void *rr(void *arg)//��תģ��
{
    while(true)
    {
        if(turn==0&&tur==0)//������ִ��&sqδ����
        {
            if(!q.empty())//���в�Ϊ�ռ��о�����ҵ
            {
                turn=1;//ռ��
                tur=1;
                Node temp=q.front();//��ȡ����Ԫ��
                q.pop();//��������Ԫ��
                cout<<"* "<<temp.name<<" * begin..."<<endl;
                if(temp.tim<=1000)//���ʱ��Ƭ�ڿ����
                {
                    Sleep(temp.tim);//ģ��ִ����ʣʱ��
                    cout<<"* "<<temp.name<<" *end..."<<temp.tim<<"ms"<<endl;
                }
                else//�粻�����
                {
                    temp.tim-=1000;//����ʱ��۳�һ��ʱ��Ƭ��ʱ��
                    q.push(temp);//ѹ���β
                    Sleep(1000);//ģ��ִ��һ��ʱ��Ƭ
                    cout<<"* "<<temp.name<<" * ... 1000 ms"<<endl;
                }
                tur=0;
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
        if(tur==0)//rrδ����
        {
            tur=1;
            Node t;
            memset(t.name,0,sizeof t.name);//������ٳ�ʼ��Ϊ0
            int x=rand();//��ȡ�����

            for(int i=0; i<x%5+1; i++)
                t.name[i]='x';//�������ȡ����
            t.tim=(x+1000)%5000;//�������ȡʱ��
            Node te=t;
            q.push(te);//ѹ�����
            cout<<t.name<<" sq............"<<t.tim<<" ms"<<endl;
            tur=0;//�ͷ�
            Sleep(1000);
        }
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
