#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

vector <int> map[1000][2];
int np, ne;

int main()
{
	int i, j, k;
	freopen("min.in", "r", stdin);

	scanf("%d%d", &np, &ne);
	for(i = 0; i < ne; i++)
	{
		scanf("%d%d%d", &i, &j, &k);
		i--; j--;
		map[i][0].push_back(j);
		map[i][1].push_back(k);
	}

	return 0;
}