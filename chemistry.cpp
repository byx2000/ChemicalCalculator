#include <string.h>
#include <malloc.h>
#include "def.h"
#include "mem.h"
#include "equ.h"

ELEM elem[] =
{
	{"H" , 1},
	{"He", 4},
	{"Li", 7},
	{"Be", 9},
	{"B" , 11},
	{"C" , 12},
	{"N" , 14},
	{"O" , 16},
	{"F" , 19},
	{"Ne", 20},
	{"Na", 23},
	{"Mg", 24},
	{"Al", 27},
	{"Si", 28},
	{"P" , 31},
	{"S" , 32},
	{"Cl", 35.5},
	{"Ar", 40},
	{"K" , 39},
	{"Ca", 40},
	{"Sc", 45},
	{"Ti", 48},
	{"V" , 51},
	{"Cr", 52},
	{"Mn", 55},
	{"Fe", 56},
	{"Co", 59},
	{"Ni", 59},
	{"Cu", 64},
	{"Zn", 65},
	{"Ga", 70},
	{"Ge", 73},
	{"As", 75},
	{"Se", 79},
	{"Br", 80},
	{"Kr", 84},
	{"Rb", 85},
	{"Sr", 88},
	{"Y" , 89},
	{"Zr", 91},
	{"Nb", 93},
	{"Mo", 96},
	{"Tc", 98},
	{"Ru", 101},
	{"Rh", 103},
	{"Pd", 106},
	{"Ag", 108},
	{"Cd", 112},
	{"In", 115},
	{"Sn", 119},
	{"Sb", 122},
	{"Te", 128},
	{"I" , 127},
	{"Xe", 131},
	{"Cs", 133},
	{"Ba", 137},
	{"Hf", 179},
	{"Ta", 181},
	{"W" , 184},
	{"Re", 186},
	{"Os", 190},
	{"Ir", 192},
	{"Pt", 195},
	{"Au", 197},
	{"Hg", 201},
	{"Ti", 204},
	{"Pb", 207},
	{"Bi", 209}
};

int SIZE_LIST = sizeof(elem) / sizeof(ELEM);

int AddToString(char * s, char c)
{
	if (s == NULL)
		return 0;

	int i = strlen(s);
	s[i] = c;
	s[i + 1] = '\0';
	return 1;
}

int Preprocess(char * s, int left, int right, STACK * t, int c)
{
	static int it = 0;
	int i, j;
	int a, b;
	int sum;

	if (left == 0)
		it = 0;

	for (i = left; i <= right; ++i)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			AddToString(t[it].elem, s[i]);
			if ((s[i + 1] >= 'A' && s[i + 1] <= 'Z') || s[i + 1] == '\0' || s[i + 1] == '(' || s[i + 1] == ')')
			{
				t[it].cnt = 1 * c;
				it++;
			}
			continue;
		}
		else if (s[i] >= 'a' && s[i] <= 'z')
		{
			AddToString(t[it].elem, s[i]);
			if ((s[i + 1] >= 'A' && s[i + 1] <= 'Z') || s[i + 1] == '\0' || s[i + 1] == '(' || s[i + 1] == ')')
			{
				t[it].cnt = 1 * c;
				it++;
			}
			continue;
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			sum = 0;
			while (s[i] >= '0' && s[i] <= '9')
			{
				sum = sum * 10 + s[i] - '0';
				i++;
			}
			t[it].cnt = sum * c;
			it++;
			i--;
			continue;
		}
		else if (s[i] == '(')
		{
			a = i + 1;
			b = i + 1;
			while (s[b + 1] != ')')
			{
				b++;
			}
			sum = 0;
			j = b + 2;
			while (s[j] >= '0' && s[j] <= '9')
			{
				sum = sum * 10 + s[j] - '0';
				j++;
			}
			Preprocess(s, a, b, t, sum);
			i = j - 1;
			continue;
		}
		else
		{

		}
	}
	return it;

}

