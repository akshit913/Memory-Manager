#include<iostream>
#include<functional>

class MemoryManager{

private:
  char *p;
  size_t sizeInWords;
  void* rlist;
  void* uselist;
  unsigned wordSize;
  std::function<int(int, void*)> allocator;
public:
  MemoryManager(unsigned wordSize, std::function<int(int, void *)> allocator);
  ~MemoryManager();
  void initialize(size_t sizeInWords);
  void shutdown();
  void *allocate(size_t sizeInBytes);
  void free(void *address);
  void setAllocator(std::function<int(int, void *)> allocator);
  int dumpMemoryMap(char *filename);
  void *getList();
  void *getBitmap();
  unsigned getWordSize();
  void *getMemoryStart();
  unsigned getMemoryLimit();
};
int bestFit(int sizeInWords, void *list);
int worstFit(int sizeInWords, void *list);

