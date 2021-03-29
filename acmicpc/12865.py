import sys
input = sys.stdin.readline

n,k = map(int,input().split())

data = []
for _ in range(n):
    data.append(map(int,input().split()))

dp = [-1]*(k+1)
dp[0] = 0 #무게 i일 때 최대 가치
for w,v in data:
    for i in range(k-w,-1,-1):
        if dp[i] != -1:
            dp[i+w] = max(dp[i+w],dp[i]+v)

print(max(dp))


    
