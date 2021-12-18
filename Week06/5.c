#include<stdio.h>
#include "../cgen/cgen.ic"
#include<string.h>

int bns_is_key_exist(bn_tree_t tree, char *val) {
    bn_traverse_lnr(cur, tree) {
        if (!strcmp(bns_node_g_key(cur).s, val)) return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (!argv[1]) {
        printf("Input file not sepcified!\n");
        return 1;
    }
    FILE *f = fopen(argv[1] , "r");
    if (f == NULL) {
        printf("Input file not found!\n");
        return 2;
    }

    int i = 0;
    char buff[1000][20];
    while(feof(f) == 0) {
        fscanf(f, "%s", buff[i]);
        i++;
    }
    bn_tree_t list = bns_create_tree_g(NULL, gtype_cmp_s);
    for (int j = 0; j < i; j++) {
        if (!bns_is_key_exist(list, buff[j])) bns_insert_g(list, gtype_s(buff[j]));
    }
    printf("Số lượng từ duy nhất: i = %d %ld\n", i, bn_size(list));
    printf("Các từ duy nhất: ");
    bn_traverse_lnr(cur, list) {
        printf("%s ", bns_node_g_key(cur).s);
    }
    printf("\n");
    bn_free_tree(&list);
    fclose(f);
    return 0;
}