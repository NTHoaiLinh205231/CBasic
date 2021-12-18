#include "/media/sf_CBasic/cgen/ext/io.h"
#include "/media/sf_CBasic/cgen/cgen.ic"

#include<string.h>

/*typedef struct song_s {
	char *name;
	char *path;
} *song_t;*/
typedef struct dll_node_song_s {
  struct dll_node_s base;
  char *name;
  char *path;  
} *dll_node_song_t;


#define to_dll_node_song(n) ((dll_node_song_t)n)
#define dll_node_song_name(n) (to_dll_node_song(n)->name)
#define dll_node_song_path(n) (to_dll_node_song(n)->path)

dll_node_t dll_create_node_song(const char *name, const char *path){
  dll_node_t tmp = dll_create_node();
  dll_node_song_t nn = realloc(tmp, sizeof(struct dll_node_song_s));
  nn->name = strdup(name);
  nn->path = strdup(path);
  return to_dll(nn);
}

void dll_push_back_song(dll_t list, const char *name, const char *path) {
  dll_push_back(list, dll_create_node_song(name, path));
}

void dll_pprint_node_song(dll_node_t node) {
  printf("[%s]", dll_node_song_name(node));
}

void dll_pprint_list_song(dll_t list) {
  int stt = 1;
  dll_traverse(cur, list) {
    printf("%d. ", stt);
    dll_pprint_node_song(cur);
    printf("\n");
    stt++;
  }
}

//Chỉ số từ 1
dll_node_t dll_node_by_id(dll_t list, long id) {
  long len = dll_length(list);
  if (id < 1 || id > len) {
  	return NULL;
  }
  dll_node_t cur = list->front;
  for (int i = 1; i < id; ++i) {
  	cur = cur->next;
  }
  return cur;
}

int main() {
  FILE *inp = fopen("songs.txt", "r");
  char *line = NULL;
  dll_t list = dll_create_list();
  char *name;
  char *path;
  int stt;
  while (cgetline(&line, 0, inp)) {
	if (line[strlen(line)-1] == '\n') {
      line[strlen(line)-1] = '\0';
	}
	for (int i = 0; i < strlen(line); ++i) {
	  if (line[i] == '*' && line[i+1] == '#' && line[i+2] == '*') {
		path = line + i +3;
		line[i] = '\0';
		name = line;
		dll_push_back_song(list, name, path);
		printf("%s\n%s\n", name, path);
	  }
	}
  }
  dll_pprint_list_song(list);
  char c;
  do {
  	printf("Chon bai hat: stt = ");
  	scanf("%d", &stt);
  	if (dll_node_by_id(list, stt)) {
  	  printf("%s\n", dll_node_song_path(dll_node_by_id(list, stt)));
  	} else {
  	  printf("Khong co bai hat da chon\n");
  	}
  	printf("Ban co muon nghe tiep? (Y/n): ");
  	scanf(" %c", &c);
  } while(c != 'n' && c != 'N');
  dll_traverse(cur, list) {
  	dll_node_song_t node = to_dll_node_song(cur);
  	free(node->name);
  	free(node->path);
  }
  dll_free_list(list);
  fclose(inp);
  return 0;
}