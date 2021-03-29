from collections import deque
import sys

input = sys.stdin.readline
n,m = map(int,input().strip().split())

board = []
for i in range(n):
    board.append(list(map(int,input().strip())))

INF = float('inf')
def bfs(board,y,x):
    n = len(board)
    m = len(board[0])

    distance = [[[INF,INF] for _ in range(m)] for _ in range(n)]
    #distance = [[[INF,INF]]*m for _ in range(n)]
    distance[y][x][0] = 1

    q = deque([(0,y,x)])
    while q:
        count,y,x = q.popleft()
        for dy,dx in (-1,0),(1,0),(0,-1),(0,1):
            ny,nx = y+dy,x+dx
            if 0 <= ny < n and 0 <= nx < m:
                if distance[ny][nx][count] != INF:
                    continue
                if board[ny][nx] == 1 and count == 0:
                    distance[ny][nx][1] = distance[y][x][count]+1
                    q.append((1,ny,nx))
                if board[ny][nx] == 0:
                    distance[ny][nx][count] = distance[y][x][count]+1
                    q.append((count,ny,nx))

    return min(distance[n-1][m-1])

best = bfs(board,0,0)
print(best if best != INF else -1)



