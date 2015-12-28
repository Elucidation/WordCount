CFLAGS = -std=c++0x -Wall
wordcount: wordcount.o parser.o sorter.o hashmap.o
	g++ $(CFLAGS) wordcount.o parser.o sorter.o hashmap.o -o wordcount

wordcount.o: wordcount.cpp parser.h sorter.h
	g++ $(CFLAGS) -c wordcount.cpp

parser.o: parser.cpp
	g++ $(CFLAGS) -c parser.cpp

sorter.o: sorter.cpp
	g++ $(CFLAGS) -c sorter.cpp

hashmap.o: hashmap.cpp
	g++ $(CFLAGS) -c hashmap.cpp

testEmpty:
	./wordcount test/inputs/test_empty.txt > /tmp/wordcounttmpresult 2> /dev/null
	diff /tmp/wordcounttmpresult test/correct/test_empty_result.txt

testBasic:
	./wordcount test/inputs/test_basic.txt > /tmp/wordcounttmpresult 2> /dev/null
	diff /tmp/wordcounttmpresult test/correct/test_basic_result.txt

testSimpleDuplicates:
	./wordcount test/inputs/test_simple_duplicates.txt > /tmp/wordcounttmpresult 2> /dev/null
	diff /tmp/wordcounttmpresult test/correct/test_simple_duplicates_result.txt

testLorem:
	./wordcount test/inputs/test_lorem.txt > /tmp/wordcounttmpresult 2> /dev/null
	diff /tmp/wordcounttmpresult test/correct/test_lorem_result.txt


test: testEmpty testBasic testSimpleDuplicates testLorem

clean:
	rm -rf *.o wordcount wordcount.exe