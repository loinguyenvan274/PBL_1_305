#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>

#define ERROR_MARGIN 1e-5
#define maxmatrix 50

#define DEFAULT_FLAG 0
#define TICK_FLAG 1
#define NOT_SUITABLE -1
#define MIDDLE_INSESRT_FLAG 2
#define LAST_INSERT_FLAG 3
#define SAVE_BUTTON_FLAG 4
#define SOLVE_FLAG 5
#define SAVE_BOTTON_EX_FLAG 6

#define MAX_KEY 30

////maxtrix
#define SHOW_MATRIX "Show_matrix"
#define SHOW_DEFAULT "Not_show_matrix"

int eNumber;
typedef struct numbersList
{
    float data;
    struct numbersList *next;
} numbersList;
typedef struct lineList
{
    struct numbersList *numbersList;
    struct lineList *lineListNext;
} lineList;
// stack lưu xóa nhập ký tự bàn phím
typedef struct stackEnterKey
{
    int top;
    char *key;
} stackEnterKey;

void changematrix(double **matrix);
void EnterE(lineList *listNumberLine, double **matrix, double *conTerms);
void MaWriteLog(double **matrix);
int checkMaxInLine(double **matrix, int loc, int cow);
/*chuyển đổi ma trận sao cho các phẩn thử Aij với i == j lớn nhất các phẩn tử
trên hàng của nó ngoại trừ
*/
void tranfo(double **matrix, int mDRow, int away);
double maxDecrease(double numberOrigin, double numberTemp);
// Swap
void Swap(double *a, double *b);
void SwapRow(double **matrix, int row_1, int row_2);
int maxArray(double Array[], int NElement);
typedef double general_Solution;
general_Solution *solve(double **matrix);
int Round(int a);
void init(double a[], int n);
// kiểm tra số phần tử trên một dòng
int countEleNumber(char filePath[]);
// thêm data vào danh sách
numbersList *buidNumbersListToFile(FILE *f, int ElementNumbers);

/**
 * \brief in các phân tử ra màng hình
 * \param [in] LocaInsert : là vị trí hiển trị khoảng trống để nhập vào số chèn;
 * bao gồm 2 tin hiệu SHOW_MATRIX in ra matrix & SHOW_DEFAULT in ra các phần tử của danh sách
 */
void printAllElement(lineList *listNumberLine, int LocaInsert, char typeShow[]);
// kết nối các hàng lại
void connetAllNumberList(FILE *f, lineList **listNumberLine, int ElementNumberALine);

