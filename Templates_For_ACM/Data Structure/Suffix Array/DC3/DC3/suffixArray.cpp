#include <stdio.h>

int leq(int a1, int a2, int b1 ,int b2)
{
	return (a1 < b1 || a1 == b1 && a2 < b2);
}

int  leq(int a1, int a2 ,int a3 ,int b1 ,int b2 ,int b3)
{
	return (a1 < b1 || a1 == b1 && leq(a2,a3 ,b2 ,b3));
}

//stably sort a[0 .. n -1] to b[0 .. n-1] , with keys in 0 ... K from r
static void radixPass(int * a ,int *b ,int * r ,int n ,int K)
{
	int * c = new int[K + 1];
	for (int i =0; i <=K  ;i++ )
	{
		c[i] = 0;
	}

	for (int i = 0 ; i < n  ;i ++ )
	{
		c[r[a[i]]]++;
	}

	for (int i = 0 ,sum = 0; i<=K ;i++ )
	{
		int t = c[i]; c[i] = sum ; sum += t;
	}

	for(int i = 0 ; i < n; i++)
	{
		b[c[r[a[i]]]++] = a[i];
	}

	delete [] c;
}



void suffixArray(int * T ,int *SA , int n , int K)
{
	int n0 = (n+2)/3 , n1 = (n+1)/3, n2 = n/3 , n02 = n0 + n2;

	printf("n= %d ,n0 = %d , n1 = %d ,n2 = %d,n02 = %d \n",n,n0 ,n1, n2,n02);  //这里面n0,n1,n2,n02指的是什么意思呢？
	

	int *R = new int [n02 +3];
	R[n02] = R[n02 + 1] = R[n02 +2] = 0;

	int *SA12 = new int[n02 + 3];
	SA12[n02] = SA12[n02 + 1] = SA12[n02 +2] = 0;
	int *R0 = new int[n0];
	int *SA0 = new int[n0];



	//*******Step0 : Construct sample **********
	//genearte positions of mod 1 and mod 2 suffixes
	// the (n0 - n1) adds a dummy mod 1 suffix if n %3 == 1
	for(int i = 0 ,j =0 ; i < n+(n0 - n1); i++)  
		if(i %3 != 0) R[j++] = i;
	//********step1: Sort sample suffixes*********************

	radixPass(R , SA12 , T+2 ,n02 ,K);
	radixPass(SA12 , R ,T+1, n02, K);
	radixPass(R ,SA12, T ,n02, K);

	//finde lexicographic names of triples and 
	//write them to correct palces in R

	int name = 0 ,c0 = -1 ,c1 =-1 ,c2 = -1;
	for(int i = 0 ;i< n02 ;i++)
	{
		if(T[SA12[i]] != c0 || T[SA12[i] +1 ] !=c1 || T[SA12[i] +2 ] != c2)
		{
			name++;
			c0 = T[SA12[i]] ; c1 = T[SA12[i] +1 ] ; c2 = T[SA12[i] +2 ];
		}

		if(SA12[i] % 3 == 1) { R[SA12[i] / 3] = name;}   //write to R1
		else {R[SA12[i] / 3 + n0] = name;}     //write to R2
	}


	// rucruse if names are not yet unique

	if(name < n02)
	{
		suffixArray(R ,SA12 , n02 ,name);

		//store  unique names in R using the suffix array;
		for (int i = 0;i < n02  ;i++ )
		{
			R[SA12[i]] = i + 1;   //如果要和前面的保持一致的话，R 的值至少是从1 开始算起的。
		}
	}

	else 
	{
		for(int i = 0 ; i < n02 ;i++)
			SA12[R[i] - 1 ] = i;   //这里面的排名是正确的。
	}



	///*********Step2:  Sort nonsample suffixes*********************
	//stably sort the mode  0 suffixes from SA12 by their first character
	for(int i = 0 ,j = 0 ; i < n02 ; i++)
		if(SA12[i] < n0) R0[j++] = SA12[i] * 3;
	
	radixPass(R0, SA0 ,T ,n0,K);  //这里面的n0应该改写成j吧，二者是相等的么？？？？

	////*******Step3: Merge************
	for(int p =0 ,t = n0 -n1, k = 0 ; k <n ;k++)
	{
#define GetI() (SA12[t] < n0 ? SA12[t] *3 +1 :( SA12[t] - n0 )*3+2)
		
		int i  = GetI();
		int j = SA0[p];

		if(SA12[t] < n0 ? leq(T[i] , R[SA12[t] + n0] ,T[j] , R[j/3]) : leq(T[i], T[i+1] ,R[SA12[t] - n0 +1] , T[j], T[j+1] ,R[j/3+n0]))
		{
			//suffix from SA12 is smaller
			SA[k] = i ; t++;
			if(t == n02)   //done -- only SA0 suffixes left
				for(k++; p < n0 ; p++,k++) SA[k] = SA0[p];
		}

		else 
		{
			// suffix from SA0 is smaller 
			SA[k] = j ; p++;
			if(p == n0)   //done -- noly SA12 suffixes left 
			{
				for(k++; t < n02 ;t++,k++)  SA[k] = GetI();
			}

		}
	}

	delete[] R; delete [] SA12 ; delete [] SA0 ; delete [] R0;
	
}

int length(char * str)
{
	int i =0 ;
	while(str[i]!='\0') i++;
	return i;
}


void main()
{
	char * ch = "zhaoyuhaonihaomewobuhzzhaoyuhaonihaomewobuhzzhaoyuhaonihaomewobuhzzhaoyuhaonihaomewobuhz";
	
	int n = length(ch); 
	int K = 26; 
	printf("%d \n",n);
	int *SA = new int[n + 3] , * T=new int[n+3];
	for(int i = 0 ;i < n ;i++)
		T[i]=ch[i] - 'a' +1;
	T[n] = T[n+1] = T[n+2] = 0;

	suffixArray(T , SA , n ,K);

	for(int i = 0 ; i < n ;i ++)
	{
		printf("%d  ",SA[i]);
	}
	delete [] SA; delete [] T ;
	return ;
}
