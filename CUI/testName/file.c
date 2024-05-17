#include <string.h>
#include <stdio.h>
int main()
{
    printf("\033[34;41m");
    char name[1023];
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';
    // scanf("%s", name);
    printf("%s", name);
    FILE *f;
    f = fopen(name, "w");

    char *n = "toi khong biet ban al ai";
    fprintf(f, "%s", n);
    fclose(f);
    printf("\033[0m");
}