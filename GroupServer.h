#include <iostream>
#include <string>
#include <vector>
#include<map>

class GroupServer {
public:
    int CreateGroup(int comm_rank, const std::vector<int>& ranks);
    bool FreeGroup(int group_id);

private:
    std::map<int, std::vector<int>> groups_;
    int next_group_id_ = 0;
};
