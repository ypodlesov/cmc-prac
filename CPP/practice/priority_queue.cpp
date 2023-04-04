#include <queue>
#include <iostream>
#include <vector>

class cmp {
  public:
    bool operator ()(const std::pair<int,int> &a, const std::pair<int,int> &b) {
        return a.first > b.first;
    }
};

int main() {
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, cmp> q{};
    q.push(std::make_pair(5, 2));
    q.push(std::make_pair(4, 3));
    q.push(std::make_pair(3, 1));
    q.push(std::make_pair(1, 4));
    q.push(std::make_pair(2, 3));
    while (!q.empty()) {
        auto tmp = q.top();
        std::cout << tmp.first << ' ' << tmp.second << std::endl;
        q.pop();
    }
}
