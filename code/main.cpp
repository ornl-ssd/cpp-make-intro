#include <map>        // STD map
#include <string>     // STD string
#include <vector>     // STD vector
#include <algorithm>  // STD algorithm

#include <iostream>   // STD I/O
#include <istream>    // InputStream
#include <fstream>    // FileStream

#include "wordcount.h"

using namespace std;

char delims[] = {'.', ',', ';', ':', '?', '$', '@', '^', '<', '>', '#', '%', '`', '!', '*', '-', '=', '(', ')', '[', ']', '{', '}', '/', '"', '\'', '_'};

int main(int argc, char *argv[])
{
  wordcount *wc = new wordcount();
  vector<string> words;

  multimap<int, string> freq;
  map<int, string>::reverse_iterator iter;

  if (argc > 1) {
    wc = new wordcount(argv[1]);
  }

  words = wc->read_words(delims);
  freq = wc->calculate_frequency(words);

  /* Print out frequency map in reverse order as "V-K" pairs in output. */

  for (iter = freq.rbegin(); iter != freq.rend(); iter++) {
    cout << iter->second << " " << iter->first << " " << (float)iter->first / words.size() * 100.0 << endl;
  }

  return 0;
}
