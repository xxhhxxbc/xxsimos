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
        while(flag[1])
        {
            if(turn == 1)
            {
                flag[0]=false;
                while(turn == 1);
                flag[0]=true;
            }
        }
        Sleep(1);
        printf("p0...\n");
        turn = 1;
        flag[0]=false;
    }
}
void *p1(void *arg)
{
    while(true)
    {
        flag[1]=true;
        while(flag[0])
        {
            if(turn == 0)
            {
                flag[1]=false;
                while(turn == 0);
                flag[1]=true;
            }
        }
        Sleep(1);
        printf("p1...\n");
        turn = 0;
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
