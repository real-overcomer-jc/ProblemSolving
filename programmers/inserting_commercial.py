def time_to_sec(time):
    hh,mm,ss = map(int,time.split(":"))
    return hh*3600+mm*60+ss

def sec_to_time(ss):
    hh = str(ss//3600).zfill(2)
    ss %= 3600
    mm = str(ss//60).zfill(2)
    ss %= 60
    ss = str(ss).zfill(2)
    return ":".join([hh,mm,ss])
    
    
def solution(play_time, adv_time, logs):
    play_time_sec = time_to_sec(play_time)
    adv_time_sec = time_to_sec(adv_time)
    
    total_time = [0]*(play_time_sec+1)
    
    for log in logs:
        start_time_sec,end_time_sec = map(time_to_sec,log.split("-"))
        total_time[start_time_sec] += 1
        total_time[end_time_sec] -= 1
        
    for i in range(1,play_time_sec+1):
        total_time[i] = total_time[i] + total_time[i-1]
    
    for i in range(1,play_time_sec+1):
        total_time[i] = total_time[i] + total_time[i-1]
        
    max_acc_time = total_time[adv_time_sec-1]
    adv_start_time = 0
    
    for i in range(adv_time_sec,play_time_sec+1):
        acc_time = total_time[i] - total_time[i-adv_time_sec]
        if max_acc_time < acc_time:
            max_acc_time = acc_time
            adv_start_time = i-adv_time_sec+1
    
    return sec_to_time(adv_start_time)
