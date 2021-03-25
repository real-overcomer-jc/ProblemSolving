n,r,c = map(int,input().split())

n = 2**n
result = -1
def dfs(y,x,size,no):
    global r,c,counter,result
    if not (y <= r < y+size and x <= c < x+size): 
        return
    if size == 2:
        for i in range(y,y+2):
            for j in range(x,x+2):
                if i == r and j == c:
                    result = no
                    return
                no += 1
        return

    half = size // 2
    blocks = half*half
    dfs(y,x,half,no)
    dfs(y,x+half,half,no+blocks)
    dfs(y+half,x,half,no+blocks*2)
    dfs(y+half,x+half,half,no+blocks*3)

dfs(0,0,n,0)
print(result)
