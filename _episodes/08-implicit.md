---
title: "Implicit Rules"
teaching: 15
exercises: 15
questions:
- "Are there standard ways of doing things with Makefiles?"
objectives:
- "Allow make to find a customary method for updating a target file."
keypoints:
- "Certain standard ways of remaking target files are used very often."
- "Implicit rules tell make how to use customary techniques so that you do not have to specify them in detail."
- "A chain of implicit rules can apply in sequence."
- "You can define your own implicit rules by writing pattern rules."
---

At this point, we have the following Makefile:

~~~
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

$(COUNT_EXE) : $(COUNT_SRC)
	c++ --std=c++11 -o $(COUNT_EXE) $(COUNT_SRC)

.PHONY : clean
clean :
	rm -f $(DAT_FILES)
	rm -f results.txt

.PHONY : variables
variables:
	@echo TXT_FILES: $(TXT_FILES)
	@echo DAT_FILES: $(DAT_FILES)
~~~
{: .make}

 Our `wordcount` program is generated from two source files, `wordcount.cpp` and
`main.cpp`. You may have noticed that whenever one of these files changes, *both* are
recompiled to generate the `wordcount` program. It would be much better to only
recompile the source file that changed. Fortunately it is possible to compile each
source file into an object file before combining it into the final program. If we 
were to do that manually, it would look something like this:

~~~
wordcount.o : wordcount.cpp
	c++ --std=c++11 -c -o wordcount.o wordcount.cpp

main.o : main.cpp
	c++ --std=c++11 -c -o main.o main.cpp
	
wordcount : wordcount.o main.o
	c++ -o wordcount wordcount.o main.o
~~~
{: .make}

Try replacing the following lines with the lines above and see what happens. 

~~~
$(COUNT_EXE) : $(COUNT_SRC)
	c++ --std=c++11 -o $(COUNT_EXE) $(COUNT_SRC)
~~~
{: .make}

~~~
$ touch wordcount.cpp
$ make
c++ --std=c++11   -c -o wordcount.o wordcount.cpp
c++ -o wordcount wordcount.o main.o
./wordcount books/abyss.txt > abyss.dat
./wordcount books/isles.txt > isles.dat
./wordcount books/last.txt > last.dat
./wordcount books/sierra.txt > sierra.dat
python zipf_test.py  abyss.dat  isles.dat  last.dat  sierra.dat > results.txt
~~~
{: .shell}

You should notice the `wordcount` program is still recompiled whenever a source
file is changed, but now only the modified source file (in this case `wordcount.cpp`)
is recompiled.

However, the changes we made have re-introduced a lot of redundancy. We could remove
some of this by using variables again, such as using COUNT_OBJ to represent the object
files:

~~~
COUNT_OBJ=wordcount.o main.o
COUNT_EXE=wordcount

wordcount.o : wordcount.cpp
	c++ --std=c++11 -c -o wordcount.o wordcount.cpp

main.o : main.cpp
	c++ --std=c++11 -c -o main.o main.cpp
	
$(COUNT_EXE) : $(COUNT_OBJ)
	c++ -o $(COUNT_EXE) $(COUNT_OBJ)
~~~
{: .make}

We could continue to do this for the other source and object files, but fortunately
there is an easier way. Make provides some standard ways of creating certain types
of targets. These *implicit rules* tell Make to use customary methods for creating
a target.

Often all that needs to be done to allow Make to find a customary method is
to refrain from specifying commands yourself. Either 
write a rule with no command lines, or don't write a rule at all. Then Make 
will figure out which implicit rule to use based on which kind of source file 
exists or can be made.

We can do this by removing the commands for compiling the object files:

~~~
COUNT_OBJ=wordcount.o main.o
COUNT_EXE=wordcount

wordcount.o : wordcount.cpp

main.o : main.cpp
	
$(COUNT_EXE) : $(COUNT_OBJ)
	c++ -o $(COUNT_EXE) $(COUNT_OBJ)
~~~
{: .make}

~~~
$ touch wordcount.cpp
$ make
c++    -c -o wordcount.o wordcount.cpp
wordcount.cpp:47:8: warning: 'auto' type specifier is a C++11 extension
      [-Wc++11-extensions]
  for (auto& word : words) {
       ^
wordcount.cpp:47:19: warning: range-based for loop is a C++11 extension
      [-Wc++11-extensions]
  for (auto& word : words) {
                  ^
wordcount.cpp:58:8: warning: 'auto' type specifier is a C++11 extension
      [-Wc++11-extensions]
  for (auto& kv : get_freq) {
       ^
wordcount.cpp:58:17: warning: range-based for loop is a C++11 extension
      [-Wc++11-extensions]
  for (auto& kv : get_freq) {
                ^
4 warnings generated.
c++ -o wordcount wordcount.o main.o
./wordcount books/abyss.txt > abyss.dat
./wordcount books/isles.txt > isles.dat
./wordcount books/last.txt > last.dat
./wordcount books/sierra.txt > sierra.dat
python zipf_test.py  abyss.dat  isles.dat  last.dat  sierra.dat > results.txt
~~~
{: .shell}

Note however that the commands being executed are different from
the orginal commands, they don't have the `--std=c++11` option. This may cause
some compilers to generate warnings if they default to using an earlier
C++ standard. 

We can solve this because implict rules also have implicit *variables*
defined with them. In the case of the rule to generate an object file from
a C++ source file, there is a variable called `CXXFLAGS` which are extra flags
to be given to the compiler. By setting this variable, we can modify the
command that is executed by the implict rule.

We can even go one step further and remove the rules altogether as make will still
know that you want to use the implicit rule by specifying the object files as 
part of the last compile rule.
 
Assuming we added `COUNT_OBJ`, `COUNT_EXE`, and `CXXFLAGS` to `config.mk`, our 
complete `Makefile` with these changes would be:

~~~
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
	c++ -o $(COUNT_EXE) $(COUNT_OBJ)

.PHONY : clean
clean :
	rm -f $(DAT_FILES)
	rm -f results.txt

.PHONY : variables
variables:
	@echo TXT_FILES: $(TXT_FILES)
	@echo DAT_FILES: $(DAT_FILES)
~~~
{: .make}

Remember, the `config.mk` file contains:

~~~
# Count words program.
COUNT_SRC=wordcount.cpp main.cpp
COUNT_OBJ=wordcount.o main.o
COUNT_EXE=wordcount
CXXFLAGS=--std=c++11

# Test Zipf's rule
ZIPF_SRC=zipf_test.py
ZIPF_EXE=python $(ZIPF_SRC)
~~~
{: .make}

> ## Linking a single object file
>
> In addition to knowing how to build an object file from a source file, Make also knows
> how to build a program from multiple object files. Remove the remaining compile command 
> (leaving the rule) and check that the program is still built correctly.
>
> > ## Solution
> > [This Makefile]({{ page.root }}/code/08-implicit-challenge/Makefile)
> > contains a solution to this challenge.
> {: .solution}
{: .challenge}
