#include "create_dic.h"

void check_string(char *source,char *dest) // tach word va denifition
{
  int i,j,k=0,check=0;
  for(i=0;i<strlen(source);i++)
  {
    if(source[i]=='/'){
      dest[0]='\0';
      check=1;
      break;
    }
  }
  if(check==0) {
    source[strlen(source)-1]='\0';
    return;
  }
  for(j=i;j<=strlen(source);j++){
    dest[k]=source[j];
    k++;
  }
  source[i-1]='\0';
}

void check_word(char *a){    // tách từ
  int i;
  for(i=1;i<=strlen(a);i++)
    {
      a[i-1]=a[i];
    }
}

void creat(BTA **root,char *filename){
  FILE *f;
  int count=0;
  if(!(f=fopen(filename,"r"))){
    printf("Opened file unsuccessfully\n");
    return ;
  }
  *root=btcrt("Dictionary",0,0);
  char word[MAX_WORD],data[MAX_DATA],tmp[10000];
  word[0]='\0';
  while(!feof(f)){
    fgets(tmp,10000,f);
   // printf("1. %s\n",tmp);
    while(tmp[0]!='@'){
      strcat(data,tmp); // thêm chuỗi nghĩa của từ.
    //  printf("data: %s\n",data);
      if(feof(f)) break;
      fgets(tmp,10000,f);
    }
    if(word[0]!='\0')
    {
      int k=btins(*root,word,data,MAX_DATA*sizeof(char));
      if(k==0) count++;
    }
    if(tmp[0]=='@'){
      strcpy(word,tmp);
     // printf("word: %s\n",word);
      data[0]='\0';
      check_string(word,data); // tách từ và nghĩa.
      check_word(word); // tách từ.
    }
  }
  printf("Added %d word(s) in Dictionary.\n",count);
  fclose(f);
}

 