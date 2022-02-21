#include "hmap.h"
#include "ext/io.h"
#include <stdio.h>

int main() {
  hmap_t map = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
  hmap_insert(map, gtype_s("aaa"), gtype_l(100));
  hmap_insert(map, gtype_s("bbb"), gtype_l(200));
  hmap_insert(map, gtype_s("ccc"), gtype_l(300));
  hmap_insert(map, gtype_s("ddd"), gtype_l(400));
  hmap_insert(map, gtype_s("eee"), gtype_l(500));
  hmap_insert(map, gtype_s("fff"), gtype_l(600));

  printf("hmap_size: %d\n", hmap_size(map));
  printf("hmap_key_at(map, 0): %s\n", hmap_key_at(map, 0)->s);
  printf("hmap_value_at(map, 2): %ld\n", hmap_value_at(map, 2)->l);

  printf("Nhap key can tra cuu: ");
  char s[100];
  fscanf(stdin, "%s", s);
  gtype *value;
  if (value = hmap_value(map, gtype_s(s))) {
    printf("Value of %s = %ld\n", s, value->l);
  } else {
    printf("Surprised\n");
  }

  printf("hmap_traverse:\n");  
  hmap_traverse(key, value, map) {
    printf("%s:%ld\n", key->s, value->l);
  }  

  gtype *nextv = hmap_next_pvalue(map, value);
  printf("hmap_next_pvalue(map, %ld): %ld\n", value->l, nextv->l);

  /*gtype *key;
  key->s = s;
  gtype *nextk = hmap_next_pkey(map, value);
  printf("hmap_next_pkey(map, %s): %s\n", key->s, nextk->s);
  /*gtype *hmap_next_pkey(hmap_t, gtype*);*/

  hmap_remove(map, gtype_s(s));
  printf("hmap_traverse after remove %s:\n", s);  
  hmap_traverse(key, value, map) {
    printf("%s:%ld\n", key->s, value->l);
  }
  printf("hmap_size: %d\n", hmap_size(map));
  hmap_free(map);
  return 0;
}