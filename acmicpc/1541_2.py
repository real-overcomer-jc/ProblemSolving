import re

p = re.compile(r'[\-\+]')
def evaluate(expr):
    global p
    result = float('inf')
    count = 0
    for m in p.finditer(expr):
        op = m.group()
        pos = m.start()
        lhs = evaluate(expr[:pos])
        rhs = evaluate(expr[pos+1:])
        if op == '+':
            result = min(result,lhs+rhs)
        else:
            result = min(result,lhs-rhs)
        count += 1

    if count == 0:
        return int(expr)
    return result

print(evaluate(input()))


