#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>


char* correctInput(char* path)
{
	
	int lenght;
	lenght = strlen(path);
	if(path[lenght] != '/')
	{
        	char* newPath = new char[lenght + 2];
		strcat(newPath,path);
		strcat(newPath,"/");
		return newPath;
	}
	else
	return path;	
}

void printAll(char* path)
{
	DIR *mydir;
    DIR *thedir;
    struct dirent *myfile;
    struct stat myStat;
    struct passwd *pwd;
    int size = 0;
    struct tm lt;
    char buf[1024];
    char length[100];
    long width;
    struct group *gf;
    int len = 0;
    mydir = opendir(path);
    thedir = opendir(path);
    if(mydir!= NULL){
    while((myfile = readdir(thedir)) != NULL){
        lstat(myfile->d_name, &myStat);
        size += myStat.st_blocks;
        width = (long)myStat.st_size;
        sprintf(length, "%ld", width);
        if(len < strlen(length)){
        len = strlen(length);
     }

    }

    printf("total %d\n", size/2);
    closedir(thedir);

    while((myfile = readdir(mydir)) != NULL)
    {

        lstat(myfile->d_name, &myStat);
        if((lstat(myfile->d_name, &myStat) ) == 0){
            pwd = getpwuid(myStat.st_uid);
        }
        gf = getgrgid(myStat.st_gid);
        time_t t = myStat.st_mtime;
        localtime_r(&t, &lt);
        char timebuf[80];
        char timebuf2[80];

        strftime(timebuf, sizeof(timebuf), "%F", &lt);
        strftime(timebuf2, sizeof(timebuf2), "%R", &lt);
        printf( (S_ISDIR(myStat.st_mode)) ? "d" : "-");
        printf( (myStat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (myStat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (myStat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (myStat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (myStat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (myStat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (myStat.st_mode & S_IROTH) ? "r" : "-");
        printf( (myStat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (myStat.st_mode & S_IXOTH) ? "x" : "-");
        printf(" ");
        printf("%ld ", myStat.st_nlink);
        if(pwd != 0){
        printf("%s %s %*ld %s %s %s", pwd->pw_name, gf->gr_name, len, (long)myStat.st_size, timebuf, timebuf2, myfile->d_name);
    }else  {
        printf("%d %s %*ld %s %s %s", myStat.st_uid, gf->gr_name, len, (long)myStat.st_size, timebuf, timebuf2, myfile->d_name);
    } 

    char linkname[PATH_MAX];
    ssize_t r = readlink(myfile->d_name, linkname, PATH_MAX);

    if (r != -1) {
      linkname[r] = '\0';
      printf(" -> %s\n", linkname);
    }
    else
      putchar('\n');
        }
    closedir(mydir);
    }else{
        printf("ls: cannot open directory .: Permission denied");

    }

}
int main(int argc, char **argv)
{
    

	if(argc == 1)
	{
		printAll("./");
		
	}
  

        if(argc == 2) {
            printAll(correctInput(argv[1]));
            return 0;
        }





}
