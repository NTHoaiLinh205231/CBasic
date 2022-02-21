Bien dich bang cmake + ninja trong thu muc doc lap:
mkdir b
cd b
cmake .. -G Ninja
ninja

Hoac dung gcc:
gcc -o prog dethi2020.c ${CGEN_PATH}/all.c -I ${CGEN_PATH}
với CGEN_PATH là đường dẫn tới thư mục cgen