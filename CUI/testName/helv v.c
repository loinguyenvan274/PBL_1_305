#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_KEY 1000
typedef struct enterKey
{
    int top;
    char key[MAX_KEY + 1];
} enterKey;
void initSKey(enterKey *enterKey)
{
    enterKey->top = -1;
}
void popKey(enterKey *enterKey, char key)
{
    if (enterKey->top == MAX_KEY - 1)
        return;
    else
    {
        enterKey->key[++enterKey->top] = key;
        enterKey->key[enterKey->top + 1] = '\0';
    }
}
void pushKey(enterKey *enterKey)
{
    if (enterKey->top == -1)
        return;
    else
        enterKey->key[enterKey->top--] = '\0';
}

void main()
{
    enterKey enterKey;
    initSKey(&enterKey);
    char c;
    while (c != 'q')
    {
        printf("%d\n", c);
        c = getch();
        switch (c)
        {
        case 8:
            pushKey(&enterKey);
            break;

        default:
            popKey(&enterKey, c);
            break;
        }
    }
}