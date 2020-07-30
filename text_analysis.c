
#include "text_analysis.h"
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include <string.h>

#define MAX_LEN 100

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
void problem_2_a() {
	Trie trie;
	int num_lines;

	scanf("%d", &num_lines);
	getchar(); // skips new line char from first line

	trie = build_trie(num_lines);
	printPreorder(trie.root);
	free_all(trie.root);
}

//***AUXILARY FUNCTIONS************************************
//
void free_all(Node* curs) {
    int i;
    if(!curs) {
    	return;   // safe guard including root node. 
    }

    // recursive case (go to end of trie)
    for (i = 0; i < 27; i++) {
       free_all(curs->children[i]);
    }

    // base case
    free(curs);
}


// builds trie by reading lines in stdin
Trie build_trie(int num_strings) {
	int lines_read;
	char cur_line[MAX_LEN];
	Trie trie; 

	trie.root = new_node('^', 0);
	trie.num_strings = num_strings;
	trie.root->freq = num_strings;

	for (lines_read = 0; lines_read < trie.num_strings; lines_read++) {
		

		// reading string into cur_line
		fgets(cur_line, MAX_LEN, stdin);
		// removing new line char
		if (cur_line[strlen(cur_line) - 1] == '\n') {
			cur_line[strlen(cur_line) - 1] = '\0';
		}
		add_str(&trie, cur_line);
	}
	return trie;
}

// adds a str to trie
void add_str(Trie* trie, char* cur_line) {
	int len = strlen(cur_line);
	Node* cur_node = trie->root;
	int cur_child;
	char cur_char;
	int iter;

	for (iter = 0; iter < len; iter++) {
		cur_char = cur_line[iter];
		cur_child = cur_char - 'a' + 1; 

		// current sequence is new to trie
		if (cur_node->children[cur_child] == NULL) {
			cur_node->children[cur_child] = new_node(cur_char, iter + 1);
			(cur_node->children[cur_child])->prev = cur_node;
			cur_node->number_of_children += 1;
			cur_node = cur_node->children[cur_child];
		} 
		// sequence is already in trie
		else {
			cur_node = cur_node->children[cur_child];
			cur_node->freq += 1;
		}
	}
	// end of string 
	// this sequence is new 
	if (cur_node->children[0] == NULL) {
		cur_node->children[0] = new_node('$', iter + 1);
		(cur_node->children[0])->prev = cur_node;
		cur_node->number_of_children += 1;
	} 
	// sequence is already in trie
	else{
		cur_node = cur_node->children[0];
		cur_node->freq += 1;
	}
}

// initialises new node
Node* new_node(char new_char, int depth_ ) {
	Node *node = malloc(sizeof(*node));
	int iter;

	node->char_val = new_char;
	node->depth = depth_;
	node->freq = 1;
	node->number_of_children = 0;
	for (iter = 0; iter < 28; iter++) {
		node->children[iter] = NULL;
	}

  return node;
}

// pre order traversal 
void printPreorder(Node* node) {
	int iter;

    if (node == NULL) 
        return; 

   	printf("%c\n", node->char_val);
   	// recursive call on children
  	for (iter = 0; iter < 28; iter++) {
  		printPreorder(node->children[iter]); 
  	}
}

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
void problem_2_b() {
	Trie trie;
	int num_lines;
	int prefix_len;

	scanf("%d %d", &num_lines, &prefix_len);
	getchar(); // skips new line char from first line

	trie = build_trie(num_lines);
	printPrefixes(trie.root, prefix_len);
	free_all(trie.root);
}

//***AUXILARY FUNCTIONS************************************

void printPrefixes(Node* node, int prefix_len) {
	int iter;
	int freq;
	char prefix[prefix_len];

    if (node == NULL) 
        return; 

   	if (node->depth == prefix_len && node->char_val != '$') {
   		freq = node->freq;
   		// iterating upwords towards root
   		for (iter = 0; iter < prefix_len; iter++) {
   			prefix[prefix_len - iter - 1] = node->char_val;
   			//printf("/%c   %c/", prefix[prefix_len - iter - 1], node->char_val);
   			//printf(" +++ %d +++ ", prefix_len - iter - 1);
   			node = node->prev;

   		}
   		for (iter = 0; iter < prefix_len; iter++) {
   			printf("%c", prefix[iter]);
   		}
   		printf(" %d\n", freq);
   		return;
   	}
   	// recursive call
  	for (iter = 0; iter < 28; iter++) {
  		printPrefixes(node->children[iter], prefix_len); 
  	}

}

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
void problem_2_c() {
	Trie trie;
	int num_lines;
	int iter;
	char stub[MAX_LEN];
	Node* cur_node;
	float total_freq;

	scanf("%d", &num_lines);
	getchar(); // skips new line char from first line
	scanf("%s", stub);
	getchar(); // skips new line char from first line

	trie = build_trie(num_lines);
	cur_node = trie.root;
	int freqs[num_lines];
	int strings_collected = 0;
	char **strings;

	strings = malloc(num_lines * sizeof(char*));
	for (iter = 0; iter < num_lines; iter++) {
		strings[iter] = malloc(MAX_LEN * sizeof(char));
	}

	// setting cur_node to end of stub
	for (iter = 0; iter < strlen(stub); iter++) {
		cur_node = cur_node->children[stub[iter] - 'a' + 1];
	}

	total_freq = (float) cur_node->freq;
	get_pos_strs(strings, freqs, cur_node, &strings_collected);
	bubbleSort(freqs, strings_collected, strings);

	// printing output 
	for (iter = 0; iter < 5 && iter < strings_collected; iter++) {
		printf("%0.2f %s\n", (freqs[iter] / total_freq), strings[iter]);
	}
	free_all(trie.root);
}

//***AUXILARY FUNCTIONS************************************

void get_pos_strs(char** strings, int* freqs, Node* node, int* strings_collected) {
	int iter;
	int freq;
	int str_len;

    if (node == NULL) 
        return; 

    // we are at the end of a string 
   	if (node->char_val == '$') {
   		freq = node->freq;
   		node = node->prev;
   		str_len = node->depth;

   		// collecting string 
   		for (iter = 0; node->char_val != '^'; iter++) {
   			strings[*strings_collected][str_len - iter - 1] = node->char_val;
   			node = node->prev;
   		}
   		freqs[*strings_collected] = freq;
   		*strings_collected += 1;
   		return;
   	}

   	// recursive call on children
  	for (iter = 0; iter < 28; iter++) {
  		get_pos_strs(strings, freqs, node->children[iter], strings_collected); 
  	}
}
  
// an implementation of bubble sort that sorts both arrays 
void bubbleSort(int* freqs, int len, char** strings) { 
    int j;
    int i;
    
    for (i = 0; i < len - 1; i++) {  
    // Last i elements are already in place  
    	for (j = 0; j < len - 1 - i; j++)  {
       	 if (freqs[j] < freqs[j + 1]) {
         		swap_ints(&freqs[j], &freqs[j + 1]);
        		swap_strs(strings[j], strings[j + 1]);
        	}
     	}   
     }

}  

void swap_ints(int *xp, int *yp) {
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  

void swap_strs(char *str1, char *str2) { 
	char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char)); 
 	strcpy(temp, str1); 
 	strcpy(str1, str2); 
 	strcpy(str2, temp); 
 	free(temp); 
}   





