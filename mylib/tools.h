#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmake-btree-master/inc/btree.h"
#define MAX_WORD 30
#define MAX_DATA 100000

char x[MAX_WORD];
char y[MAX_DATA];
char z[MAX_WORD];
char s[3][MAX_DATA];
char history[3][MAX_WORD];
int count_history;

int search_full(BTA* dict, char* input_word, char* output_word);
int suggest_word_list(BTA *dict, char *word, char *result);
int suggestion(BTA *dict, char *input_word);
int del_dic(BTA* dict, char* input_word);
void input_history(char* input_word);

#endif