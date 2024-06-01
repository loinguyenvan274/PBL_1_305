# README

## Mô tả chương trình

Chương trình được viết bằng ngôn ngữ C thực hiện các công việc sau:

1. Đọc vào N danh sách liên kết từ file `*.IN`.
2. Thêm một phần tử vào vị trí giữa của mỗi danh sách liên kết và lưu kết quả ra file `*.OUT`.
3. Giải hệ phương trình tuyến tính 𝐴𝑋 = 𝐵 bằng phương pháp giảm dư và lưu kết quả ra file `*.OUT`.

## Các bước thực hiện

### Bước 1: Đọc dữ liệu từ file `**.IN`

- File `*.IN` gồm N hàng (N ≥ 5), mỗi hàng gồm M phần tử số (M = N-1).
- Mỗi hàng này tương ứng với một danh sách liên kết.

### Bước 2: Thêm phần tử vào danh sách liên kết

- Thêm một phần tử vào vị trí giữa (M/2, làm tròn nếu M lẻ) của mỗi danh sách liên kết.
- Hiển thị kết quả và lưu vào file `*.OUT`.

### Bước 3: Giải hệ phương trình tuyến tính

- Sau khi thực hiện bước 2, ta có N danh sách liên kết, mỗi danh sách chứa N phần tử.
- Các phần tử này được biểu diễn theo ma trận:
  ```
  A = [a11 a12 ... a1N
       a21 a22 ... a2N
       ...
       aN1 aN2 ... aNN]
  ```
- Giải hệ phương trình 𝐴𝑋 = 𝐵 bằng phương pháp giảm dư với 𝐵 = [b1, b2, ..., bN] (𝐵 là mảng một chiều được nhập vào).
- Hiển thị kết quả và lưu vào file `**.OUT`.

## Yêu cầu

- Sử dụng danh sách liên kết đơn để thực hiện các công việc trên.
- Dữ liệu đầu vào: file `**.IN`.

## Hướng dẫn cài đặt và chạy chương trình

### Yêu cầu

- Trình biên dịch C (gcc, clang, ...)
- Trình quản lý make (đã cài đặt MinGW nếu dùng Windows hoặc `sudo apt install make` nếu dùng Linux)

### Các bước cài đặt và chạy chương trình

1. Biên dịch chương trình với lệnh:
   ```
   gcc -o index ./src_Code/index.c
   ```

2. Chạy chương trình:
   ```
   ./index
   ```

### Sử dụng Makefile

Chương trình đã được cấu hình sẵn với Makefile. Để biên dịch và chạy chương trình, bạn có thể sử dụng các lệnh sau:

1. Biên dịch chương trình với Makefile:
   ```
   make
   ```

2. Chạy chương trình:
   ```
   make run
   ```

## Cấu trúc thư mục

- `src_Code/` - Chứa mã nguồn của chương trình.
- `*.IN` - File đầu vào chứa danh sách liên kết.
- `**.OUT` - File kết quả sau khi thêm phần tử vào danh sách liên kết.
- `**.OUT` - File kết quả sau khi giải hệ phương trình.

## 🚀 About We

- Chúng mình là sinh viên của trường Bách Khoa. 
- yêu khoa học và thích thế giới công nghệ.
  
## Liên hệ

Nếu bạn có bất kỳ câu hỏi hoặc góp ý nào, vui lòng liên hệ qua email: [loinguyenvan274@gmail.com].

- [![Facebook Lợi Nguyễn]](https://www.facebook.com/duyen.mi.33483)
- [![Facebook Trần Đức]](https://www.facebook.com/profile.php?id=100023136875087)
                                                                

