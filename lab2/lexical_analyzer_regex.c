#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = {"int","float","char","return","if","else","for","while","void"};

int iskeyword(const char *str){
    int numkeywords = sizeof(keywords) / sizeof(keywords[0]);
    for(int i=0; i < numkeywords; i++){
        if(strcmp(str, keywords[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int isArithmetic(char ch){
    return (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/');
}

int isAssignment(char ch){
    return (ch == '=');
}

int isPunctuation(char ch){
    return (ch == ';') || (ch == '(') || (ch == ')') || (ch == '{') || (ch == '}') || (ch == ',') || (ch == '[') || (ch == ']');
}

void identifyTokens(char *code){
    int i = 0, j = 0;
    char buffer[100];

    while(code[i] != '\0'){
        if(isspace(code[i])){
            i++;
            continue;
        }

        if(code[i] == '/' && code[i+1] == '/'){
            printf("Comment: %s\n", &code[i]);
            break;
        }

        if(code[i] == '#'){
            j = 0;
            while(code[i] != '\0' && !isspace(code[i])){
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';
            printf("Pre-processor Directive: %s\n", buffer);
            continue;
        }

        if(code[i] == '"'){
            j = 0;
            buffer[j++] = code[i++];
            while(code[i] != '\0' && code[i] != '"'){
                buffer[j++] = code[i++];
            }
            if(code[i] == '"'){
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';
            printf("String Literal: %s\n", buffer);
            continue;
        }

        if(isalpha(code[i]) || code[i] == '_'){
            j = 0;
            while(isalnum(code[i]) || code[i] == '_'){
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';
            if(iskeyword(buffer)){
                printf("Keyword: %s\n", buffer);
            }
            else{
                printf("Identifier: %s\n", buffer);
            }
        }

        else if(isdigit(code[i])){
            j = 0;
            while(isdigit(code[i])){
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';
            printf("Number: %s\n", buffer);
        }

        else if(isArithmetic(code[i])){
            printf("Arithmetic Operator: %c\n", code[i++]);
        }
        else if(isAssignment(code[i])){
            printf("Assignment Operator: %c\n", code[i++]);
        }
        else if(isPunctuation(code[i])){
            printf("Punctuation: %c\n", code[i++]);
        }
        else {
            printf("Unknown Character: %c\n", code[i++]);
        }
    }
}

int main(){
    char input[1024];
    while(fgets(input, sizeof(input), stdin) != NULL){
        input[strcspn(input, "\n")] = 0;
        if(strlen(input) == 0) continue;
        identifyTokens(input);
    }

    return 0;
}
