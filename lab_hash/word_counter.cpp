/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::string;
using std::vector;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& filename) : dict(256) {
  /**
   * @todo Implement this function.
   * @see char_counter.cpp if you're having trouble.
   */
  TextFile file(filename);
  while (file.good()) {
    auto word = file.getNextWord();
    auto found = dict.find(word);
    if (found) {
      dict[word] += 1;
    } else {
      dict.insert(word, 1);
    }
  }
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) {
  vector<pair<string, int>> ret;
  for (auto it = dict.begin(); it != dict.end(); it++) {
    if (it->second >= threshold) {
      ret.push_back(pair<string, int>(it->first, it->second));
    }
  }
  return ret;
}
