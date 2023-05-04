
****Mimicking MPI Functions Using gRPC****

<br> This project demonstrates how to mimic the behavior of MPI_Comm_group_create() and MPI_Group_free() operations using gRPC. It simulates creating and freeing groups of processes, just like the actual MPI functions, but using gRPC as the underlying communication mechanism. </br>

****Program Overview****

<br> The program consists of the following components: </br>

**gRPC Service Definition**: A .proto file that defines a gRPC service called GroupService with two RPC methods: CreateGroup and FreeGroup. It also defines the request and response message types for each method.

**GroupServer**: A C++ class that manages the groups internally. It has two methods, CreateGroup and FreeGroup, that create and free groups and maintain them in a data structure.

**GroupClient**: A C++ class that communicates with the gRPC server using the defined GroupService. It has methods CreateGroup and FreeGroup that send requests to the server and handle the responses.

**GroupServiceImpl**: A C++ class that inherits from the gRPC service generated from the .proto file. This class acts as the server-side implementation of the service. It uses the GroupServer class to perform group management tasks when it receives requests from clients.

**gRPC Server**: A C++ function that starts a gRPC server, binds it to a network address, and registers the GroupServiceImpl as the service handler. The server listens for incoming client requests and processes them using the service implementation.

**Main Function**: A C++ function that starts the gRPC server in a separate thread, creates a GroupClient instance, and uses it to mimic MPI_Comm_group_create() and MPI_Group_free() operations. Finally, it stops the gRPC server.

****Code Flow****

**Defined gRPC service**: Creating a .proto file that defines the gRPC service and the message types for request and response.

**Implement GroupServer**: Creating a GroupServer class that manages groups internally using methods CreateGroup and FreeGroup.

**Implement GroupClient**: Creating a GroupClient class that communicates with the gRPC server using the defined GroupService. Implemented the methods CreateGroup and FreeGroup that send requests and handle responses.

**Implement GroupServiceImpl**: Creating a GroupServiceImpl class that inherits from the generated GroupService::Service class. Overridden the RPC methods CreateGroup and FreeGroup to handle client requests and used the GroupServer for group management.

**Run gRPC server**: Implemented a RunServer function that starts a gRPC server, setted up the GroupServiceImpl, and waited for incoming client requests.

**Main function**: Started the gRPC server in a separate thread, created a GroupClient instance, and used it to mimic MPI_Comm_group_create() and MPI_Group_free() operations.
