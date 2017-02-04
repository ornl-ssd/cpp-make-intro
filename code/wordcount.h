#include <map>        // STD map
#include <string>     // STD string
#include <vector>     // STD vector
#include <algorithm>  // STD algorithm

#include <iostream>   // STD I/O
#include <sstream>    // StringStream
#include <istream>    // InputStream
#include <fstream>    // FileStream

using namespace std;

class wordcount {
    istream *in;
  public:
    wordcount();
    wordcount(char *filename);
    vector<string> read_words(char* delims);
    multimap<int, string> calculate_frequency(vector<string> words);
};
