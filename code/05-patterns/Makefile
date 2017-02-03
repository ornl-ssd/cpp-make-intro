# Generate summary table.
results.txt : *.dat zipf_test.py
	python zipf_test.py $< > $@

# Count words.
.PHONY : dats
dats : isles.dat abyss.dat last.dat

%.dat : books/%.txt wordcount
	./wordcount $< > $*.dat

wordcount : wordcount.cpp
	c++ --std=c++11 -o wordcount wordcount.cpp

.PHONY : clean
clean :
	rm -f *.dat
	rm -f results.txt
