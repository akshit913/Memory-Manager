#include <iostream>
#include <functional>
#include <vector>
#include "MemoryManager.h"

using namespace std;
  MemoryManager::MemoryManager(unsigned wordSize, std::function<int(int, void *)> allocator){
    this->wordSize = wordSize;
    this->allocator = allocator;
  }
  MemoryManager::~MemoryManager(){
  shutdown();
  }
  void MemoryManager::initialize(size_t sizeInWords){
    p=new char[sizeInWords];
  }
  void MemoryManager::shutdown(){
    delete p;
  }
  void* MemoryManager::allocate(size_t sizeInBytes){
    uselist=getList();
    int add=allocator(sizeInBytes, uselist);
    if(sizeInBytes<0 || add == -1){
      return nullptr;
    }else{
      int i=add;
      while( p[i+1]!='1' && i < (wordSize-add)){
        p[i]='1';
        i++;
      }
    }
    void* rAdd;
    rAdd=&p[add];
    return rAdd;
   }
  void MemoryManager::free(void *address){
    char *addx = static_cast<char*>(address);
    char* add = addx;
    int index;
    for(int i;i < wordSize;i++){
      if(add==&p[i]){
        index=i;
      }
    }
    int j=0;
    while(*(add+1)!=0 && j<(wordSize-index)){
      *(add+j)=0;
      j++;
    }
  }
  void MemoryManager::setAllocator(std::function<int(int, void *)> allocator){
    this->allocator=allocator;
  }
  int MemoryManager::dumpMemoryMap(char *filename){}
  void* MemoryManager::getList(){
    void *rlist;
    vector<int> list;
    int j,m;
    m=0;
    int flag=0;
    int i=0;
    while(i<wordSize){
      if(p[i]=='0'){
        j=i;
        while(p[j]=='0'){
          flag++;
          j++;
        }
        list.insert(list.begin()+m,i);
        list.insert(list.begin()+m+1,flag);
        i=flag+i;
        m++;
      }else{i++;}
      flag=0;
    }
    rlist=&list;
    return rlist;
  }
  void* MemoryManager::getBitmap(){}
  unsigned MemoryManager::getWordSize(){
    return this->wordSize;
  }
  void * MemoryManager::getMemoryStart(){}
  unsigned MemoryManager::getMemoryLimit(){
    return sizeInWords*wordSize;
  }
  int bestFit(int sizeInWords,void *list){
    uint16_t* ulist=static_cast<uint16_t*>(list);
    uint16_t bestFit = -1;
    uint16_t bestOffset;
    for (uint16_t i = 0; i < 3; i++) {
       if ((ulist[2*i+1] - sizeInWords >= 0) && (ulist[2*i+1] < bestFit)) {
         bestFit = ulist[2*i+1];
         bestOffset = ulist[2*i];
         cout<<ulist[2*i+1]<<endl;
       }
    }
    if(bestFit == -1){
      return -1;
    }else{
      return bestOffset;
    }
  }
  int worstFit(int sizeInWords,void *list){
    uint16_t* ulist = static_cast<uint16_t*>(list);
    uint16_t worstFit = ulist[1];
    uint16_t worstOffset = -1;
    for(uint16_t i=0;i<3;i++){
      if((ulist[2*i+1] >= sizeInWords) && (worstFit <= ulist[2*i+1])){
        worstFit = ulist[2*i+1];
        worstOffset = ulist[2*i];
      }
    }
    if(worstOffset==-1){
      return -1;
    }else{
    return worstOffset;
    }
  }

