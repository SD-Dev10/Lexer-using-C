#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define KW_COUNT 18
#define OPT_COUNT 9
#define DELIM_COUNT 10
#define tokens_size 20

typedef enum{
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    DELIMITER,
}TOKEN;


struct Keyword{
    TOKEN t1;
    char *kw_values[100];
};
struct Identifier{
    TOKEN t2;
    char *id_value;
};
struct Operator{
    TOKEN t3;
    char *opt_values[100];
};
struct Delimiter{
    TOKEN t4;
    char *delim_values[100];
};


struct Keyword s1 = {
        .t1 = KEYWORD,
        .kw_values = {"int", "float", "double", "char", "void", "for", "while", "do-while", "for", "if", "else", 
                      "else if", "typedef", "enum", "struct", "return", "const", "sizeof"}

};


struct Operator s2 ={
        .t3 = OPERATOR,
        .opt_values = {"+","-","/","=","*","&","!","%","#"}
};


struct Delimiter s3 = {
        .t4 = DELIMITER,
        .delim_values = {"=", ";", "(", ")", "{", "}", "[", "]", ",", ":", """, """}

};

char **tokens = NULL;
int token_index = 0;

int is_keyword(char *str, int length){
    for(int i=0; i<length; i++){
        if(strcmp(str, s1.kw_values[i])==0) return 1;
   }
   return 0;
}
int is_operator(char *str, int length){
    for(int i=0; i<length; i++){
        if(strcmp(str,s2.opt_values[i])==0) return 1;
    }
    return 0;
}
int is_delimiter(char *str, int length){
    for(int i=0; i<length; i++){
        if(strcmp(str,s3.delim_values[i])==0) return 1;
    }
    return 0;
}

void token_list(char *lexeme){
  if(tokens == NULL){
    printf("Couldn't allocate memory for tokens\n");
  }

  if(token_index>=tokens_size)return;

  if(is_keyword(lexeme, KW_COUNT)){
        tokens[token_index] = strdup(lexeme);    
  }else if(isdigit(lexeme[0])){
        tokens[token_index] = strdup(lexeme);  
  }else if(isalpha(lexeme[0])){
        tokens[token_index] = strdup(lexeme); 
  }else if(is_operator(lexeme,  OPT_COUNT)){
         tokens[token_index] = strdup(lexeme);
  }else if(is_delimiter(lexeme,  DELIM_COUNT)){
         tokens[token_index]  = strdup(lexeme);
  }else{ 
        tokens[token_index]= strdup(lexeme); 
  }
    token_index++; 
}

void tokenize(char *line) {
    char *token = strtok(line, " ");  
    while (token != NULL) {
        token_list(token);
        token = strtok(NULL, " ");   
    }
}



int main(){
       
   FILE *fp = fopen("test.c","r");
   if(!fp){
       perror("File not found");
       return 1;
   }
   //char line[256];
   char *line = (char *)malloc(256);
   tokens = malloc(tokens_size*sizeof(char *)); 
   if(line == NULL){
       printf("Couldn't allocate memeory for line\n");
   }
   while(fgets(line, sizeof(line),fp)){
       tokenize(line);
   }
   fclose(fp);
   for(int i=0; i<tokens_size; i++){
       printf("%s\n",tokens[i]);
       free(tokens[i]);
   }
   free(line);
   free(tokens);
   return 0;
}
