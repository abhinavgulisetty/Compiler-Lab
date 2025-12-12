//Program for Starts with a digit, ends with 'c'
#include <stdio.h>
#include <regex.h>

int main(){
    regex_t regex;
    int reti;
    char msgbuf[100];
    char input[100];
    scanf("%s",input);
    reti = regcomp(&regex,"^[0-9].*c$",REG_EXTENDED);
    if(reti){
        fprintf(stderr,"Could not compile regex\n");
        return 1;
    }
    reti = regexec(&regex,input,0,NULL,0);
    if(!reti){
        printf("Match found\n");
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