// giải phóng bộ nhớ
void freeStruct(lineList **listNumberLine);
// chèn vào vị trí chính giữa
void insert(numbersList **head, int location, float insNumber);
void insertAllLine(lineList **head, int location, char **insertNumber);
// Viết vào file
void writeToFile(lineList *head, FILE *f);
// graphic
void getPath(char path[], char FOF[]);
void remoChPath(char str[]);
int checkFile(char str[]);
int CpNameList(char pathName[], char **nameList);
int CpNameList(char pathName[], char **nameList);
void boxFiledialog();
void showHeadF();
void showBox(int n);
void About();
void homeFace(char fileName[]);
void mallString(char **str, int size_str);
void freeString(char **str, int size_str);
char **showEnterKey(int rowNumber);
void freeEnIn(char **EnterInsert, int size_str);
// functions stack
void initSKey(stackEnterKey *enterKey);
void popKey(stackEnterKey *enterKey, char key);
void pushKey(stackEnterKey *enterKey);
// giải ma trận
void solvematrix(lineList *listNumberLine, int ElementALineNumber, general_Solution **genSolution, double *conTerms);
int main()
{
    printf("\033[2J");
    char button, tempButton = '\0';
    FILE *fLog = fopen("./OUT/solver_output.log", "w");
    fprintf(fLog, "");
    fclose(fLog);
    int flagKey = DEFAULT_FLAG;
    double exper[10];
    homeFace("No Find");
    char filePath[1024];
    char Path[1024];
    char **enterKey;
    int aLineElementNumber, count__File_Number;
    FILE *f, *fWrite;
    lineList *listNumberLine = NULL;
    general_Solution *genSolution = NULL;
    while (1)
    {
        button = getch();
        switch (button)
        {
        case 105: // insert I
            if (flagKey == DEFAULT_FLAG || flagKey == SAVE_BUTTON_FLAG)
                break;
            printf("\033[2J");
            int count = 0;
            getPath(Path, "file");
            if (strcmp(Path, "EXIT") == 0)
                break;
            count__File_Number = countEleNumber(Path);
            if (count__File_Number < aLineElementNumber + 1)
            {
                homeFace(filePath);
                printf("\033[3;0H"
                       "\033[37;43m Warning: \033[34;41m The File \"%s\" is invalid\033[0m.",
                       filePath);
                continue;
            }
            f = fopen(filePath, "r");
            double tempNumber;
            enterKey = (char **)malloc(sizeof(char *) * (aLineElementNumber));
            while ((fscanf(f, "%lf", &tempNumber) != -1) && (count != aLineElementNumber + 1))
            {
                enterKey[count] = (char *)malloc(sizeof(char) * 30);
                sprintf(enterKey[count], "%lf", tempNumber);
                count++;
            }
            fclose(f);
            if (flagKey == MIDDLE_INSESRT_FLAG)
            {
                insertAllLine(&listNumberLine, Round(aLineElementNumber), enterKey);
                printAllElement(listNumberLine, -1, SHOW_DEFAULT);
                flagKey = SAVE_BUTTON_FLAG;
            }
            else if (flagKey == LAST_INSERT_FLAG)
            {
                double conTerms[aLineElementNumber];
                homeFace(filePath);
                printAllElement(listNumberLine, -1, SHOW_MATRIX);
                for (int i = 0; i < aLineElementNumber; i++)
                {
                    printf("\033[%d;%dH\033[30;46m", i + 5, aLineElementNumber * 19 - 2);
                    conTerms[i] = strtod(enterKey[i], NULL);
                    showBox(12);
                    printf("\033[%d;%dH\033[30;46m %g", i + 5, aLineElementNumber * 19 - 2, conTerms[i]);
                }
                solvematrix(listNumberLine, aLineElementNumber, &genSolution, conTerms);
                freeStruct(&listNumberLine);
                flagKey = SAVE_BOTTON_EX_FLAG;
                break;
            }
            freeEnIn(enterKey, (aLineElementNumber + 1));
            break;
        case 15:
            // open Ctrl + o
            getPath(filePath, "file");
            if (strcmp(filePath, "EXIT") == 0)
                break;
            count__File_Number = countEleNumber(filePath);
            if (((int)sqrt(count__File_Number)) * ((int)sqrt(count__File_Number) + 1) != count__File_Number)
            {
                homeFace(filePath);
                printf("\033[3;0H"
                       "\033[37;43m Warning: \033[30;42m The File \"%s\" is invalid\033[0m.",
                       filePath);
                continue;
            }
            aLineElementNumber = (int)sqrt(count__File_Number);
            f = fopen(filePath, "r");
            connetAllNumberList(f, &listNumberLine, aLineElementNumber);
            fclose(f);
            printAllElement(listNumberLine, Round(aLineElementNumber), SHOW_DEFAULT);
            aLineElementNumber++;
            flagKey = MIDDLE_INSESRT_FLAG;
            printf("\033[4;0H"
                   "\033[37;43m * \033[34;41m  Insert via file  = I \033[0m."
                   "\t\t\t\t\t \033[37;43m * \033[34;41m  Insert using keyboard  = K \033[0m.");
            // printf("\033[8;0H");
            break;
        case 19:
            // Save when Ctr + S
            char saveFileName[1024];
            if (flagKey != SAVE_BUTTON_FLAG)
                break;
            getPath(Path, "directory");
            homeFace("No Find");
            printAllElement(listNumberLine, -1, SHOW_DEFAULT);
            if (strcmp(Path, "EXIT") == 0)
                break;
            strcat(Path, "\\");
            printf("\033[3;0H"
                   "\033[37;43m File name: \033[37;44m %s",
                   Path);
            scanf("%s", saveFileName);
            printf("\033[0m");
            if (strchr(saveFileName, '.') == NULL) // nếu người dùng nhập tên không có file extension mặt định là .OUT
                strcat(saveFileName, ".OUT");
            strcat(Path, saveFileName);
            fWrite = fopen(Path, "w");
            if (fWrite == NULL)
            {
                printf("\033[3;0H"
                       "\033[37;43m notification \033[37;44m File save failed \033[0m");
            }
            writeToFile(listNumberLine, fWrite);
            fclose(fWrite);
            flagKey = SOLVE_FLAG;
            printf("\033[2;0H"
                   "\033[37;43m notification \033[37;44m File save successful \033[0m\t\t "
                   "\033[37;43m * "
                   "\033[30;46m Linear equations solving = Ctrl + L "
                   " \033[0m");
            break;
        case 12: // Ctrl + L
            // giải hệ phương trình tuyến tính
            if (flagKey != SOLVE_FLAG)
                break;
            // in ra ma trận mà bắc người dùng chọn nhập từ bàn phím hay từ file
            printAllElement(listNumberLine, aLineElementNumber, SHOW_MATRIX);
            printf("\033[4;0H"
                   "\033[37;43m * \033[34;41m  Insert via file  = I \033[0m."
                   "\t\t\t\t\t \033[37;43m * \033[34;41m  Insert using keyboard  = K \033[0m.");
            flagKey = LAST_INSERT_FLAG;
            break;
        case 107:
            // nếu người dùng nhập k thì chèn bằng ban phím
            printf("\033[4;0H\033[0m                               \t\t\t\t\t                                  ");
            enterKey = showEnterKey(aLineElementNumber);
            freeEnIn(enterKey, (aLineElementNumber));
            insertAllLine(&listNumberLine, Round(aLineElementNumber), enterKey);
            printAllElement(listNumberLine, -1, SHOW_DEFAULT);
            flagKey = SAVE_BUTTON_FLAG;
            break;
        case 24:
            printf("\033[2J\033[0;0H");
            return 0;
        default:
            break;
        }
        homeFace(filePath);
        if (flagKey == SAVE_BOTTON_EX_FLAG)
        {
            if (genSolution == NULL)
            {
                printf("\033[%d;0H !Error runtime or No solution ", aLineElementNumber + 5);
            }
            else
            {
                printf("\033[%d;0H General solution  X = { %g", aLineElementNumber + 5, genSolution[0]);
                for (int i = 0; i < aLineElementNumber; i++)
                {
                    printf(", %g", genSolution[i]);
                }
                printf(" }");
            }
        }
    }
}
//====================function=================//
int countEleNumber(char filePath[])
{
    FILE *f = fopen(filePath, "r");
    if (f == NULL)
    {
        return NOT_SUITABLE;
    }
    double takeNu;
    int count = 0;
    while (fscanf(f, "%lf", &takeNu) != -1)
    {
        count++;
    }
    return count;
}
numbersList *buidNumbersListToFile(FILE *f, int ElementNumbers)
{
    numbersList *head, *node;
    double dataF;
    for (int i = 1; i <= ElementNumbers; i++)
    {
        numbersList *newNode = (numbersList *)malloc(sizeof(numbersList));
        fscanf(f, "%lf", &dataF);
        newNode->data = dataF;
        newNode->next = NULL;
        if (i == 1)
        {
            head = newNode;
            node = newNode;
        }
        else
        {
            node->next = newNode;
            node = node->next;
        }
    }
    node = NULL;
    return head;
}
void printAllElement(lineList *listNumberLine, int middle, char typeShow[])
{

    lineList *tempLine = listNumberLine;
    int i = 0, j = 1;
    char string[20];
    printf("\033[%d;0H", i + 5);
    while (tempLine != NULL)
    {
        numbersList *tempNum = tempLine->numbersList;
        while (tempNum != NULL)
        {
            if (j == middle + 1)
            {
                printf("\033[37;43m");
                showBox(12);
            }
            printf("\033[30;46m");
            if (strcmp(typeShow, "Show_matrix") == 0)
            {
                if (tempNum->data >= 0)
                {
                    printf(" + %g X(%d)", tempNum->data, j);
                    sprintf(string, " + %g X(%d)", tempNum->data);
                }
                else
                {
                    printf(" - %g X(%d)", tempNum->data * (-1), j);
                    sprintf(string, "  %g X(%d)", tempNum->data);
                }
                showBox(18 - strlen(string));
            }
            else
            {
                printf(" %g", tempNum->data);
                sprintf(string, "%g", tempNum->data);
                showBox(12 - strlen(string));
            }
            tempNum = tempNum->next;
            j++;
        }
        if (strcmp(typeShow, "Show_matrix") == 0)
        {
            printf(" = \033[37;43m");
            showBox(12);
        }
        printf("\n");
        tempLine = tempLine->lineListNext;
        j = 1;
        i += 1;
    }
    printf("\033[0m");
}
void connetAllNumberList(FILE *f, lineList **listNumberLine, int ElementNumberALine)
{
    lineList *templistNumberLine;
    for (int i = 1; i <= ElementNumberALine + 1; i++)
    {
        lineList *temp = (lineList *)malloc(sizeof(lineList));
        temp->numbersList = buidNumbersListToFile(f, ElementNumberALine);
        temp->lineListNext = NULL;
        if (i == 1)
        {
            templistNumberLine = temp;
            *listNumberLine = temp;
        }
        else
        {
            templistNumberLine->lineListNext = temp;
            templistNumberLine = templistNumberLine->lineListNext;
        }
    }
    templistNumberLine = NULL;
}
void freeStruct(lineList **listNumberLine)
{
    lineList *templocation = *listNumberLine;
    while (templocation != NULL)
    {
        numbersList *tempNumberLocation = templocation->numbersList;
        while (tempNumberLocation != NULL)
        {
            numbersList *saveLoca = tempNumberLocation;
            tempNumberLocation = tempNumberLocation->next;
            free(saveLoca);
        }
        templocation = templocation->lineListNext;
    }
    templocation = *listNumberLine;
    while (templocation != NULL)
    {
        lineList *saveloca = templocation;
        templocation = templocation->lineListNext;
        free(saveloca);
    }
}
void insert(numbersList **head, int location, float insNumber)
{
    numbersList *temp = *head;
    for (int i = 0; i < location - 1; i++)
    {
        temp = temp->next;
    }
    numbersList *newNode = (numbersList *)malloc(sizeof(numbersList));
    newNode->next = temp->next;
    temp->next = newNode;
    newNode->data = insNumber;
}
void insertAllLine(lineList **head, int location, char **insertNumber)
{
    int i = 0;
    lineList *temp = *head;
    while (temp != NULL)
    {
        float insNumber = strtod(insertNumber[i++], NULL);
        insert(&(temp->numbersList), location, insNumber);
        temp = temp->lineListNext;
    }
}
void writeToFile(lineList *head, FILE *f)
{
    lineList *temp = head;
    while (temp != NULL)
    {
        numbersList *tempSub = temp->numbersList;
        while (tempSub != NULL)
        {
            fprintf(f, "%g ", tempSub->data);
            tempSub = tempSub->next;
        }
        fprintf(f, "\n");
        temp = temp->lineListNext;
    }
}
void solvematrix(lineList *listNumberLine, int ElementALineNumber, general_Solution **genSolution, double *conTerms)
{
    eNumber = ElementALineNumber;
    double **matrix = (double **)malloc(eNumber * sizeof(double *));
    for (int i = 0; i < eNumber; i++)
    {
        for (int j = 0; j < eNumber + 1; j++)
        {
            matrix[i] = (double *)malloc((eNumber + 1) * sizeof(double));
        }
    }
    EnterE(listNumberLine, matrix, conTerms);
    changematrix(matrix);
    MaWriteLog(matrix);
    *genSolution = solve(matrix);
}
void MaWriteLog(double **matrix)
{
    FILE *f;
    f = fopen("./OUT/solver_output.log", "a");
    fprintf(f, "\n\n");
    int j;
    for (int i = 0; i < eNumber; i++)
    {
        for (j = 0; j < eNumber + 1; j++)
        {
            fprintf(f, "%g ", matrix[i][j]);
        }
        fprintf(f, "\n");
    }
}
void EnterE(lineList *listNumberLine, double **matrix, double *conTerms)
{
    printf("\n");
    lineList *tempLine = listNumberLine;
    numbersList *tempNumberlist = tempLine->numbersList;
    for (int i = 0; i < eNumber; i++)
    {

        for (int j = 0; j < eNumber; j++)
        {

            matrix[i][j] = tempNumberlist->data;
            tempNumberlist = tempNumberlist->next;
        }

        tempLine = tempLine->lineListNext;
        if (tempLine == NULL)
            break;
        tempNumberlist = tempLine->numbersList;
    }
    for (int i = 0; i < eNumber; i++)
    {
        matrix[i][eNumber] = conTerms[i];
    }
}
void init(double a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = DEFAULT_FLAG;
    }
}
int checkMaxInLine(double **matrix, int loc, int cow)
{
    int markdow = -1;
    double SValue = matrix[loc][cow];
    for (int j = 0; j < eNumber; j++)
    {
        if (fabs(matrix[loc][j]) >= fabs(SValue) && j != cow)
        {
            markdow = j;
            SValue = matrix[loc][j];
        }
    }
    return markdow;
}
void Swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}
void SwapRow(double **matrix, int row_1, int row_2)
{
    for (int j = 0; j < eNumber + 1; j++)
    {
        Swap(&matrix[row_1][j], &matrix[row_2][j]);
    }
}
int Round(int a)
{
    if (a % 2 == 0)
        return a / 2;
    else
        return (a + 1) / 2;
}
void changematrix(double **matrix)
{
    double tick[eNumber];
    init(tick, eNumber);
    for (int j = 0; j < eNumber; j++)
    {
        double findMax = -1;
        int loc = -1;
        for (int i = 0; i < eNumber; i++)
        {
            if (tick[i] == TICK_FLAG)
                continue;
            if (fabs(matrix[i][j]) > fabs(findMax))
            {
                findMax = matrix[i][j];
                loc = i;
            }
        }
        int markdow = checkMaxInLine(matrix, loc, j);
        if (tick[loc] == 0 && markdow == -1)
        {

            SwapRow(matrix, loc, j);
            tick[j] = TICK_FLAG;
        }
        // sap xep theo cot
    }
    for (int i = 0; i < eNumber; i++)
    {
        if (tick[i] != TICK_FLAG)
        {
            tranfo(matrix, i, -1);
            tick[i] = TICK_FLAG;
            // markdow lưu vị trí có phần tử có độ lơn cao nhất
        }
    }
    for (int i = 0; i < eNumber; i++)
    {
        double tempValue = matrix[i][i];
        for (int j = 0; j < eNumber + 1; j++)
        {
            matrix[i][j] /= tempValue * (-1);
        }
        matrix[i][eNumber] *= -1;
    }
    MaWriteLog(matrix);
}

