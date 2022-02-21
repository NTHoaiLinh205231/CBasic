Dung cmake + ninja:
cd b
cmake .. -G Ninja
ninja
./prog inp20k.txt

Hoac dung gcc:
gcc -o prog bai11.c ${CGEN_PATH}/all.c -I ${CGEN_PATH}
	với CGEN_PATH là đường dẫn tới thư mục cgen
./prog inp20k.txt
