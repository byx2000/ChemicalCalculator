#pragma once

#include "def.h"

int AddToString(char * s, char c);
int Preprocess(char * s, int left, int right, STACK * t, int c);
int Analyze(char * s, STACK * t);
double GetAr(char * s);
double GetMw(char * s);
int GetCnt(char * s, STACK * t, int len);
void Simplification(int * a, int len);
int Equal(char * s1, char * s2, double * res);
void FormatString(char * s1, char * s2, double * res, int len, char * s3);

