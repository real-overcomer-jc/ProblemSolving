from bisect import bisect_left

def solution(info, query):
    answer = []
    query_dict = {}
    for x in info:
        tokens = list(x.split())
        score = int(tokens[-1])
        
        #make possible queries from info
        for c1 in tokens[0],"-":
            for c2 in tokens[1],"-":
                for c3 in tokens[2],"-":
                    for c4 in tokens[3],"-":
                        q = c1+c2+c3+c4
                        query_dict.setdefault(q,[]).append(score)
                        
    for key in query_dict:
        query_dict[key].sort()
        
    for q in query:
        tokens = q.replace(" and ","").split()
        q = tokens[0]
        score = int(tokens[1])
        
        if q not in query_dict:
            answer.append(0)
            continue
            
        score_list = query_dict[q]
        count = len(score_list)-bisect_left(score_list,score)
       	answer.append(count)
        
    return answer
