#include <string>
#include <vector>
#include <cstring>

using namespace std;

//dp[i] : i번째 집까지 훔칠 수 있는 최대 금액
//dp[i] = max(dp[i-1], money[i] + dp[i-2])
//dp1은 첫번째 집을 도둑질하는 경우, dp2는 그렇지 않은 경우
int dp1[1000001], dp2[1000001];

int solution(vector<int> money) {
    memset(dp1, 0, sizeof dp1);
    memset(dp2, 0, sizeof dp2);
    
    dp1[0] = money[0], dp1[1] = dp1[0];
    for (int i = 2; i < money.size()-1; ++i) {
        dp1[i] = max(dp1[i-1], money[i] + dp1[i-2]);
    }
    
    dp2[1] = money[1];
    for (int i = 2; i < money.size(); ++i) {
        dp2[i] = max(dp2[i-1], money[i] + dp2[i-2]);
    }
    
    return max(dp1[money.size()-2],dp2[money.size()-1]);
}
