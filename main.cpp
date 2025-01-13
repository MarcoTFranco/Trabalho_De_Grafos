#include <algorithm>
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <limits>

using namespace std;

const char delimiter = ':';  // Delimitador entre a palavra-chave e o valor
const double RRR = 6378.388; // Raio da Terra em km
const double PI = 3.141592;  // Valor de PI

struct TSPProblem
{
    string type;
    int dimension;
    string edgeWeightType;
    string displayDataType;
    map<int, pair<double, double>> node;
    vector<vector<int>> adjacencyMatrix; // Matriz de adjacência com distâncias
    vector<int> cycle;
    int totalCost;
};

pair<double, double> convertToRadians(TSPProblem &problem, int i)
{
    int deg, min;
    pair<double, double> coordInRadians = make_pair(problem.node[i].first, problem.node[i].second);
    deg = round(problem.node[i].first);
    min = problem.node[i].first - deg;
    coordInRadians.first = PI * (deg + 5.0 * min / 3.0) / 180.0;
    deg = round(problem.node[i].second);
    min = problem.node[i].second - deg;
    coordInRadians.second = PI * (deg + 5.0 * min / 3.0) / 180.0;
    return coordInRadians;
}

// Calcula a distância geográfica entre dois pontos
int calculateGeographicalDistance(TSPProblem &problem, int i, int j)
{
    pair<double, double> a = convertToRadians(problem, i);
    pair<double, double> b = convertToRadians(problem, j);
    double latA = a.first;
    double lonA = a.second;
    double latB = b.first;
    double lonB = b.second;

    double q1 = cos(lonA - lonB);
    double q2 = cos(latA - latB);
    double q3 = cos(latA + latB);

    return RRR * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0;
}

// Calcula a distância euclidiana entre dois pontos
int calculateEuclideanDistance(TSPProblem &problem, int i, int j)
{
    double xd = problem.node[i].first - problem.node[j].first;
    double yd = problem.node[i].second - problem.node[j].second;
    return round(sqrt(xd * xd + yd * yd));
}

void buildAdjacencyMatrix(TSPProblem &problem)
{
    problem.adjacencyMatrix.resize(problem.dimension + 1, vector<int>(problem.dimension + 1, 0)); // Inicializa a matriz de adjacência com 0

    for (int i = 1; i <= problem.dimension; i++)
    {
        for (int j = i + 1; j <= problem.dimension; j++) // Apenas para j > i (aproveitando simetria)
        {
            int distance = 0;
            if (problem.edgeWeightType == "GEO")
            {
                distance = calculateGeographicalDistance(problem, i, j);
            }
            else if (problem.edgeWeightType == "EUC_2D")
            {
                distance = calculateEuclideanDistance(problem, i, j);
            }
            problem.adjacencyMatrix[i][j] = distance;
            problem.adjacencyMatrix[j][i] = distance; // Simetria
        }
    }
}

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

// Remove espaços à esquerda e à direita de uma string
string trim(string s)
{
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !isspace(c); }).base(), s.end()); // Remove espaços à direita
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char c){ return !isspace(c); })); // Remove espaços à esquerda
    return s; // Retorna a string sem espaços à esquerda e à direita
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

    cout << "Adjacency Matrix:" << endl;
    cout << "   ";
    for (int j = 1; j <= problem.dimension; j++)
    {
        cout << j << "   ";
    }
    cout << endl;
    for (int i = 1; i <= problem.dimension; i++)
    {
        cout << i << " ";
        for (int j = 1; j <= problem.dimension; j++)
        {
            cout << problem.adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void apply2Opt(vector<int> &cycle, const vector<vector<int>> &adjacencyMatrix, int &totalCost) {
    bool improvement = true;
    int numVertices = cycle.size() - 1; // O ciclo inclui o retorno ao ponto inicial

    while (improvement) {
        improvement = false;

        for (int i = 1; i < numVertices - 1; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                // Calcula o custo antes e depois de trocar as arestas
                int currentCost = adjacencyMatrix[cycle[i - 1]][cycle[i]] +
                                  adjacencyMatrix[cycle[j]][cycle[j + 1]];
                int newCost = adjacencyMatrix[cycle[i - 1]][cycle[j]] +
                              adjacencyMatrix[cycle[i]][cycle[j + 1]];

                if (newCost < currentCost) {
                    // Realiza a troca (inversão do subcaminho entre i e j)
                    reverse(cycle.begin() + i, cycle.begin() + j + 1);

                    // Atualiza o custo total
                    totalCost += (newCost - currentCost);
                    improvement = true;
                }
            }
        }
    }
}

void nearestInsertion(TSPProblem &problem)
{
    vector<int> cycle;
    vector<bool> visited(problem.dimension + 1, false);
    int totalCost = 0;

    // 1. Selecione um par de vértices qualquer
    int start = 1;
    int end = 2;

    // 2. Crie um ciclo indo do primeiro vértice ao segundo e voltando ao primeiro
    cycle.push_back(start);
    cycle.push_back(end);
    cycle.push_back(start);
    visited[start] = true;
    visited[end] = true;

    // 3. Enquanto houver vértices não visitados:
    while (cycle.size() - 1 < problem.dimension)
    {
        int bestVertex = -1;
        int bestPosition = -1;
        int bestIncrease = numeric_limits<int>::max();

        // 3.1 Para todo vértice não visitado:
        for (int v = 1; v <= problem.dimension; ++v)
        {
            if (!visited[v])
            {
                // 3.1.1 Encontre a posição no ciclo atual onde a visita do vértice provoca o menor aumento no custo total do ciclo
                for (int i = 0; i < cycle.size() - 1; ++i)
                {
                    int currentIncrease = problem.adjacencyMatrix[cycle[i]][v] + problem.adjacencyMatrix[v][cycle[i + 1]] - problem.adjacencyMatrix[cycle[i]][cycle[i + 1]];
                    if (currentIncrease < bestIncrease)
                    {
                        bestIncrease = currentIncrease;
                        bestVertex = v;
                        bestPosition = i + 1;
                    }
                }
            }
        }

        // 3.2 Encontre o vértice não visitado tal que o aumento calculado no passo 3.1.1 é o menor dentre todos os vértices não visitados
        // 3.3 Insira-o na posição correspondente do ciclo
        cycle.insert(cycle.begin() + bestPosition, bestVertex);
        visited[bestVertex] = true;
    }

    problem.cycle = cycle;

    for (int i = 0; i < cycle.size() - 1; ++i)
    {
        totalCost += problem.adjacencyMatrix[cycle[i]][cycle[i + 1]];
    }

    problem.totalCost = totalCost;
}

void nearestInsertionWith2Opt(TSPProblem &problem) {
    // Gera o ciclo inicial usando Nearest Insertion
    nearestInsertion(problem);

    // Refina o ciclo inicial com o algoritmo 2-opt
    apply2Opt(problem.cycle, problem.adjacencyMatrix, problem.totalCost);
}

// Imprime o ciclo encontrado e o custo total
void printSolution(TSPProblem &problem)
{
    nearestInsertionWith2Opt(problem);

    cout << "Ciclo encontrado:" << endl;
    for (int v : problem.cycle)
    {
        cout << v << " ";
    }
    cout << endl;

    cout << "Valor total do caminho: " << problem.totalCost << endl;
}

int main()
{
    TSPProblem problem;
    readInstance(problem);
    buildAdjacencyMatrix(problem);
    printSolution(problem);
    return 0;
}