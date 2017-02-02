# Count words.
.PHONY : dats
dats : isles.dat abyss.dat

isles.dat : books/isles.txt wordcount
	./wordcount books/isles.txt > isles.dat

abyss.dat : books/abyss.txt wordcount
	./wordcount books/abyss.txt > abyss.dat

wordcount : wordcount.cpp
	c++ --std=c++11 -o wordcount wordcount.cpp

.PHONY : clean
clean : 
	rm -f *.dat
