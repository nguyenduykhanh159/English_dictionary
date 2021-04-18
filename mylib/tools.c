#include "tools.h"

int replace(char *s1, char *s2){
  int len1=strlen(s1);
  int len2=strlen(s2),i;
  if(len1>len2) return 0;
  else{
    for(i=0;i<len1;i++){
      if(s1[i]!=s2[i])
        return 0;
    }
  }
  return 1;
}

int search_full(BTA* dict, char* input_word, char* output_word) {
  btpos(dict, ZSTART);
  int size;
  char* key = (char*) malloc (MAX_WORD * sizeof(char));
  char* data = (char*) malloc (MAX_DATA * sizeof(char));
  while(btseln(dict, key, data, MAX_DATA, &size) == 0) {
    if(strcmp(key, input_word) == 0) {
      // printf("%s\t%s\n", key, data);
      strcpy(output_word, data);
      return 1;
    }
  }
  return 0;
}

int reset_string(char* input_word) {
 for(int i = 0; i < strlen(input_word); i++) {
 input_word[i] = '\0';
 }
}

int suggest_word_list(BTA *dict, char *word, char *result){
  //int len1=strlen(word);
  int rsize;
  char* key = (char*) malloc (MAX_WORD * sizeof(char));
  char* data = (char*) malloc (MAX_DATA * sizeof(char));
  btpos(dict, ZSTART);
  while(btseln(dict,key,data, MAX_DATA ,&rsize)==0){
    if(replace(word,key)==1){
      strcpy(result,data);
      strcpy(z,key);
      return 1;
    }
  }
  return 0;
}

int suggestion(BTA *dict, char *input_word){
  int rsize,i=0;
  int check=0;
  char* key = (char*) malloc (MAX_WORD * sizeof(char));
  char* data = (char*) malloc (MAX_DATA * sizeof(char));
  btpos(dict, ZSTART);
  while(btseln(dict,key,data, MAX_DATA, &rsize)== 0 && i < 3){
    if(replace(input_word, key)==1){
      strcpy(s[i++],key);
      check=1;
    }
  }
  return check;
}


int del_dic(BTA* dict, char* input_word) {
 int rsize;
 char* key = (char*) malloc (MAX_WORD * sizeof(char));
 char* data = (char*) malloc (MAX_DATA * sizeof(char));
 btpos(dict, ZSTART);
 while(btseln(dict,key,data, MAX_DATA ,&rsize)==0){
 	if(strcmp(key, input_word) == 0) {
 	btdel(dict, input_word);
 	return 1;
 	}
 }
 return 0;
}

count_history=0;

void input_history(char* input_word) {
 strcpy(history[count_history], input_word);
 count_history = (count_history + 1) % 3;
}