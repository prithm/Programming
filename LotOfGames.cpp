#include <bits/stdc++.h>
using namespace std;

#define ALPHABET_SIZE 26
#define ORIGIN_LETTER 'a'
#define MAX_N 100001

char inp[MAX_N];

typedef struct TrieNode_
{	
	struct TrieNode_* children[ALPHABET_SIZE];
	int prefix_count;
	int word_count;
	bool win;
	bool lose;
}TrieNode;

TrieNode* init(){
	TrieNode* trieNode = (TrieNode *)malloc(sizeof(TrieNode));
	trieNode->prefix_count = 0;
	trieNode->word_count = 0;
	for(int i=0; i<ALPHABET_SIZE; i++) trieNode->children[i] = NULL;
	trieNode->win = false;
	trieNode->lose = true;
	return trieNode;
}

void insert_iter(TrieNode* root, char* word) {
	root->prefix_count++;
	// if (strlen(word) == 0) {root->word_count++; return;}
	// cout << word << endl;
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


// bool search(TrieNode* root, char* word) {
// 	TrieNode* cur_node = root;
// 	int i = 0;
// 	for(i=0; i<strlen(word); i++){
// 		int next_char = word[i] - ORIGIN_LETTER;
// 		if(cur_node->children[next_char] == NULL) return false;
// 		cur_node = cur_node->children[next_char];
// 	}
// 	return cur_node->word_count > 0 ? true : false;
// }

bool isLeaf(TrieNode* root){
	for(int i=0;i<ALPHABET_SIZE;i++)
		if(root->children[i] != NULL) return false;
	return true;
}

// int deleteTrie(TrieNode* root, char* word) { 

// 	// cout << word << endl;
// 	if(strlen(word) == 0){
// 		if(root->word_count > 0){
// 			root->word_count--;
// 			root->prefix_count--;
// 			return root->word_count;
// 		}
// 		else return -1;		
// 	}
// 	int next_char = word[0]-ORIGIN_LETTER;
// 	if(root->children[next_char] == NULL) { cout << "NOT FOUND" << endl ; return -1;}
// 	int flag = deleteTrie(root->children[next_char], word+1); 
// 	/*flag -1 not found, -2 found, just decrease prefix count, 0 check if childeren can be set to NULL*/
// 	if(flag == -1) return -1;
// 	root->prefix_count--;
// 	if(flag == 0) if(isLeaf(root->children[next_char])) {root->children[next_char] = NULL; return 0;}
// 	return -2;	
// }

pair<bool,bool> dfs(TrieNode* root){
	// cout << temp << endl;
	if(isLeaf(root)) {root->win = false; root->lose = true; return make_pair(false,true);}
	root->win = false;
	root->lose = false;
	for(int i=0; i<ALPHABET_SIZE; i++) 
		if(root->children[i] != NULL) {
			pair<bool,bool> t = dfs(root->children[i]);
			root->win = root->win || !t.first;
			root->lose = root->lose || !t.second;
		}
	return make_pair(root->win,root->lose);
}

// void dfs_debug(TrieNode* root, string temp){
// 	cout << temp << " " << root->win << endl; 
// 	if(isLeaf(root)) return;
// 	bool ret = false;
// 	for(int i=0; i<ALPHABET_SIZE; i++) 
// 		if(root->children[i] != NULL) dfs_debug(root->children[i], temp + (char)('a' + i));
// 	return;
// }

int main()
{
	int n,k;
	cin >> n >> k;
	TrieNode* root = init();
	for(int i=0; i<n; i++){
		cin >> inp;
		// cout << inp << endl;
		insert_iter(root, inp);
	}
	pair<bool, bool> win_lose = dfs(root);
	if((win_lose.first && win_lose.second) || (win_lose.first && !win_lose.second && k%2==1)) cout << "First" << endl;
	else cout << "Second" << endl;
	// dfs_debug(root, "");

}