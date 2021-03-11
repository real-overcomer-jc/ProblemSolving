#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

int cache[2][100000];

int maxSum(const vector<int>& sticker, int i, int isFirstDetached) {
    if (sticker.size() <= i) return 0;
    if (i+1 == sticker.size()) 
        return i == 0 ? sticker[i] : (isFirstDetached) ? 0 : sticker[i];
    
    int& ret = cache[isFirstDetached][i];
    if (ret != -1) return ret;
    
    ret = sticker[i] + maxSum(sticker, i+2, isFirstDetached);
    return ret = max(ret, maxSum(sticker, i+1, isFirstDetached));
}

int solution(vector<int> sticker)
{
    memset(cache, -1, sizeof cache);
    //if (sticker.size() == 1) return sticker[0];
    return max(maxSum(sticker,0,1),maxSum(sticker,1,0));
}
