n,m = map(int,input().split())

board = []
for _ in range(n):
    board.append(list(map(int,input().split())))

max_total = 0

shapes = [[(0,0),(-1,0),(1,0),(0,1)],[(0,0),(0,-1),(0,1),(-1,0)],[(0,0),(-1,0),(1,0),(0,-1)],[(0,0),(0,-1),(0,1),(1,0)]]

def dfs(board,y,x,visited,count,total):
    global n,m,max_total
    if count == 4:
        max_total = max(max_total,total)
        return
    
    visited[y][x] = True
    for dy,dx in (-1,0),(1,0),(0,-1),(0,1):
        ny,nx = y+dy,x+dx
        if 0 <= ny < n and 0 <= nx < m and not visited[ny][nx]:
            dfs(board,ny,nx,visited,count+1,total+board[ny][nx])
    visited[y][x] = False

def check(board,y,x):
    global n,m,max_total
    for positions in shapes:
        total = 0
        for dy,dx in positions:
            ny,nx = y+dy,x+dx
            if not (0 <= ny < n and 0 <= nx < m):
                total = 0 
                break
            total += board[ny][nx]
        max_total = max(max_total,total)

visited = [[False]*m for _ in range(n)]
for i in range(n):
    for j in range(m):
        dfs(board,i,j,visited,1,board[i][j])
        check(board,i,j)

print(max_total)



