#include <stdio.h>

int main()
{
    // Sử dụng ANSI escape sequence để in chữ màu đỏ trên nền đen\033[1;31m
    printf("\033[1;31m");
    printf("hello anh em chào anh em rất nhều");

    return 0;
}

/*
\033[1;31m được sử dụng để bắt đầu in chữ màu đỏ.
\033[0m được sử dụng để kết thúc việc in chữ màu và đưa màu về lại mặc định.
\033[1;31;40m được sử dụng để đặt màu chữ là đỏ (1;31) và màu nền là đen (40).
\033[0m được sử dụng để kết thúc việc in màu và đưa màu về lại mặc định.
\033[2J là mã ANSI escape để xóa màn hình.
\033[1;1H là mã ANSI escape để đặt con trỏ văn bản về vị trí (1, 1) trên màn hình (góc trên bên trái). Điều này đảm bảo rằng sau khi xóa màn hình, con trỏ văn bản sẽ được đặt lại ở đầu trang.
*/