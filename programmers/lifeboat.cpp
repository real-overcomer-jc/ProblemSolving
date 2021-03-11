#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    sort(people.begin(), people.end());
    
    int count = 0, start = 0, end = people.size()-1;
    while (start < end) {
        if (people[start] + people[end] <= limit) ++start, --end;
        else --end;
        ++count;        
    }
    return count + (start == end);
}
