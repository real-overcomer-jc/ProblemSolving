#include <string>
#include <vector>

using namespace std;

int count(const vector<int>& numbers, int n, int target, int sum) {
    if (n == numbers.size()) return (sum == target) ? 1: 0;
    return count(numbers, n+1, target, sum + numbers[n]) + count(numbers, n+1, target, sum - numbers[n]);  
}

int solution(vector<int> numbers, int target) {
    return count(numbers, 0, target, 0);
}