int Analyze(char * s, STACK * t)
{
	int len = Preprocess(s, 0, strlen(s), t, 1);
	int i, j;

	for (i = 0; i < len - 1; ++i)
	{
		for (j = i + 1; j < len; ++j)
		{
			if (!strcmp(t[i].elem, t[j].elem))
			{
				t[i].cnt += t[j].cnt;
				if (j != len - 1)
					t[j] = t[len - 1];
				len--;
			}
		}
	}

	return len;
}

double GetAr(char * s)
{
	int i;
	for (i = 0; i < SIZE_LIST; ++i)
	{
		if (!strcmp(s, elem[i].symbol))
			return elem[i].Ar;
	}
	return (-1);
}

double GetMw(char * s)
{
	STACK t[100] = {0};
	int t2;
	int i;
	double sum = 0;

	t2 = Analyze(s, t);

	for (i = 0; i < t2; ++i)
	{
	    if (GetAr(t[i].elem) == -1)
            return (-1);
        else
            sum += GetAr(t[i].elem) * t[i].cnt;
	}
	return sum;
}

int GetCnt(char * s, STACK * t, int len)
{
	int i;
	for (i = 0; i < len; ++i)
	{
		if (!strcmp(s, t[i].elem))
			return t[i].cnt;
	}
	return 0;
}

void Simplification(int * a, int len)
{
    int t = a[0];
    int i, j;
    int flag;

    for (i = 1; i < len; ++i)
        if (a[i] < t)
            t = a[i];
    for (i = t; i >= 1; --i)
    {
        flag = 1;
        for (j = 0; j < len; ++j)
            if (a[j] % i != 0)
                flag = 0;
        if (flag)
        {
            for (j = 0; j < len; ++j)
                a[j] /= i;
            return;
        }
    }
}

