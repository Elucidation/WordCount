CFLAGS = -std=c++0x -Wall
WordCount: wordcount.o parser.o sorter.o hashmap.o
	g++ $(CFLAGS) wordcount.o parser.o sorter.o hashmap.o -o WordCount

wordcount.o: wordcount.cpp parser.h sorter.h
	g++ $(CFLAGS) -c wordcount.cpp

parser.o: parser.cpp
	g++ $(CFLAGS) -c parser.cpp

sorter.o: sorter.cpp
	g++ $(CFLAGS) -c sorter.cpp

hashmap.o: hashmap.cpp
	g++ $(CFLAGS) -c hashmap.cpp

clean:
	rm -rf *.o WordCount WordCount.exe