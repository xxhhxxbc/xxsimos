#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define null NULL

int turn;
bool flag[2];
void *p0(void *arg)
{
    while(true)
    {
        flag[0]=true;
        turn=1;
        while(flag[1]&&turn==1)
        {
            Sleep(1);
            printf("p0...\n");
        }
        flag[0]=false;
    }
}

void *p1(void *arg)
{
    while(true)
    {
        flag[1]=true;
        turn=0;
        while(flag[0]&&turn==0)
        {
            Sleep(1);
            printf("p1...\n");
        }
        flag[1]=false;
    }
}

int main()
{
    pthread_t t1,t2;
    memset(flag,false,sizeof flag);
    turn = 0;
    pthread_create(&t1,null,p0,null);
    pthread_create(&t2,null,p1,null);

    pthread_join(t1,null);
    pthread_join(t2,null);
    return 0;
}
