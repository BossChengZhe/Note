#include "iostream"
#include "vector"
using namespace std;

int main()
{
    int m, n;
    cin >> n >> m;
    vector<vector<bool>> graph(m, vector<bool>(m, false));
    for(int i = 0; i < m; i++)
    {
        int from, to;
        cin >> from >> to;
        if(from!=to)
        { 
            graph[from-1][to-1] = true;
            graph[to-1][from-1] = true;
        }
    }

    return 0;
}