Dung cmake + ninja:
cd b
cmake .. -G Ninja
ninja
./prog A.txt B.txt

Hoac dung gcc:
gcc -o prog dethi2015.c ${CGEN_PATH}/all.c -I ${CGEN_PATH}
với CGEN_PATH là đường dẫn tới thư mục cgen