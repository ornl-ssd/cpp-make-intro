# Generate summary table.
results.txt : *.dat
	python zipf_test.py $^ > $@

# Count words.
.PHONY : dats
dats : isles.dat abyss.dat last.dat

isles.dat : books/isles.txt
	./wordcount $< > $@

abyss.dat : books/abyss.txt
	./wordcount $< > $@

last.dat : books/last.txt
	./wordcount $< > $@

wordcount : wordcount.cpp
	c++ --std=c++11 -o wordcount wordcount.cpp

.PHONY : clean
clean :
	rm -f *.dat
	rm -f results.txt
