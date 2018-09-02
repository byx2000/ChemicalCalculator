#pragma once

typedef struct Elem
{
	const char * symbol;
	double Ar;
}ELEM;

typedef struct Stack
{
	char elem[5];
	int cnt;
}STACK;
