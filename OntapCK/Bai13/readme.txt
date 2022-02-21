Dung cmake + ninja:
cd b
cmake .. -G Ninja
ninja

Chay chuong trinh da bien dich de thuc hien cac chuc nang nhu sau:
Chuc nang 1: ./prog f1 mã-nhà-cung-cấp tệp-dữ-liệu-đầu-vào
Chuc nang 2: ./prog f2 mã-hàng tệp-dữ-liệu-đầu-vào
Chuc nang 3: ./prog f3 tệp-dữ-liệu-đầu-vào

Vi du voi tap du lieu dau vao inp1m.txt:
./prog f1 c222222 inp1m.txt
./prog f2 h111111 inp1m.txt
./prog f3 inp1m.txt
Hoac don gian hon, kiem tra bang file test.c de biet thoi gian chay va bo nho:
gcc -o test test_tool.c
./test