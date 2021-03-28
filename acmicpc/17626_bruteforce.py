n = int(input())
sqrtn = int(n**0.5)
one_square = {i*i for i in range(1,sqrtn+1)}
two_square = {i+j for i in one_square for j in one_square if i+j <= n}

#print(one_square)
#print(two_square)

if n in one_square:
    print(1)
elif n in two_square:
    print(2)
else:
    found = False
    for square in one_square:
        if n-square in two_square:
            print(3)
            found = True
            break

    if not found:
        print(4)



