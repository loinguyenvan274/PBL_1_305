#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>
void showEnterKey(char **EnterKey, int rowNumber);
int main()
{
    char **EnterKey;
    printf("\033[2J");
    showEnterKey(EnterKey, 5);
    printf("\033[0m");
}
void showEnterKey(char **EnterKey, int rowNumber)
{

    char insertBotton = '\0';
    EnterKey = (char **)malloc(rowNumber * sizeof(char *));
    for (int i = 0; i <= rowNumber; i++)
    {
        EnterKey[i] = (char *)malloc(30 * sizeof(char));
        strcpy(EnterKey[i], "\0");
    }

    int tickLocation = 0;
    while (insertBotton != 24)
    {
        insertBotton = getch();
        printf("\033[30;46m\033[%d;%dH%s", tickLocation + 5, Round(rowNumber) * 12, EnterKey[tickLocation]);
        switch (insertBotton)
        {
        case 80:
            if (tickLocation == rowNumber)
                continue;
            tickLocation++;
            break;
        case 72:
        case 10:
            if (tickLocation == 0)
                continue;
            tickLocation--;
            break;
        default:
            if (insertBotton >= '0' && insertBotton <= '9')
            {
                char temp[2];
                temp[0] = insertBotton;
                strcat(EnterKey[tickLocation], temp);
            }
            else if (insertBotton == 8)
            {
                char *endOfString = EnterKey[tickLocation];
                while (*endOfString != '\0')
                {
                    ++endOfString;
                }
                *(endOfString - 1) = '\0';
            }
            break;
        }
        printf("\033[34;41m\033[%d;%dH%s", tickLocation + 5, Round(rowNumber) * 12, EnterKey[tickLocation]);
    }
}