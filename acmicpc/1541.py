terms = list(input().split('-'))

result = 0
for i,term in enumerate(terms):
    values = term.split('+')
    total = 0
    for value in values:
        total += int(value)

    if i == 0:  
        total = -total
    result -= total 

print(result)



        
