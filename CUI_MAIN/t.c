#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main()
{
    int eNumber = 10;
    char CMD_E[1024] = "start cmd.exe /k view_p.exe ";
    char tempS[10] = "";
    sprintf(tempS, "%d", eNumber);
    strcat(CMD_E, tempS);
    strcat(CMD_E, " && pause");
    system(CMD_E);
}