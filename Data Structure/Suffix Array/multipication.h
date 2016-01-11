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
     for(i=0;i<n;i++){
    	 if(rank[i] == 0) continue;
	     for(k?k--:0,j=sa[rank[i]-1]; i + k < n && j + k < n && r[i+k]==r[j+k];k++);
	     height[rank[i] - 1]=k;
     }
     return;
}
int d[20];
int logg[maxn];
int st[maxn][22];
// h为height数组，n为长度
void InitRMQ(const int &n, int *h){
	int i, j;
	for( d[0]=1, i=1; i < 21; ++i ) d[i] = 2*d[i-1];
	for( i=0; i < n; ++i ) st[i][0] = h[i];
	int k = int( log(double(n))/log(2) ) + 1;
	logg[0] = 0; logg[1] = 0;
	for(int i = 2; i <= n; i++) logg[i] = logg[i / 2] + 1;
	for( j=1; j < k; ++j )
		for( i=0; i < n; ++i ){
			if( i+d[j-1]-1 < n ){
				st[i][j] = min(st[i][j-1],
						st[i+d[j-1]][j-1]);
			}
			else break; // st[i][j] = st[i][j-1];
		}
}
//x, y为rank的序号(在sa中为x和y位置的lcp应为quelcp(x, y))
inline int quelcp(int x, int y){
	int k = logg[y - x + 1];
	return min(st[x][k], st[y-d[k]+1][k]);
}
//此为真正的quelcp(y--）
inline int quelcp1(int x, int y){
	if(y < x) swap(x, y);
	y--;
	int k = logg[y - x + 1];
	return min(st[x][k], st[y-d[k]+1][k]);
}
//querange为询问rank序号为no的位置与之lcp >= height的左右边界
inline pii querange(int no, int height, int l) {
	int be1 = 0, en1 = no - 1;
	while(be1 < en1) {
		int height1 = (be1 + en1) / 2;
		if(quelcp(height1, no - 1) < height) be1 = height1 + 1;
		else en1 = height1;
	}
	if(quelcp(be1, no - 1) < height) be1++;
	int from = min1(be1, no);
	be1 = no; en1 = l - 1;
	while(be1 < en1) {
		int height1 = (be1 + en1 + 1) / 2;
		if(quelcp(no, height1) < height) en1 = height1 - 1;
		else be1 = height1;
	}
	if(quelcp(no, be1) < height) be1--;
	int to = max1(be1 + 1, no);
	return mpr(from, to);
}