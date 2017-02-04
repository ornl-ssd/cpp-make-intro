# Generate summary table.
results.txt : isles.dat abyss.dat last.dat
	python zipf_test.py abyss.dat isles.dat last.dat > results.txt

# Count words.
.PHONY : dats
dats : isles.dat abyss.dat last.dat

isles.dat : books/isles.txt
	./wordcount books/isles.txt > isles.dat

abyss.dat : books/abyss.txt
	./wordcount books/abyss.txt > abyss.dat

last.dat : books/last.txt
	./wordcount books/last.txt > last.dat

wordcount : wordcount.cpp main.cpp
	c++ --std=c++11 -o wordcount wordcount.cpp main.cpp

.PHONY : clean
clean :
	rm -f *.dat
	rm -f results.txt
