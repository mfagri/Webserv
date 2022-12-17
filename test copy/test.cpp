#include <cstdio>

int main()
{
    int c;
    FILE *fp;
    fp = fopen("file.txt", "r");
    if (fp)
    {
        while ((c = getc(fp)) != EOF)
            putchar(c);
        
        //rewind(fp);
        putchar('\n');
        
        while ((c = getc(fp)) != EOF)
            putchar(c);
    }
    fclose(fp);
    return 0;
}