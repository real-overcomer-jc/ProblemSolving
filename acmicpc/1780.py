n = int(input())

board = []
for _ in range(n):
    board.append(list(map(int,input().split())))

result = [0]*3
def dfs(board,y,x,size):
    global n,result
    
    value = board[y][x]
    allMatched = True
    for i in range(y,y+size):
        for j in range(x,x+size):
            if board[i][j] != value:
                allMatched = False
                break
        if not allMatched:
            break

    if allMatched:
        result[value+1] += 1
        return

    new_size = size // 3
    for i in range(y,y+new_size*2+1,new_size):
        for j in range(x,x+new_size*2+1,new_size):
            dfs(board,i,j,new_size)

    '''
    dfs(board,y,x,new_size)
    dfs(board,y,x+new_size,new_size)
    dfs(board,y,x+new_size*2,new_size)
    dfs(board,y+new_size,x,new_size)
    dfs(board,y+new_size,x+new_size,new_size)
    dfs(board,y+new_size,x+new_size*2,new_size)
    dfs(board,y+new_size*2,x,new_size)
    dfs(board,y+new_size*2,x+new_size,new_size)
    dfs(board,y+new_size*2,x+new_size*2,new_size)
    '''

dfs(board,0,0,n)
print(*result,sep='\n')




