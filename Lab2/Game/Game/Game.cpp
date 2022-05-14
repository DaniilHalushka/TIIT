#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <vector>
#include <Windows.h>

using namespace std;

class Graph
{
    int V;
    int eCount;
    int start;
    list<int>* adj;

public:

    Graph(int V, int start, int eCount);
    int geteCount();
    int getStart();
    void addEdge(int v, int w);
    bool dfs(int v, vector<int>& checkList, vector<bool>& finishList, int* visited);
    void sorting();
};

Graph::Graph(int V, int start, int eCount)
{
    this->V = V;
    this->eCount = eCount;
    this->start = start;
    adj = new list<int>[V];

}

int Graph::geteCount()
{
    return this->eCount;
}

int Graph::getStart()
{
    return this->start;
}

void Graph::addEdge(int v, int w)
{
    w = w - 1;
    adj[v].push_front(w);
}

bool Graph::dfs(int v, vector<int>& checkList, vector<bool>& finishList, int* visited)
{
    visited[v] = true;
    if (checkList[v] <= 0)
    {
        return false;
    }
    if (finishList[v])
    {
        checkList[v]--;
        return true;
    }
    list<int>::iterator i;
    int min = 10000;
    int max = 0;
    int vertex = -1;
    for (i = adj[v].begin(); i != adj[v].end(); i++)
    {
        if (checkList[*i] <= 0)
        {
            continue;
        }

        if (checkList[*i] < min && visited[*i] == false)
        {
            min = checkList[*i];
            vertex = *i;
        }
    }

    if (min >= 10000 || vertex < 0)
    {
        return false;
    }

    if (dfs(vertex, checkList, finishList, visited))
    {
        checkList[vertex]--;
        return true;
    }

    if (finishList[vertex])
    {
        return true;
    }

    return dfs(v, checkList, finishList, visited);
}

void Graph::sorting()
{
    for (int i = 0; i < V; i++)
    {
        adj[i].sort();

    }
}

bool sortGraphList(Graph& a, Graph& b)
{
    return a.geteCount() < b.geteCount();
}

int main()
{
    setlocale(LC_ALL, "ru");
    int i;
    int j;

    ifstream fin("game.in");

    string str{};

    getline(fin, str);
    istringstream strStream(str);
    vector<int> vv(istream_iterator<int>(strStream), {});

    if (vv.size() != 3)
    {
        return 0;
    }

    int pStartCount = vv[0];
    int pMiddleCount = vv[1];
    int pEndCount = vv[2];
    int vCount = pStartCount + pMiddleCount + pEndCount;

    vector<int> checkList(vCount);
    vector<bool> finishList(vCount);

    i = 0;
    j = 0;
    for (i = 0; i < pStartCount; i++)
    {
        checkList[i] = 1;
        finishList[i] = 0;
    }

    i = 0;
    while (i < pMiddleCount && getline(fin, str))
    {
        checkList[i + pStartCount] = stoi(str);
        finishList[i + pStartCount] = 0;
        i++;
    }

    for (i = 0; i < pEndCount; i++)
    {
        checkList[i + pStartCount + pMiddleCount] = 1;
        finishList[i + pStartCount + pMiddleCount] = 1;
    }

    vector<Graph> gList;
    i = 0;

    while (i < pStartCount && getline(fin, str))
    {
        istringstream strStream(str);
        vector<int> vEdge(istream_iterator<int>(strStream), {});

        Graph g(vCount, i, vEdge[0]);
        int vSize = vEdge.size();

        for (int j = 1; j < vSize; j++)
        {
            g.addEdge(i, vEdge[j]);
        }

        gList.push_back(g);

        i++;
    }

    sort(gList.begin(), gList.end(), sortGraphList);

    i = 0;

    int gSize = gList.size();
    while (i < pMiddleCount && getline(fin, str))
    {
        istringstream strStream(str);
        vector<int> vEdge(istream_iterator<int>(strStream), {});
        int vSize = vEdge.size();

        for (j = 1; j < vSize; j++)
        {
            for (int k = 0; k < gSize; k++)
            {
                gList[k].addEdge(i + pStartCount, vEdge[j]);
            }
        }
        i++;
    }

    int ballCounter = 0;
    for (i = 0; i < gSize; i++)
    {
        int* visited = new int[vCount];
        for (j = 0; j < vCount; j++)
        {
            visited[j] = false;
        }
        if (gList[i].dfs(gList[i].getStart(), checkList, finishList, visited))
        {
            ballCounter++;
        }
        delete[] visited;
    }

    ofstream fout("game.out");

    if (!fout.is_open())
    {
        cout << "Файл не открыт";
    }
    else
    {
        fout << ballCounter << endl;
    }

    return 0;
}