#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ERROR_MARGIN 1e-5
#define maxmatrix 50
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

void changematrix(double **matrix);
void EnterE(lineList *listNumberLine, double **matrix);
void Printmatrix(double **matrix);
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
void solve(double **matrix, double Array[]);

void init(double a[], int n);
// kiểm tra số phần tử trên một dòng
int checkMaxNumberSeries(FILE *f);
// thêm data vào danh sách
numbersList *buidNumbersListToFile(FILE *f, int ElementNumbers);

// in danh sách ra màn hình console
void printAllElement(lineList *listNumberLine);
// kết nối các hàng lại
void connetAllNumberList(FILE *f, lineList **listNumberLine, int ElementNumberALine);

// giải phóng bộ nhớ
void freeStruct(lineList **listNumberLine);
// chèn vào vị trí chính giữa
void insert(numbersList **head, int location, float insNumber);
void insertAllLine(lineList **head, int location);
// Viết vào file
void writeToFile(lineList *head, FILE *f);

// giải ma trận
void solvematrix(lineList *listNumberLine, int ElementALineNumber, double exper[]);
int main()
{
    FILE *checkElementNumber, *f, *fWrite;
    checkElementNumber = fopen("DAYSO.IN", "r");

    int aLineElementNumber = checkMaxNumberSeries(checkElementNumber);
    fclose(checkElementNumber);

    lineList *listNumberLine;
    f = fopen("DAYSO.IN", "r");
    connetAllNumberList(f, &listNumberLine, aLineElementNumber);
    fclose(f);
    printAllElement(listNumberLine);
    printf("\n");
    insertAllLine(&listNumberLine, (int)roundf(((float)aLineElementNumber) / 2));
    aLineElementNumber += 1;
    printAllElement(listNumberLine);

    fWrite = fopen("RESULT1.OUT", "w");
    writeToFile(listNumberLine, fWrite);
    fclose(fWrite);

    double exper[10];
    solvematrix(listNumberLine, aLineElementNumber, exper);

    freeStruct(&listNumberLine);
    printf("End\n");
}

//====================function=================//
int checkMaxNumberSeries(FILE *f)
{
    int count = 0;
    char c, check = ' ';
    while (fscanf(f, "%c", &c))
    {
        if ((c == 10 || c == ' ') && check != ' ')
        {
            count++;
            check = ' ';
            if (c == 10)
                return count;
        }
        check = c;
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
void printAllElement(lineList *listNumberLine)
{
    lineList *tempLine = listNumberLine;
    while (tempLine != NULL)
    {
        numbersList *tempNum = tempLine->numbersList;
        while (tempNum != NULL)
        {
            printf("%lf ", tempNum->data);
            tempNum = tempNum->next;
        }
        printf("\n");
        tempLine = tempLine->lineListNext;
    }
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
void insertAllLine(lineList **head, int location)
{
    lineList *temp = *head;
    while (temp != NULL)
    {
        float insNumber;
        scanf("%f", &insNumber);
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
            fprintf(f, "%f ", tempSub->data);
            tempSub = tempSub->next;
        }
        fprintf(f, "\n");
        temp = temp->lineListNext;
    }
}
void solvematrix(lineList *listNumberLine, int ElementALineNumber, double exper[])
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
    EnterE(listNumberLine, matrix);
    changematrix(matrix);
    Printmatrix(matrix);
    free(matrix);
    printf("\nEnd");
    double ex[eNumber];
    init(ex, eNumber);
    solve(matrix, ex);
    printf("ex : \n");
    for (int i = 0; i < eNumber; i++)
    {
        printf("%lf ", ex[i]);
    }
}
void Printmatrix(double **matrix)
{
    for (int i = 0; i < eNumber; i++)
    {
        for (int j = 0; j < eNumber + 1; j++)
        {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}
void EnterE(lineList *listNumberLine, double **matrix)
{
    printf("\n");
    lineList *tempLine = listNumberLine;
    numbersList *tempNumberlist = tempLine->numbersList;
    for (int i = 0; i < eNumber; i++)
    {

        for (int j = 0; j < eNumber; j++)
        {

            matrix[i][j] = tempNumberlist->data;
            printf("%0.3lf ", matrix[i][j]);
            tempNumberlist = tempNumberlist->next;
        }

        tempLine = tempLine->lineListNext;
        if (tempLine == NULL)
            break;
        tempNumberlist = tempLine->numbersList;
        printf("B[%d]\n", i + 1);
    }
    printf("\n");
    for (int i = 0; i < eNumber; i++)
    {
        printf("~$ B[%d] = ", i + 1);
        scanf("%lf", &matrix[i][eNumber]);
    }
}
void init(double a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = 0;
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
void changematrix(double **matrix)
{
    double a[eNumber];
    init(a, eNumber);
    for (int j = 0; j < eNumber; j++)
    {
        double findMax = -1;
        int loc = -1;
        for (int i = 0; i < eNumber; i++)
        {
            if (a[i] == 1)
                continue;
            if (fabs(matrix[i][j]) > fabs(findMax))
            {
                findMax = matrix[i][j];
                loc = i;
            }
        }
        int markdow = checkMaxInLine(matrix, loc, j);
        if (a[loc] == 0 && markdow == -1)
        {

            SwapRow(matrix, loc, j);
            a[j] = 1;
        }
        // sap xep theo cot
    }
    for (int i = 0; i < eNumber; i++)
    {
        if (a[i] != 1)
        {
            tranfo(matrix, i, -1);
            a[i] = 1;
            // markdow lưu vị trí có phần tử có độ lơn cao nhất
        }
    }
    printf("head\n");
    Printmatrix(matrix);
    printf("tail\n");

    for (int i = 0; i < eNumber; i++)
    {
        double tempValue = matrix[i][i];
        for (int j = 0; j < eNumber + 1; j++)
        {
            matrix[i][j] /= tempValue * (-1);
        }
        matrix[i][eNumber] *= -1;
    }
    printf("head\n");
    Printmatrix(matrix);
    printf("tail\n");
}

void tranfo(double **matrix, int mDRow, int away)
{
    printf("ooooooooooooooo\n");
    Printmatrix(matrix);
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
void solve(double **matrix, double allX[])
{
    double surplus[eNumber];
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
            printf("# !Error runtime or No solution\n");
            break;
        }
    }
}
