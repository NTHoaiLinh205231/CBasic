Dung cmake + ninja:
cd b
cmake .. -G Ninja
ninja
./prog dict.txt

Hoac dung gcc:
gcc -o prog dethi2019.c ${CGEN_PATH}/all.c -I ${CGEN_PATH}
với CGEN_PATH là đường dẫn tới thư mục cgen
./prog dict.txt