void tranfo(double **matrix, int mDRow, int away)
{
    MaWriteLog(matrix);
    static int count = -1;
    count++;
    int markdow = checkMaxInLine(matrix, mDRow, mDRow);

    if (markdow == -1 || count > 50)
    {
        count = -1;
        return;
    }
    double temp = fabs(matrix[mDRow][markdow]) - fabs(matrix[mDRow][mDRow]);
    int locDec = -1;
    float flag = 1;
    for (int i = 0; i < eNumber; i++)
    {
        if (i == mDRow || away == i)
            continue;
        for (int j = 0; j < eNumber + 1; j++)
        {
        }
        if (temp > fabs(matrix[mDRow][markdow] + matrix[i][markdow]) - fabs(matrix[mDRow][mDRow] + matrix[i][mDRow]))
        {
            temp = fabs(matrix[mDRow][markdow] + matrix[i][markdow]) - fabs(matrix[mDRow][mDRow] + matrix[i][mDRow]);
            locDec = i;
            flag = 1;
        }
        if (temp > fabs(matrix[mDRow][markdow] - matrix[i][markdow]) - fabs(matrix[mDRow][mDRow] - matrix[i][mDRow]))
        {
            temp = abs(matrix[mDRow][markdow] - matrix[i][markdow]) - fabs(matrix[mDRow][mDRow] - matrix[i][mDRow]);
            locDec = i;
            flag = -1;
        }
    }
    away = locDec;
    if (locDec == -1)
        return;
    else
    {
        for (int j = 0; j < eNumber + 1; j++)
        {
            matrix[mDRow][j] += matrix[locDec][j] * flag;
        }
    }
    /*
    so sánh con số cao nhất và con đang xét
    trừ hoạc cộng mỗi hàng khác với nó và so sánh khoảng cảnh nó có giảm xuống hay không

    */
    tranfo(matrix, mDRow, away);
}
/*
đầu tiên xác định hàng "x" rồi kiểm tra vị trí giá trị tuyệt đối cao nhất và trả vể vị trí của phần tử có giá trị tuyệt đối cao nhất đó
trừ hoặc cộng các phần tử trên hàng với phần các phần tử trên hàng kia.

*/
int maxArray(double Array[], int NElement)
{
    double tempValue = Array[0];
    int loc = 0;
    for (int i = 1; i < NElement; i++)
    {
        if (fabs(tempValue) < fabs(Array[i]))
        {
            tempValue = Array[i];
            loc = i;
        }
    }
    return loc;
}
general_Solution *solve(double **matrix)
{
    double surplus[eNumber];
    double *allX = (double *)malloc(sizeof(double) * (eNumber + 1));
    for (int i = 0; i < eNumber; i++)
    {
        surplus[i] = matrix[i][eNumber];
        allX[i] = 0;
    }
    int maxValueLocation = maxArray(surplus, eNumber);
    int x = 0;
    while (fabs(surplus[maxValueLocation]) > ERROR_MARGIN)
    {
        allX[maxValueLocation] += surplus[maxValueLocation];
        for (int i = 0; i < eNumber; i++)
        {
            if (i != maxValueLocation)
            {
                surplus[i] -= matrix[i][maxValueLocation] * surplus[maxValueLocation] * (-1);
            }
        }
        surplus[maxValueLocation] = 0;
        maxValueLocation = maxArray(surplus, eNumber);

        x++;
        if (x == 1000000)
        {
            // consolog
            // printf("# !Error runtime or No solution\n");
            return NULL;
        }
    }
    return allX;
}
//==============function Graphic ==============

