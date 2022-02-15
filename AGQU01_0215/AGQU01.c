#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;

    char szoveg[60];

    fp=fopen("vezeteknev.txt" ,"w+");
    fprintf(fp,"Zsigo_Bence(AGQU01)-Programtervezo_informatikus\n");
    rewind(fp);
    fscanf(fp,"%s",szoveg);
    printf("%s",szoveg);
    fclose(fp);
    return 0;
}
