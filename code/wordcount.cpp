#include <map>        // STD map
#include <string>     // STD string
#include <vector>     // STD vector
#include <algorithm>  // STD algorithm

#include <iostream>   // STD I/O
#include <sstream>    // StringStream
#include <istream>    // InputStream
#include <fstream>    // FileStream

using namespace std;

int main(int argc, char *argv[])
{
  string buffer, sentence;
  vector<string> words;

  map<string, int> get_freq;
  map<string, int>::iterator iter1;

  multimap<int, string> frequency;
  map<int, string>::reverse_iterator iter2;

  ifstream ifn;
  istream *in = &cin;

  char delims[] = {'.', ',', ';', ':', '?', '$', '@', '^', '<', '>', '#', '%', '`', '!', '*', '-', '=', '(', ')', '[', ']', '{', '}', '/', '"', '\'', '_'};

  if (argc > 1) {
    ifn.open(argv[1]);
    in = &ifn;
  }

  while(*in >> buffer) {
    transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    buffer.erase(remove_if(buffer.begin(), buffer.end(), (int(*)(int))ispunct), buffer.end());
    buffer.erase(remove_if(buffer.begin(), buffer.end(), (int(*)(int))isdigit), buffer.end());
    if (!buffer.empty())
      words.push_back(buffer);
  }

  /* Calculate frequency of words via the map. */

  for (int i = 0; i < words.size(); i++) {
    // If word does not exist, add it to the map.
    if (get_freq.find(words[i]) == get_freq.end())
      get_freq[words[i]] = 1;
    else
      get_freq[words[i]] += 1;
  }

  /* Create a second map with K-V pairs flipped so it is sorted. */

  // Set values from first map to keys of second map.
  for (iter1 = get_freq.begin(); iter1 != get_freq.end(); iter1++) {
    pair<int, string> p(iter1->second, iter1->first);
    frequency.insert(p);
  }

  /* Print out frequency map in reverse order as "V-K" pairs in output. */

  for (iter2 = frequency.rbegin(); iter2 != frequency.rend(); iter2++)
    cout << iter2->second << " " << iter2->first << " " << (float)iter2->first / words.size() * 100.0 << endl;

  return 0;
}
