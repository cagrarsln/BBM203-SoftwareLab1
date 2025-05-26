#include <fstream>
#include <sstream>
#include "Network.h"

Network::Network() {

}

void Network::process_commands(vector<Client> &clients, vector<string> &commands, int message_limit,
                      const string &sender_port, const string &receiver_port) {
    // TODO: Execute the commands given as a vector of strings while utilizing the remaining arguments.
    /* Don't use any static variables, assume this method will be called over and over during testing.
     Don't forget to update the necessary member variables after processing each command. For example,
     after the MESSAGE command, the outgoing queue of the sender must have the expected frames ready to send. */
}

vector<Client> Network::read_clients(const string &filename) {
    vector<Client> clients;
    // TODO: Read clients from the given input file and return a vector of Client instances.
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File could not be opened." << endl;
        return clients;
    }
    int number_of_clients;
    file >> number_of_clients;
    for (int i = 0; i < number_of_clients; i++) {
        string client_id;
        string client_ip;
        string client_mac;
        file >> client_id >> client_ip >> client_mac;
        Client new_client(client_id, client_ip, client_mac);
        clients.push_back(new_client);
    }
    file.close();
    return clients;
}

void Network::read_routing_tables(vector<Client> &clients, const string &filename) {
    // TODO: Read the routing tables from the given input file and populate the clients' routing_table member variable.
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File could not be opened." << endl;
        return;
    }
    string line;
    int client_index = 0;
    while (getline(file, line)) {
        if (line == "-") {
            client_index++;
            continue;
        }
        istringstream iss(line);
        string client_id, next_hop_id;
        iss >> client_id >> next_hop_id;

        clients[client_index].routing_table[client_id] = next_hop_id;
    }
    file.close();
}

// Returns a list of token lists for each command
vector<string> Network::read_commands(const string &filename) {
    vector<string> commands;
    // TODO: Read commands from the given input file and return them as a vector of strings.
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File could not be opened." << endl;
        return commands;
    }
    int number_of_commands;
    file >> number_of_commands;

    string line;
    getline(file, line);

    for (int i = 0; i < number_of_commands; i++) {
        getline(file, line);
        commands.push_back(line);
    }
    file.close();
    return commands;
}

Network::~Network() {
    // TODO: Free any dynamically allocated memory if necessary.
}
