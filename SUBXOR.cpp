#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100001

int inp[MAX_N];
int max_level;

typedef struct TrieNode_
{	
	struct TrieNode_* left;
	struct TrieNode_* right;
	int prefix_count;
	int word_count;
}TrieNode;

TrieNode* init(){
	TrieNode* trieNode = (TrieNode *)malloc(sizeof(TrieNode));
	trieNode->prefix_count = 0;
	trieNode->word_count = 0;
	trieNode->left = NULL;
	trieNode->right = NULL;
	return trieNode;
}

// void insert_iter(TrieNode* root, char* word) {
// 	root->prefix_count++;
// 	// if (strlen(word) == 0) {root->word_count++; return;}

// 	TrieNode* cur_node = root;
// 	for(int i=0; i<strlen(word); i++) {
// 		int next_char = word[i] - ORIGIN_LETTER;
// 		// cout << next_char << " " << cur_node << endl;
// 		if(cur_node->children[next_char] == NULL) cur_node->children[next_char] = init();
// 		cur_node = cur_node->children[next_char];
// 		cur_node->prefix_count++;
// 	}
// 	cur_node->word_count++;

// 	return;
// }

void insert_recur(TrieNode* root, int num, int level) {
	root->prefix_count++;
	if (level == 0) {root->word_count++; return;}
	int next_char = num / (1 << (level-1));
	// cout << "(" << next_char << " , " << level << "),  ";
	if (next_char == 0){
		if(root->left == NULL) root->left = init();
		insert_recur(root->left, num % (1 << (level-1)), level-1);
	}
	else {
		if(root->right == NULL) root->right = init();
		insert_recur(root->right, num % (1 << (level-1)), level-1);
	}
	return;
}


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

// bool isLeaf(TrieNode* root){
// 	for(int i=0;i<ALPHABET_SIZE;i++)
// 		if(root->children[i] != NULL) return false;
// 	return true;
// }

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

long long int find_subarrays(TrieNode* root, int num, int k, int level) {

	if(level == 0) return 0;
	int num_dig = num / (1 << (level-1));
	int k_dig = k / (1 << (level-1));

	long long int ret = 0;
	if(num_dig == 0 && k_dig == 0) {
		if(root->left != NULL) ret = find_subarrays(root->left, num % (1 << (level-1)), k % (1 << (level-1)), level-1);
	}
	else if(num_dig == 1 && k_dig == 1) {
		if(root->right != NULL) ret = root->right->prefix_count;
		if(root->left != NULL) ret += find_subarrays(root->left, num % (1 << (level-1)), k % (1 << (level-1)), level-1);
	}
	if(num_dig == 0 && k_dig == 1) {
		if(root->left != NULL) ret = root->left->prefix_count;
		if(root->right != NULL) ret += find_subarrays(root->right, num % (1 << (level-1)), k % (1 << (level-1)), level-1);
	}
	if(num_dig == 1 && k_dig == 0) {
		if(root->right != NULL) ret = find_subarrays(root->right, num % (1 << (level-1)), k % (1 << (level-1)), level-1);
	}

	return ret;
}


int main(){

	int t;
	cin >> t;
	while(t--){
		int n,k;
		cin >> n >> k;
		int maxx = k;
		for(int i=0; i<n; i++) {
			cin >> inp[i];
			maxx = max(maxx, inp[i]);
		}
		max_level = 0;
		while(maxx > 0) {
			maxx = maxx >> 1;
			max_level ++;
		}
		// cout << max_level << endl;
		TrieNode* root = init();
		long long int ans = 0;
		int pre = 0;
		for(int i=0; i<n; i++){
			pre = pre ^ inp[i];
			if (pre < k) ans++;
			// cout << "XOR: " << pre << endl;
			// cout << "FIND: " << find_subarrays(root, pre, k, max_level) << endl;
			ans += find_subarrays(root, pre, k, max_level);
			insert_recur(root, pre, max_level);
			// cout << endl;
		}
		cout << ans << endl;
	}
}