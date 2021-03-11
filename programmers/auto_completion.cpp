#include <string>
#include <vector>
#include <cstring>

using namespace std;

const int ALPHABETS = 26;

struct TrieNode {
    TrieNode* children[ALPHABETS];
    int count;
    bool isTerminal;
    
    TrieNode() : count(0), isTerminal(false) {
        memset(children, 0, sizeof(children));
    }
    
    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; ++i) 
            if (children[i]) delete children[i];
    }
};

void insert(TrieNode* root, const char* key) {
    if (*key == '\0') {
        root->isTerminal = true;
        return;
    }
    
    if (root->children[*key-'a'] == nullptr) {
        root->children[*key-'a'] = new TrieNode();
    }
    ++root->children[*key-'a']->count;
    insert(root->children[*key-'a'], key+1);
}

int find(TrieNode* root, const char* key, int depth) {
    if (*key == '\0') return (root->isTerminal) ? depth : 0;
    else if (root->children[*key-'a'] == nullptr) return 0;
    else if (root->children[*key-'a']->count == 1) return depth+1;
    return find(root->children[*key-'a'], key+1, depth+1);
}

int solution(vector<string> words) {
    TrieNode* root = new TrieNode();
    for (int i = 0; i < words.size(); ++i) {
        insert(root, words[i].c_str());
    }
    
    int ret = 0;
    for (int i = 0; i < words.size(); ++i) {
        ret += find(root, words[i].c_str(), 0);
    }
    delete(root);
    return ret;
}
