#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;

const int ALPHABETS = 26;

struct TrieNode {
    TrieNode* children[ALPHABETS];
    map<int,int> count;
    bool isTerminal;
    TrieNode() : isTerminal(false) {
        memset(children, 0, sizeof children);
    }
    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; ++i)
            if (children[i]) delete children[i];
    }
};

void insert(TrieNode* root, const char* key, int len) {
    ++root->count[len];
    if (*key == '\0') {
        root->isTerminal = true;
        return;
    }

    if (root->children[*key-'a'] == nullptr) {
        root->children[*key-'a'] = new TrieNode();
    }
    insert(root->children[*key-'a'], key+1, len);
}

int find(TrieNode* root, const char* key, int len) {
    if (*key == '\0') return root->isTerminal ? 1 : 0;
    else if (*key == '?') return root->count[len];
    else if (root->children[*key-'a'] == nullptr) return 0;
    return find(root->children[*key-'a'], key+1, len);
}

vector<int> solution(vector<string> words, vector<string> queries) {
    TrieNode forwardTrie, reverseTrie;
    for (auto& word : words) {
        insert(&forwardTrie, word.c_str(), word.size());
        reverse(word.begin(), word.end());
        insert(&reverseTrie, word.c_str(), word.size());
    }
    
    vector<int> ret(queries.size(),0);
    for (int i = 0; i < queries.size(); ++i) {
        string& query = queries[i];
        if (query.front() == '?' && query.back() == '?') {
            ret[i] = forwardTrie.count[query.size()];
        } else if (query.front() == '?') {
            reverse(query.begin(), query.end());
            ret[i] = find(&reverseTrie, query.c_str(), query.size());
        } else {
            ret[i] = find(&forwardTrie, query.c_str(), query.size());
        }
    }
    return ret;
}
