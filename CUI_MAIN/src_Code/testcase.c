#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define ROWS 8
#define COLS 9

int main()
{
    double matrix[ROWS][COLS];

    // Khởi tạo random seed dựa trên thời gian hiện tại
    srand(time(0));

    // Điền ma trận với các số ngẫu nhiên từ -50 đến 50
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            matrix[i][j] = ((double)(rand() % 101) - 50); // Giá trị ngẫu nhiên từ -50 đến 50
            if (i == j && i <= ROWS)
                matrix[i][j] += ((double)(rand() % 101) - 50) * 2;
            else if (i + 1 == j && i > ROWS)
                matrix[i][j] += fabs(((double)(rand() % 101) - 50)) * 2;
        }
    }

    // In ra ma trận
    printf("Ma tran ngau nhien 8x9:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%0.3g ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
