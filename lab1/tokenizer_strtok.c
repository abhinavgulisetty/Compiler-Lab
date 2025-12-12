#include <stdio.h>
#include <string.h>

int main(){
    char input[200];
    char *token;

    if(fgets(input,sizeof(input),stdin) != NULL){
        input[strcspn(input,"\n")] = 0;
    }
    token = strtok(input," ,");

    while(token != NULL){
        printf("%s\n",token);
        token = strtok(NULL," ,");
    }

    return 0;
}
