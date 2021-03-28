from collections import deque

n = int(input())

board = []
start = (-1,-1)
size = 2
for i in range(n):
    row = list(map(int,input().split()))
    for j in range(n):
        if row[j] == 9:
            start = (i,j)
            row[j] = 0
    board.append(row)

INF = int(1e9)
def bfs(board,y,x):
    global size
    n = len(board)
    distance = [[INF]*n for _ in range(n)]
    q = deque([(y,x)])
    distance[y][x] = 0
    while q:
        y,x = q.popleft()
        for dy,dx in (-1,0),(1,0),(0,-1),(0,1):
            ny,nx = y+dy,x+dx
            if 0 <= ny < n and 0 <= nx < n and board[ny][nx] <= size:
                if distance[ny][nx] == INF:
                    distance[ny][nx] = distance[y][x]+1
                    q.append((ny,nx))
    return distance

time = 0
eat_count = 0
y,x = start
while True:
    distance = bfs(board,y,x)
    min_dist = INF
    min_pos = (-1,-1)
    for i in range(n):
        for j in range(n):
            if min_dist > distance[i][j] and 0 < board[i][j] < size:
                min_dist = distance[i][j]
                min_pos = (i,j)

    if min_dist == INF:
        break

    y,x = min_pos
    board[y][x] = 0

    eat_count += 1
    if eat_count == size:
        eat_count = 0
        size += 1

    time += min_dist

print(time)

