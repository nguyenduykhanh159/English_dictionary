#ifndef CREATE_H_
#define CREATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmake-btree-master/inc/btree.h"

#define MAX_WORD 30
#define MAX_DATA 100000

BTA *Dic;
void creat(BTA **root,char *filename);

#endif