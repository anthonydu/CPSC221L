/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::feof;
using std::ifstream;
using std::string;
using std::vector;

string remove_punct(const string& str) {
  string ret;
  std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                      [](int c) { return std::ispunct(c); });
  return ret;
}

CommonWords::CommonWords(const vector<string>& filenames) {
  // initialize all member variables
  init_file_word_maps(filenames);
  init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames) {
  // make the length of file_word_maps the same as the length of filenames
  file_word_maps.resize(filenames.size());

  // go through all files
  for (size_t i = 0; i < filenames.size(); i++) {
    // get the corresponding vector of words that represents the current file
    vector<string> words = file_to_vector(filenames[i]);

    // go through all the words in the file
    /* Your code goes here! */
    for (unsigned j = 0; j < words.size(); j++) {
      file_word_maps[i][words[j]] += 1;
    }
  }
}

void CommonWords::init_common() {
  /* Your code goes here!  */
  for (unsigned i = 0; i < file_word_maps.size(); i++) {
    auto file_word_map = file_word_maps[i];
    for (auto p = file_word_map.begin(); p != file_word_map.end(); p++) {
      common[p->first] += 1;
    }
  }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const {
  vector<string> out;
  /* Your code goes here! */
  auto number_of_files = file_word_maps.size();
  for (auto p = common.begin(); p != common.end(); p++) {
    if (p->second == number_of_files) {
      for (unsigned j = 0; j < number_of_files; j++) {
        if (file_word_maps[j].find(p->first)->second >= n) {
          out.push_back(p->first);
        }
      }
    }
  }

  return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const {
  ifstream words(filename);
  vector<string> out;

  if (words.is_open()) {
    std::istream_iterator<string> word_iter(words);
    while (!words.eof()) {
      out.push_back(remove_punct(*word_iter));
      ++word_iter;
    }
  }
  return out;
}
