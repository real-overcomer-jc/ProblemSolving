n = int(input())
board = []
for _ in range(n):
    board.append(list(map(int,input())))

def dfs(board,y,x,size):
    allMatched = True 
    value = board[y][x]
    for i in range(y,y+size):
        for j in range(x,x+size):
            if board[i][j] != value:
                allMatched = False
                break
        if not allMatched:
            break

    if allMatched:
        return str(value)

    half = size // 2
    res = '('
    res += dfs(board,y,x,half)
    res += dfs(board,y,x+half,half)
    res += dfs(board,y+half,x,half)
    res += dfs(board,y+half,x+half,half)
    res += ')'
    return res

compressed = dfs(board,0,0,n)
print(compressed)
