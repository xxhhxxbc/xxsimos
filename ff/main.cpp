#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int lat[1010];//������С����
int total;//��������
bool sign[1010];//��֤�޸����ݲ���ͻ
bool turn=false;//��֤��ӡ����ͻ

struct Node
{
    char name[30];
    int tim,siz,la;//ʱ�䡢��С������ʱ���ñ��
};//ģ����������

queue<Node>q;//STL����

void *ru(void *arg)//ģ����ҵִ��ռ�ÿռ�
{
    Node temp1 = *(Node *)arg;//��ȡ����
    while(turn);
    turn=true;
    printf("* %s * in %d...\n",temp1.name,temp1.la+1);
    turn=false;
    Sleep(temp1.tim);//ģ��ִ��ʱ��

    while(sign[temp1.la]);

    sign[temp1.la]=true;
    lat[temp1.la]+=temp1.siz;//ִ������ͷ���ռ�ռ�
    sign[temp1.la]=false;

    while(turn);
    turn=true;
    printf("* %s * end...%d ms\n",temp1.name,temp1.tim);
    turn=false;
}

void *ff(void *arg)//�״���Ӧ�㷨ģ��
{
    while(true)
    {
        if(!q.empty())//���в�Ϊ�ռ��о�����ҵ
        {
            while(turn);
            turn=true;
            printf("\n");
            for(int i=0; i<3; i++)//��ӡ��ǰ�ռ�ʣ�����
                printf("$$$$$ %d\n",lat[i]);
            printf("\n");
            turn=false;

            Node temp=q.front();//��ȡ����Ԫ��
            q.pop();//��������

            int tte=-1;
            for(int i=0; i<total; i++)//��ͷ��ʼѰ�ҵ�һ�����ʵĿռ�
            {
                if(temp.siz<=lat[i])
                {
                    tte=i;
                    break;
                }
            }
            if(tte==-1)//��û�ҵ�
            {
                Sleep(500);
                q.push(temp);//����ʧ��ѹ�ض���
                while(turn);
                turn=true;
                printf("error\n");
                turn=false;
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
        while(turn);
        turn=true;
        printf("%s sq......... size = %d time = %d ms\n",t.name,t.siz,t.tim);
        turn=false;
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
    scanf("%d",&total);
    for(int i=0; i<total; i++)
    {
        printf("�������%d���Ĵ�С��\n",i+1);
        scanf("%d",&lat[i]);
    }

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,ff,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
