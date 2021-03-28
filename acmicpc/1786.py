t = input()
p = input()

def get_fail_func(p):
    m = len(p)
    f = [-1]*m
    matched = 0
    for i in range(1,m):
        while matched > 0 and p[i] != p[matched]:
            matched = f[matched-1]+1

        if p[i] == p[matched]:
            f[i] = matched
            matched += 1
    return f

def kmp_search(t,p):
    n = len(t)
    m = len(p)
    f = get_fail_func(p)
    result = []
    matched = 0
    for i in range(n):
        while matched > 0 and t[i] != p[matched]:
            matched = f[matched-1]+1

        if t[i] == p[matched]:
            matched += 1
            if matched == m:
                result.append(i-m+1)
                matched = f[matched-1]+1
    return result

result = kmp_search(t,p)
print(len(result))
for i in result:
    print(i+1)

