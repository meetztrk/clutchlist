#ifndef clutchlist
#define clutchlist

#define getOffset(STRUCT, MEMBER) ((size_t) &((STRUCT *)0)->MEMBER)
#define setOffsetPtr(start, offset) ((void*) ((char*)start + offset))

typedef struct ItemAdapter{
  struct ItemAdapter* next;
  void* item;
}ItemAdapter;

typedef struct{
  ItemAdapter* head;
  ItemAdapter* current;
  size_t size;
}clutchList;

clutchList* newList();
ItemAdapter* getItemAdapter(clutchList*, int);
void* getItem(clutchList*, int);
void insertItem(clutchList*, int, void*);
void addItem(clutchList*, void*);
void delItem(clutchList*, int);
void swapItem(clutchList*, int, int);
int integerComparer(void*, void*);
int doubleComparer(void*, void*);
int stringComparer(void*, void*);
void listBubbleSort(clutchList*, size_t, int(*itemComparer)(void*, void*));
void* queryItem(clutchList*, size_t, void*, int(*itemComparer)(void*, void*));
void reverseList(clutchList*);
clutchList* getHoldOfList(void*, size_t);
clutchList* cloneClutchList(clutchList*);
void* applyClutch(clutchList*, size_t);
void makeCircular(clutchList*);
void makeLinear(clutchList*);
clutchList* queryList(clutchList*, size_t, void*, int(*itemComparer)(void*, void*));
clutchList* queryBetween(clutchList*, size_t, void*, void*, int(*itemComparer)(void*, void*));

#endif
