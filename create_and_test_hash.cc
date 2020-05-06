// Anum Hassan
/* Program that tests the 3 different probing implementations, Linear, Double, and Quadratic Hashing
Each hashing implementation is tested with the total number of elements in the table, the size of the table, the load factor, the total number of collisions, and the average number of collisions. It also checks whether each word in another given file, query_words.txt, is in the hashtable, and print corresponding output depending on whether the word is found and not found, and how many probes it took to find the word, if it exists. */
#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// Test function that creates and analyzes the hashtable
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {

  hash_table.MakeEmpty();  
  //..Insert your own code

  // read in file
  ifstream word_file;
  word_file.open(words_filename);
  if(word_file.fail()){
    cout << "Error in opening file" << endl;
    exit(1);
  }
  string line;

  // insert words into hashtable
  while(getline(word_file, line)){
    hash_table.Insert(line);
  }

  cout << "number_of_elements: " << hash_table.GetNumElements()<< endl;
  cout << "size_of_table: " << hash_table.GetSizeOfTable() << endl;
  cout << "load_factor: " << hash_table.GetNumElements()/(float)hash_table.GetSizeOfTable() << endl;
  cout << "collisions: " << hash_table.GetNumCollisions()<< endl;
  cout << "avg_collisions: " <<(float)hash_table.GetNumCollisions()/hash_table.GetNumElements()<< endl<<endl;

  ifstream query_file;
  string query_;

  query_file.open(query_filename);

  while(getline(query_file, query_)){
    if(hash_table.Contains(query_)){
      cout << query_ << " Found " << hash_table.GetNumProbes() << endl;
    }

    else{
      cout << query_ << " Not_Found " << hash_table.GetNumProbes() << endl;
    }
  }
  word_file.close();
  query_file.close();

}

//method for double hashing - stores r value in .h file
template <typename HashTableType>
void TestFunctionForDouble(HashTableType &hash_table, const string &words_filename, const string &query_filename, int r){
hash_table.MakeEmpty();  

  // read in file
  ifstream word_file;
  word_file.open(words_filename);
  if(word_file.fail()){
    cout << "Error in opening file" << endl;
    exit(1);
  }
  string line;

  // insert words into hashtable
  while(getline(word_file, line)){
    hash_table.Insert(line, r);
  }

  cout << "number_of_elements: " << hash_table.GetNumElements()<< endl;
  cout << "size_of_table: " << hash_table.GetSizeOfTable() << endl;
  cout << "load_factor: " << hash_table.GetNumElements()/(float)hash_table.GetSizeOfTable() << endl;
  cout << "collisions: " << hash_table.GetNumCollisions()<< endl;
  cout << "avg_collisions: " <<(float)hash_table.GetNumCollisions()/hash_table.GetNumElements()<< endl<<endl;

  ifstream query_file;
  string query_;

  query_file.open(query_filename);

  while(getline(query_file, query_)){
    if(hash_table.Contains(query_, r)){
      cout << query_ << " Found " << hash_table.GetNumProbes() << endl;
    }

    else{
      cout << query_ << " Not_Found " << hash_table.GetNumProbes() << endl;
    }
  }
  word_file.close();
  query_file.close();
}

int testFunctionWrapper(int argument_count, char **argument_list) {
  const string words_filename(argument_list[1]);
  const string query_filename(argument_list[2]);
  const string param_flag(argument_list[3]);
  

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
    const string r_val(argument_list[4]);
    cout << "r_val: " << r_val << endl;
    int rvalue = stoi(r_val); //changes string to an int
    HashTableDouble<string> double_probing_table;
    TestFunctionForDouble(double_probing_table, words_filename, query_filename, rvalue);    
  } else {
    cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}

// Sample main for program create_and_test_hash.
int main(int argc, char **argv) {

  if (argc != 4 && argc != 5)  {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  testFunctionWrapper(argc, argv);
  return 0;
}
