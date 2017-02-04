# Count words.
.PHONY : dats
dats : isles.dat abyss.dat

isles.dat : books/isles.txt
	./wordcount books/isles.txt > isles.dat

abyss.dat : books/abyss.txt
	./wordcount books/abyss.txt > abyss.dat

wordcount : wordcount.cpp main.cpp
	c++ --std=c++11 -o wordcount wordcount.cpp main.cpp

.PHONY : clean
clean : 
	rm -f *.dat
