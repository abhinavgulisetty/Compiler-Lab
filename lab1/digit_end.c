//Program for Starts with a digit, ends with 'c'
// or starts with 'z' and ends with 'a' with atleast 1 digit in b/ws
#include <stdio.h>
#include <regex.h>

int main(){
    regex_t regex;
    int reti;
    char msgbuf[100];
    char input[100];
    scanf("%s",input);
    const char* pattern = "^[0-9].*c$ | ^z.*[0-9].*a$";
    reti = regcomp(&regex,pattern,REG_EXTENDED);
    if(reti){
        fprintf(stderr,"Could not compile regex\n");
        return 1;
    }
    reti = regexec(&regex,input,0,NULL,0);
    if(!reti){
        printf("Match found in either of the patterns\n");
    }
    else if(reti == REG_NOMATCH){
        printf("No match\n");
    }
    else{
        regerr(reti,&regex,msgbuf,sizeof(msgbuf));
        fprintf(stderr,"Regex match failed: %s\n",msgbuf);
    }
    regfree(&regex);
    return 0;
}
