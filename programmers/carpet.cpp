#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    int width = (brown/2)-1, height = 3;
    while (height <= width) {
        if (height*width - yellow == brown) break;
        ++height, --width; 
    }
    return {width,height};
}
