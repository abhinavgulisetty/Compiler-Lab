#include <stdio.h>
#include <regex.h>
#include <string.h>

int main(){
    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    char input[200];
    char* cursor;
    //bruh
    if(fgets(input,sizeof(input),stdin) != NULL){ // Takes input till sizeof(input) - 1
        input[strcspn(input,"\n")] = 0; // strcspn return index where \n is there
                                                        // and gets replaced with \0
    }
    const char *pattern = "[a-zA-Z0-9]+|[,.;!]";
    reti = regcomp(&regex,pattern,REG_EXTENDED);
    if(reti){
        fprintf(stderr, "Could not compile\n");
        return 1;
    }
    cursor = input;
    while(1){
        reti = regexec(&regex,cursor,1,pmatch,0);
        if(reti == 0){
            int start = pmatch[0].rm_so;
            int end = pmatch[0].rm_eo;
            int len = end - start;
            printf("Token : %.*s\n",len,cursor + start);
            cursor += end;
        }
        else if(reti == REG_NOMATCH){
            break;
        }
    }
    regfree(&regex);
    return 0;
}
