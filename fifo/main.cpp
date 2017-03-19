#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct Node
{
    char name[30];
    int pag;//ҳ��
};//ģ����������

queue<Node>q;//ҳ���������
queue<int>te;//����˳��
int turn=0;
int page[3];//ģ���ڴ��

void sub(Node t1)
{
    Node t2=t1;
    int w=te.front();//��ȡ��ǰ���ȵ���
    te.pop();
    int v=-1;//��ʱ�����洢���
    for(int i=0; i<3; i++) //��������С����ȡ�������ҿ��
    {
        if(page[i]==w)//����ҳ��Ϊ��ǰ���ȵ���ҳ
        {
            v=i;
            break;
        }
    }
    page[v]=t2.pag;//�����ҳ��
    te.push(t2.pag);//ѹ�뵽������β
    cout<<"*** substitution "<<t2.name<<" * ..."<<v<<endl;
}

void wai(Node temp)
{
    Node t1=temp;
    int ff=-1;
    for(int i=0; i<3; i++)
        if(page[i]==-1)//���ڿ�ҳ��
            ff=i;

    if(ff!=-1)//ֱ��ѹ��
    {
        page[ff]=t1.pag;//�����ҳ��
        te.push(t1.pag);//ѹ�뵽������β
        cout<<"** press "<<t1.name<<" * ..."<<ff<<endl;
    }
    else//���û�
        sub(t1);
}

void *fifo(void *arg)//�Ƚ��ȳ�ģ��
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

                for(int i=0; i<3; i++) //��ӡ��ǰ����״��
                    cout<<"&&&       "<<page[i]<<endl;

                int flag=-1;//ҳ����ڱ�ǣ���ҳ����

                for(int i=0; i<3; i++)
                {
                    if(temp.pag==page[i])//����ҳ���ѷ���
                    {
                        flag=i;//��ȡ���
                        cout<<"* "<<temp.name<<" * in..."<<flag<<endl;
                        break;
                    }
                }

                if(flag==-1)//����ҳ��δ����
                    wai(temp);

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
        t.pag=(x+9)%10;//�������ȡҳ��
        cout<<t.name<<" sq..............."<<t.pag<<endl;
        q.push(t);//ѹ�����
        Sleep(100);
    }
}

int main()
{
    pthread_t t1,t2;
    memset(page,-1,sizeof page);
    while(!q.empty())
        q.pop();//��ն���
    while(!te.empty())
        te.pop();//��ն���

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,fifo,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
