WordCount: wordcount.o parser.o
	g++ -Wall wordcount.o parser.o -o WordCount

wordcount.o: wordcount.cpp parser.h
	g++ -Wall -c wordcount.cpp

parser.o: parser.cpp
	g++ -Wall -c parser.cpp

clean:
	rm -rf *.o WordCount WordCount.exe