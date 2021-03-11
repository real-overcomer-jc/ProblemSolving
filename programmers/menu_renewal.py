from itertools import combinations

def count_in_orders(orders,candidate):
    count = 0
    for order in orders:
        if set(candidate) <= set(order):
            count += 1
    return count

def solution(orders, course):
    answer = []
    for i in range(len(orders)):
        orders[i] = "".join(sorted(orders[i]))
        
    for n in course:
        selected = []
        max_count = 2
        for order in orders:
            for candidate in combinations(order,n):
                count = count_in_orders(orders,candidate)
                candidate = "".join(candidate)
                if count > max_count:
                    selected = [candidate]
                    max_count = count
                elif count == max_count:
                	selected.append(candidate)
        answer.extend(selected) 
    return sorted(set(answer))
