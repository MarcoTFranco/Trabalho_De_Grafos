#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

const char delimiter = ':'; // Delimitador entre a palavra-chave e o valor

struct TSPProblem
{
    string type;
    int dimension;
    string edgeWeightType;
    string displayDataType;
    map<int, pair<double, double>> node;
};

bool checkKeyword(string keyword, string value, TSPProblem &problem)
{
    if (keyword == "TYPE")
    {
        if (value == "TSP" || value == "ATSP")
        {
            problem.type = value;
        }
        else
        {
            cout << keyword << " não suportado." << endl;
            return false;
        }
    }
    else if (keyword == "DIMENSION")
    {
        problem.dimension = stoi(value);
    }
    else if (keyword == "EDGE_WEIGHT_TYPE")
    {
        if (value == "GEO")
        {
            problem.edgeWeightType = value;
        }
        else if (value == "EUC_2D")
        {
            problem.edgeWeightType = value;
        }
        else
        {
            cout << keyword << " não suportado." << endl;
            return false;
        }
    }
    else if (keyword == "DISPLAY_DATA_TYPE")
    {
        if (value == "COORD_DISPLAY")
        {
            problem.displayDataType = value;
        }
        else
        {
            cout << keyword << " não suportado." << endl;
            return false;
        }
    }
    else
    {
        cout << "Erro: Palavra-chave desconhecida " << keyword << endl;
        return false;
    }
    return true;
}

string trim(string s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char c)
                         { return !std::isspace(c); })
                .base(),
            s.end());
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c)
                                    { return !std::isspace(c); }));
    return s;
}

void readInstance(TSPProblem &problem)
{
    string line;
    while (getline(cin, line))
    {
        if (line == "NODE_COORD_SECTION")
        {
            break;
        }
        if (line.find(delimiter) != std::string::npos)
        {
            string keyword = line.substr(0, line.find(delimiter));
            string value = line.substr(line.find(delimiter) + 1, line.npos);

            if (!checkKeyword(trim(keyword), trim(value), problem))
            {
                break;
            }
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
        double x, y;
        ss >> id >> x >> y;
        problem.node[id] = make_pair(x, y);
    }
}

void printInstance(TSPProblem &problem)
{
    cout << "TYPE: " << problem.type << endl;
    cout << "DIMENSION: " << problem.dimension << endl;
    cout << "EDGE_WEIGHT_TYPE: " << problem.edgeWeightType << endl;
    cout << "DISPLAY_DATA_TYPE: " << problem.displayDataType << endl;
    cout << "NODE_COORD_SECTION" << endl;
    for (auto &p : problem.node)
    {
        cout << p.first << " " << p.second.first << " " << p.second.second << endl;
    }
}

int main()
{
    TSPProblem problem;
    readInstance(problem);
    printInstance(problem);
    return 0;
}