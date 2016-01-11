//ÀëÉ¢»¯Ïß¶ÎÊ÷
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;

struct tr
{
	long long be, en, maxv, add, mid;
	tr *left, *right;
} tree[40000];

struct star
{
	long long x, y, val;
} ox[10010], oy[10010];

struct rec1
{
	star poi;
	int ju;
	bool operator < (const rec1 &a) const
	{
		if(poi.x != a.poi.x)
			return poi.x < a.poi.x;
		else
			return ju < a.ju;
	}
} rec[22000];

int lt, n, w, h;

bool cmp1(star i, star j)
{
	return i.x < j.x;
}

bool cmp2(star i, star j)
{
	return i.y < j.y;
}

void build(tr *node, long long be1, long long en1)
{
	long long mid = (en1 + be1) / 2;

	if(be1 == en1)
	{
		node->be = oy[be1].y;
		node->en = oy[be1].y;
		node->mid = oy[be1].y;
		return;
	}
	if(!node->left)
	{
		node->left = tree + ++lt;
		build(node->left, be1, mid);
	}
	if(!node->right)
	{
		node->right = tree + ++lt;
		build(node->right, mid + 1, en1);
	}
	node->be = oy[be1].y;
	node->en = oy[en1].y;
	node->mid = oy[mid].y;
}

inline int max1(int i, int j)
{
	return i > j ? i : j;
}

void upd(tr *node, long long be, long long en, long long val)
{
	long long mid = (be + en) / 2;
	bool f = 0;

	if(node->be >= be && node->en <= en)
	{
		node->add += val;
		node->maxv += val;
		return;
	}
	if(be <= node->mid && en >=node->be)
	{
		upd(node->left, be, en, val);
		f = 1;
	}
	if(en > node->mid && be <= node->en)
	{
		upd(node->right, be, en, val);
		f = 1;
	}
	if(f)
		node->maxv = node->add + max1(node->left->maxv, node->right->maxv);
}

int main()
{
	long long i, j, k, ans = 0;
	FILE *fin = fopen("2482.in", "r");

	while(scanf("%d%d%d", &n, &w, &h) != -1)
	{
		ans = 0;
		memset(tree, 0, sizeof(tree));
		lt = 0;
		for(i = 0; i < n; i++)
			scanf("%d%d%d", &ox[i].x, &ox[i].y, &ox[i].val);
		memcpy(oy, ox, sizeof(ox));
		sort(ox, ox + n, cmp1);
		sort(oy, oy + n, cmp2);
		build(tree, 0, n - 1);
		for(i = 0; i < n; i++)
		{
			rec[2 * i].poi.x = ox[i].x - w + 1;
			rec[2 * i].poi.y = ox[i].y - h + 1;
			rec[2 * i].poi.val = ox[i].val;
			rec[2 * i].ju = 1;
			rec[2 * i + 1].poi.x = ox[i].x + 1;
			rec[2 * i + 1].poi.y = ox[i].y - h + 1;
			rec[2 * i + 1].poi.val = ox[i].val;
			rec[2 * i + 1].ju = -1;
		}
		sort(rec, rec + 2 * n);

		for(i = 0; i < 2 * n; i++)
		{
			upd(tree, rec[i].poi.y, rec[i].poi.y + h - 1, rec[i].ju * rec[i].poi.val);
			if(ans < tree->maxv)
				ans = tree->maxv;
		}

		printf("%d\n", ans);
	}

	return 0;
}