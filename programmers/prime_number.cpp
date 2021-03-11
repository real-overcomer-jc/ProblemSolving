#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

int answer;
map<int,bool> checkedMap;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n%2 == 0) return false;
    if (n%6 != 1 && n%6 != 5) return false;
    
    for (int i = 3; i <= sqrt(n); i+=2) {
        if (n%i == 0) return false;
    }
    return true;
}

void countPrimeNumber(const string& numbers, int used, string& candidate) {
    if (candidate.size() > 0 && !checkedMap[stoi(candidate)]) {
        if(isPrime(stoi(candidate))) ++answer;
        checkedMap[stoi(candidate)] = true;
    }
    
    for (int i = 0; i < numbers.size(); ++i) {
        if (used & (1<<i)) continue;
        candidate.push_back(numbers[i]);
        countPrimeNumber(numbers, used | (1<<i), candidate);
        candidate.pop_back();
    }
}

int solution(string numbers) {
    //sort(numbers.begin(), numbers.end());
    //numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
    
    answer = 0;
    checkedMap.clear();
    
    string candidate;
    countPrimeNumber(numbers, 0, candidate);
    return answer;
}
