#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int lat[1010];//������С����
int qqq;//��������
bool sign[1010];//��֤�޸����ݲ���ͻ
int kkk=-1;//��ǰ���·���ɹ�λ��

struct Node
{
    char name[30];
    int tim,siz,la;//ʱ�䡢��С������ʱ���ñ��
};//ģ����������

queue<Node>q;//STL����

void *ru(void *arg)//ģ����ҵִ��ռ�ÿռ�
{
    Node temp1 = *(Node *)arg;//��ȡ����
    printf("* %s * in %d...\n",temp1.name,temp1.la+1);
    Sleep(temp1.tim);//ģ��ִ��ʱ��

    while(sign[temp1.la]);

    sign[temp1.la]=true;
    lat[temp1.la]+=temp1.siz;//ִ������ͷ���ռ�ռ�
    sign[temp1.la]=false;

    printf("* %s * end... %d ms\n",temp1.name,temp1.tim);
}

void *nf(void *arg)//ѭ���״���Ӧ�㷨ģ��
{
    while(true)
    {
        if(!q.empty())//���в�Ϊ�ռ��о�����ҵ
        {
            printf("\n");
            for(int i=0; i<3; i++)//��ӡ��ǰ�ռ�ʣ�����
                printf("$$$$$ %d\n",lat[i]);
            printf("\n");

            Node temp=q.front();//��ȡ����Ԫ��
            q.pop();//��������

            int tte=-1;
            int ii=(kkk+1)%qqq;
            while(true)//���ϴγɹ�����λ��֮��Ѱ�ҵ�һ�����ʵĿռ�
            {
                if(temp.siz<=lat[ii])
                {
                    tte=ii;
                    kkk=ii;
                    break;
                }
                if(ii==kkk)
                    break;
                ii=(ii+1)%qqq;
            }
            if(tte==-1)//��û�ҵ�
            {
                Sleep(500);
                q.push(temp);//����ʧ��ѹ�ض���
                printf("%s error\n",temp.name);
            }
            else//��Ѱ�ҳɹ�
            {
                temp.la=tte;
                while(sign[temp.la]);
                sign[temp.la]=true;
                lat[tte]-=temp.siz;//����ɹ���ȥ������Ŀռ��С
                sign[temp.la]=false;
                pthread_t tq;
                int ttq=pthread_create(&tq,NULL,ru,&temp);//ģ��ռ�ռ��
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
        t.siz=(x+499)%500;//�������ȡ��С
        printf("%s sq.........size = %d time = %d ms\n",t.name,t.siz,t.tim);
        q.push(t);//ѹ�����
        Sleep(500);
    }
}

int main()
{
    pthread_t t1,t2;
    while(!q.empty())
        q.pop();//��ն���
    memset(lat,0,sizeof lat);
    memset(sign,0,sizeof sign);//���ٳ�ʼ������

    printf("���������������\n");
    cin>>qqq;
    for(int i=0; i<qqq; i++)
    {
        printf("�������%d���Ĵ�С��\n",i+1);
        cin>>lat[i];
    }

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,nf,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
