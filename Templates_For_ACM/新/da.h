//待排序的字符串放在r 数组中，从r[0]到r[n-1]，长度为n，且单个字符最大值小于m。sa为结果 
#define maxn 300100
int wa[maxn * 2],wb[maxn * 2],wv[maxn * 2],ws1[maxn * 2];
int cmp(int *r,int a,int b,int l)
{return r[a]==r[b]&&r[a+l]==r[b+l];}
void da(int *r,int *sa,int n,int m)
{
     int i,j,p,*x=wa,*y=wb,*t;
     for(i=0;i<m;i++) ws1[i]=0;
     for(i=0;i<n;i++) ws1[x[i]=r[i]]++;
     for(i=1;i<m;i++) ws1[i]+=ws1[i-1];
     for(i=n-1;i>=0;i--) sa[--ws1[x[i]]]=i;
     for(j=1,p=1;p<=n;j*=2,m=p)
     {
       for(p=0,i=n-j;i<n;i++) y[p++]=i;
       for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
       for(i=0;i<n;i++) wv[i]=x[y[i]];
       for(i=0;i<m;i++) ws1[i]=0;
       for(i=0;i<n;i++) ws1[wv[i]]++;
       for(i=1;i<m;i++) ws1[i]+=ws1[i-1];
       for(i=n-1;i>=0;i--) sa[--ws1[wv[i]]]=y[i];
       for(t=x,x=y,y=t,p=2,x[sa[0]]=1,i=1;i<n;i++)
       x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
     }
     return;
}
void calheight(int *r, int *sa, int*rank, int*height,int n)
{
     int i,j,k=0;
     for(i=0; i<n;i++) rank[sa[i]]=i;
     for(i=0;i<n;height[rank[i++] - 1]=k){
    	 if(rank[i] == 0) continue;
	     for(k?k--:0,j=sa[rank[i]-1]; i + k < n && j + k < n && r[i+k]==r[j+k];k++);
     }
     return;
}
int RMQ[maxn];
int mm[maxn];
int best[20][maxn];
void initRMQ(int n)
{
     int i,j,a,b;
     for(mm[0]=-1,i=1;i<=n;i++)
     mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
     for(i=1;i<=n;i++) best[0][i]=i;
     for(i=1;i<=mm[n];i++)
     for(j=1;j<=n+1-(1<<i);j++)
     {
       a=best[i-1][j];
       b=best[i-1][j+(1<<(i-1))];
       if(RMQ[a]<RMQ[b]) best[i][j]=a;
       else best[i][j]=b;
     }
     return;
}
int askRMQ(int a,int b)
{
    int t;
    t=mm[b-a+1];b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}
int lcp(int a,int b)
{
    int t;
    a=rank[a];b=rank[b];
    if(a>b) {t=a;a=b;b=t;}
    return(height[askRMQ(a+1,b)]);
}
