#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

void do_ls(char[]);
void do_ls_all(char[]);
void do_ls_l(char[]);
void dostat(char*);
void show_file_info(char*, struct stat*);
void mode_to_letters(int, char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/

int main(int ac, char *av[]){
	if(ac > 3){
		printf("\nToo Many Arguments.\n");
		exit(1);
		}
	
	if(ac == 2){
		do_ls(*(av+1));
		}

	if(ac == 3){
		if(strcmp(*(av+2), "-a" )==0 || strcmp(*(av+2),"--all")==0)
			do_ls_all(*(av+1));

		else if(strcmp(*(av+2), "-l" )==0 || strcmp(*(av+2),"-al")==0 || strcmp(*(av+2),"-la")==0)
			do_ls_l(*(av+1));


		else{
			printf("\nArgument \'%s\' is invalid",*(av+2));
			exit(1);
			}

		}
	
	return 0;
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


