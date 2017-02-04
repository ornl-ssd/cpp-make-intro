---
title: "Variables"
teaching: 15
exercises: 15
questions:
- "How can I eliminate redundancy in my Makefiles?"
objectives:
- "Use variables in a Makefile."
- "Explain the benefits of decoupling configuration from computation."
keypoints:
- "Define variables by assigning values to names."
- "Reference variables using `$(...)`."
---

Despite our efforts, our Makefile still has repeated content, namely
the name of our program, `wordcount` and the corresponding source files
`wordcount.cpp` and `main.cpp`. If we renamed our program we'd have to update our 
Makefile in multiple places.

We can introduce a Make [variable]({{ page.root }}/reference/#variable) (called a
[macro]({{ page.root }}/reference/#macro) in some versions of Make) to hold the
name of the source files:

~~~
COUNT_SRC=wordcount.cpp main.cpp
~~~
{: .make}

This is a variable [assignment]({{ page.root }}/reference/#assignment) -
`COUNT_SRC` is assigned the value `wordcount.cpp main.cpp`.

Defining the variable `COUNT_SRC` in this way allows us to easily
change which source files are used to build the `wordcount` program. In the
same way, we can also define the variable `COUNT_EXE` to
refer to the `wordcount` program. 

The `zipf-test.py` script is slightly different, but we can use the same 
technique to define the variable `ZIPF_SRC` to refer to the script. Since 
this script is invoked by passing it to `python`. We can introduce another 
variable to represent this execution:

~~~
ZIPF_EXE=python $(ZIPF_SRC)
~~~
{: .make}

`$(...)` tells Make to replace a variable with its value when Make
is run. This is a variable [reference]({{ page.root }}/reference/#reference). At
any place where we want to use the value of a variable we have to
write it, or reference it, in this way.

Here we reference the variable `ZIPF_SRC`. This tells Make to
replace the variable `ZIPF_SRC` with its value `zipf-test.py`. When
Make is run it will assign to `ZIPF_EXE` the value `python
zipf-test.py`.

> ## Use Variables
>
> Update `Makefile` so that the `%.dat` rule
> references the variables `COUNT_SRC` and `COUNT_EXE`.
> Then do the same for the `zipf-test.py` script
> and the `results.txt` rule,
> using `ZIPF_SRC` and `ZIPF_EXE` as variable names
>
> > ## Solution
> > [This Makefile]({{ page.root }}/code/06-variables-challenge/Makefile)
> > contains a solution to this challenge.
> {: .solution}
{: .challenge}

We place variables at the top of a Makefile so they are easy to
find and modify. Alternatively, we can pull them out into a new
file that just holds variable definitions (i.e. delete them from
the original makefile). Let us create `config.mk`:

~~~
# Count words program.
COUNT_SRC=wordcount.cpp main.cpp
COUNT_EXE=wordcount

# Test Zipf's rule
ZIPF_SRC=zipf_test.py
ZIPF_EXE=python $(ZIPF_SRC)
~~~
{: .make}

We can then import `config.mk` into `Makefile` using:

~~~
include config.mk
~~~
{: .make}

We can re-run Make to see that everything still works:

~~~
$ make clean
$ make dats
$ make results.txt
~~~
{: .bash}

We have separated the configuration of our Makefile from its rules,
the parts that do all the work. If we want to change our script name
or how it is executed we just need to edit our configuration file, not
our source code in `Makefile`. Decoupling code from configuration in
this way is good programming practice, as it promotes more modular,
flexible and reusable code.

> ## Where We Are
>
> [This Makefile]({{ page.root }}/code/06-variables/Makefile)
> and [its accompanying `config.mk`]({{ page.root }}/code/06-variables/config.mk)
> contain all of our work so far.
{: .callout}
