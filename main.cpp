/******************************************************************************
 * Course       : CS 2250 E01 (Spring 2016)
 * Assignment   : 
 * Summary      : 
 * Author       : Jamy Spencer
 * Last Modified: 
 ******************************************************************************/
#include "Dictionary.h"
#include <iostream>
#include <string>
using namespace std;

string getFile(Dictionary);
void look(Dictionary);

 /******************************************************************************
 * Name    : main
 * Purpose : This is main
 * Inputs  : None.
 * Outputs : Returns 0 if ran successfully.
 ******************************************************************************/
int main(){

  Dictionary myDictionary;
  string file;
  bool badOpen;
  
  file = getFile();
  look();

  cout << "Please enter the name of the output file: ";
  cin >> file;
  cout << "Writing dictionary...\n";
  badOpen = myDictionary.writeTrie(file.c_str());
  if (badOpen){
    cout << "Error: File could not open.\n";
  }
  return 0;
}

/******************************************************************************
 * Name    : getFile
 * Purpose : get file name of file to open and load it into data tree
 * Inputs  : none
 * Outputs : string
 ******************************************************************************/
string getFile(){
  
  bool badOpen;
  string file;
   
  do{
    cout << "Please enter the name of the input dictionary file: ";
    cin >> file;
    badOpen = myDictionary.loadDictionary(file);
    if (badOpen){
      cout << "Error: " << file << " failed to open.\n";
    }
  }while(badOpen);
  return file;
}

/******************************************************************************
 * Name    : look
 * Purpose : run user interface to search for words in dictionary
 * Inputs  : none 
 * Outputs : none
 ******************************************************************************/
void look(){

  string lookFor;
  
  do{
    cin.ignore(1000, '\n');
    cout << "Would you like to lookup a word (y/n)? ";
    cin >> lookFor;
    lookFor[0] = tolower(lookFor[0]);
    if(lookFor != "n"){
      cout << "Enter a word: ";
      cin >> lookFor;
      cout << myDictionary.lookup(lookFor);
    }
  }while(lookFor != "n");
}
/******************************************************************************
 * Name    : 
 * Purpose : 
 * Inputs  : 
 * Outputs : 
 ******************************************************************************/

/******************************************************************************
 * Name    : 
 * Purpose : 
 * Inputs  : 
 * Outputs : 
 ******************************************************************************/

/******************************************************************************
 * Name    : 
 * Purpose : 
 * Inputs  : 
 * Outputs : 
 ******************************************************************************/
