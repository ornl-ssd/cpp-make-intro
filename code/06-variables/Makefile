include config.mk

# Generate summary table.
results.txt : *.dat $(ZIPF_SRC)
	$(ZIPF_EXE) $< > $@

# Count words.
.PHONY : dats
dats : isles.dat abyss.dat last.dat

%.dat : books/%.txt $(COUNT_EXE)
	./$(COUNT_EXE) $< > $*.dat

$(COUNT_EXE) : $(COUNT_SRC)
	c++ --std=c++11 -o $(COUNT_EXE) $(COUNT_SRC)

.PHONY : clean
clean :
	rm -f *.dat
	rm -f results.txt
