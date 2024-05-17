#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void boxFiledialog();
void showHeadF();
int CpNameList(char pathName[], char **nameList)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
    printf("\033[0m\n");
}

int CpNameList(char pathName[], char **nameList)
{
    DIR *dir = opendir(pathName);
    int i = -1;
    struct dirent *readDir;
    while ((readDir = readdir(dir)) != NULL)
    {
        i++;
        if (i == 20)
            break;
        nameList[i] = strdup(readDir->d_name);
    }
    closedir(dir);
    return i;
}

int checkFile(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '.')
            return 1;
        i++;
    }
    return 0;
}
void remoChPath(char str[])
{
    int i = 0, count = 0;
    while (str[i] != 0)
    {
        if (str[i] == '\\')
        {
            count++;
        }
        i++;
    }
    if (count == 1)
        return;
    i = strlen(str);
    for (; i >= 0; i--)
    {
        str[i - 1] = '\0';
        if (str[i - 2] == '\\')
            break;
    }
}
void showBox(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
    printf("\033[0m\n");
}
int main()
{
    printf("\033[2J\033[1;0H");
    char path[1024];
    boxFiledialog(path);
    printf("%s\n", path);
    return 0;
}

void boxFiledialog(char path[])
{
    char cwd[1024], tempDirPath[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("Error while retrieving current work directory\n");
        return;
    }
    strcpy(tempDirPath, cwd);
    strcat(tempDirPath, "/..");

    char **cuDirList = (char **)malloc(50 * sizeof(char *));
    char **paDirList = (char **)malloc(50 * sizeof(char *));
    for (int i = 0; i < 50; i++)
    {
        cuDirList[i] = (char *)malloc(256 * sizeof(char));
        paDirList[i] = (char *)malloc(256 * sizeof(char));
    }

    int countCurrent = CpNameList(cwd, cuDirList);
    int countParent = CpNameList(tempDirPath, paDirList);

    int count = 0, flag = 1, fileNumber = 1;

    char c = '\0';
    strcat(cwd, "\\");
    showHeadF();
    do
    {

        strcpy(tempDirPath, cwd);
        strcat(tempDirPath, "\\");
        strcat(tempDirPath, cuDirList[count]);
        printf("\033[3;0H%\033[37;43m Current directory \033[37;44m %s", tempDirPath);
        showBox(108 - strlen(tempDirPath));
        if (flag == 1)
        {
            int tick = 2;
            while (cwd[tick] != '\0')
            {
                if (cwd[tick] != '\\')
                    break;
                tick++;
            }
            if (tick != strlen(cwd))
            {

                for (int i = 2; i <= countParent; i++)
                {
                    if (checkFile(paDirList[i]))
                        printf("\033[%d;0H\033[0m %s", i + 4, paDirList[i]);
                    else
                        printf("\033[%d;0H\033[30;42m %s", i + 4, paDirList[i]);
                    showBox(20 - strlen(paDirList[i]));
                }
            }
            else
            {
                printf("\033[%d;0H\033[30;42m %s", 6, cwd);
                showBox(20 - strlen(cwd));
            }
            for (int i = 2; i <= countCurrent; i++)
            {
                if (checkFile(cuDirList[i]))
                    printf("\033[%d;29H\033[0m %s", i + 5, cuDirList[i]);
                else
                    printf("\033[%d;29H\033[30;42m %s", i + 5, cuDirList[i]);
                showBox(28 - strlen(cuDirList[i]));
            }
            flag = 0;
        }
        printf("\033[5;0H%\033[37;43m Parent \033[20C Current \033[30C Contents \033[0m");
        for (int i = 0; i < 20; i++)
        {
            printf("\033[%d;60H  ", 6 + i);
            showBox(80);
        }
        if (strstr(cuDirList[count], ".") != NULL)
        {
            FILE *f;
            char strLine[68];
            f = fopen(tempDirPath, "r");
            int row = 0;
            while (fgets(strLine, 68, f) != NULL)
            {

                if (row > 20)
                    break;
                printf("\033[%d;60H%s", 7 + row, strLine);
                row++;
            }
            fclose(f);
        }
        c = getch();
        if (checkFile(cuDirList[count]))
        {
            printf("\033[%d;29H\033[0m %s", count + 5, cuDirList[count]);
        }
        else
            printf("\033[%d;29H\033[30;42m %s", count + 5, cuDirList[count]);
        showBox(28 - strlen(cuDirList[count]));
        switch (c)
        {
        case 80:
            if (count == countCurrent)
                break;
            count++;
            break;
        case 72:
            if (count <= 0)
                break;
            count--;
            break;
        default:
            break;
        }
        if (checkFile(cuDirList[count]))
            printf("\033[%d;29H\033[34;41m %s", count + 5, cuDirList[count]);
        else
            printf("\033[%d;29H\033[37;43m %s", count + 5, cuDirList[count]);
        showBox(28 - strlen(cuDirList[count]));

        if (c == 13 || c == 75 || c == 77)
        {
            if (strcmp(cuDirList[count], "..") == 0 || c == 75)
            {
                remoChPath(cwd);
            }
            else if (c == 13)
            {
                printf("\033[2J\033[1;0H\033[0m");
                strcpy(path, tempDirPath);
                return;
            }
            else
            {

                strcat(cwd, "\\");
                strcat(cwd, cuDirList[count]);
            }
            showHeadF();
            strcpy(tempDirPath, cwd);
            countCurrent = CpNameList(cwd, cuDirList);
            strcat(tempDirPath, "\\..");
            countParent = CpNameList(tempDirPath, paDirList);
            flag = 1;
            count = 0;
        }
    } while (c != 'q');

    for (int i = 0; i < 50; i++)
    {
        free(paDirList[i]);
        free(cuDirList[i]);
    }
    free(paDirList);
    free(cuDirList);
}
void showHeadF()
{
    printf("\033[2J\033[1;0H");
    printf("\033[37;43m * "
           "\033[30;46m Exit = q \033[2C"
           "\033[37;43m * "
           "\033[30;46m Choose = enter \033[2C"
           "\033[37;43m * "
           "\033[30;46m Up = up arrow \033[2C"
           "\033[37;43m * "
           "\033[30;46m Down = down arrow \033[2C"
           "\033[37;43m * "
           "\033[30;46m Left = left arrow \033[2C"
           "\033[37;43m * "
           "\033[30;46m Right = right arrow \n\033[0m");
    printf("\033[5;0H%\033[37;43m Parent \033[20C Current \033[30C Contents ");
}