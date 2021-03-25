n = int(input())

adj = [[] for _ in range(n+1)]
for _ in range(n-1):
    u,v,cost = map(int,input().split())
    adj[u].append((v,cost))

longest = 0
def dfs(u):
    global longest
    if not adj[u]:
        return 0

    heights = []
    for v,cost in adj[u]:
        cost += dfs(v)
        heights.append(cost)
    heights.sort(reverse = True)

    if len(heights) > 1:
        longest = max(longest,heights[0]+heights[1])

    return heights[0]

h = dfs(1)
print(max(h,longest))

