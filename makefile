WordCount: wordcount.o
	g++ -Wall wordcount.o -o WordCount

wordcount.o: wordcount.cpp
	g++ -Wall -c wordcount.cpp