#include "GroupClient.h"
#include <grpcpp/grpcpp.h>
#include "mimicked_mpi.grpc.pb.h"
#include "GroupServer.h"
#include <thread>

class GroupServiceImpl final : public mimicked_mpi::GroupService::Service {
public:
    explicit GroupServiceImpl(GroupServer& group_server)
        : group_server_(group_server) {}

    grpc::Status CreateGroup(grpc::ServerContext* context,
                             const mimicked_mpi::CreateGroupRequest* request,
                             mimicked_mpi::CreateGroupResponse* response) override {
        std::vector<int> ranks(request->ranks().begin(), request->ranks().end());
        int group_id = group_server_.CreateGroup(request->comm_rank(), ranks);
        response->set_group_id(group_id);
        return grpc::Status::OK;
    }

    grpc::Status FreeGroup(grpc::ServerContext* context,
                           const mimicked_mpi::FreeGroupRequest* request,
                           mimicked_mpi::FreeGroupResponse* response) override {
        bool success = group_server_.FreeGroup(request->group_id());
        response->set_success(success);
        return grpc::Status::OK;
    }

private:
    GroupServer& group_server_;
};

void RunServer() {
    std::string server_address("0.0.0.0:3000");
    GroupServer group_server;
    GroupServiceImpl service(group_server);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main( int argc, char* argv[] ) 
{
    std::thread server_thread(RunServer);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    GroupClient client(grpc::CreateChannel("localhost:3000", grpc::InsecureChannelCredentials()));

    // Mimicing MPI_Comm_group_create().
    std::vector<int> ranks = {0, 1, 2};
    int group_id = client.CreateGroup(0, ranks);
    std::cout << "Created group with ID: " << group_id << std::endl;

    // Mimicing MPI_Group_free().
    bool success = client.FreeGroup(group_id);
    if (success) 
    {
        std::cout << "Freed group with ID: " << group_id << std::endl;
    } 
    else
    {
        std::cout << "Failed to free group with ID: " << group_id << std::endl;
    }
  
    server_thread.join();

    return 0;
}
