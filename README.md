Anum Hassan
Assignment 3 - Hashtables

Description:
All parts of this assignment were completed. Using the code provided by Hunter College, the textbook, and various online sources (Geeksforgeeks, stackoverflow, youtube, cplusplus.com, etc) implemented hashtables using linear probing, quadratic probing, and double hashing. Also implemented a spell checker that would correct words in a document by comparing it to a given dictionary. This was done by feeding the dictionary words into a hashtable, and checking to see if the other document's words were present in the hashtable, and if not, tried 3 cases (Adding one character in any possible position, Removing one character from the word, Swapping adjacent characters in the word) to change the word up to see if that word is present in the dictionary. 

Double Hashing: R value = 69. \
 
--------------------------------
Instructions:\

Compile everything by typing:\
make clean\
make all\

Part 1 and Part 2:

./create_and_test_hash words_file_name query_words_file_name flag \
 where flag can be linear, quadratic, or double. If double is chosen, include an R value. \
e.g ./create_and_test_hash words.txt query_words.txt quadratic\
\
Part 3:\
./spell_check document_file dictionary_file\
e.g ./spell_check document1_short.txt wordsEN.txt\

--------------------------------
