
#ifndef HASH_H
#define HASH_H

// additional functions i have implemented 
int hash(char* cur_str, int mod);
int char_to_int(char ch);
int mod_bi_line(char* bi_string, int mod);
void fill_bi_line(char* bi_string, int pos, int num);
int my_mod(int power, int modnum);
int my_pow(int exp);

char** tabilfy(char** strings, char** table, int num_strings, int *mem, int k);
int new_score(int old_score, int mem, int k);


// Implements a solution to Problem 1 (a), which reads in from stdin:
//   N M
//   str_1
//   str_2
//   ...
//   str_N
// And outputs (to stdout) the hash values of the N strings 1 per line.
void problem_1_a();

// Implements a solution to Problem 1 (b), which reads in from stdin:
//   N M K
//   str_1
//   str_2
//   ...
//   str_N
// Each string is inputed (in the given order) into a hash table with size
// M. The collision resolution strategy must be linear probing with step
// size K. If an element cannot be inserted then the table size should be
// doubled and all elements should be re-hashed (in index order) before
// the element is re-inserted.
//
// This function must output the state of the hash table after all insertions
// are performed, in the following format
//   0: str_k
//   1:
//   2: str_l
//   3: str_p
//   4:
//   ...
//   (M-2): str_q
//   (M-1):
void problem_1_b();

#endif
