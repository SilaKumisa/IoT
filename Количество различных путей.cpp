#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void bfs(int a, vector<int>& used, vector<int>& dist, vector<vector<int> >& graph, queue <int>& help_queue) {
    used[a] *= -1;
    for (int i = 0; i < graph[a].size(); ++i) {
        if (used[graph[a][i]] == 0) {
            help_queue.push(graph[a][i]);
            dist[graph[a][i]] = dist[a] + 1;
        }
        if (used[graph[a][i]] >= 0 && dist[graph[a][i]] == dist[a] + 1)
            used[graph[a][i]] += used[a] * -1;
    }
    while (!help_queue.empty()) {
        int q = help_queue.front();
        help_queue.pop();
        bfs(q, used, dist, graph, help_queue);
    }
}
//Алгоритм считает попутно длину пути//

int main() {
    int n, m;
    cin >> n >> m;

	vector<int> used (n);
	vector<int> dist (n);
	vector<vector<int> > graph (n, vector<int> ());
	queue <int> help_queue;

    for (int i = 0; i < n; ++i) {
        used[i] = 0;
        dist[i] = 0;
    }

    int ver1, ver2;
    for (int i = 0; i < m; ++i) {
        cin >> ver1 >> ver2;
        graph[ver1].push_back(ver2);
        graph[ver2].push_back(ver1);
    }

    int v, w;
    cin >> v >> w;
    
    used[v] = 1;
    bfs(v, used, dist, graph, help_queue);

    cout << used[w] * -1;
    system("pause");
    return 0;
}