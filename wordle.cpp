#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordlehelper(const string& in, string current, int count, string floatings, set<std::string>& wordset, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
  // int f = 0;
  // map<char, int> floatingmap;
  string floatings = floating;
  // for (char c : floating) {
  //   floatingmap[c]++;  
  //   f++;
  // }
  int c = 0;
  for (size_t j = 0; j < in.size(); ++j) {
    if(in[j]=='-'){
      c++;
    }
  }
  set<std::string> wordset;
  wordlehelper(in, "", c, floatings, wordset, dict); 
  return wordset;
}

// Define any helper functions here
void wordlehelper(const string& in, string current, int count, string floatings, set<std::string>& wordset, const std::set<std::string>& dict){
  // word is complete
  int c;
  if(current.empty()){
    c = 0;
  } else {
    c = current.size();
  }
  if(c==in.size() && floatings.empty()){
    if(dict.find(current)!=dict.end()){
        wordset.insert(current);
    }
    return;
  }
  // find alphabet
  if(in[c]=='-'){
    if(count<=floatings.size()){
      string temp;
      for (size_t i = 0; i < floatings.size(); ++i) {
        temp = floatings;
        temp.erase(i, 1);
        wordlehelper(in, current+floatings[i], count-1, temp, wordset, dict);
      }
    } else {
      for (char ch = 'a'; ch <= 'z'; ++ch) {
        bool check = true;
        for (size_t i = 0; i < floatings.size(); ++i) {
          if(floatings[i] == ch){
            string temp = floatings;
            temp.erase(i, 1);
            wordlehelper(in, current+ch, count-1, temp, wordset, dict);
            check = false;
          }
        }
        if(check){
          wordlehelper(in, current+ch, count-1, floatings, wordset, dict);
        }
      }
    }
  }
  // has a set alphabet
  else {
    current += in[c];
    wordlehelper(in, current, count, floatings, wordset, dict);
  }
}
