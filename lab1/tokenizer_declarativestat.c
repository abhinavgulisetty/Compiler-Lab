#include <stdio.h>
#include <string.h>
#include <regex.h>

int main(){
    regex_t regex;
    regmatch_t pmatch[5];
    int reti;
    char input[200];
    char *cursor;
    if(fgets(input,sizeof(input),stdin) != NULL){
        input[strcspn(input,"\n")] = 0;
    }
    const char *pattern = "(int|float|char|double)|([0-9]+)|([a-zA-Z_][a-zA-Z0-9_]*)|([=;,])";

    if(regcomp(&regex,pattern,REG_EXTENDED)){
        return 1;
    }

    cursor  = input;
    while(1){
        reti = regexec(&regex,cursor,5,pmatch,0);
        if(reti == 0){
            int start = pmatch[0].rm_so;
            int end = pmatch[0].rm_eo;
            int len = end - start;

            char token_text[50];
            snprintf(token_text,len + 1, "%s", cursor + start);

            if(pmatch[1].rm_so != -1){
                printf("Token: %-10s | Type: Datatype\n", token_text);
            }
            else if(pmatch[2].rm_so != -1){
                printf("Token: %-10s | Type: Integer Literal\n", token_text);
            }
            else if(pmatch[3].rm_so != -1){
                printf("Token: %-10s | Type: Variable\n", token_text);
            }
            else if(pmatch[4].rm_so != -1){
                printf("Token: %-10s | Type: Operator/Punctuation\n", token_text);
            }
            cursor += end;
        }
        else if (reti == REG_NOMATCH){
            break;
        }
    }
    regfree(&regex);
    return 0;
}
