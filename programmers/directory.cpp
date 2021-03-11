#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int NUMBERS = 10; //0~9

bool hasPrefix;

struct TrieNode {
    TrieNode* children[NUMBERS];
    bool isTerminal;
    TrieNode() : isTerminal(false) {
        memset(children, 0, sizeof children);
    }
    ~TrieNode() {
        for (int i = 0; i < NUMBERS; ++i) {
            if (children[i]) delete children[i];
        }
    }
};

void insert(TrieNode* root, const char* key) {
    if (*key == '\0') {
        root->isTerminal = true;
        return;
    }
    
    if (root->children[*key-'0'] == nullptr) {
        root->children[*key-'0'] = new TrieNode();
    } else if (root->children[*key-'0']->isTerminal){
        hasPrefix = true;
    }
    insert(root->children[*key-'0'], key+1);
}

bool solution(vector<string> phone_book) {
    auto criterion = [](const string& s1, const string& s2) {
        return s1.size() < s2.size();  
    };
    sort(phone_book.begin(), phone_book.end(), criterion);
    
    hasPrefix = false;
    TrieNode root;
    for (auto& number : phone_book) {
        insert(&root, number.c_str());
        if (hasPrefix) return false;
    }
    return true;
}
