#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

void ls(int argc, char **argv);
void do_ls(char[]);
void do_ls_all(char[]);
void do_ls_l(char[]);
void dostat(char*);
void show_file_info(char*, struct stat*);
void mode_to_letters(int, char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

#define prompt "!!@[HaSH]@!! $ "
#define execute "./execute "
#define Buffer_SIZE 201
#define pipe_read 0
#define pipe_write 1

char u_input[201];
char command[211];

char **argv;
char argc;

void praser(char[]);
void pwd(int argc, char **argv);
void cd(int argc, char **argv);


int main(){
    printf("\n\t\tHASH - HANDY SHELL");
    printf("\n\tAn easy to use shell for linux environment.\n");
    printf("\n\tNOTE: The total character count of user input cannot go more than 200 characters.");
    printf("\n\tThankyou for giving it a try.\n");
    system("~/.linuxLogo/linuxLogoXonfig");
    system("~/.linuxLogo/linuxLogo");

    int flag;
    for(;;){
        flag = 0;
        u_input[0] = '\0';
        command[0] = '\0';
        printf("\n%s",prompt);
        fscanf(stdin,"%[^\n]s",u_input);

        if(strcmp(u_input, "exit") == 0){
            printf("\n\n\t\tTHANKYOU FOR USING HASH\n");
            return 0;
            }

        getchar();

        praser(u_input);
/*
        for(int i=0; i<argc; i++)
            printf("%s\n",argv[i]);*/

        if(strcmp(*(argv), "pwd") == 0  ){
            pwd(argc,argv);
            }

        else if(strcmp(*(argv), "cd") == 0  ){
            cd(argc,argv);
            }

        else if(strcmp(*(argv), "ls") == 0  ){
            ls(argc,argv);
            }
            
            
            
            
            
            
            
            
            }

    

    }

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void pwd(int argc, char **argv){
    int flag = 0;

    if(argc > 1){
        if(strcmp(*(argv+1) , "|") == 0 && strcmp(*(argv+2),"ls")==0)
            flag =1;

        else
	    printf("\nToo Many Arguments.\n");
        }

    char cwd[1024];
    getcwd(cwd,sizeof(cwd));
    printf("Current Working Directory: %s",cwd);

    if(flag == 1){
        printf("\n");
        char write_msg[Buffer_SIZE];
        strcpy(write_msg, cwd);
        char read_msg[Buffer_SIZE];

        int fd[2];

        pid_t pid;

        if(pipe(fd) == -1){
            fprintf(stderr,"Pipe Failed");
            return;
            }

        pid = fork();

        if(pid < 0){
            fprintf(stderr,"Fork Failed");
            return;
            }

        if(pid > 0){
            close(fd[pipe_read]);
            write(fd[pipe_write], write_msg, strlen(write_msg)+1);
            close(fd[pipe_write]);
            return;
            }

        else{
            close(fd[pipe_write]);
            read(fd[pipe_read], read_msg, Buffer_SIZE);
            do_ls_all(read_msg);
            close(fd[pipe_read]);
            exit(0);
            }
        int status; 
        waitpid(pid, &status, 0); 

        }
    
    }
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void cd(int argc, char **argv){
    command[0]='\0';

    if(isalpha(*(argv+1)[0])){
        getcwd(command,sizeof(command));
        strcat(command,"/");
        strcat(command,*(argv+1));
        }

    else if((*(argv+1))[0] == '~'       &&      (*(argv+1))[1] == '\0'){
        strcpy(command,getenv("HOME"));
        }

    else if((*(argv+1))[0] == '~'       &&      (*(argv+1))[1] == '/'){
        strcpy(command,getenv("HOME"));
        if((*(argv+1))[2] != '\0'){
            strcat(command,"/");
            strcat(command,&((*(argv+1))[2]));
            }
        }


    else if((*(argv+1))[0] == '.'       &&      (*(argv+1))[1] == '/'){
        getcwd(command,sizeof(command));
        strcat(command,&((*(argv+1))[1]));
        }

    else
        strcpy(command,*(argv+1));

    int flag=0;
    flag = chdir(command);
    if(flag == 0)
        printf("Directory Changed to: %s",command);
    else
        printf("Could not change directory.");    
}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void praser(char input[]){
    int num = strlen(input);
    num ++;

    char tt[num];
    strcpy(tt,input);

    char *token = strtok(tt," ");
    char **temp;

    int n=0;
    while(token != NULL){
        n++;
        token = strtok(NULL, " ");
        }

    temp = (char**)malloc(sizeof(char*)*n);

    token = strtok(input, " ");

    int i=0;
    while(token != NULL){
        temp[i] = (char*)malloc(    ((int)strlen(token))+1  );
        strcpy(temp[i],token);
        token = strtok(NULL, " ");
        i++;
        }

    argc = n;
    argv = temp;
    }
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void ls(int argc, char **argv){
	if(argc > 3){
		printf("\nToo Many Arguments.\n");
		exit(1);
		}
	
	if(argc == 2){
		do_ls(*(argv+1));
		}

	if(argc == 3){
		if(strcmp(*(argv+2), "-a" )==0 || strcmp(*(argv+2),"--all")==0)
			do_ls_all(*(argv+1));

		else if(strcmp(*(argv+2), "-l" )==0 || strcmp(*(argv+2),"-al")==0 || strcmp(*(argv+2),"-la")==0)
			do_ls_l(*(argv+1));


		else{
			printf("\nArgument \'%s\' is invalid",*(argv+2));
			exit(1);
			}

		}

    }

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void do_ls(char dirname[]){
	DIR *dir_ptr;				//The directory
	struct dirent *direntp; 	//each entry
	if((dir_ptr = opendir(dirname)) == NULL){
		fprintf(stderr, "\nls: cannot open %s\n", dirname);
		exit(1);
		}

	printf("\n");
	while((direntp = readdir(dir_ptr)) != NULL){
		if(direntp->d_name[0] == '.') //This will not display hidden folders and ".", "..".
			continue;
		printf("%s\n",direntp->d_name);

		}
	closedir(dir_ptr);

	}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void do_ls_all(char dirname[]){
	DIR *dir_ptr;				//The directory
	struct dirent *direntp; 	//each entry
	if((dir_ptr = opendir(dirname)) == NULL){
		fprintf(stderr, "\nls: cannot open %s\n", dirname);
		exit(1);
		}

	printf("\n");
	while((direntp = readdir(dir_ptr)) != NULL){
		printf("%s\n",direntp->d_name);
		}
	closedir(dir_ptr);

	}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void do_ls_l(char dirname[]){
	DIR *dir_ptr;				//The directory
	struct dirent *direntp; 	//each entry
	if((dir_ptr = opendir(dirname)) == NULL){
		fprintf(stderr, "\nls: cannot open %s\n", dirname);
		exit(1);
		}

	printf("\n");
	while((direntp = readdir(dir_ptr)) != NULL){
		dostat(direntp->d_name);
		}
	closedir(dir_ptr);

	}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
//Stat functions is used to display file information
void dostat(char* filename){
	struct stat info;
	if(stat (filename, &info) == 1)		//Cannot Stat
		perror(filename);

	else
		show_file_info(filename, &info);	//show info
}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/

void show_file_info(char *filename, struct stat *info_p){
	//display the info about 'filename'. The info is stored in struct at *info_p

	char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	void mode_to_letters();
	char modestr[11];

	mode_to_letters(info_p->st_mode, modestr);

	printf("%s " , modestr);
	printf("%4d " , (int) info_p->st_nlink);
	printf("%-8s " , uid_to_name(info_p->st_uid));
	printf("%-8s " , gid_to_name(info_p->st_gid));
	printf("%8ld " , (long) info_p->st_size);
	printf("%.12s " , 4+ctime(&info_p->st_mtime));
	printf("%s\n" , filename);
	}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/

void mode_to_letters(int mode, char str[]){
	strcpy(str,"----------");		//default = no perms
	if(S_ISDIR(mode))
		str[0] = 'd';		//directory

	if(S_ISCHR(mode))
		str[0] = 'c';		//char devices

	if(S_ISBLK(mode))
		str[0] = 'b';		//block devices

	if(mode & S_IRUSR)
		str[1] = 'r';		//3 bits for user
	
	if(mode & S_IWUSR)
		str[2] = 'w';

	if(mode & S_IXUSR)
		str[3] = 'x';


	if(mode & S_IRGRP)
		str[4] = 'r';		//3 bits for group
	
	if(mode & S_IWGRP)
		str[5] = 'w';

	if(mode & S_IXGRP)
		str[6] = 'x';	


	if(mode & S_IROTH)
		str[7] = 'r';		//3 bits for other
	
	if(mode & S_IWOTH)
		str[8] = 'w';

	if(mode & S_IXOTH)
		str[9] = 'x';		
	}
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
#include<pwd.h>
char *uid_to_name(uid_t uid){
	//return pointer to username associated with uid.
	struct passwd *getpwuid(), *pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid)) == NULL){
		sprintf(numstr, "%d", uid);
		return numstr;
		}

	else
		return pw_ptr->pw_name;

	}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
#include<grp.h>

char *gid_to_name(gid_t gid){
	//returns pointed to group number gid
	struct group *getgrgid(), *grp_ptr;
	static char numstr[10];

	if((grp_ptr = getgrgid(gid)) == NULL){
		sprintf(numstr,"%d",gid);
		return numstr;
		}

	else
		return grp_ptr->gr_name;
	}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
