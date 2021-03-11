#include <string>
#include <vector>
#include <ctime>
#include <set>

using namespace std;

struct Node {
    long long start, end, max;
    Node* left;
    Node* right;
    int priority;
    Node(long long start, long long end) : start(start), end(end), max(end), left(nullptr), right(nullptr), priority(rand()) {}
};

using NodePair = pair<Node*,Node*>;
NodePair split(Node* root, long long start) {
    if (root == nullptr) return {nullptr, nullptr};
    if (start < root->start) {
        NodePair pair = split(root->left, start);
        root->left = pair.second;
        return make_pair(pair.first, root);
    }
    NodePair pair = split(root->right, start);
    root->right = pair.first;
    return make_pair(root, pair.second);
}

Node* insert(Node* root, Node* newNode) {
    if (root == nullptr) return newNode;
    
    if (root->priority < newNode->priority) {
        newNode->max = max(root->max, newNode->max);
        NodePair pair = split(root, newNode->start);
        newNode->left = pair.first;
        newNode->right = pair.second;
        return newNode;
    }
    
    root->max = max(root->max, newNode->max);
    if (newNode->start < root->start) {
        root->left = insert(root->left, newNode);
    } else {
        root->right = insert(root->right, newNode);
    }
    return root;
}

void query(Node* root, long long start, long long end, vector<pair<long long,long long>>& intervals) {
    if (root == nullptr) return;
    if (root->max < start) return;

    if (!(root->end < start || end < root->start)) {
        intervals.push_back({root->start, root->end});
    }
    query(root->left, start, end, intervals);
    query(root->right, start, end, intervals);
}

long long min(Node* root) {
    if (root->left == nullptr) return root->start;
    return min(root->left);
}

long long max(Node* root) {
    if (root == nullptr) return -1;
    return root->max;
}

void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int solution(vector<string> lines) {
    Node* root = nullptr;
    for (int i = 0; i < lines.size(); ++i) {
        struct tm t;
        double milsec = 0;
        double elapsed = 0;
        sscanf(lines[i].c_str(), "%d-%d-%d %d:%d:%d.%lf %lf", &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec, &milsec, &elapsed);
        elapsed *= 1000;

        t.tm_year -= 1900;
        t.tm_mon -= 1;
        time_t time = mktime(&t);
        //cout << "timestamp: " << time << endl;

        long long end = time*1000 + milsec;
        long long start = end - elapsed + 1;
        //cout << "start: " << start << ", end: " << end << endl;

        root = insert(root, new Node(start, end));
    }

    int maxThroughput = 0;
    long long rangeStart = min(root), rangeEnd = max(root);
    while (rangeStart <= rangeEnd) {
        vector<pair<long long,long long>> ret;
        query(root, rangeStart, rangeStart+999, ret);
        if (ret.size() == 0) {
            rangeStart += 1000;
        }  else {
            maxThroughput = max<long long>(maxThroughput, static_cast<long long>(ret.size()));
            if (ret.size() == 1) {
                if (rangeStart < ret[0].second) rangeStart = min(ret[0].second-1, rangeStart+998);
                else if (rangeStart == ret[0].second) rangeStart = rangeStart+998;
            } 
            ++rangeStart;
        }
    }
    deleteTree(root);
    return maxThroughput;
}
