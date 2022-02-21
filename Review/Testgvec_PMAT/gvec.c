/*
    File lưu tên đăng nhập, mật khẩu, điểm của người dùng 
    mà chưa cho biết số lượng người dùng
*/
#include "all.c"
#include "io.h"
/*Tạo cấu trúc để lưu trữ như lúc làm bằng mảng*/
typedef struct SV_t{
    char *user;
    char *pass;
    int diem;
}*SV;
char *user, *pass, *line = NULL;
int diem;
void freeS(gtype s){
	free (s.s);
} 
int main(){
    /*Tạo một phần tử "sinh viên", ý t là người dùng*/
    SV tmp;
    gvec_t vec = gvec_create(10, freeS);
    FILE *f = fopen("inp.txt", "r");
    while(cgetline(&line,0,f)){
        /*Lấy ra user pass và điểm như hồi làm mảng*/
        user = strtok(line, "\n ");
        pass = strtok(NULL, "\n ");
        diem = atoi(strtok(NULL, "\n "));
        /*************************/


        /*Mỗi lần đọc được 1 dòng từ file cấp phát bộ nhớ*/
        tmp = malloc(sizeof(SV));
        tmp->user = strdup(user);
        tmp->pass = strdup(pass);
        tmp->diem = diem;


        /*
            Đến đây hãy nhớ lại con trỏ void * có thể ép mọi kiểu
            ép SV tmp về void * rồi cho vào vector. Như vậy có thể
            lưu thông tin sinh viên mà không cần đến số lượng 
            sinh viên ban đầu để calloc như là mảng
        */
        gvec_append(vec, gtype_v(tmp));
    }
    /*
        Câu hỏi đặt ra, nếu mình malloc SV tmp ở ngoài vòng lặp thì
        hiện tượng gì xảy ra?
        Test thử để có câu trả lời nhé, câu trả lời tôi nhận được là 
        tất cả user đều chung pass và điểm. Tại vì mỗi lần malloc
        trong vòng lặp nó sẽ tạo ra 1 không gian mới cho SV tmp,
        nên con trỏ void * k trỏ đến cùng 1 địa chỉ
    */
    gvec_traverse(cur, vec){
        /*
            Lưu ý: không làm được cur->v->user, cur->v->pass, cur->v->diem
            do con trỏ void * không tồn tại user, pass, diem
        */
        tmp = cur->v; // ép kiểu
        printf("%s %s %d\n", tmp->user, tmp->pass, tmp->diem);
    }
    fclose(f);
    gvec_free(vec);
    free(line);
    return 0;
}