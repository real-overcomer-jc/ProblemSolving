#include <cmath>

using namespace std;

int count(int n, int plus) {
    if (n == 1) return plus ? 0 : 1;
    if (n <= 0 || 2*log(n)/log(3) < plus) return 0; 

    int ret = count(n-1,plus+1);
    if (plus >= 2) {
        if (n % 3 == 0) ret += count(n/3, plus-2);
    } 
    return ret;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n) {
    return count(n,0);
}
