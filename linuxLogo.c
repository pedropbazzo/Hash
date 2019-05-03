#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 51

struct info
{
 char cpu[size];
 char hostname[size];
 char kernel[size];
 char user[size];
 char distro[size];
 char packagenum[size];
 char uptime[size];
 }s;


//BB- bold,bright
#define BBblack "\033[1;30m"
#define BBred "\033[1;31m"
#define BBgreen "\033[1;32m"
#define BByellow "\033[1;33m"
#define BBblue "\033[1;34m"
#define BBmagenta "\033[1;35m"
#define BBcyan "\033[1;36m"
#define BBwhite "\033[1;37m"

#define black "\033[2;30m"
#define red "\033[2;31m"
#define green "\033[2;32m"
#define yellow "\033[2;33m"
#define blue "\033[2;34m"
#define magenta "\033[2;35m"
#define cyan "\033[2;36m"
#define white "\033[2;37m"

#define end "\033[0m"


void archLogo(void);
void setup(void);
/*-----------------------------------------------------------------------------------------------------*/
char uptime[size];
char home[size];
char file[size];
char user[]=" ";
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/



int main()
{
    setup();
 archLogo();
 }
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/




void archLogo(void)
{
//printf("................................................................................");
printf("    		   	 \n");
printf("%s                   & 		        %s\n",BBcyan,end);
printf("%s                  ##9		        %s\n",BBcyan,end);
printf("%s                 @@@#%s}            %s%sOS:%s Linux\n",BBcyan,cyan,end,BBcyan,end);
printf("%s                @@@@@%s#;           %s%sHostname:%s %s\n",BBcyan,cyan,end,BBcyan,end,s.hostname);
printf("%s               . '@@@@%s#;          %s%sKernel Version:%s %s\n",BBcyan,cyan,end,BBcyan,end,s.kernel);
printf("%s              @$/. @@@@%s#;         %s%sDistribution:%s %s\n",BBcyan,cyan,end,BBcyan,end,s.distro); 
printf("%s             @@@@@@;@@@@%s#;        %s%sUptime:%s %s\n",BBcyan,cyan,end,BBcyan,end,s.uptime); 
printf("%s            @@@@@@@@@@@@@#%s;       %s%sPackages:%s %s\n",BBcyan,cyan,end,BBcyan,end, s.packagenum);
printf("%s           @@@@%s###########%s@;      %s\n",BBcyan,BBblue,BBcyan,end);
printf("%s          @%s########_########;     %sCPU:%s %s\n",BBcyan,BBblue,BBcyan,end, s.cpu);
printf("%s         #######       ######;	%s  \n",BBblue,end);
printf("%s        ######/         \\#####}  %s User:%s %s\n",BBblue,BBcyan,end,s.user);
printf("%s       #######;         ;######;  %s            \n",BBblue,end);
printf("%s      ########:         :####^##;	%s  \n",BBblue,end);
printf("%s     ##########.       .######. *;%s   	\n",BBblue,end);
printf("%s    #######                 ####.   %s     \n",BBblue,end);
printf("%s   ####                        ####.	%s\n",BBblue,end);
printf("%s  /#                               #\\	%s\n",BBblue,end);
printf("\n");
 }

 void setup (void)
 {
   FILE *fp;  
   short i=0;
      strcpy(home,getenv("HOME"));
strcpy(file,home);
strcat(file,"/.linuxLogoConfig");
 fp=fopen(file,"rb");
    if(fp==NULL)
     exit(1);
    fread(&s,sizeof(s),1,fp);
   fclose(fp);   
/*-----------------------------------------------------------*/

 }
