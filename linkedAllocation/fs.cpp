#include <iostream>
#include <fstream>
#include <vector>
#include <string> 

#include "helper.h"

using namespace std;

class discEmulator{
  public:
    //constructor that uses user's specifications
    //  blockSize must be >= 1 + 2 * indexLength
    //  if it is not, blockSize will be increased until it is
    //todo: save user specifications so they can be accessed after
    //  program stops running
    discEmulator(int bQ, int bS, int fS, int lL, string fN, int iL);
    //constructor that uses default specifications
    discEmulator();
    //writes the disc string to disc.txt
    void paste();
    //writes text to a file with the name as fileName
    void touch(string fileName, string text);
    //allocates text at the top free space, decrements topFreeBlockIndex and freeBlockQuantity
    void allocate(string text, int indexToInsert);
    //given a block index, returns index of linked block
    int getNextBlockIndex(int index);
    //changes corresponding private variable
    void setTopFreeBlockIndex(int num);
    void setFreeBlockQuantity(int num);
    //inserts newFatEntry into fat
    void updateFat(string newFatEntry);
    //return index of top free block
    int getTopFreeBlockIndex();

  private:
    //these can only be altered by touch, mkdir, append, write
    string disc;
    int topFreeBlockIndex = 0;
    //freeBlocksQuantity is based on blockQuantity and can be altered by the constructor
    //  that has parameters but is also reduced/increase when blocks are allocated/deallocated
    int freeBlockQuantity = 50;
    //specifications that can be altered by the constructor that has parameters
    int blockQuantity = 50;
    int blockSize = 20;
    int fatSize = 300;
    int lineLength = 100;//length of lines in disc.txt
    string fileName = "disc.txt";
    int indexLength = 2;//number of characters in blocks reserved for indexes
};

