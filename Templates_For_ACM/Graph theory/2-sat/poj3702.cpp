//POJ 2-sat的六道题目之一：
//
//平面上，一个圆，圆的边上按顺时针放着n个点。现在要连m条边，比如a，b，那么a到b可以从圆的内部连接，也可以从圆的外部连接。给你的信息中，每个点最多只会连接的一条边。问能不能连接这m条边，使这些边都不相交。
//
//解题报告：
//
//题意可能刚开始不是很好理解，比如1 5连边，2，6连边，由于点是顺序排列的，一画图就可以发现，这两条边必须一个从圆外面连，一个从内部连，否则就会相交。如果再加入3 7这条边，那么就必须相交了。
//
//这样，就可以转化成标准的2-sta问题：
//
//1：每个边看成2个点：分别表示在内部连接和在外部连接，只能选择一个。计作点i和点i'
//
//2：如果两条边i和j必须一个画在内部，一个画在外部（一个简单判断就可以）
//
//那么连边：
//
//i->j’, 表示i画内部的话，j只能画外部，即j’
//
//j->i’，同理
//
//i’->j，同理
//
//j’->i，同理
//
//然后就是2-sat算法了，tarjan一下，如果有i和i'同属于一个强联通，返回false，否则就成立。
//
//代码如下：
#include<iostream>
#include<cmath>
using namespace std;
#define size 1100
int n, m, a, b, v[size], cnt, ee[size][2];
struct edge{int to, next;} e[500000];
void insert(int from, int to)
{
    e[cnt].to = to;
    e[cnt].next = v[from];//每次都插入到最前面
    v[from] = cnt++;
}
int belong[size], num[size], cntnum;
int dfn[size], low[size], index, instack[size], sta[size], top;
void tarjan(int id)
{
    dfn[id] = low[id] = ++index;
    instack[id] = 1; sta[top++] = id;
    int tmp = v[id];
    while(tmp != -1)
    {
        if (!dfn[e[tmp].to])
        {
            tarjan(e[tmp].to);
            if (low[e[tmp].to] < low[id]) low[id] = low[e[tmp].to];
        }
        else if (instack[e[tmp].to] && dfn[e[tmp].to] < low[id])
            low[id] = dfn[e[tmp].to];
        tmp = e[tmp].next;
    }
    if (dfn[id] == low[id])
    {
        do
        {
            tmp = sta[--top]; instack[tmp] = 0;
            belong[tmp] = cntnum;
            num[cntnum]++;
        }while(tmp != id);
        cntnum++;
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    memset(v, -1, sizeof(v)); cnt = 0;
    for(int i = 0; i < m ;i++)
    {
        scanf("%d%d", &ee[i][0], &ee[i][1]);
        if (ee[i][0] > ee[i][1]) swap(ee[i][0], ee[i][1]);
    }
    for(int i = 0; i < m; i++)
        for(int j = i + 1; j < m; j++)
        {
            if (ee[i][0] < ee[j][1] && ee[i][0] > ee[j][0] && ee[i][1] > ee[j][1]
            ||  ee[i][1] < ee[j][1] && ee[i][1] > ee[j][0] && ee[i][0] < ee[j][0])
            {
                insert(i, j + m);
                insert(j, i + m);
                insert(j + m, i);
                insert(i + m, j);
            }
        }
    index = top = cntnum = 0;
    memset(num, 0, sizeof(num));
    memset(dfn, 0, sizeof(dfn));
    for(int i = 0; i < 2 * m; i++)
        if (!dfn[i]) tarjan(i);
    bool flag = true;
    for(int i = 0; i < m; i++)
        if (belong[i] == belong[i + m])
        {
            flag = false;
            break;
        }
    if (flag) printf("panda is telling the truth...\n");
    else printf("the evil panda is lying again\n");
    return 0;
}

