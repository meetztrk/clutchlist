/*
 *   author  mert ozturk <mrtztrk1@gmail.com> 07.09.2017
 */

#include<stdlib.h> //malloc//
#include<string.h> //strcmp//
#include"clutchlist.h"

clutchList* newList(){
  return (clutchList*) malloc(sizeof(clutchList));
}

ItemAdapter* getItemAdapter(clutchList* list, int index){
  list->current = list->head;
  for(int i=0; i<index; i++){
    list->current = list->current->next;
  }
  return list->current;
}

void* getItem(clutchList* list, int index){
  return getItemAdapter(list, index)->item;
}

void insertItem(clutchList* list, int index, void* item){
  ItemAdapter* temp = (ItemAdapter*) malloc(sizeof(ItemAdapter));
  temp->next = getItemAdapter(list, index);
  if(index<1) list->head = temp;
  else getItemAdapter(list, index-1)->next = temp;
  list->size++;
  temp->item = item;
}

void addItem(clutchList* list, void* item){
  insertItem(list, list->size, item);
}

void delItem(clutchList* list, int index){
  if(index < 1) list->head = getItemAdapter(list, index+1);
  else getItemAdapter(list, index-1)->next = getItemAdapter(list, index+1);
  list->size--;
}

void swapItem(clutchList* list, int index1, int index2){
  ItemAdapter* o1 = getItemAdapter(list, index1);
  ItemAdapter* o2 = getItemAdapter(list, index2);
  void* temp = o1->item;
  o1->item = o2->item;
  o2->item = temp;
}

int integerComparer(void* o1, void* o2){
  return (*((int*)o1) > *((int*)o2)) - (*((int*)o1) < *((int*)o2));
}

int doubleComparer(void* o1, void* o2){
  return (*((double*)o1) > *((double*)o2)) - (*((double*)o1) < *((double*)o2));
}

int stringComparer(void* o1, void* o2){
  return strcmp(*((char**)o1), *((char**)o2));
}

void listBubbleSort(clutchList* list, size_t itemOffset, int(*itemComparer)(void*, void*)){
  int min;
  for(int i=0; i<list->size-1; i++){
    min = i;
    for(int j=i+1; j<list->size; j++){
      if((*itemComparer)(setOffsetPtr(getItem(list, min), itemOffset), setOffsetPtr(getItem(list, j), itemOffset)) > 0) min = j;
    }
    if(i != min) swapItem(list, i, min);
  }
}

void* queryItem(clutchList* list, size_t offset, void* equals, int(*itemComparer)(void*, void*)){
  list->current = list->head;
  for(int i=0; i<list->size; i++){
    if((*itemComparer)(setOffsetPtr(list->current->item, offset), equals) == 0) return list->current->item;
    list->current = list->current->next;
  }
  return NULL;
}

void reverseList(clutchList* list){
  int count = list->size >> 1;
  while(count > 0){
    swapItem(list, count-1, list->size - count);
    count--;
  }
}

clutchList* getHoldOfList(void* listhead, size_t nextOffset){
  clutchList* temp = (clutchList*) malloc(sizeof(clutchList));
  while(1){
    addItem(temp, listhead);
    listhead = *(void**)setOffsetPtr(listhead, nextOffset);
    if(listhead == NULL) return temp;
  }
}

clutchList* cloneClutchList(clutchList* list){
  clutchList* temp = newList();
  list->current = list->head;
  for(int i=0; i<list->size; i++){
    addItem(temp, list->current->item);
    list->current = list->current->next;
  }
  return temp;
}

void* applyClutch(clutchList* list, size_t nextOffset){
  list->current = list->head;
  for(int i=0; i<list->size-1; i++){
    *(void**)setOffsetPtr(list->current->item, nextOffset) = list->current->next->item;
    list->current = list->current->next;
  }
  *(void**)setOffsetPtr(list->current->item, nextOffset) = NULL;
  return list->head->item;
}

//  ******Under Construction******  //

void makeCircular(clutchList* list){
  list->current = list->head;
  if(list->current == NULL){  //  *** at least one item required ***  //
    return;
  }
  for(int i=0; i<list->size-1; i++){
    list->current = list->current->next;
  }
  list->current->next = list->head;
}

void makeLinear(clutchList* list){
  list->current = list->head;
  for(int i=0; i<list->size-1; i++){
    list->current = list->current->next;
  }
  list->current->next = NULL;
}

clutchList* queryList(clutchList* list, size_t offset, void* equals, int(*itemComparer)(void*, void*)){
  clutchList* temp = (clutchList*) malloc(sizeof(clutchList));
  list->current = list->head;
  for(int i=0; i<list->size; i++){
    if((*itemComparer)(setOffsetPtr(list->current->item, offset), equals) == 0) addItem(temp, list->current->item);
    list->current = list->current->next;
  }
  return temp;
}

clutchList* queryBetween(clutchList* list, size_t offset, void* upper, void* lower, int(*itemComparer)(void*, void*)){
  clutchList* temp = (clutchList*) malloc(sizeof(clutchList));
  list->current = list->head;
  for(int i=0; i<list->size; i++){
    if((*itemComparer)(setOffsetPtr(list->current->item, offset), upper) >= 0){
      if((*itemComparer)(setOffsetPtr(list->current->item, offset), lower) <= 0) addItem(temp, list->current->item);
    }
    list->current = list->current->next;
  }
  return temp;
}
