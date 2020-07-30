
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include <string.h>

#define MAX_LEN 257 
#define MAX_BI_LEN 6 * (MAX_LEN - 1)

// Implements a solution to Problem 1 (a), which reads in from stdin:
//   N M
//   str_1
//   str_2
//   ...
//   str_N
// And outputs (to stdout) the hash values of the N strings 1 per line.
void problem_1_a() {
	char cur_line[MAX_LEN];
	int num_lines;
	int mod;
	int lines_read;

	scanf("%d %d", &num_lines, &mod);
	getchar(); // skips new line char from first line

	for (lines_read = 0; lines_read < num_lines; lines_read++) {
		// reading string into cur_line
		fgets(cur_line, MAX_LEN, stdin);
		// removing new line char
		if (cur_line[strlen(cur_line) - 1] == '\n') {
			cur_line[strlen(cur_line) - 1] = '\0';
		}
		printf("%d\n", hash(cur_line, mod));
	}
}
//AUXILARY FUNCTIONS********************************

// calcs 2^exp
int my_pow(int exp) {
	int i;
	int sum = 2;
	if (exp == 0) {
		return 1;
	}

	for (i = 1;  i < exp;  i++) {
		sum = sum * 2;
	}
	return sum;
}

// calcs 2^power % modnum, by div and conq
int my_mod(int power, int modnum) {
	int div;

	if(power == 0) {
		return 1;
	}
	div = my_mod(power / 2, modnum); 
	if(power % 2 == 0) {
		return (div * div) % modnum;
	} 
	return (((div * 2) % modnum) * div) % modnum;
}

// performs hashing used in 1.a) and 1.b)
int hash(char* cur_str, int mod) {
	char bi_string[MAX_BI_LEN] = { '\0' };
	int pos;
	int ch_as_int;

	//iter through word to create relevant binary string
	for (pos = 0; pos < strlen(cur_str); pos++){
		ch_as_int = char_to_int(cur_str[pos]); 

		fill_bi_line(bi_string, pos, ch_as_int);	
	}
	return mod_bi_line(bi_string, mod);
}

//populates bi_line based of num 
void fill_bi_line(char* bi_string, int pos, int num) {
	int exp;
	int digit;

	for (digit = 0; digit < 6; digit++) {
		exp = 5 - digit;
		if (num >= my_pow(exp)){
			bi_string[(6 * pos) + digit] = '1';
			num = num - my_pow(exp);
		} else {
			bi_string[(6 * pos) + digit] = '0';
		}
	}
}

//finds mod of binary num as string 
int mod_bi_line(char* bi_string, int mod) {
	int exp;
	int pos;
	int carry = 0;
	int len = strlen(bi_string);

	for (pos = 0; pos < MAX_BI_LEN; pos++) {
		exp = len - 1 - pos;
		
		if (bi_string[pos] == '\0') {
			break;
		}
		if (bi_string[pos] == '1') {
			carry = (my_mod(exp, mod) + (carry % mod)) % mod;
		}
		bi_string[pos] = '\0';
	}
	return carry;
}

// maps char to int based on project specs
int char_to_int(char ch) {
	if (ch >= 'a' && ch <= 'z') {
		return ch - 'a';
	} 
	if (ch >= 'A' && ch <= 'Z') {
		return (ch - 'A') + 26;
	} 
	return (ch - '0') + 52;
}

//************************************************************
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
void problem_1_b() {
	int num_lines;
	int mod_mem;
	int stp_sz;
	char** lines;
	int pos;
	int chr;
	char cur_line[MAX_LEN];
	char** first_table;
  
 	scanf("%d %d %d", &num_lines, &mod_mem, &stp_sz);
	getchar(); // skips new line char from first line

	lines = malloc(num_lines * sizeof(char*));
	for (pos = 0; pos < num_lines; pos++) {
		lines[pos] = malloc(MAX_LEN * sizeof(char));
	}

	for (pos = 0; pos < num_lines; pos++) {
		// reading string into cur_line
		fgets(cur_line, MAX_LEN, stdin);
		// removing new line char
		if (cur_line[strlen(cur_line) - 1] == '\n') {
			cur_line[strlen(cur_line) - 1] = '\0';
		}

		// adding line to lines 
		for (chr = 0; chr < strlen(cur_line); chr++) {
			lines[pos][chr] = cur_line[chr];
		}
	}
	// allocaing mem for first table
	first_table = malloc(mod_mem * sizeof(char*));
	for (pos = 0; pos < mod_mem; pos++) {
		first_table[pos] = malloc(MAX_LEN * sizeof(char));
		first_table[pos][0] = '\0';
	}

	char** final_table = tabilfy(lines, first_table, num_lines, &mod_mem, stp_sz);

	for (pos = 0; pos < mod_mem; pos++) {
		printf("%d: %s\n", pos, final_table[pos]);
	}

	// freeing memory 
	for (pos = 0; pos < mod_mem; pos++) {
		final_table[pos] = NULL;

	}
	for (pos = 0; pos < num_lines; pos++) {
		free(lines[pos]);
	}
	free(final_table);
	free(lines);

}

//AUXILARY FUNCTIONS********************************

char** tabilfy(char** strings, char** table, int num_strings, int *mem, int k) {
	int str;
	int h_score;
	int n_score;
	int tb_pos;
	int new_pos_strings;
	char** new_table;
	int pos;

	for (str = 0; str < num_strings; str++) {
		h_score = hash(strings[str], *mem);

		if (table[h_score][0] == '\0') {
			table[h_score] = strings[str];

		}
		else {
			// incrementing by step size 
			n_score = new_score(h_score, *mem, k);

			// loop stops when all viable indicies checked 
			while (n_score != h_score) {

				// try to hash
				if (table[n_score][0] == '\0') {
					table[n_score] = strings[str];
					break; 
				}
				n_score = new_score(n_score, *mem, k);
			}

			// table needs to be rehashed 
			if (n_score == h_score) {

				// re ordering strings based on order in table
				new_pos_strings = 0;
				for (tb_pos = 0; tb_pos < *mem; tb_pos++) {
					
					if (table[tb_pos][0] != '\0') {
						strings[new_pos_strings] = table[tb_pos];
						new_pos_strings += 1;
					}
					
					// freeing old table
					table[tb_pos] = NULL;
					free(table[tb_pos]);
					
				}
				free(table);

				// creating new hash table	
				*mem = *mem * 2;
				new_table = malloc(*mem * sizeof(char*));
				for (pos = 0; pos < *mem; pos++) {
					new_table[pos] = malloc(MAX_LEN * sizeof(char));
					new_table[pos][0] = '\0';
				}

				return tabilfy(strings, new_table, num_strings, mem, k);	
			}
		}
	}
	return table;
}	

// carries out linear probing to give new 
int new_score(int old_score, int mem, int k) {
	if (old_score + k < mem) {
		return old_score + k;
	} 
	return (old_score + k) % mem;
}






