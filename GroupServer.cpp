#include "GroupServer.h"

int GroupServer::CreateGroup(int comm_rank, const std::vector<int>& ranks) {
    int group_id = next_group_id_++;
    groups_[group_id] = ranks;
    return group_id;
}

bool GroupServer::FreeGroup(int group_id) {
    auto it = groups_.find(group_id);
    if (it == groups_.end()) {
        return false;
    }

    groups_.erase(it);
    return true;
}
