#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int qqq;//��������
bool tur=false;//������������ҳ�ͻ

struct Node
{
    char name[30];
    int tim,siz,la;//ʱ�䡢��С������ʱ���ñ��
};//ģ����������

struct Spa
{
    int sig,si,sign;//��ţ���С��ռ�ñ��
} lat[1010]; //ģ���������

int cmp(Spa a,Spa b)//�Զ���ṹ������ʽ
{
    if(a.si==b.si)
        return a.sig<b.sig;
    return a.si>b.si;
}

queue<Node>q;//STL����

void *ru(void *arg)//ģ����ҵִ��ռ�ÿռ�
{
    Node temp1 = *(Node *)arg;//��ȡ����
    printf("* %s * in %d ...\n",temp1.name,temp1.la+1);
    Sleep(temp1.tim);//ģ��ִ��ʱ��

    while(tur);
    tur = true;
    for(int i=0; i<qqq; i++)//���ݱ�Ų��ҿռ�
        if(temp1.la==lat[i].sig)
        {
            while(lat[i].sign);
            lat[i].sign=true;
            lat[i].si+=temp1.siz;//ִ������ͷ���ռ�ռ�
            lat[i].sign=false;
            break;
        }

    tur=false;

    printf("* %s * end... %d ms\n",temp1.name,temp1.tim);
}

void *wf(void *arg)//���Ӧģ��
{
    while(true)
    {
        if(!q.empty())//���в�Ϊ�ռ��о�����ҵ
        {
            Node temp=q.front();//��ȡ����Ԫ��
            q.pop();//��������

            while(tur);
            tur = true;
            sort(lat,lat+qqq,cmp);//������С�ݼ�����
            tur=false;

            printf("\n");
            for(int i=0; i<3; i++)//��ӡ��ǰ�ռ�ʣ�����
                printf("$$$$$ %d %d\n",lat[i].sig+1,lat[i].si);
            printf("\n");
            if(temp.siz<=lat[0].si)
            {
                temp.la=lat[0].sig;
                while(lat[0].sign);

                lat[0].sign=true;
                lat[0].si-=temp.siz;//����ɹ���ȥ������Ŀռ��С
                lat[0].sign=false;

                pthread_t tq;
                int ttq=pthread_create(&tq,NULL,ru,&temp);//ģ��ռ�ռ��
            }
            else//��û�ҵ�
            {
                Sleep(500);
                q.push(temp);//����ʧ��ѹ�ض���
                printf("error\n");
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
    memset(lat,0,sizeof lat);//���ٳ�ʼ������

    printf("���������������\n");
    cin>>qqq;
    for(int i=0; i<qqq; i++)
    {
        printf("�������%d���Ĵ�С��\n",i+1);
        lat[i].sig=i;
        cin>>lat[i].si;
    }

    sort(lat,lat+qqq,cmp);

    pthread_create(&t1,NULL,sq,NULL);
    pthread_create(&t2,NULL,wf,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
