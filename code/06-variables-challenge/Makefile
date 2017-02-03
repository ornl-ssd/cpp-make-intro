COUNT_SRC=wordcount.cpp
COUNT_EXE=wordcount
ZIPF_SRC=zipf_test.py
ZIPF_EXE=python $(ZIPF_SRC)

# Generate summary table.
results.txt : *.dat $(ZIPF_SRC)
	$(ZIPF_EXE) $< > $@

# Count words.
.PHONY : dats
dats : isles.dat abyss.dat last.dat

%.dat : books/%.txt $(COUNT_SRC)
	./$(COUNT_EXE) $< > $*.dat
	
$(COUNT_EXE) : $(COUNT_SRC)
	c++ --std=c++11 -o $(COUNT_EXE) $(COUNT_SRC)

.PHONY : clean
clean :
	rm -f *.dat
	rm -f results.txt
