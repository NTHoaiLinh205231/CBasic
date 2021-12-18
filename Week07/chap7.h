#ifndef CHAP7_H_
#define CHAP7_H_

#include "bns.h"

/*
  t - la con tro toi doi tuong bns_tree_g va cac nut 
      la nhung con tro toi cac doi tuong bns_node_g.
  Tra ve: 1 - neu dung la cay nhi phan tim kiem
  		  0 - neu nguoc lai (khong phai bns)
*/
int bn_is_bns(bn_tree_t t);

/*
  lac = lowest common ancestor/nut tren gan nhat
     n1
  n2      n3
       n5    n6
  bn_lac(n5, n6) => n3
  bn_lac(n2, n6) => n1
  bn_lac(n1, n2) => NULL
  Tra ve:
    lca cua n1 va n2 neu co hoac tra ve NULL trong truong hop nguoc lai
*/
bn_node_t bn_lca(bn_node_t n1, bn_node_t n2);

/*
  a va n la con tro ca so luong phan tu cua mang.
  Cac phan tu trong mang da duoc sap xep theo thu tu tang dan.
  Tra ve: 
    Con tro kieu bn_tree_t va tro toi doi tuong bns_tree_g voi cac nut co kieu bns_node_g_t.
    Trong truong hop co loi thi tra ve NULL.
*/
bn_tree_t bns_parse_arri(int *a, size_t n);

/*
			n1
		 n2    n3
	  n4    n5
	  x(n1) = 0
	  x(n5) = 0
	  x(n2) = -1
	  x(n3) = 1

  Tra ve:
    Khoang cach theo truc x
*/
long bn_xdist(bn_tree_t t, bn_node_t n);

bns_node_g_t

#endif // CHAP7_H_