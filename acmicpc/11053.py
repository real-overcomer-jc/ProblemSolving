n = int(input())
data = list(map(int,input().split()))

dp = [1]*n
best = 1 
for i in range(n):
    for j in range(i-1,-1,-1):
        if data[j] < data[i]:
            dp[i] = max(dp[i],dp[j]+1)
    best = max(best,dp[i])

print(best)


