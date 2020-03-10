/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    std::map<string, vector<string>> temp;
    vector<string> vec;
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
      while (getline(wordsFile, word)) {
          vec.push_back(word);
      }
    }
    for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
      string sorted = *itr;
      std::sort(sorted.begin(), sorted.end());
      if (temp.find(sorted) != temp.end()) {
        if (std::find(temp[sorted].begin(), temp[sorted].end(), *itr) != temp[sorted].end()) {
          continue;
        }
        temp[sorted].push_back(*itr);
      } else {
        vector<string> lib;
        lib.push_back(*itr);
        temp[sorted] = lib;
      }
    }
    for (auto itr = temp.begin(); itr != temp.end(); ++itr) {
      for (auto it = itr->second.begin(); it != itr->second.end(); ++it) {
        dict[*it] = itr->second;
      }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    std::map<string, vector<string>> temp;
    for (auto itr = words.begin(); itr != words.end(); ++itr) {
      string sorted = *itr;
      std::sort(sorted.begin(), sorted.end());
      if (temp.find(sorted) != temp.end()) {
        if (std::find(temp[sorted].begin(), temp[sorted].end(), *itr) != temp[sorted].end()) {
          continue;
        }
        temp[sorted].push_back(*itr);
      } else {
        vector<string> lib;
        lib.push_back(*itr);
        temp[sorted] = lib;
      }
    }
    for (auto itr = temp.begin(); itr != temp.end(); ++itr) {
      for (auto it = itr->second.begin(); it != itr->second.end(); ++it) {
        dict[*it] = itr->second;
      }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    auto result = dict.find(word);
    if (result != dict.end()) {
      return result->second;
    } else {
      return vector<string>();
    }
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> all;
    for (auto itr = dict.begin(); itr != dict.end(); ++itr) {
      if (itr->second.size() == 1) {
        continue;
      }
      all.push_back(itr->second);
    }
    return all;
}
