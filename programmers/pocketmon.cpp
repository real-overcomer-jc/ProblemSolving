#include <vector>
#include <set>
#include <cmath>

using namespace std;

int solution(vector<int> nums)
{
    set<int> used(nums.begin(), nums.end());
    return min(used.size(), nums.size()/2);
}
