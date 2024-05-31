#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"

#define BHBLU "\e[1;94m"
#define BHGRN "\e[1;92m"

#define YELB "\e[43m"

#define DEF "\033[0m"

void sizeBox(int eNumber, char *str, char *COLOR)
{
    int sizeB = 140 / (eNumber * 2);
    int length = strlen(str);
    printf("|");
    for (int i = 1; i <= (sizeB - length); i++)
    {
        printf(" ");
        if (i == (sizeB - length) / 2 + 1)
        {
            printf("%s%s" DEF, COLOR, str);
        }
    }
}
char *view_p()
{
    FILE *View_process = fopen("./OUT/convergence_process.txt", "r");
    if (View_process == NULL)
        return "Error! opening file";
    int eNumber;
    double *arr;
    int findMax;
    double tempMaxAbsV = 0;
    char checkBoxS[1024];
    fscanf(View_process, "%d", &eNumber);
    arr = (double *)malloc(sizeof(double) * eNumber);
    printf(BLK YELB " Convergence Solution Table " DEF);
    printf("\n\n");
    for (int i = 0; i < eNumber * 2; i++)
    {
        if (i < eNumber)
        {
            sprintf(checkBoxS, "X[%d]", i);
            sizeBox(eNumber, checkBoxS, BHGRN);
        }
        else
        {
            sprintf(checkBoxS, "R[%d]", i - eNumber);
            sizeBox(eNumber, checkBoxS, BHBLU);
        }
    }
    printf("|\n");
    while (1)
    {
        for (int i = 0; i < eNumber * 2; i++)
        {
            if (fscanf(View_process, "%lf", &arr[i]) == EOF)
                return "Printed successfully!\n";
            if (i >= eNumber && fabs(arr[i]) > tempMaxAbsV)
            {
                findMax = i;
                tempMaxAbsV = fabs(arr[i]);
            }
        }
        tempMaxAbsV = 0;

        for (int i = 0; i < eNumber * 2; i++)
        {
            sprintf(checkBoxS, "%.4g", arr[i]);
            if (i < eNumber)
                sizeBox(eNumber, checkBoxS, GRN);
            else if (i == findMax)
                sizeBox(eNumber, checkBoxS, RED);
            else
                sizeBox(eNumber, checkBoxS, BLU);
        }
        printf("|\n");
    }

    fclose(View_process);
    free(arr);
    return "Printed successfully!\n";
}

int main()
{
    printf("\n" YEL "%s" DEF, view_p());
    return 0;
}
