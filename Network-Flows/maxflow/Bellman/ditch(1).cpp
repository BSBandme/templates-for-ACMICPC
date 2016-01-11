/*
ÍøÂçÁ÷£ºBellman
*/
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
const int MAX=202;
int edge[MAX][MAX];
bool vis[MAX];
int fa[MAX];
int N,M;
int ford()
{
    while(1)
    {
        queue<int> q;
        memset(vis,0,sizeof(vis));
        memset(fa,-1,sizeof(fa));
        int now;
        vis[0]=true;
        q.push(0);
        while(!q.empty())
        {
            now=q.front();
            q.pop();
            if(now==M-1)
                break;
            for(int i=0;i<M;i++)
            {
                if(edge[now][i]&& !vis[i])
                {
                    fa[i]=now;
                    vis[i]=true;
                    q.push(i);
                }
            }
        }
        if(!vis[M-1])
            break;
        int u,min=0xffff;
        for(u=M-1;u;u=fa[u])
        {
            if(edge[fa[u]][u]<min)
                min=edge[fa[u]][u];
        }
        for(u=M-1;u;u=fa[u])
        {
            edge[fa[u]][u]-=min;
            edge[u][fa[u]]+=min;
        }
    }
    int max=0;
    for(int i=0;i<M;i++)
        max+=edge[M-1][i];
    return max;
}
int main()
{
    int s,e,val;
	freopen("ditch.in", "r", stdin);
	freopen("ditch.out", "w", stdout);
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        memset(edge,0,sizeof(edge));
        int i;
        for(i=0;i<N;i++)
        {
            scanf("%d%d%d",&s,&e,&val);
            if(s==M)
                continue;
            edge[s-1][e-1]+=val;
        }
        printf("%d\n",ford());
    }
    return 0;
}
