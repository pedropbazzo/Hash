#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<stdio.h>
#define size 51

char home[size];
char file[size];

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


/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/

void add(void)
{
short i,k;
char ch=0;
char name[101];
FILE *fp;
/*-------------------------------------------------------------*/
 system("pacman -Q | wc -l >> ~/no_of_packages.txt");
 system("uname -r >> ~/kernelRelease.txt");
 system("who -b >> ~/uptime.txt");


strcpy(s.user, getenv("USER"));
gethostname(s.hostname, size);
strcpy(home,getenv("HOME"));
/*-------------------------------------------------------------*/
fp = fopen("/proc/cpuinfo","r");
 if(fp == NULL)
  exit(1);
while(!feof(fp))
{
 fgets(name,101,fp);
 if(strncmp(name,"model name",10) == 0)
  break;
 }
 fclose(fp);

 for(i=0; name[i]!=':'; i++);
 strcpy(s.cpu,&(name[0])+i+2);
 s.cpu[strlen(s.cpu)-1]='\0';
/*-------------------------------------------------------------*/
fp = fopen("/etc/os-release","r");
 if(fp == NULL)
  exit(1);
  ch=0;

 while(ch!='\"')
  fscanf(fp,"%c",&ch);
  
i=0;
s.distro[i]=0;
 while(s.distro[i-1]!='\"' && !feof(fp))
 {
  fscanf(fp,"%c",&(s.distro[i]));
  i++;
  } 
 fclose(fp);

 s.distro[i-1]='\0';
 
/*-------------------------------------------------------------*/
strcpy(file,home);
strcat(file,"/no_of_packages.txt");
 fp=fopen(file,"r");
    if(fp==NULL)
        exit(1);

    fgets(s.packagenum,size,fp);
   fclose(fp);
   remove(file);
   s.packagenum[strlen(s.packagenum)-1]='\0';
/*-------------------------------------------------------------*/

strcpy(file,home);
   strcat(file,"/uptime.txt");
   fp=fopen(file,"r");
    if(fp==NULL)
     exit(1);
    fgets(s.uptime,size,fp);
   fclose(fp);
   remove(file);

   i=0;
   while(s.uptime[i]==' ')
    i++;

   strcpy(s.uptime, (s.uptime+i)); 
    
   while(s.uptime[i]!='\n')
   i++;

   s.uptime[i]='\0';    

/*-------------------------------------------------------------*/
strcpy(file,home);
strcat(file,"/kernelRelease.txt");
 fp=fopen(file,"r");
    if(fp==NULL)
     exit(1);
    fgets(s.kernel,size,fp);
   fclose(fp);
   remove(file);
   s.kernel[strlen(s.kernel)-1]='\0';
/*-------------------------------------------------------------*/

 }

/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/

int main()
{
  FILE *fp;
 add();
strcpy(file,home);
strcat(file,"/.linuxLogoConfig");
 fp=fopen(file,"wb");
    if(fp==NULL)
     exit(1);
    fwrite(&s,sizeof(s),1,fp);
   fclose(fp);

}