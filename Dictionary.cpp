#include "Dictionary.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Dictionary::Dictionary(){
  root = createTrie();
}

Dictionary::~Dictionary(){
  deleteTrie(root);
}

/******************************************************************************
 * Name    : createTrie
 * Purpose : creates a new node, initializes dynamic array of pointers
 * Inputs  : none
 * Outputs : returns a dynamically allocated arrays address.
 ******************************************************************************/
 
Dictionary::Trie Dictionary::createTrie(){
  Trie newNode = new TrieNode;
  newNode->word = "";
  newNode->definition = "";
  for(int i = 0; i < ALPHABET_SIZE; i++){
    newNode->next[i] = 0;
  }
  return newNode;
}

/******************************************************************************
 * Name    : findNxtLtr
 * Purpose : used to set the array subscript that corresponds to the letters position
 * Inputs  : a char
 * Outputs : an int that is numerically equivalent to the char inputted.
 ******************************************************************************/

int Dictionary::findNxtLtr(char findThis){
  int arrPos;
  arrPos = static_cast<int>(findThis) - 97;  
  return arrPos; 
}


/******************************************************************************
 * Name    : lookup
 * Purpose : used to look at a word/definition in the tree
 * Inputs  : a word being looked up as a string
 * Outputs : a string of the word and definition appended to it.
 ******************************************************************************/

string Dictionary::lookup(string wordIn){
  Trie scan = root;
  string rVal;
  int arrSubScript = 0,
      wrdLength = wordIn.length();
    
  for (int i = 0; i < wrdLength; i++){
    wordIn[i] = tolower(wordIn[i]);
    arrSubScript = findNxtLtr(wordIn[i]);
    
    if (scan->next[arrSubScript]){
      scan = scan->next[arrSubScript];
      if(scan->definition == ""){
        rVal = wordIn + ": No definition for this string.\n";
      }
      else{
        rVal = scan->word + ": " + scan->definition + "\n";
      }
    }
    else{
      rVal = "ERROR: " + wordIn + " is not in the dictionary.\n";
    }
  } 
  return rVal; 
}

/******************************************************************************
 * Name    : checkString
 * Purpose : used to lowercase all chars and to throw an error if a nonchar value is detected
 * Inputs  : a word as a string
 * Outputs : the same word in lowercase
 ******************************************************************************/

string Dictionary::checkString(string checkThis){

  ErrNotChar notAlpha;
  int strLength = checkThis.length();
  for (int i = 0; i < strLength; i++){
    if(isalpha(checkThis[i])){
      checkThis[i] = tolower(checkThis[i]);
    }
    else if(isspace(checkThis[i])){
      checkThis.erase(i,1);
      strLength--;
    }
    else{
      throw notAlpha;
    }
  }
  return checkThis;
}

/******************************************************************************
 * Name    : deleteTrie
 * Purpose : deletes and deallocates memory of entire tree or subtree
 * Inputs  : pointer to node struct
 * Outputs : none
 ******************************************************************************/

void Dictionary::deleteTrie(Trie deleteThis){
  for (int i = 0; i < ALPHABET_SIZE; i++){
    if(deleteThis->next[i]){
      deleteTrie(deleteThis->next[i]);
    }
  } 
  delete deleteThis;
  deleteThis = 0;

}

/******************************************************************************
 * Name    : writeTrie
 * Purpose : uses recurWrite to write the entire tree to a file
 * Inputs  : file name to write to as a string
 * Outputs : returns a bool value indicating success or failure of the write
 ******************************************************************************/

bool Dictionary::writeTrie(string fileName){
  fstream outFile(fileName.c_str(), ios::out);
  if (outFile.fail()){
    return 1;
  }
  recurWrite(root, outFile);
  outFile.close();
  return 0;
}

/******************************************************************************
 * Name    : recurWrite
 * Purpose : recursively writes the entire tree, or subtree
 * Inputs  : pointer address to a node struct and an fstream object 
 * Outputs : none
 ******************************************************************************/

void Dictionary::recurWrite(Trie writeThis, fstream & outFile){
  
  if (writeThis != root){
    outFile << writeThis->word << ":"<< writeThis->definition << endl;
  }
  for (int i = 0; i < ALPHABET_SIZE; i++){
    if(writeThis->next[i]){
      recurWrite(writeThis->next[i], outFile);
    }
  }
}

/******************************************************************************
 * Name    : insertTrie
 * Purpose : to insert an item into the dictionary tree
 * Inputs  : word along with a definition
 * Outputs : bool value indicating the write was successful
 ******************************************************************************/

bool Dictionary::insertTrie(string word, string defnIn){
  Trie  scan = root,
        newNode;
  
  try{
    word = checkString(word);
  }
  catch(ErrNotChar a){
    cout << "Invalid character detected, closing program\n";
    exit(1);
  }
  
  string check = "";  
  bool  success = false;
  int   arrSubScript = 0,
        wrdLength = word.length();
          
  for (int i = 0; i < wrdLength; i++){
    check += word[i];
    arrSubScript = findNxtLtr(word[i]);

    if (scan->next[arrSubScript] == 0){
      newNode = createTrie();
      scan->next[arrSubScript] = newNode;
      newNode->word = check;
      if(check == word){
        newNode->definition = defnIn;
        success = true;
      }
    }
    scan = scan->next[arrSubScript]; 
  }
  return success;
}

/******************************************************************************
 * Name    : loadDictionary
 * Purpose : populates the dictionary with data from a txt file
 * Inputs  : file name as a string
 * Outputs : bool value that indicates the write was successful.
 ******************************************************************************/

bool Dictionary::loadDictionary(string fileName){
  string  getWord,
          getDefn;

  ifstream inFile(fileName.c_str());
  
  if(inFile.fail()){
    return 1;
  }
  else{
    while(!(inFile.eof())){
      getline(inFile, getWord, ':');
      getline(inFile, getDefn, '\n');

      if(getWord.length() && !(insertTrie(getWord, getDefn))){
        cout << "Warning, " << getWord << " already exists in database, it was not added.\n";
      }
    }
  }
  inFile.close();
  return 0;
}
