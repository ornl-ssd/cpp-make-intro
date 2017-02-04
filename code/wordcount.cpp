#include <map>        // STD map
#include <string>     // STD string
#include <vector>     // STD vector
#include <algorithm>  // STD algorithm

#include <iostream>   // STD I/O
#include <sstream>    // StringStream
#include <istream>    // InputStream
#include <fstream>    // FileStream

#include "wordcount.h"

using namespace std;

wordcount::wordcount() {
  in = &cin;
}

wordcount::wordcount(char *filename) {
  ifstream *ifn = new ifstream();
  ifn->open(filename);
  in = ifn;
}

vector<string> wordcount::read_words(char* delims) {
  string buffer;
  vector<string> words;

  while(*in >> buffer) {
    transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    buffer.erase(remove_if(buffer.begin(), buffer.end(), (int(*)(int))ispunct), buffer.end());
    buffer.erase(remove_if(buffer.begin(), buffer.end(), (int(*)(int))isdigit), buffer.end());
    if (!buffer.empty())
      words.push_back(buffer);
  }

  return words;
}

multimap<int, string> wordcount::calculate_frequency(vector<string> words) {
  map<string, int> get_freq;
  map<string, int>::iterator iter;
  multimap<int, string> frequency;

  /* Calculate frequency of words via the map. */

  for (auto& word : words) {
    // If word does not exist, add it to the map.
    if (get_freq.find(word) == get_freq.end())
      get_freq[word] = 1;
    else
      get_freq[word] += 1;
  }

  /* Create a second map with K-V pairs flipped so it is sorted. */

  // Set values from first map to keys of second map.
  for (auto& kv : get_freq) {
    pair<int, string> p(kv.second, kv.first);
    frequency.insert(p);
  }

  return frequency;
}
