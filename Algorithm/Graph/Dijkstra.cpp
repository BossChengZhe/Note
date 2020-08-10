#include "iostream"
#include "queue"
#include "string"
#include "vector"
using namespace std;

const int M = 1000;
vector<vector<int>> graph = {{0, 4, M, 2, M},
                             {4, 0, 4, 1, M},
                             {M, 4, 0, 1, 3},
                             {2, 1, 1, 0, 7},
                             {M, M, 3, 7, 0}};
vector<string> path(graph.size(), "");

struct node
{
    int node_id;
    int dist;
    int update;
    bool operator<(const node &a) const
    {
        if (dist == a.dist)
            return node_id > a.node_id;
        return dist > a.dist;
    }
};

void dijkstra(vector<vector<int>> &graph, vector<string> &path, int start)
{
    int node_num = graph.size();
    vector<node> d(node_num, {0, M, 0});
    vector<bool> visit(node_num, false);
    for (int i = 0; i < node_num; i++)
        d[i].node_id = i;

    d[start].dist = 0;
    path[start] = to_string(start);

    priority_queue<node> q;
    q.push(d[start]);
    while (!q.empty())
    {
        node tmp = q.top();
        q.pop();
        if (visit[tmp.node_id])
            continue;
        visit[tmp.node_id] = true;
        // 打印路径
        path[tmp.node_id] = (path[tmp.update] + "->" + (char)(tmp.node_id + 'A'));
        if (tmp.node_id == start)
            path[tmp.node_id] = tmp.node_id + 'A';

        // 更新节点信息
        for (int i = 0; i < node_num; i++)
        {
            if (!visit[i] && d[i].dist > d[tmp.node_id].dist + graph[tmp.node_id][i])
            {
                d[i].update = tmp.node_id;
                d[i].dist = d[tmp.node_id].dist + graph[tmp.node_id][i];
                q.push(d[i]);
            }
        }
    }
    for (int i = 0; i < node_num; i++)
        cout << "node:" << i << " dist:" << d[i].dist << " path:" << path[i] << endl;
}
int main()
{
    dijkstra(graph, path, 0);
    return 0;
}