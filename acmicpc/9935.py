t = input()
p = input()

n = len(t)
m = len(p)

result = ['']*n
i = 0
for j in range(n):
    result[i] = t[j]
    i += 1
    if i < m:
        continue
    
    found = True
    for k in range(m):
        if p[k] != result[i-m+k]:
            found = False
            break
    
    if found:
        i -= m

if i == 0:
    print('FRULA')
else:
    print(''.join(result[:i]))


    


