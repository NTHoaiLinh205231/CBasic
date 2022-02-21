#include "all.c"
#include "ext/io.h"
#include <ctype.h>
char *strlwr(char* s){
    char* tmp = s;
    for (;*tmp;++tmp){
        *tmp = tolower((unsigned char) *tmp);
    }
    return s;
}
typedef char string[26];
string anh, viet;
int choice = -1;
char c;
char *line = NULL, *word;
void menu(){
    printf("CHUONG TRINH BKTRANSLATE\n");
    printf("1. Nap tu dien\n");
    printf("2. Noi dung tu dien\n");
    printf("3. Them/sua tu\n");
    printf("4. Dich cau anh viet\n");
    printf("5. Thoat\n");
}
void f1(rbm_t tree, char *s){
    FILE *f = fopen(s, "r");
    while(!feof(f)){
        fscanf(f, "%s %s", anh, viet);
        rbm_insert(tree, gtype_s(strdup(anh)), gtype_s(strdup(viet)));
        printf("%s %s\n", anh, viet);
    }
    fclose(f);
}
void f2(rbm_t tree){
    rbm_traverse(k, v, tree){
        printf("%s: %s\n", k->s, v->s);
    }
}
void f3(rbm_t tree){
    printf("Nhap vao mot tu tieng anh: ");
    scanf("%s", anh);
    clear_stdin();
    if(rbm_value(tree, gtype_s(anh))){
        printf("Ban co muon nhap noi dung moi khong: ");
        scanf("%c", &c);
        clear_stdin();
        if(c == 'y'){
            printf("Nhap noi dung moi: ");
            scanf("%s", viet);
            free(rbm_value(tree, gtype_s(anh))->s);
            rbm_value(tree, gtype_s(anh))->s = strdup(viet);
        }
    }
    else{
        printf("Nhap nghia tieng viet: ");
        scanf("%s", viet);
        rbm_insert(tree, gtype_s(strdup(anh)), gtype_s(strdup(viet)));
        printf("Da them %s: %s vao tu dien\n", anh, viet);
    }
}
void f4(rbm_t tree){
    int count = 1;
    printf("Nhap tu tieng anh: ");
    cgetline(&line, 0, stdin);
    remove_tail_lf(line);
    line = strlwr(line);
    char *tmp = strdup(line);
    word = strtok(tmp, " \n");
    while(word != NULL){
        printf("%s\n", word);
        word = strtok(NULL, " \n");
    }
    free(tmp);
    c = 'y';
    while(c == 'y' && count != 0){
        count = 0;
        char *tmp = strdup(line);
        word = strtok(tmp, " \n");
        while(word != NULL){
            if(rbm_value(tree, gtype_s(word))){
                printf("%s ", rbm_value(tree, gtype_s(word))->s);
            }
            else{
                printf("<thieu tu>");
                count ++;
            }
            word = strtok(NULL, " \n");
        }
        printf("\n");
        if(count > 0){
            printf("Ban co muon cap nhat tu dien? y/n: ");
            scanf("%c",&c);
            clear_stdin();
            if(c == 'y') f3(tree);
            else{
                free(tmp);
                break;
            }
        }
        free(tmp);
    }
}
int main(int argc, char *argv[]){
    rbm_t tree = rbm_create(gtype_cmp_s, gtype_free_s, gtype_free_s);
    while(choice != 5){
        menu();
        printf("Nhap vao lua chon cua ban: ");
        scanf("%d", &choice);
        clear_stdin();
        if(choice == 1){
            f1(tree, argv[1]);
        }
        else if(choice == 2){
            f2(tree);
        }
        else if(choice == 3){
            f3(tree);
        }
        else if(choice == 4){
            f4(tree);
        }
    }
    rbm_free(tree);
    free(line);
    free(word);
    return 0;
}