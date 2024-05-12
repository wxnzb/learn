#include "hash_lock.h"

#include <stdio.h>
#include <stdlib.h>

void hashInit(hash_lock_t* bucket) {
  for (int i = 0; i < HASHNUM; i++) {
    pthread_mutex_init(&bucket->table[i].mutex, NULL);
    bucket->table[i].head = NULL;
  }
}
//通过 key 值来获取对应的 value。
int getValue(hash_lock_t* bucket, int key) {
  int hash = HASH(key);
  pthread_mutex_lock(&bucket->table[hash].mutex);
  Hlist cur = bucket->table[hash].head;
  while (cur != NULL) {
    if (cur->key == key) {
      int value = cur->value;
      pthread_mutex_unlock(&bucket->table[hash].mutex);
      return value;
    } else {
      cur = cur->next;
    }
  }
  pthread_mutex_unlock(&bucket->table[hash].mutex);
  return -1;
}
// 向哈希桶中添加一个节点，通过 key 来索引对应的哈希序列，如果键已经存在，则覆盖现有值。
void insert(hash_lock_t* bucket, int key, int value) {
  int hash = HASH(key);
  pthread_mutex_lock(&bucket->table[hash].mutex);
  Hlist cur = bucket->table[hash].head;
  while (cur != NULL) {
    if (cur->key == key) {
      cur->value = value;
      pthread_mutex_unlock(&bucket->table[hash].mutex);
      return;
    } else {
      cur = cur->next;
    }
  }
  Hlist insert = (Hlist)malloc(sizeof(Hnode));
  insert->value = value;
  insert->key = key;
  insert->next = NULL;
  // cur=insert;
  insert->next = bucket->table[hash].head;
  bucket->table[hash].head = insert;
  pthread_mutex_unlock(&bucket->table[hash].mutex);
}
//重新设置一个节点的key,并将其移动到对应的序列，如果键不存在，则返回-1,成功返回0。
int setKey(hash_lock_t* bucket, int key, int new_key) {
  int hash_old = HASH(key);
  int hash_new = HASH(new_key);
  pthread_mutex_lock(&bucket->table[hash_old].mutex);
  Hlist cur = bucket->table[hash_old].head;
  Hlist pre = NULL;
  while (cur != NULL) {
    if (cur->key == key) {
      if (pre == NULL) {
        bucket->table[hash_old].head = cur->next;
      } else {
        pre->next = cur->next;
      }
      cur->key = new_key;
      pthread_mutex_unlock(&bucket->table[hash_old].mutex);//注意，容易出错！
      pthread_mutex_lock(&bucket->table[hash_new].mutex);
      cur->next = bucket->table[hash_new].head;
      bucket->table[hash_new].head = cur;
      pthread_mutex_unlock(&bucket->table[hash_new].mutex);
      return 0;
    } else {
      pre = cur;
      cur = cur->next;
    }
  }
  pthread_mutex_unlock(&bucket->table[hash_old].mutex);
  return -1;
}
