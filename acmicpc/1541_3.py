cache = [[-1]*51 for _ in range(51)]

def evaluate(expr,start,end):
    global cache
    if cache[start][end] != -1:
        return cache[start][end]

    result = float('inf')
    count = 0
    pos = start 
    next_pos = -1
    while True:
        next_pos = max(expr.find('+',pos,end),expr.find('-',pos,end))
        if next_pos == -1:
            break

        op = expr[next_pos]
        lhs = evaluate(expr,start,next_pos)
        rhs = evaluate(expr,next_pos+1,end)
        if op == '+':
            result = min(result,lhs+rhs)
        else:
            result = min(result,lhs-rhs)
        count += 1
        pos = next_pos+1

    if count == 0:
        literal = expr[start:end]
        result = int(literal) if literal else 0
    cache[start][end] = result
    return result

expr = input()
print(evaluate(expr,0,len(expr)))

