#include "mem.h"

double ** GetMemory(int r, int c)
{
	int i;
	double ** p = (double **)malloc(sizeof(double *) * r);
	if (p == NULL)
		return NULL;

	for (i = 0; i < r; ++i)
	{
		p[i] = (double *)malloc(sizeof(double) * c);
		if (p[i] == NULL)
			return NULL;
	}
	return p;
}

int FreeMemory(double ** p, int r)
{
	if (p == NULL)
		return 0;

	int i;
	for (i = 0; i < r; ++i)
	{
		if (p[i] != NULL)
			free(p[i]);
	}
	free(p);
	return 1;
}
