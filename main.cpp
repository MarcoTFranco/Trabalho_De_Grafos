#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <fstream>

using namespace std;

// TSP- Insercao Mais Proxima

int main()
{
    string line;
    string type, edge_weight_type, display_data_type;
    int dimension;
    map<int, pair<double, double>> nodes;
    map<int, vector<pair<int, double>>> adjacencyList; // Lista de adjacência

    while (getline(cin, line))
    {
        if (line.find("TYPE:") != string::npos)
        {
            type = line.substr(line.find(":") + 2);
        }
        else if (line.find("DIMENSION:") != string::npos)
        {
            dimension = stoi(line.substr(line.find(":") + 2));
        }
        else if (line.find("EDGE_WEIGHT_TYPE:") != string::npos)
        {
            edge_weight_type = line.substr(line.find(":") + 2);
        }
        else if (line.find("DISPLAY_DATA_TYPE:") != string::npos)
        {
            display_data_type = line.substr(line.find(":") + 2);
        }
        else if (line == "NODE_COORD_SECTION")
        {
            break;
        }
    }

    while (getline(cin, line))
    {
        if (line == "EOF")
        {
            break;
        }
        stringstream ss(line);
        int id;
        double latitude, longitude;
        ss >> id >> latitude >> longitude;
        nodes[id] = {latitude, longitude};
    }

    cout << "Lendo os dados:\n";
    cout << "TYPE: " << type << endl;
    cout << "DIMENSION: " << dimension << endl;
    cout << "EDGE_WEIGHT_TYPE: " << edge_weight_type << endl;
    cout << "DISPLAY_DATA_TYPE: " << display_data_type << endl;

    for (const auto &node : nodes)
    {
        cout << node.first << " " << node.second.first << " " << node.second.second << endl;
    }

    return 0;
}