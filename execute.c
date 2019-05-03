#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>

char command[211];
void pwd(int argc, char *argv[]);
void cd(int argc, char *argv[]);
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/

int main(int argc, char *argv[]){
    if(strcmp(*(argv+1), "pwd") == 0  ){
        pwd(argc,argv);
        }

    else if(strcmp(*(argv+1), "cd") == 0  ){
        cd(argc,argv);
        }
    return 0;
    }
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void pwd(int argc, char *argv[]){
    if(argc > 2){
	    printf("\nToo Many Arguments.\n");
	    exit(1);
        }
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));
    printf("Current Working Directory: %s",cwd);
    exit(0);
    }
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void cd(int argc, char *argv[]){
    command[0]='\0';

    if(isalpha(*(argv+2)[0])){
        getcwd(command,sizeof(command));
        strcat(command,"/");
        strcat(command,*(argv+2));
        }

    else if((*(argv+2)[0]) == '.'       &&      (*(argv+2)[1]) == '/'){
        getcwd(command,sizeof(command));
        strcat(command,(*(argv+2))+1);
        }

    else
        strcpy(command,*(argv+2));

    printf("The given Directory: %s",*(argv+2));    
}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
