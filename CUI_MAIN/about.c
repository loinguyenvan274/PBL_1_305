#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define BLK "\e[0;30m"
#define BBLU "\e[1;34m"
#define BBLK "\e[1;30m"
#define WHTB "\e[47m"
#define reset "\e[0m"

void display_about();
int main()
{
       char button;
       display_about();
       button = getch();
}
void display_about()
{
       printf(WHTB "\033[2J\033[H");
       printf("\n");
       printf(BBLK "                         ABOUT THIS APPLICATION                        \n");
       printf("\n");
       printf(BBLU "  Project Title   :" BLK WHTB " PBL1 : COMPUTATIONAL PROGRAMMING                  \n");
       printf(BBLU "  Topic Code      :" BLK WHTB " 305                                               \n");
       printf("\n");
       printf(BBLU "  Instructor      :" BLK WHTB " Pham Cong Thang                                   \n");
       printf("\n");
       printf(BBLU "  Implemented by  :" BLK WHTB " Nguyen Van Loi (ID: 102230026)                    \n");
       printf("                     Tran Anh Duc  (ID: 102230010)                    \n");
       printf("\n");
       printf(BBLU "  Description     :" BLK WHTB " This application reads linked lists from a file,  \n");
       printf("                    performs specific operations on them, and solves  \n");
       printf("                    a system of linear equations using the residual   \n");
       printf("                    reduction method.                                 \n");
       printf("\n");
       printf(BBLU "  Features        :" BLK WHTB " - Reads N linked lists from a file                \n");
       printf("                    - Adds an element at the middle position of each  \n");
       printf("                      list and saves the result to a file             \n");
       printf("                    - Solves a system of linear equations with the    \n");
       printf("                      modified lists and saves the result to a file   \n");
       printf("\n");
       printf(BBLU "  Version         :" BLK WHTB " 1.0.0                                             \n");
       printf(BBLU "  Release Date    :" BLK WHTB " 24 / 4 / 2024                                     \n");
       printf("\n");
       printf(reset);
}
