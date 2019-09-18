libMemoryManager.a: MemoryManager.o
	ar cr libMemoryManager.a MemoryManager.o
MemoryManager.o: MemoryManager.cpp MemoryManager.h
	g++ -c MemoryManager.cpp

