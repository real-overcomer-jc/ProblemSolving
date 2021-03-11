#include <vector>
#include <cmath>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    if (n % 6 != 1 && n % 6 != 5) return false;
    
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int count(const vector<int>& nums, int n, int start, int sum) {
    if (n == 3) return isPrime(sum) ? 1 : 0;
    
    int ret = 0;
    for (int i = start; i < nums.size(); ++i) {
        ret += count(nums, n+1, i+1, sum+nums[i]);
    }
    return ret;
}

int solution(vector<int> nums) {
    return count(nums, 0, 0, 0);
}
