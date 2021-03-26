from collections import deque

n = int(input())

board = []
for _ in range(n):
    board.append(list(map(int,input())))

def bfs(board,y,x):
    n = len(board) 
    q = deque([(y,x)])
    board[y][x] = 0
    count = 1
    while q:
        y,x = q.popleft()
        for dy,dx in (-1,0),(1,0),(0,-1),(0,1):
            ny,nx = y+dy,x+dx
            if 0 <= ny < n and 0 <= nx < n and board[ny][nx] == 1:
                board[ny][nx] = 0
                count += 1
                q.append((ny,nx))
    return count

component_count = 0
result = []
for i in range(n):
    for j in range(n):
        if board[i][j] == 1:
            component_count += 1
            count = bfs(board,i,j)
            result.append(count)
result.sort()

print(component_count)
print(*result,sep='\n')




