

#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H

//TYPEDEFS 

typedef struct node Node;

typedef struct trie Trie;

struct node {
   char char_val;
   int number_of_children;
   int depth;
   int freq;
   Node* children[28];
   Node* prev; 
};

struct trie {
	Node* root;
	int num_strings;
}; 


// Build a character level trie for a given set of words.
//
// The input to your program is an integer N followed by N lines containing
// words of length < 100 characters, containing only lowercase letters.
//
// Your program should built a character level trie where each node indicates
// a single character. Branches should be ordered in alphabetic order.
//
// Your program must output the pre-order traversal of the characters in
// the trie, on a single line.
void problem_2_a();

void free_all(Node* curs);
Node* new_node(char new_char, int depth_ );
void add_str(Trie* trie, char* cur_line);
Trie build_trie(int num_strings);
void printPreorder(Node* node);
// Using the trie constructed in Part (a) this program should output all
// prefixes of length K, in alphabetic order along with their frequencies
// with their frequencies. The input will be:
//   n k
//   str_0
//   ...
//   str_(n-1)
// The output format should be as follows:
//   an 3
//   az 1
//   ba 12
//   ...
//   ye 1
void problem_2_b();


void printPrefixes(Node* node, int prefix_len);

// Again using the trie data structure you implemented for Part (a) you will
// provide a list (up to 5) of the most probable word completions for a given
// word stub.
//
// For example if the word stub is "al" your program may output:
//   0.50 algorithm
//   0.25 algebra
//   0.13 alright
//   0.06 albert
//   0.03 albania
//
// The probabilities should be formatted to exactly 2 decimal places and
// should be computed according to the following formula, for a word W with the
// prefix S:
//   Pr(word = W | stub = S) = Freq(word = W) / Freq(stub = S)
//
// The input to your program will be the following:
//   n
//   stub
//   str_0
//   ...
//   str_(n-1)
// That is, there are n + 1 strings in total, with the first being the word
// stub.
//
// If there are two strings with the same probability ties should be broken
// alphabetically (with "a" coming before "aa").
void problem_2_c();

void get_pos_strs(char** strings, int* freqs, Node* node, int* strings_collected);

void bubbleSort(int* freqs, int len, char** strings);

void swap_ints(int *xp, int *yp);

void swap_strs(char *str1, char *str2);

#endif
