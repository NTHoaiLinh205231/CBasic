#include "all.c"
#include <time.h>
#define to_string(x) (*(const char **)x) // từ con trỏ void*, chuyển thành string
#define to_node(x) (*(const node *)x) // từ con trỏ void*, chuyển thành dạng node
typedef struct node{
    char *w;
    int a;
}node;
int compare_s(const void *a, const void *b){ // so sánh string
    return strcmp(to_string(a), to_string(b));
}
int compare_n(const void *a, const void *b){ // so sánh số lần xuất hiện, theo thứ tự giảm dần
    return to_node(b).a - to_node(a).a;
}
int main(){
    clock_t start = clock();
    FILE *f = fopen("/media/pmat/Data/School/Cbasic/c-basic/text/lisa_all_text.txt", "r"); // NHỚ ĐỔI ĐƯỜNG DẪN
    sll_t list = sll_create_list();
    char buff[1024];
    int n_word = 0;
    /*Nhập dữ liệu vào, cho vào danh sách liên kết để tìm số lượng từ, cho ngược lại vào mảng để sort*/ 
    while(!feof(f)){
        fscanf(f, "%s", buff);
        sll_push_back_g(list,(gtype){.s = strdup(buff)});
        n_word++;
    }
    char **words = calloc(n_word, sizeof(char*));
    int idx = 0;
    for(sll_node_t cur = list->front; cur!=NULL; cur=cur->next){
        words[idx++] = sll_node_g_value(cur).s;
    }
    qsort(words, n_word, sizeof(char*),compare_s);
    /*-------------------------------------------*/


    /*Lưu phần tử khác nhau vào node, số lần lặp được lưu lại vào node.a, text được lưu vào node.w,
    xong sort lại node theo node.a để có thứ tự xuất hiện từ bé đến lớn*/
    node *result = calloc(n_word, sizeof(node));
    int count = 1;
    idx = 0;
    for(int i=1; i<n_word; i++){
        if(!strcmp(words[i],words[i-1])){ // nếu phần tử đang duyệt giống phần tử trước đó thì biến đếm +1
            count ++;
        }
        else{
            result[idx].w = words[i-1]; // lưu lại kí tự 
            result[idx].a = count; // lưu lại số lần xuất hiện
            idx++;
            count = 1; // reset count
        }
    }
    qsort(result, idx, sizeof(node), compare_n); // sắp xếp theo số lượng xuất hiện
    printf("So luong tu khac nhau: %d\n",idx+1);
    for(int i=0; i<10; i++){
        printf("%s - %d lan\n",result[i].w, result[i].a);
    }
    /*-------------------------------------------*/
    free(result);
    free(words);
    fclose(f);
    clock_t end = clock();
    double time_process = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Thoi gian xu ly: %lf\n",time_process);
    return 0;
}
