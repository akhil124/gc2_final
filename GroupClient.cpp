#include "GroupClient.h"

GroupClient::GroupClient(std::shared_ptr<grpc::Channel> channel)
    : stub_(mimicked_mpi::GroupService::NewStub(channel)) {}

int GroupClient::CreateGroup(int comm_rank, const std::vector<int>& ranks) {
    mimicked_mpi::CreateGroupRequest request;
    request.set_comm_rank(comm_rank);
    for (int rank : ranks) {
        request.add_ranks(rank);
    }

    mimicked_mpi::CreateGroupResponse response;
    grpc::ClientContext context;
    grpc::Status status = stub_->CreateGroup(&context, request, &response);

    if (status.ok()) {
        return response.group_id();
    } else {
        return -1;
    }
}

bool GroupClient::FreeGroup(int group_id) {
    mimicked_mpi::FreeGroupRequest request;
    request.set_group_id(group_id);

    mimicked_mpi::FreeGroupResponse response;
    grpc::ClientContext context;
    grpc::Status status = stub_->FreeGroup(&context, request, &response);

    if (status.ok()) {
        return response.success();
    } else {
        return false;
    }
}
