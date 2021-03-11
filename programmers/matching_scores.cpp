#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

const regex urlPattern(R"*(<head>(.|\n)*<meta property="og:url" content="https://([^<]+)"/>(.|\n)*</head>)*");
const regex linkPattern(R"*(<a href="https://([^<]+)">)*");

struct PageInfo {
    double score{}, linkScore{};
    vector<string> outLinkPages;
};

map<string,int> pageMap;
vector<PageInfo> pageInfoList;

string trim(const string& s) {
    regex trimPattern(R"(^(\s*)(.*)(\s*)$)");
    return regex_replace(s, trimPattern, "$2");
}

string extractPageUrl(const string& page) {
    smatch m;
    regex_search(page.begin(), page.end(), m, urlPattern);
    return trim(m.str(2));
}

vector<string> extractOutLink(const string& page, const string& pageUrl) {
    vector<string> ret;
    sregex_iterator pos(page.begin(), page.end(), linkPattern);
    sregex_iterator end;
    for (; pos != end; ++pos) {
        string link = trim(pos->str(1));
        if (link.empty() || link == pageUrl) continue;
        ret.push_back(link);
    }
    return ret;
}

int countWord(const string& word, const string& page) {
    regex textPattern(R"(>(([^>]|\n)*)<)");
    regex wordPattern("(^|[^[:alpha:]]+)(" + word + ")($|[^[:alpha:]]+)", regex_constants::icase);

    sregex_iterator pos(page.cbegin(), page.cend(), textPattern);
    sregex_iterator end;

    int ret = 0;
    for (; pos != end; ++pos) {
        string text = trim(pos->str(1));
        auto pos=text.cbegin(), end=text.cend();
        smatch m;
        for (; regex_search(pos,end,m,wordPattern); pos=m[2].second) {
            ++ret;
        }
    }
    return ret;
}

int solution(string word, vector<string> pages) {
    pageInfoList = vector<PageInfo>(pages.size());
    for (int i = 0; i < pages.size(); ++i) {
        string url = extractPageUrl(pages[i]);
        if (url.empty()) continue;

        pageMap[url] = i;
        PageInfo& pageInfo = pageInfoList[i];
        pageInfo.score = countWord(word, pages[i]);
        pageInfo.outLinkPages = extractOutLink(pages[i], url);
    }

    for (int i = 0; i < pageInfoList.size(); ++i) {
        vector<string>& outLinkPages = pageInfoList[i].outLinkPages;
        sort(outLinkPages.begin(), outLinkPages.end());
        outLinkPages.erase(unique(outLinkPages.begin(), outLinkPages.end()), outLinkPages.end());
    }

    for (int i = 0; i < pageInfoList.size(); ++i) {
        double linkScore = 0;
        if (pageInfoList[i].outLinkPages.size() > 0)
            linkScore = pageInfoList[i].score / static_cast<double>(pageInfoList[i].outLinkPages.size());

        for (int j = 0; j < pageInfoList[i].outLinkPages.size(); ++j) {
            string link = pageInfoList[i].outLinkPages[j];
            if (pageMap.count(link) == 0) continue;
            pageInfoList[pageMap[link]].linkScore += linkScore;
        }
    }

    int maxMatchingIdx = 0;
    double maxMatchingValue = pageInfoList[0].score + pageInfoList[0].linkScore;
    for (int i = 1; i < pageInfoList.size(); ++i) {
        double candidate = pageInfoList[i].score + pageInfoList[i].linkScore;
        if (maxMatchingValue < candidate) {
            maxMatchingValue = candidate;
            maxMatchingIdx = i;
        }
    }
    return maxMatchingIdx;
}
