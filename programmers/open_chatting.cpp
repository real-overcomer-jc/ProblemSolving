nclude <string>
#include <vector>
#include <map>

using namespace std;

vector<string> parseRecord(const string& columns) {
    vector<string> userinfo;
    auto begin = columns.find_first_not_of(" ");
    auto end = string::npos;
    while (begin != string::npos) {
        end = columns.find_first_of(" ", begin);
        if (end == string::npos) {
            end = columns.size();
        }
        userinfo.push_back(columns.substr(begin, end-begin));
        begin = columns.find_first_not_of(" ", end);
    }
    return userinfo;
}

vector<string> solution(vector<string> record) {
    map<string, string> nicknameMap;
    for (const string& line : record) {
        vector<string> userinfo = parseRecord(line);
        if (userinfo[0] == "Enter" || userinfo[0] == "Change")
            nicknameMap[userinfo[1]] = userinfo[2];
    }
    
    vector<string> ret;
    for (int i = 0; i < record.size(); ++i) {
        vector<string> userinfo = parseRecord(record[i]);
        if (userinfo[0] != "Enter" && userinfo[0] != "Leave") continue;
        
        string message = nicknameMap[userinfo[1]];
        message += "님이 ";
        if (userinfo[0] == "Enter") {
            message += "들어왔습니다.";
        } else if (userinfo[0] == "Leave") {
            message += "나갔습니다.";
        }
        ret.push_back(message);
    }
    return ret;
}
