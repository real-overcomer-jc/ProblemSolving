for _ in range(int(input())):
    n = int(input())
    positions = []
    for _ in range(n+2):
        y,x = map(int,input().split())
        positions.append((y,x))

    INF = int(1e9)
    adj = [[INF]*(n+2) for _ in range(n+2)]
    for i in range(n+2):
        for j in range(n+2):
            y1,x1 = positions[i]
            y2,x2 = positions[j]
            dist = abs(y1-y2)+abs(x1-x2)
            if dist <= 1000:
                adj[i][j] = adj[j][i] = dist

    for k in range(n+2):
        for i in range(n+2):
            if adj[i][k] == INF:
                continue
            for j in range(n+2):
                adj[i][j] = min(adj[i][j],adj[i][k]+adj[k][j])

    if adj[0][n+1] != INF:
        print('happy')
    else:
        print('sad')



            






