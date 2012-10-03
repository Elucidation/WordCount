#ifndef _SORTER_H
#define _SORTER_H
#include <iostream>
using namespace std;

/* Sorts an array of strings by alphabetical order */
void quicksort(string arr[], const int arrLen);

void quicksortR(string arr[], int left, int right);

#endif