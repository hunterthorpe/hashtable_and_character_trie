# hashtable_and_character_trie
Linear probing hash table implementation and character level trie implementation. 

HASHING and HASH TABLE
    
    Problem 1 A
hash.c implements a string hash function, reads in a file containing N strings and outputs the hash value for each string.
The strings will be between 1 and 256 characters long and will contain lowercase letters, uppercase letters and digits.
Each character will be mapped to a 6 digit binary string according to the following function:
chr(a) = 0 chr(A) = 26 chr(0) = 52
chr(b) = 1 ··· chr(B) = 27 ··· chr(1) = 53 ···
chr(z) = 25 chr(Z) = 51 chr(9) = 61
For example A maps to the binary string 011010.
The hash value for a string is computed by concatenating the binary strings for each of the characters
which make up the string, and taking this mod M, for a given M. For example if M = 17 the string "pub" would hash to 8. Since,
chr(p) = 15, chr(u) = 20, chr(b) = 1, we have the concatenated binary string,
001111 010100 000001
This binary number represents the decimal number 62721. Taking 62721 mod 17 yields 8. We say that h17("pub") = 8.
We use 64 here because each binary string we’re concatenating has length 6 and 26 = 64.
Your program will be given input via stdin, where the first line of input contains the two integers N and M and the next N lines contain each of the N strings to be hashed (be careful that your program doesn’t include the newline character in the string).
For example the input file tests/p1a-in-1.txt contains:

    4 17
    pub
    Dijkstra
    AB
    comp20007
    
Your program should output the hash values of each of these strings, one per line. E.g.,

    $ ./a2 p1a < tests/p1a-in-1.txt
    8
    16
    8
    13
        
    Problem 1 B

In this problem I implemented a hash table with initial size M capable of storing strings using the hash function hM described in Problem 1 A.
Your program will again be given N strings which should be inserted (in the given order) into the hash table.
Collisions should be handled using linear probing with a step size of K.
If an element cannot be inserted into the table then the size of the hash table must be doubled (i.e., M(new) = 2 * M(old)) and the strings already in the hash table must be rehashed and inserted (in the order in which they appear in the hash table). Finally the string which initially could not be inserted should be hashed and inserted into the larger hash table.
Your program will receive input from stdin, where the first line will contain the three integers N, M and K and the next N lines will contain the N strings to be inserted into the new larger hash table. Any memory associated with the hash table before the size was increased should be correctly freed.

The program must output the final state of the hash table with one line per slot. e.g:

        $ ./a2 p1b < tests/p1b-in-2.txt
        0:
        1:
        2:
        3:
        4: ba
        5:
        6:
        7: scu
        8: cam
        9:
        10: wam
        11: sal
        
CHARACTER LEVEL TRIE

    Problem 2 A

A trie is a tree where each node represents a character in a word (or a "^" or "$" which represent the start and the end of a word respectively).
Each path from the root to a leaf in a trie corresponds to a word in the data set which the trie represents. Each node has a corresponding frequency.

text_analysis.c is able to read in N strings containing between 1 and 99 lowercase letters and use them to build a character level trie. 

Your program must print the pre-order traversal of the trie after inserting all N strings. For example:
        tests/p2a-in-1.txt :    
        6 
        ab 
        a 
        aa 
        ba 
        aa 
        a
        
Output

        $ ./a2 p2a < tests/p2a-in-1.txt
        ^
        a
        $
        a 
        $ 
        b 
        $ 
        b 
        a 
        $
Note that the children must be stored (and thus, traversed) in alphabetic order, where $ comes before a, which comes before b etc.

    Problem 2 B

In this problem you will construct a trie, as in Problem 2 (a), and use this trie to output all of the prefixes of length exactly K, along with their corresponding frequencies.
The prefixes must be output in alphabetic order.
The input will have one line containing N and K followed by N strings (one per line). For example

        tests/p2b-in-2.txt contains:
        15 3
        algebra
        algorithmics
        already
        algebra
        algae
        albert
        algorithm
        algorithms
        again
        algorithms
        artistic
        albania
        artemis
        alg
        algorithms

In this example your program should output the following:

        $ ./a2 p2b < tests/p2b-in-2.txt
        aga 1
        alb 2
        alg 9
        alr 1 
        art 2
        
    Problem 2 C

You are provided with a word stub, which is the start of a word which is yet to be completed. Your program should predict the probabilities of the possible word completions, based on the set of words provided to your program.
For example if the word stub is "alg" then you should calculate the probability of each possible word W with prefix "alg" according to the following formula:
Pr(W |stub = "alg") = Freq(W )/Freq(prefix = "alg")
The input to your program will contain N (the number of strings) on the first line, the word stub on the second line, and then N lines containing the N strings (one per line).
For example, consider the input 

        tests/p2c-in-2.txt:
        15
        alg
        algebra
        algorithmics
        already
        algebra
        algae
        albert
        algorithm
        algorithms
        again
        algorithms
        artistic
        albania
        artemis
        alg
        algorithms
        
The word stub given in "alg". The possible word completions are "algorithms", "algebra", "algorithm", "algorithmics", "algae" and "alg" with frequencies of 3, 2, 1, 1, 1 and 1 respectively.
Your program should output the probability (formatted to 2 decimal places) followed by the word completion of up to 5 word completions (there may be fewer possibilities). Your program should output the most probable word completions, in descending order of probability, breaking ties alphabetically where a comes before aa.
The output in this example should be:

        $ ./a2 p2c < tests/p2c-in-6.txt
        0.33 algorithms
        0.22 algebra
        0.11 alg
        0.11 algae
        0.11 algorithm
