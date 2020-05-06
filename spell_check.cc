/* Anum Hassan 
 Program that uses quadratic probing to implement a spell checker. Given a document, the program outputs all of the correctly spelled words, and all of the misspelled words. For each misspelled word, a list of candidate corections are provided from the dictionary, that can be formed by
applying one of the following rules to the misspelled word:
a) adding  one character in any possible position
b) Removing one character from the word
c) Swapping adjacent characters in the word
*/
#include "quadratic_probing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// make all words from input file become lower case and removes punctuation
string standardizeWord(string & word){
  string changed_word = "";
  for (auto & letter : word){
    if(isalnum(letter) && letter != '.'  ){
      letter = tolower(letter);
      changed_word += letter;
    }
  }
  return changed_word;
}

// for words with apostrophes - just makes them lowercase
string lowercase (string & word) {
  string changed_word = "";
  for (int i = 0; i < word.length(); i++){
    if(isalnum(word[i]) || word[i]== '-' || word[i] == '\''){
      changed_word += tolower(word[i]);
    }
  }
  return changed_word;
}

//check to see if there are hyphens
bool hyphen_present (string & word){
  for (int i =0; i < word.length(); i ++){
    if (word[i] == '-'){
      return true;
    }
  }
  return false;
}

// contains functions for all 3 cases
template<typename HashTableType>
void SpellCheck(HashTableType &hash_table, const string &document_filename, const string &words_filename){
  // open up files
  ifstream doc_stream;
  doc_stream.open(document_filename);

  ifstream word_stream;
  word_stream.open(words_filename);

  //inserting words from dictionary into hash table
  string word;
  hash_table.MakeEmpty();
  while(word_stream.good()){
    getline(word_stream, word);
    hash_table.Insert(word);
  }

// check to see if hashtable populated with words from dictionary
  // if(hash_table.Contains("abandoned")){
  //   cout << "yes" << endl;
  // }
  // else{
  //   cout << " no " << endl;
  // }
  
  string corrected_word = standardizeWord(word);
  string special_word; //'s words

  while(doc_stream >> word){
    //************** check for 's words
    if(word[word.length()-2] == '\''){
     cout << lowercase(word) << " is INCORRECT" << endl;
      //case a - adding on char in any possible position
      for (int i =0; i< special_word.length() +1; i++){
        for(char l = 'a'; l<='z'; ++l){
          special_word = lowercase(word);
          special_word.insert(i, 1, l);
          if(hash_table.Contains(special_word)){
            cout << "** " << lowercase(word) << " -> " << special_word << " ** case A" << endl;
          }
          special_word = lowercase(word);
         }

      }
      //case b - Removing one character from the word
      for (int i =0; i < special_word.length(); i++){
       special_word.erase(i,1);
       if(hash_table.Contains(special_word)){
        cout << "** " << lowercase(word) << " -> " << special_word << " ** case B" << endl;
          }
          special_word = lowercase(word);
      }

      //case c- swapping adjacent characters in the word
      for (int i =0; i < special_word.length()-1; i++){
       swap(special_word[i], special_word[i+1]);
       if(hash_table.Contains(special_word)){
        cout << "** " << lowercase(word) << " -> " << special_word << " ** case C" << endl;
          }
          special_word = lowercase(word);
        }
      }
//check for hyphenated words 
    else if (!hash_table.Contains(word) && hyphen_present(word)){
        cout << lowercase(word) << " is INCORRECT" << endl;
      }
  //*************** if word is found, print correct
    else if (hash_table.Contains(standardizeWord(word))){
      cout << standardizeWord(word) << " is CORRECT" << endl; 
    }
  // ************** all other incorrect words 
    else {
      cout << standardizeWord(word) << " is INCORRECT" << endl;
      // corrections

      //case a - adding on char in any possible position
      for (int i =0; i<= corrected_word.length(); i++){
        for(char l = 'a'; l<='z'; ++l){
          corrected_word = standardizeWord(word);
          corrected_word.insert(i, 1, l);
          
          if(hash_table.Contains(corrected_word)){
            cout << "** " << standardizeWord(word) << " -> " << corrected_word << " ** case A" << endl;
          }
          corrected_word = standardizeWord(word);
        }
      }
      //case b - Removing one character from the word
      for (int i =0; i < corrected_word.length(); i++){
       corrected_word.erase(i,1);
       if(hash_table.Contains(corrected_word)){
         cout << "** " << standardizeWord(word) << " -> " << corrected_word << " ** case B" << endl;
       }
       corrected_word = standardizeWord(word); 
      }

      //case c- swapping adjacent characters in the word
      for (int i =0; i < corrected_word.length()-1; i++){
        swap(corrected_word[i], corrected_word[i+1]);
          if(hash_table.Contains(corrected_word)){
          cout << "** " << standardizeWord(word) << " -> " << corrected_word << " ** case C" << endl;
        }
       corrected_word = standardizeWord(word); 
      }
    }
  }
  doc_stream.close();
  word_stream.close();
}


int testSpellingWrapper(int argument_count, char** argument_list) {

  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);
  

  // Call functions implementing the assignment requirements.
  HashTable<string> quadratic_probing_table;
  SpellCheck(quadratic_probing_table, document_filename, dictionary_filename);
}

// Sample main for program spell_check.
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);

  return 0;
}

