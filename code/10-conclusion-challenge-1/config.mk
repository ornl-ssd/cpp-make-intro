# Count words program.
COUNT_SRC=wordcount.cpp main.cpp
COUNT_OBJ=wordcount.o main.o
COUNT_EXE=wordcount
CXXFLAGS=--std=c++11

# Plot word counts script.
PLOT_SRC=plotcount.py
PLOT_EXE=python $(PLOT_SRC)

# Test Zipf's rule
ZIPF_SRC=zipf_test.py
ZIPF_EXE=python $(ZIPF_SRC)
