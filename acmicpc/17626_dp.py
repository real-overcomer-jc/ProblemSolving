n = int(input())

dp = [-1]*(n+1)
dp[0] = 0
dp[1] = 1
for i in range(2,n+1):
    min_count = float('inf')
    for j in range(1,int(i**0.5)+1):
        min_count = min(min_count,dp[i-j*j])
    dp[i] = min_count+1

print(dp[i])
