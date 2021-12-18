#include "/media/sf_CBasic/cgen/OOP/Sll.c"

int main() {
  SllGt list = New(SllGt);
  list->PushBack(list, (gtype){.i = 100});
  list->PushBack(list, (gtype){.i = 200});
  list->PushBack(list, (gtype){.i = 300});
  list->PushFront(list, (gtype){.i = 60});
  //list->PPrint(list);
  SllPPrint((Sll) list);
  return 0;
}
//gcc -o prog -I /home/bangoc/git/cgen vidu5-1-OOP-sll-g.c /homebangoc/git/cgen/OOP/Sll.c