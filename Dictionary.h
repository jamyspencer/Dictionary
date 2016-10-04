#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <fstream>
#include <string>

class Dictionary{

  private:
  static const int ALPHABET_SIZE = 26;
  
  struct Node{
    std::string   word,
                  definition;
    Node* next[ALPHABET_SIZE];
  };
  typedef Node TrieNode;
  typedef TrieNode* Trie;

  Trie root;
  
  //private functions
  Trie createTrie();
  int findNxtLtr(char);
  void recurWrite(Trie, std::fstream &);
  
  public:
  Dictionary();
  ~Dictionary();
  struct ErrNotChar{ };
  struct ErrFileFailed{ };
  bool insertTrie(std::string, std::string);
  void deleteTrie(Node*);
  std::string lookup(std::string);
  std::string checkString(std::string);
  bool writeTrie(std::string);
  void displayTrie();
  bool loadDictionary(std::string);
  
};
#endif
