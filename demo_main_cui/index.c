// #include <stdio.h>
// #include <dirent.h>

// int main()
// {
//     DIR *dir;
//     struct dirent *entry;

//     // Mở thư mục hiện tại
//     dir = opendir("..");

//     if (dir == NULL)
//     {
//         perror("Không thể mở thư mục");
//         return 1;
//     }

//     // Đọc danh sách các tệp tin và thư mục
//     while ((entry = readdir(dir)) != NULL)
//     {
//         printf("%s\n", entry->d_name);
//     }

//     // Đóng thư mục
//     closedir(dir);
//     return 0;
// }
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
void About();
void homeFace(char fileName[]);
int main()
{
    char c = getch();
    switch (c)
    {
    case '6':
        About();
        break;
    }
}
void homeFace(char fileName[])
{
    printf("\033[0m");
    printf("\033[2J\033[1;0H");
    printf("\033[37;43m * "
           "\033[30;46m Exit = Ctrl + Q \033[2C"
           "\033[37;43m * "
           "\033[30;46m OPen File = Ctrl + O \033[2C"
           "\033[37;43m * "
           "\033[30;46m History = Ctrl + H  \033[2C"
           "\033[37;43m * "
           "\033[30;46m Save = Ctrl + S \033[2C"
           "\033[37;43m * "
           "\033[30;46m About = F2 \n\033[0m");
    printf("\033[3;0H%\033[37;43m Current File \033[37;44m %s ", fileName);
    printf("\033[0m");
}
void About()
{
    printf("\033[6;28H\033[37;43m"
           "                                                     ");
    printf("\033[7;28H\033[30;46m"
           "                                                     ");
    printf("\033[8;28H"
           "        PBL1 : COMPUTATIONAL PROGRAMMING             ");
    printf("\033[9;28H"
           "                                                     ");
    printf("\033[10;28H"
           "        Topic : 305                                  ");
    printf("\033[11;28H"
           "                                                     ");
    printf("\033[12;28H"
           "        Instructor : Pham Cong Thang                 ");
    printf("\033[13;28H"
           "                                                     ");
    printf("\033[14;28H"
           "        Implemented by: Nguyen Van Loi ~ 102230026   ");
    printf("\033[15;28H"
           "                                                     ");
    printf("\033[16;28H"
           "                        Tran Anh Duc ~ 102230010     ");
    printf("\033[17;28H"
           "                                                     ");
    printf("\033[0m");
}