#include "equ.h"

void PrintArray(double ** a, int r, int c)
{
	int i, j;
	for (i = 0; i < r; ++i)
	{
		for (j = 0; j < c; ++j)
			printf("%lf ", a[i][j]);
		printf("\n");
	}
	return;
}

void PrintArray2(double * a, int len)
{
	int i;
	for (i = 0; i < len; ++i)
		printf("%lf ", a[i]);
	printf("\n");
	return;
}

double GetMaxFactorial(double * a, int len)
{
	int i;
	double res = 1;

	for (i = 0; i < len; ++i)
		if (a[i] != 0)
			res *= a[i];
	return res;
}

int SolveLinearEquak(int n, double * para, double * res, int index)
{
	if (n == 1)
	{
		if (para[0] == 0)
			return (-1);
		res[index] = para[1] / para[0];
		//printf("%lf %lf\n", para[0], para[1]);
		//printf("%lf\n", res[index]);
		return 1;
	}

	int i, j;
	int t;
	int ret;
	int cnt;
	int flag = 1;
	double ** matrix = GetMemory(n, n + 1);
	double * t1;
	double mf;
	double t2;
	double * para_n = (double *)malloc(sizeof(double) * n * (n - 1));

	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n + 1; ++j)
			matrix[i][j] = para[i*(n+1)+j];
	}
	//PrintArray(matrix, n, n + 1);
	//printf("\n");

	for (i = 0; i < n; ++i)
	{
		if (matrix[i][0] != 0)
			flag = 0;
	}
	if (flag)
		return (-1);

	t1 = (double*)malloc(sizeof(double) * n);
	for (i = 0; i < n; ++i)
		t1[i] = matrix[i][0];

	mf = GetMaxFactorial(t1, n);
	free(t1);

	for (i = 0; i < n; ++i)
	{
		if (matrix[i][0] != 0)
		{
			t2 = matrix[i][0];
			for (j = 0; j < n + 1; ++j)
			{
				matrix[i][j] = (mf / t2 * matrix[i][j]);
			}
		}
	}
	//PrintArray(matrix, n, n + 1);
	//printf("\n");

	for (t = 0; t < n; ++t)
		if (matrix[t][0] != 0)
			break;
	//printf("%d\n\n", t);

	cnt = 0;
	for (i = 0; i < n; ++i)
	{
		if (matrix[i][0] == 0)
		{
			for (j = 1; j < n + 1; ++j)
				para_n[cnt++] = matrix[i][j];
		}
		else if (i == t)
		{
			continue;
		}
		else
		{
			for (j = 1; j < n + 1; ++j)
				para_n[cnt++] = matrix[t][j] - matrix[i][j];
		}
		/*for (j = 0; j < n; ++j)
		{
			if ()
			//para_n[i * n + j] = matrix[i][j + 1] - matrix[i + 1][j + 1];
		}*/
	}
	//PrintArray2(para_n, n * (n - 1));
	//printf("%lf %lf\n", para_n[0], para_n[1]);

	ret = SolveLinearEquak(n - 1, para_n, res, index + 1);
	if (ret == -1)
	{
		FreeMemory(matrix, n);
		free(para_n);
		return (-1);
	}
	free(para_n);

	for (j = 0; matrix[j][0] == 0 && j < n; ++j);
	//printf("%lf %lf\n", res[0], res[1]);
	t2 = matrix[j][n];
	//printf("%lf\n", t2);
	for (i = 1; i < n; ++i)
		t2 -= (matrix[j][i] * res[index + i]);
	res[index] = t2 / matrix[j][0];

	FreeMemory(matrix, n);
	return 1;
}
