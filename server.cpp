#include <iostream>
#include <boost/asio.hpp> // Boost.Asio for networking
#include <string>

using boost::asio::ip::tcp;

int main() {
    try {
        // Step 1: Create an IO context
        boost::asio::io_context io_context;

        // Step 2: Create an acceptor to listen on a port
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345)); // Port 12345

        std::cout << "Server is running and waiting for connections on port 12345...\n";

        while (true) {
            // Step 3: Create a socket for communication
            tcp::socket socket(io_context);

            // Step 4: Wait and accept a new connection
            acceptor.accept(socket);

            std::cout << "New connection received from: " << socket.remote_endpoint() << "\n";

            // Step 5: Communicate with the client
            std::string message = "Welcome to the server! Type 'exit' to close the connection.\n";
            boost::asio::write(socket, boost::asio::buffer(message));

            char buffer[1024];
            while (true) {
                std::memset(buffer, 0, sizeof(buffer)); // Clear the buffer
                size_t bytes = socket.read_some(boost::asio::buffer(buffer));

                std::string received_message(buffer, bytes);
                std::cout << "Client: " << received_message;

                if (received_message == "exit\n") {
                    std::cout << "Client disconnected.\n";
                    break;
                }

                // Echo the message back to the client
                boost::asio::write(socket, boost::asio::buffer("Server: " + received_message));
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
