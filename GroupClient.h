#include <string>
#include <vector>
#include <grpcpp/grpcpp.h>
#include "mimicked_mpi.grpc.pb.h"

class GroupClient {
public:
    GroupClient(std::shared_ptr<grpc::Channel> channel);
    int CreateGroup(int comm_rank, const std::vector<int>& ranks);
    bool FreeGroup(int group_id);

private:
    std::unique_ptr<mimicked_mpi::GroupService::Stub> stub_;
};
