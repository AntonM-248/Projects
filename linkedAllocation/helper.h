#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
using namespace std;

string appendZeroIfShort(string word, int length){
  while(word.length() < length){
    word = "0" + word;
  }
  return word;
}

string convertToEnd(string index){
  string result(index.length(), '@');
  return result;
}