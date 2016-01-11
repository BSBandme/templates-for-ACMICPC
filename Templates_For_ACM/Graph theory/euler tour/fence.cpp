/*
Å·À­Â·
*/
#include <iostream>
#include <fstream>
#include <memory.h> 

using namespace std;

int data[500][100], ju[500][500], st, en, n;
int ans[1200], lans;
const int maxn = 2000000;

void euler(int point)
{
	int i, j, k;
	int min1, min2;
	bool f = 0;

	if(point == en)
	{
    	for(i = 1; i <= data[point][0]; i++)
	    	if(!ju[point][i])
		    	f = 1;
    	if(!f)
		{
     		ans[lans] = point; 
	        lans++;
			return;
		}
	}
	for(i = 1; i <= data[point][0]; i++)
	{
		min2 = maxn;
		for(j = 1; j <= data[point][0]; j++)
			if((min2 > data[point][j]) && (!ju[point][j]))//
			{
				min1 = j;
				min2 = data[point][j];
			}
		if(min2 != maxn)
		{
    		ju[point][min1] = 1;
			j = data[point][min1];
			k = 1;
			while((data[j][k] != point) || (ju[j][k]))
				k++;
			ju[j][k] = 1;
	    	euler(j);
			ans[lans] = point; 
	    	lans++;
		}
	}
}

int main()
{
	int np, nodd = 0;
	int i, j, k;

	ifstream fin("fence.in");
	fin >> np;
	for(i = 0; i < np; i++)
	{
		fin >> j >> k;
		j--; k--;
		data[j][0]++;
		data[j][data[j][0]] = k;
		data[k][0]++;
		data[k][data[k][0]] = j;
	}
	fin.close();

	for(i = 499; i >= 0; i--)
		if(data[i][0] % 2)
		{
			nodd++;
			en = st;
			st = i;
		}
	if(nodd == 0)
	{
		st = 0;
		en = 0;
	}
	euler(st);

	ofstream fout("fence.out");
	for(i = lans; i > 0; i--)
		fout << ans[i - 1] + 1 << endl;
	fout.close();

	return 0;
}