void getPath(char path[], char FOD[])
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
        printf("\033[5;0H\033[37;43m Parent \033[20C Current \033[30C Contents \033[0m");
        for (int i = 0; i < 20; i++)
        {
            printf("\033[%d;60H   ", 6 + i);
            showBox(60);
        }
        if (strstr(cuDirList[count], ".") != NULL)
        {
            FILE *f;
            char strLine[68];
            f = fopen(tempDirPath, "r");
            int row = 0;
            while (fgets(strLine, 64, f) != NULL)
            {

                if (row > 18)
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
            else if (c == 13 || c == 77)
            {
                if (!((strcmp(FOD, "directory") == 0 && checkFile(tempDirPath) == 0 && c == 13)) && !(strcmp(FOD, "file") == 0 && checkFile(tempDirPath) == 1))
                {
                    strcat(cwd, "\\");
                    strcat(cwd, cuDirList[count]);
                }
                else
                {
                    printf("\033[2J\033[1;0H\033[0m");
                    strcpy(path, tempDirPath);
                    for (int i = 0; i < 50; i++)
                    {
                        free(paDirList[i]);
                        free(cuDirList[i]);
                    }
                    free(paDirList);
                    free(cuDirList);
                    return;
                }
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
    strcpy(path, "EXIT");
    printf("\033[2J\033[1;0H");
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
void showBox(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
    printf("\033[0m");
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
    int finaChar = strlen(str);
    if (str[finaChar - 1] == '.' && str[finaChar - 2] == '\\')
        return 0;
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
void homeFace(char fileName[])
{

    printf("\033[1;0H");
    printf("\033[37;43m * "
           "\033[30;46m Exit = Ctrl + X \033[2C"
           "\033[37;43m * "
           "\033[30;46m Open File = Ctrl + O \033[2C"
           "\033[37;43m * "
           "\033[30;46m History = Ctrl + H  \033[2C"
           "\033[37;43m * "
           "\033[30;46m Save = Ctrl + S \033[2C"
           "\033[37;43m * "
           "\033[30;46m About = F2 \n\033[0m");
    printf("\033[3;0H"
           "\033[37;43m Current File \033[37;44m %s ",
           fileName);
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
void mallString(char **str, int size_str)
{
    str = (char **)malloc(sizeof(char *) * size_str);
    for (int i = 0; i < size_str; i++)
    {
        str[i] = (char *)malloc(30 * sizeof(char));
    }
}
void freeString(char **str, int size_str)
{
    for (int i = 0; i < size_str; i++)
    {
        free(str[i]);
    }
    free(str);
}
char **showEnterKey(int rowNumber)
{
    char insertBotton = '\0';
    char **EnterKey;
    stackEnterKey keyNumber[rowNumber];

    EnterKey = (char **)malloc(rowNumber * sizeof(char *));
    for (int i = 0; i < rowNumber; i++)
    {
        initSKey(&keyNumber[i]);
        EnterKey[i] = (char *)malloc(30 * sizeof(char));
        keyNumber[i].key = EnterKey[i];
    }

    int tickLocation = 0;
    while (insertBotton != 24)
    {

        insertBotton = getch();
        printf("\033[37;43m\033[%d;%dH%s", tickLocation + 5, Round(rowNumber) * 13 + 1, EnterKey[tickLocation]);
        showBox(12 - strlen(EnterKey[tickLocation]));
        switch (insertBotton)
        {
        case 13:
            int i;
            for (i = 0; i < rowNumber; i++)
            {
                if (keyNumber[i].top == -1)
                    break;
            }
            if (i == rowNumber)
                return EnterKey;
        case 80:
            if (tickLocation == rowNumber - 1)
                continue;
            tickLocation++;
            break;
        case 72:
            if (tickLocation == 0)
                continue;
            tickLocation--;
            break;
        case 8:
            pushKey(&keyNumber[tickLocation]);
            break;
        default:
            if ((insertBotton >= '0' && insertBotton <= '9') || insertBotton == '-' || insertBotton == '.')
                popKey(&keyNumber[tickLocation], insertBotton);
            break;
        }
        printf("\033[34;41m\033[%d;%dH%s", tickLocation + 5, Round(rowNumber) * 13 + 1, EnterKey[tickLocation]);
        showBox(12 - strlen(EnterKey[tickLocation]));
    }
}
void initSKey(stackEnterKey *enterKey)
{
    enterKey->top = -1;
}
void popKey(stackEnterKey *enterKey, char key)
{
    if (enterKey->top == MAX_KEY - 1)
        return;
    else
    {
        enterKey->key[++enterKey->top] = key;
        enterKey->key[enterKey->top + 1] = '\0';
    }
}
void pushKey(stackEnterKey *enterKey)
{
    if (enterKey->top == -1)
        return;
    else
        enterKey->key[enterKey->top--] = '\0';
}
void freeEnIn(char **EnterInsert, int size_str)
{
    for (int i = 0; i < size_str; i++)
    {
        free(EnterInsert[i]);
    }
    free(EnterInsert);
}