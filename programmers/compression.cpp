#include <string>
#include <vector>
#include <cstring>
#include <limits>

using namespace std;

int compress(const string& s, int chunkSize) {
    const int n = s.size();
    string compressed;
    int i = 0;
    while (i < n) {
        int count = 1;
        while (i+chunkSize < n && strncmp(s.c_str()+i+chunkSize, s.c_str()+i, chunkSize) == 0) {
            ++count; 
            i += chunkSize;
        }
        if (count > 1) compressed += to_string(count);
        compressed += s.substr(i, chunkSize);
        i += chunkSize;
    }
    return compressed.size();
}

int solution(string s) {
    int shortest = numeric_limits<int>::max();
    for (int chunkSize = 1; chunkSize <= ((s.size()+1) >> 1); ++chunkSize) {
        shortest = min(shortest, compress(s, chunkSize));
    }
    return shortest;
}
