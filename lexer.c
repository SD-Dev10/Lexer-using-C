#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define KW_COUNT 18
#define OPT_COUNT 9
#define DELIM_COUNT 10

enum TOKEN{
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    DELIMITER,
};


struct Keyword{
    enum TOKEN t1;
    char *kw_values[100];
};
struct Identifier{
    enum TOKEN t2;
    char *id_value;
};
struct Operator{
    enum TOKEN t3;
    char *opt_values[100];
};
struct Delimiter{
    enum TOKEN t4;
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
        .delim_values = {";", "(", ")", "{", "}", "[", "]", ",", ":", """, """}

};



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

void print_tokens(char *lexeme){
    if(is_keyword(lexeme, KW_COUNT)){
        printf("[%-10s] -> KEYWORD\n", lexeme);
    }else if(isdigit(lexeme[0])){
        printf("[%-10s] -> NUM_LITERAL\n", lexeme); 
    }else if(isalpha(lexeme[0])){
        printf("[%-10s] -> IDENTIFIER\n",lexeme);
    }else if(is_operator(lexeme,  OPT_COUNT)){
        printf("[%-10s] -> OPERATOR\n", lexeme);
    }else if(is_delimiter(lexeme,  DELIM_COUNT)){
        printf("[%-10s] -> DELIMITER\n", lexeme);
    }else{ 
        printf("[%-10s] -> UNKNOWN\n", lexeme);
    }
}

void tokenize(char *line) {
    char *token = strtok(line, " \t\n(){};,\"");  
    while (token != NULL) {
        print_tokens(token);
        token = strtok(NULL, " \t\n(){};,\"");   
    }
}



int main(){
       
   FILE *fp = fopen("test.c","r");
   if(!fp){
       perror("File not found");
       return 1;
   }
   char line[256];
   while(fgets(line, sizeof(line),fp)){
       tokenize(line);
   }
   fclose(fp);

   return 0;
}
