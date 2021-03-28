n = int(input())

adj = [[] for _ in range(n+1)]
for _ in range(n):
    u,*adj_list,sentinel = map(int,input().split())
    m = len(adj_list)-1
    for i in range(0,m,2):
        adj[u].append((adj_list[i],adj_list[i+1]))

max_distance = 0
def dfs(u,visited):
    global adj,max_distance
    visited[u] = True
    first,second = 0,-1
    for v,cost in adj[u]:
        if not visited[v]:
            cost += dfs(v,visited)
            if cost > first:
                second = first
                first = cost
            elif cost > second:
                second = cost

    if second != -1:
        max_distance = max(max_distance,first+second)
    return first

visited = [False]*(n+1)
dfs(u,visited)
print(max_distance)

