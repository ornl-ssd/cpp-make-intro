include config.mk

TXT_FILES=$(wildcard books/*.txt)
DAT_FILES=$(patsubst books/%.txt, %.dat, $(TXT_FILES))

# Generate summary table.
results.txt : $(DAT_FILES) $(ZIPF_SRC)
	$(ZIPF_EXE) $(DAT_FILES) > $@

# Count words.
.PHONY : dats
dats : $(DAT_FILES)

%.dat : books/%.txt $(COUNT_EXE)
	./$(COUNT_EXE) $< > $*.dat

$(COUNT_EXE) : $(COUNT_OBJ)
	c++ --std=c++11 -o $(COUNT_EXE) $(COUNT_OBJ)

.PHONY : clean
clean :
	rm -f $(DAT_FILES)
	rm -f results.txt

.PHONY : variables
variables:
	@echo TXT_FILES: $(TXT_FILES)
	@echo DAT_FILES: $(DAT_FILES)