int main(){
  discEmulator sandisc = discEmulator();
  sandisc.paste();
  sandisc.touch("zero","000000000000000000000000");
  sandisc.touch("advice", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  sandisc.touch("query", "how old is the oldest person who ever lived?");
  cout<<sandisc.getTopFreeBlockIndex()<<endl;
  cout<<sandisc.getNextBlockIndex(20)<<endl;
}

//todo: save user specifications to disc.txt so they can be reused after program stops running
//  user can still technically just run the constructor with parameters again with the same
//  inputs and that would acheive the same thing
discEmulator::discEmulator(int bQ, int bS, int fS, int lL, string fN, int iL){
  freeBlockQuantity = bQ;
  blockQuantity = bQ;
  blockSize = bS;
  fatSize = fS;
  lineLength = lL;
  fileName = fN;
  indexLength = iL;
  if(blockSize < (1 + 2 * indexLength)){
    blockSize = 1 + 2 * indexLength;
  }
  string temp_str;
  ifstream read(fileName);
  while(getline(read, temp_str)){
    disc += temp_str;
  }
  read.close();
  if(disc == ""){
    for(int i = 0; i < fatSize; i++){
      disc += '@';
    }
    for(int i = 0; i < blockQuantity; i++){
      string block(blockSize - indexLength, '@');
      string nextBlockIndex = to_string(i + 1);
      nextBlockIndex = appendZeroIfShort(nextBlockIndex, indexLength);
      if(i == blockQuantity - 1){
        nextBlockIndex = convertToEnd(nextBlockIndex);
      }
      block += nextBlockIndex;
      disc += block;
    }
    disc += appendZeroIfShort(to_string(0), indexLength);
    disc += appendZeroIfShort(to_string(blockQuantity), indexLength);
  }
  else{
    topFreeBlockIndex = stoi(disc.substr(fatSize + blockQuantity * blockSize, indexLength));
    freeBlockQuantity = stoi(disc.substr(fatSize + blockQuantity * blockSize + indexLength, indexLength));
  }
}

discEmulator::discEmulator(){
  string temp_str;
  ifstream read(fileName);
  while(getline(read, temp_str)){
    disc += temp_str;
  }
  read.close();
  if(disc == ""){
    for(int i = 0; i < fatSize; i++){
      disc += '@';
    }
    for(int i = 0; i < blockQuantity; i++){
      string block(blockSize - 2, '@');
      string nextBlockIndex = to_string(i + 1);
      nextBlockIndex = appendZeroIfShort(nextBlockIndex, indexLength);
      if(i == blockQuantity - 1){
        nextBlockIndex = convertToEnd(nextBlockIndex);
      }
      block += nextBlockIndex;
      disc += block;
    }
    disc += appendZeroIfShort(to_string(0), indexLength);
    disc += appendZeroIfShort(to_string(blockQuantity), indexLength);
  }
  else{
    topFreeBlockIndex = stoi(disc.substr(fatSize + blockQuantity * blockSize, indexLength));
    freeBlockQuantity = stoi(disc.substr(fatSize + blockQuantity * blockSize + indexLength, indexLength));
    //cout<<topFreeBlockIndex<<" "<<freeBlockQuantity<<endl;
  }
}

void discEmulator::paste(){
  ofstream write(fileName);
  for(int i = 0; i < disc.size(); i += lineLength){
    write<<disc.substr(i, lineLength)<<endl;
  }
  write.close();
}

void discEmulator::setTopFreeBlockIndex(int num){
  string newTop = appendZeroIfShort(to_string(num), indexLength);
  int startIndex = fatSize + blockQuantity * blockSize;
  for(int i = startIndex; i < startIndex + indexLength; i++){
    disc[i] = newTop[i - startIndex];
  }
  paste();
}

void discEmulator::setFreeBlockQuantity(int num){
  string newQuantity = appendZeroIfShort(to_string(num), indexLength);
  int startIndex = fatSize + blockQuantity * blockSize + indexLength;
  for(int i = startIndex; i < startIndex + indexLength; i++){
    disc[i] = newQuantity[i - startIndex];
  }
  paste();
}

int discEmulator::getNextBlockIndex(int index){
  string indexString = disc.substr(fatSize + index * blockSize + (blockSize - indexLength), indexLength);
  if(indexString == "@@"){
    return -1;
  }
  else{
    return stoi(disc.substr(fatSize + index * blockSize + (blockSize - indexLength), indexLength));
  }
}

void discEmulator::allocate(string text, int indexToInsert){
  cout<<text<<endl;
  int startIndex = fatSize + indexToInsert * blockSize;
  for(int i = startIndex; i < startIndex + blockSize; i++){
    disc[i] = text[i - startIndex];
  }
}

void discEmulator::touch(string fileName, string text){
  //send signal for users to be in receive mode
  string newFatEntry = fileName;
  for(int i = 0; i < text.length(); i += blockSize - indexLength){
    newFatEntry += to_string(topFreeBlockIndex) + "/";
    string newBlock = text.substr(i, blockSize - indexLength);
    int indexToInsert = topFreeBlockIndex;
    int nextBlock = getNextBlockIndex(indexToInsert);
    topFreeBlockIndex = nextBlock;
    setTopFreeBlockIndex(topFreeBlockIndex);
    freeBlockQuantity--;
    setFreeBlockQuantity(freeBlockQuantity);
    while(newBlock.length() < blockSize - indexLength){
      newBlock += '@';
    }
    if(!(i + blockSize - indexLength >= text.length())){
      newBlock += appendZeroIfShort(to_string(nextBlock), indexLength);
    }
    else{
      string lastMarker(indexLength, '@');
      newBlock += lastMarker;
      cout<<lastMarker<<endl;
    }
    allocate(newBlock, indexToInsert);
  }
  updateFat(newFatEntry);
  paste();
}

void discEmulator::updateFat(string newFatEntry){
  int entryLength = newFatEntry.length();
  int entryIndex = 0;
  for(int i = 0; i < fatSize; i++){
    if(disc[i] == '@' && entryLength > 0){
      entryLength--;
      disc[i] = newFatEntry[entryIndex];
      entryIndex++;
    }
  }
}

int discEmulator::getTopFreeBlockIndex(){
  return stoi(disc.substr(fatSize + blockQuantity * blockSize, indexLength));
}

/*
nested loop to loop through table of peers
--users are represented by characters
fat and blocks needs to write the user as well as block number
  <this should come from the loop of the peers table and shorten text length from 18 to 17.
done: need to have fat updater function that receives new fat
done: touch needs to determine next free block instead of allocate
done: function to report top free block
*/