int Equal(char * s1, char * s2, double * res)
{
	int c1 = 0, c2 = 0;
	int c3;
	int len1, len2;
	int t1, t2;
	int i, j, k;
	STACK ** table;
	char ** m;
	int * len;
	char ElemTable[100][5] = {0};
	int flag;
	double ** matrix;
	double * para;
	int ret;
	double x = 1;
	int a[100];
	int sum1, sum2;

	len1 = strlen(s1);
	i = 0;
	while (s1[i++] == ' ');
	for (; i < len1 - 1; ++i)
		if (s1[i] == ' ' && s1[i + 1] != ' ')
			c1++;
	c1++;
	i = 0;
	while (s2[i++] == ' ');
	len2 = strlen(s2);
	for (; i < len2 - 1; ++i)
		if (s2[i] == ' ' && s2[i + 1] != ' ')
			c2++;
	c2++;
	//printf("c1 = %d, c2 = %d\n\n", c1, c2);

	m = (char**)malloc(sizeof(char*) * (c1+c2));
	for (i = 0; i < c1+c2; ++i)
	{
		m[i] = (char*)malloc(sizeof(char) * 100);
		memset(m[i], 0, sizeof(char) * 100);
	}

	t1 = t2 = 0;
	for (i = 0; i < len1; ++i)
	{
		if (s1[i] == ' ')
		{
			while (s1[i++] == ' ');
			i -= 2;
			continue;
		}
		else
		{
			while (s1[i] != ' ' && i < len1)
			{
				m[t1][t2++] = s1[i];
				//printf("t1 = %d, t2 = %d, s1[i] = %c\n", t1, t2, s1[i]);
				//system("pause");
				++i;
			}
			t1++;
			i--;
			t2 = 0;
			continue;
		}
	}
	t1 = c1;
	t2 = 0;
	for (i = 0; i < len2; ++i)
	{
		if (s2[i] == ' ')
		{
			while (s2[i++] == ' ');
			i -= 2;
			continue;
		}
		else
		{
			while (s2[i] != ' ' && i < len2)
			{
				m[t1][t2++] = s2[i];
				++i;
			}
			t1++;
			i--;
			t2 = 0;
			continue;
		}
	}
	for (i = 0; i < c1+c2; ++i)
        if (GetMw(m[i]) == -1)
        {
            for (i = 0; i < c1+c2; ++i)
            free(m[i]);
            free(m);
            return (-1);
        }
	/*for (i = 0; i < c1+c2; ++i)
		printf("%s\t%d\n", m[i], strlen(m[i]));
	printf("\n");*/

	table = (STACK**)malloc(sizeof(STACK*) * (c1+c2));
	for (i = 0; i < c1+c2; ++i)
	{
		table[i] = (STACK*)malloc(sizeof(STACK) * 100);
		memset(table[i], 0, sizeof(STACK) * 100);
	}
	len = (int*)malloc(sizeof(int) * (c1+c2));

	for (i = 0; i < c1+c2; ++i)
		len[i] = Analyze(m[i], table[i]);

    for (i = 0; i < c1+c2; ++i)
    {
        for (j = 0; j < len[i]; ++j)
            x *= (double)table[i][j].cnt;
    }
	/*for (i = 0; i < c1+c2; ++i)
		printf("%d ", len[i]);
	printf("\n\n");
	for (i = 0; i <c1+c2; ++i)
	{
		for (j = 0; j < len[i]; ++j)
			printf("%s\t%d\n", table[i][j].elem, table[i][j].cnt);
		printf("\n");
	}
	printf("\n");*/

	t1 = 0;
	for (i = 0; i < c1+c2; ++i)
	{
		for (j = 0; j < len[i]; ++j)
		{
			flag = 1;
			for (k = 0; k < t1; ++k)
			{
				if (!strcmp(ElemTable[k], table[i][j].elem))
					flag = 0;
			}
			if (flag)
				memcpy(ElemTable[t1++], table[i][j].elem, 5);
		}
	}
	c3 = t1;
	/*for (i = 0; i < c3; ++i)
		printf("%s\n", ElemTable[i]);
	printf("\n");*/

	matrix = GetMemory(c1+c2, c1+c2+1);
	for (i = 0; i < c1+c2-1; ++i)
	{
		for (j = 0; j < c1+c2; ++j)
		{
			matrix[i][j] = (double)GetCnt(ElemTable[i], table[j], len[j]);
			//if (matrix[i][j] != 0)
                //x *= matrix[i][j];
		}
	}
	matrix[c1+c2-1][0] = 1;
	for (i = 1; i < c1+c2; ++i)
		matrix[c1+c2-1][i] = 0;
    for (i = 0; i < c1+c2; ++i)
        matrix[i][c1+c2] = 0;
	matrix[c1+c2-1][c1+c2] = 1;
	for (i = 0; i < c1+c2 - 1; ++i)
	{
		for (j = c1; j < c1+c2; ++j)
			matrix[i][j] *= (-1);
	}
	/*for (i = 0; i < c1+c2; ++i)
	{
		for (j = 0; j < c1+c2+1; ++j)
		{
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");*/

	para = (double*)malloc(sizeof(double) * (c1+c2) * (c1+c2+1));
	for (i = 0; i < c1+c2; ++i)
	{
		for (j = 0; j < c1+c2+1; ++j)
		{
			para[i*(c1+c2+1) + j] = matrix[i][j];
			//if (matrix[i][j] != 0)
                //x *= fabs(matrix[i][j]);
		}
	}
	//printf("%lf\n", x);
	//para[(c1+c2-1) * (c1+c2+1)] = x;
	para[(c1+c2) * (c1+c2+1) - 1] = x;
	/*for (i = 0; i < (c1+c2) * (c1+c2+1); ++i)
		printf("%lf ", para[i]);
	printf("\n");*/

	ret = SolveLinearEquak(c1+c2, para, res, 0);
	///SolveLinearEquak(c1+c2, para, res, 0);
	//printf("ret = %d\n\n", ret);

	/*for (i = 0; i < c1+c2; ++i)
		printf("%lf ", res[i]);*/

    i = 0;
	while (ret == -1 && i < c1+c2 - 1)
	{
	    if (i > 0)
        {
            for (j = 0; j < c1+c2+1; ++j)
                para[(i-1) * (c1+c2+1) + j] = matrix[i - 1][j];
        }

		for (j = 0; j < c1; ++j)
			para[i*(c1+c2+1) + j] = GetMw(m[j]);
		for (j = c1; j < c1+c2; ++j)
			para[i*(c1+c2+1) + j] = (-1) * GetMw(m[j]);
		para[i*(c1+c2+1)+c1+c2] = 0;
		ret = SolveLinearEquak(c1+c2, para, res, 0);
		i++;
		/*printf("ret = %d\n\n", ret);
		for (i = 0; i < c1+c2; ++i)
		printf("%lf ", res[i]);*/
	}

    /*for (i = 0; i < (c1+c2) * (c1+c2+1); ++i)
		printf("%lf ", para[i]);
	printf("\n");*/

	for (i = 0; i < c1+c2; ++i)
        a[i] = (int)res[i];
    Simplification(a, c1+c2);
    for (i = 0; i < c1+c2; ++i)
        res[i] = (double)a[i];

    /*check*/
    for (i = 0; i < c3; ++i)
    {
        sum1 = 0;
        for (j = 0; j < c1; ++j)
            sum1 += (int)res[j] * GetCnt(ElemTable[i], table[j], len[j]);
        sum2 = 0;
        for (j = c1; j < c1+c2; ++j)
            sum2 += (int)res[j] * GetCnt(ElemTable[i], table[j], len[j]);
        if (sum1 != sum2)
        {
            for (i = 0; i < c1+c2; ++i)
                free(table[i]);
            free(table);
            for (i = 0; i < c1+c2; ++i)
                free(m[i]);
            free(m);
            free(len);
            FreeMemory(matrix, c1+c2);
            free(para);
            return (-1);
        }
    }
    for (i = 0; i < c1+c2; ++i)
        if (res[i] <= 0)
        {
            for (i = 0; i < c1+c2; ++i)
                free(table[i]);
            free(table);
            for (i = 0; i < c1+c2; ++i)
                free(m[i]);
            free(m);
            free(len);
            FreeMemory(matrix, c1+c2);
            free(para);
            return (-1);
        }

    /*clean*/
    for (i = 0; i < c1+c2; ++i)
        free(table[i]);
    free(table);
    for (i = 0; i < c1+c2; ++i)
        free(m[i]);
    free(m);
    free(len);
    FreeMemory(matrix, c1+c2);
    free(para);

	return (c1+c2);
}

void FormatString(char * s1, char * s2, double * res, int len, char * s3)
{
    char s4[10];
    int i, j;
    int t1, t2;

    memset(s3, 0, 1024);
    t1 = strlen(s1);
    t2 = strlen(s2);

    for (i = 0, j = 0; i < len && j < t1; ++i)
    {
        if (j != 0)
            strcat(s3, " + ");
        if ((int)res[i] != 1)
        {
            itoa((int)res[i], s4, 10);
            strcat(s3, s4);
        }

        while (s1[j] == ' ')    j++;
        while (s1[j] != ' '&& j < t1)    {AddToString(s3, s1[j]); j++;}
    }

    strcat(s3, " === ");
    for (j = 0; i < len && j < t2; ++i)
    {
        if (j != 0)
            strcat(s3, " + ");
        if ((int)res[i] != 1)
        {
            itoa((int)res[i], s4, 10);
            strcat(s3, s4);
        }

        while (s2[j] == ' ')    j++;
        while (s2[j] != ' ' && j < t2)    {AddToString(s3, s2[j]); j++;};
    }
}
