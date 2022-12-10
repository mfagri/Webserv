 #include <dirent.h>
 # include <string.h>
 # include <stdio.h>

int main(int c,char **args)
{
    DIR *dir;
    struct dirent *dent;
    char buffer[50];
    strcpy(buffer, args[1]);
    dir = opendir(buffer);   //this part
    if(dir!=NULL)
    {
        while((dent=readdir(dir))!=NULL)
            puts(dent->d_name);
    }
}
