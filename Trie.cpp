#include <bits/stdc++.h>
using namespace std;

#define ALPHABET_SIZE 26
#define ORIGIN_LETTER 'a'

typedef struct TrieNode_
{	
	struct TrieNode_* children[ALPHABET_SIZE];
	int prefix_count;
	int word_count;
}TrieNode;

TrieNode* init(){
	TrieNode* trieNode = (TrieNode *)malloc(sizeof(TrieNode));
	trieNode->prefix_count = 0;
	trieNode->word_count = 0;
	for(int i=0; i<ALPHABET_SIZE; i++) trieNode->children[i] = NULL;
	return trieNode;
}

void insert_iter(TrieNode* root, char* word) {
	root->prefix_count++;
	// if (strlen(word) == 0) {root->word_count++; return;}

	TrieNode* cur_node = root;
	for(int i=0; i<strlen(word); i++) {
		int next_char = word[i] - ORIGIN_LETTER;
		// cout << next_char << " " << cur_node << endl;
		if(cur_node->children[next_char] == NULL) cur_node->children[next_char] = init();
		cur_node = cur_node->children[next_char];
		cur_node->prefix_count++;
	}
	cur_node->word_count++;

	return;
}

// void insert_recur(TrieNode* root, char* word) {
// 	root->prefix_count++;
// 	if (strlen(word) == 0) {root->word_count++; return;}
// 	int next_char = word[0] - ORIGIN_LETTER;
// 	if(root->children[next_char] == NULL) root->children[next_char] = init();
// 	insert_recur(root->children[next_char], word+1);
// 	return;
// }


bool search(TrieNode* root, char* word) {
	TrieNode* cur_node = root;
	int i = 0;
	for(i=0; i<strlen(word); i++){
		int next_char = word[i] - ORIGIN_LETTER;
		if(cur_node->children[next_char] == NULL) return false;
		cur_node = cur_node->children[next_char];
	}
	return cur_node->word_count > 0 ? true : false;
}

bool isLeaf(TrieNode* root){
	for(int i=0;i<ALPHABET_SIZE;i++)
		if(root->children[i] != NULL) return false;
	return true;
}

int deleteTrie(TrieNode* root, char* word) { 

	// cout << word << endl;
	if(strlen(word) == 0){
		if(root->word_count > 0){
			root->word_count--;
			root->prefix_count--;
			return root->word_count;
		}
		else return -1;		
	}
	int next_char = word[0]-ORIGIN_LETTER;
	if(root->children[next_char] == NULL) { cout << "NOT FOUND" << endl ; return -1;}
	int flag = deleteTrie(root->children[next_char], word+1); 
	/*flag -1 not found, -2 found, just decrease prefix count, 0 check if childeren can be set to NULL*/
	if(flag == -1) return -1;
	root->prefix_count--;
	if(flag == 0) if(isLeaf(root->children[next_char])) {root->children[next_char] = NULL; return 0;}
	return -2;	
}


int main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    char keys[][8] = {"the", "a", "there", "answer", "any",
                     "by", "bye", "their"};
 
    TrieNode *root = init();
 
    // Construct trie
    int i;
    for (i = 0; i < 8; i++)
        insert_iter(root, keys[i]);
 
    // Search for different keys
    printf("%s --- %s\n", "the", search(root, "the") ? "YES" : "NO");
    printf("%s --- %s\n", "these", search(root, "these") ? "YES" : "NO");
    printf("%s --- %s\n", "their", search(root, "their") ? "YES" : "NO");
    printf("%s --- %s\n", "thaw", search(root, "thaw") ? "YES" : "NO");

    deleteTrie(root, "their");
    printf("%s --- %s\n", "the", search(root, "the") ? "YES" : "NO");
    printf("%s --- %s\n", "these", search(root, "these") ? "YES" : "NO");
    printf("%s --- %s\n", "their", search(root, "their") ? "YES" : "NO");
    printf("%s --- %s\n", "thaw", search(root, "thaw") ? "YES" : "NO");


    insert_iter(root, "their");
    // insert_iter(root, "their");
    deleteTrie(root, "their");
    printf("%s --- %s\n", "the", search(root, "the") ? "YES" : "NO");
    printf("%s --- %s\n", "these", search(root, "these") ? "YES" : "NO");
    printf("%s --- %s\n", "their", search(root, "their") ? "YES" : "NO");
    printf("%s --- %s\n", "thaw", search(root, "thaw") ? "YES" : "NO");
 
    return 0;
}