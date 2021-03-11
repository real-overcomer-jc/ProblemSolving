def solution(n, s, a, b, fares):
    INF = int(1e9)
    graph = [[INF]*(n+1) for _ in range(n+1)]
    for c,d,f in fares:
        graph[c][d] = f
        graph[d][c] = f
        
    for i in range(1,n+1):
        graph[i][i] = 0
        
    for k in range(1,n+1):
        for i in range(1,n+1):
            for j in range(1,n+1):
                graph[i][j] = min(graph[i][j],graph[i][k]+graph[k][j])
    
    min_cost = graph[s][a]+graph[s][b]
    for k in range(1,n+1):
        min_cost = min(min_cost,graph[s][k]+graph[k][a]+graph[k][b])
    return min_cost
