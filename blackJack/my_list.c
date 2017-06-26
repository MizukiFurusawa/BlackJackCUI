#pragma once
#include<stdlib.h>
#include <stdio.h>
#include <time.h>
#include "my_list.h"

extern list stack;
const char *mark[4] = { "H", "S", "C", "D" };
const char *value[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };


void show_list(list lst){
  list p;
  p = lst;
  int i = 0;
  while (p != NULL) {
    printf("lst[%d] = ", i);
    show_card_info(p); printf("\n");
    p = p->next;
    i++;
  }
  return;
}


void show_card(list lst) {
  list p;
  p = lst;
  int i = 0;
  while (p != NULL) {
    printf(" "); show_card_info(p); printf(" ");
    p = p->next;
    i++;
    if (i % 13 == 0)printf("\n");
  }
  return;
}


list cons(card_t v, list lst) {
  list nlst;
  nlst = (list)malloc(sizeof(node_t));
  nlst->card = v;
  nlst->next = lst;
  return nlst;
}


int isEmpty(list lst) {
  return (lst == NULL);
}


list emptyList(void) {
  return NULL;
}


list get_list(list lst, int n){
  return __get_list(lst, n, 0);
}


list __get_list(list lst, int n, int k){
  if (isEmpty(lst))return NULL;
  if (n != k){
    k++;
    return __get_list(lst->next, n, k);
  }
  else{
    return lst;
  }
}


void show_card_info(list lst){
  if (isEmpty(lst))return;
  printf("[ %s ] %-2s", mark[lst->card.pic], value[lst->card.val]);
}


int get_list_size(list lst){
  return __get_list_size(lst, 0);
}


int __get_list_size(list lst, int n){
  if (isEmpty(lst))return n;
  n++;
  return __get_list_size(lst->next, n);
}


void  set_card(list lst, card_t v, int n){
  __set_card(lst, v, n, 0);
}


void  __set_card(list lst, card_t v, int n, int k){
  if (isEmpty(lst))return;
  if (n != k){
    k++;
    __set_card(lst->next, v, n, k);
  }
  else{
    lst->card = v;
    return;
  }
}


list init_card(void){
  int i, j;
  list ret = emptyList();
  card_t tmp;
  for (i = 0; i < 4; i++){
    for (j = 0; j < 13; j++){
      tmp.pic = i;
      tmp.val = j;
      ret = cons(tmp, ret);
    }
  }
  return ret;
}


void shuffle_list(list lst){
  int i, j, size;
  card_t tmp;
  srand((unsigned)time(NULL));
  size = get_list_size(lst);
  for (int i = 0; i < size; i++){
    j = rand() % size;
    tmp = get_card(get_list(lst, i));
    set_card(lst, get_card(get_list(lst, j)), i);
    set_card(lst, tmp, j);
  }
}


card_t  get_card(list lst){
  return lst->card;
}


list exceptHeadList(list lst){
  list ret = emptyList();
  if (isEmpty(lst))return NULL;
  if (isEmpty(lst->next)){
    free(lst);
    lst = NULL;
    return emptyList();
  }
  ret = lst->next;
  free(lst);
  lst = NULL;
  return ret;
}


list deleteList(list lst){
  while (get_list_size(lst) > 0){
    lst = exceptHeadList(lst);
  }
  return lst;
}


list transferList(list lst){
  list ret = lst;
  ret = cons(get_card(stack),ret);
  stack = exceptHeadList(stack);
  return ret;
}
