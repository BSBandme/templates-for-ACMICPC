#include<stdio.h>   
#include<stdlib.h>   
#include<string.h>   
#include<queue>   
  
using namespace std;  
  
#define N 1100   
#define M 201008   
#define Inf 0x7ffffff   
typedef struct{  
    int v,c,nxt;  
}Edge;  
typedef struct talQ{  
    int v,d,h;  
    bool operator <(const talQ &a)const  
    {return a.d+a.h<d+h;}  
}Q;  
  
Edge edg[M];  
int tail[N];  
int head[N];  
int h[N];  
int vis[N];  
int n,m,e;  
int s,t,k;  
  
void AddEdge(int u,int v,int c)  
{  
    edg[e].v=v;edg[e].c=c;edg[e].nxt=head[u];head[u]=e++;  
    edg[e].v=u;edg[e].c=c;edg[e].nxt=tail[v];tail[v]=e++;  
}  
  
void Dijkstra()  
{  
    int i,j,c,v;  
    int tmp,min;  
  
    memset(vis,0,sizeof(vis));  
    for(i=0;i<=n;i++)  
        h[i]=Inf;  
    h[t]=0;  
    for(i=0;i<n;i++){  
        min=Inf,c=0;  
        for(j=1;j<=n;j++){  
            if(vis[j]) continue;  
            if(h[j]<min)  
                min=h[j],c=j;  
        }  
        if(c==0) break;  
        vis[c]=1;  
        for(tmp=tail[c];tmp!=-1;tmp=edg[tmp].nxt){  
            v=edg[tmp].v;  
            if(h[v]-edg[tmp].c>h[c])  
                h[v]=h[c]+edg[tmp].c;  
        }  
    }  
}  
  
int Astarkth()  
{  
    Q cur,nxt;  
    priority_queue<Q>q;  
    int tmp,v;  
  
    if(h[s]==Inf) return -1;  
  
    memset(vis,0,sizeof(vis));  
    cur.d=0;cur.v=s;cur.h=h[s];  
    q.push(cur);  
    while(!q.empty()){  
  
        cur=q.top();q.pop();  
        vis[cur.v]++;  
        if(vis[cur.v]>k) continue;  
        if(vis[t]==k) return cur.d;  
        for(tmp=head[cur.v];tmp!=-1;tmp=edg[tmp].nxt){  
            v=edg[tmp].v;  
            nxt.d=edg[tmp].c+cur.d;  
            nxt.v=v;nxt.h=h[v];  
            q.push(nxt);  
        }  
    }  
    return -1;  
}  
  
int main()  
{  
    int i;  
    int u,v,c;  
//	freopen("2449.in", "r", stdin);
    while(scanf("%d%d",&n,&m) != -1)
	{
    for(i=0;i<=n;i++)  
        head[i]=tail[i]=-1;  
  
    while(m--){  
        scanf("%d%d%d",&u,&v,&c);  
        AddEdge(u,v,c);  
    }  
    scanf("%d%d%d",&s,&t,&k);  
    if(s==t) k++;  
    Dijkstra();  
    printf("%d\n",Astarkth());  
	}
    return 0;  
}  
