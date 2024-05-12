#include "list_lock.h"

#include <stdio.h>
#include <stdlib.h>
//初始化 list_lock_t 结构。
void listInit(list_lock_t* list) {
  list->head = NULL;
  pthread_mutex_init(&list->mutex, NULL);
  pthread_cond_init(&list->cond, NULL);
}
//将生成的数据 value 放入 list 链表中，你可能需要为此分配一个堆区资源。
void producer(list_lock_t* list, DataType value) {
  pthread_mutex_lock(&list->mutex);
  LinkList new = (LinkList)malloc(sizeof(LNode));
  new->value = value;
  new->next = list->head;
  list->head = new;
  pthread_cond_signal(&list->cond);
  pthread_mutex_unlock(&list->mutex);
}
//从 list 链表中消耗一个数据，并释放其占有的资源。
void consumer(list_lock_t* list) {
  pthread_mutex_lock(&list->mutex);
  if (list->head == NULL) {
    pthread_cond_wait(&list->cond, &list->mutex);
  }
  LinkList cur = list->head;
  list->head = cur->next;
  free(cur);
  pthread_mutex_unlock(&list->mutex);
}
//获取当前 list 中的资源个数，并返回该个数。
int getListSize(list_lock_t* list) {
  pthread_mutex_lock(&list->mutex);
  int cnt = 0;
  LinkList cur = list->head;
  while (cur) {
    cur = cur->next;
    cnt++;
  }
  pthread_mutex_unlock(&list->mutex);
  return cnt;
}
