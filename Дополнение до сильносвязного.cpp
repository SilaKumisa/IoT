#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
int used[100000];
int usedh[100000];
int lastUsed[100000];

int t;
int com;

void dfs(int v, vector<vector<int> >& graph, int* used, int dir) {
    if(dir == 1)
        used[v] = com;
    else {
        t++;
        used[v] = t;
    }
    for (int i = 0; i < int(graph[v].size()); ++i) {
        if(used[graph[v][i]] == 0)
            dfs(graph[v][i], graph, used, dir);
    }
    if (dir == 0) {
        t++;
        used[v] = t;
    }
}

int main() {

    int h;
    cin >> n >> h;

    vector<vector<int> > graph (n, vector<int> ());
    vector<vector<int> > graphh (n, vector<int> ());
    
    int v1, v2;
    for (int i = 0; i < h; ++i) {
        cin >> v1 >> v2;
        graph[v1 - 1].push_back(v2 - 1);
        graphh[v2 - 1].push_back(v1 - 1);
    }

    t = 0;
    for (int i = 0; i < n; ++i) {
        if (usedh[i] == 0) {
            dfs(i, graphh, usedh, 0);
        }
    }

    vector<vector<int> > help (n, vector<int> (2));
    for (int i = 0; i < n; ++i) {
        help[i][0] = usedh[i];
        help[i][1] = i;
    }

    stable_sort(help.begin(), help.end());

    com = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (used[help[i][1]] == 0) {
            com++;
            dfs(help[i][1], graph, used, 1);
        }
    }

    int newN = 0;
    for (int i = 0; i < n; ++i) {
        if(used[i] > newN)
            newN = used[i];
    }

    vector<vector<int> > lastGraph (newN, vector<int> (2));
    for (int i = 0; i < newN; ++i) {
        lastGraph[i][0] = 0;
        lastGraph[i][1] = 0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < int(graph[i].size()); ++j) {
            if (used[i] != used[graph[i][j]]) {
                lastGraph[used[i] - 1][0] = 1;
                lastGraph[used[graph[i][j]] - 1][1] = 1;
            }
        }
    }

    int stoks = 0, istoks = 0;
    for (int i = 0; i < newN; ++i) {
        if (lastGraph[i][0] == 0) {
            stoks++;
        }
        if (lastGraph[i][1] == 0) {
            istoks++;
        }
    }
    
    if (newN == 1) {
        cout << 0;
        return 0;
    }
    
    cout << max(stoks, istoks);
    
    return 0;
}

/* 
Очевидно, что меньшего числа ребер чем максимальное из колва стоков и истоков в конденсированном графе не хватит. 
Так как иначе в какой-то сток или из какого-то истока просто не будут выходить ребра.
Значит на потребуется хотябы max(stoks, istoks) ребер.
Теперь докажем, что этого кол-ва достаточно.
Будем доказвать по индукции следующее утверждение:"Мы можем соединяя только истоки и стоки между 
собой получить компоненту сильной связности заmax(stoks, istoks) ребер.
База для max = 1 очевидна. (Так как мы имеем или только сток и исток одновременно или один сток и один исток).
Теперь пусть мы доказали для max = n.
Докажем для n + 1.
Заметим, что каждый исток или одновременно является стоком или соединен путем с каким-нибудь стоком. Если все стоки одновременно истоки,
то просто соединяем все вершины по циклу за n+1 ребро.
Иначе найдем пару (stok, istok) между которыми есть путь.
Уберем ее вместе с путем. В оставдемся графе max равен n. А значит мы умеем его за n ребер делать компонентой сильной связности.
(Понятно, что если мы ту компоненту хоть как-то научимся связывать ребром с истоком, а потом сток связывать с ней то мы построим наш пример.)
Возьмем пару истока и стока из того графа между которыми мы проводили ребро.
Уберем это ребро и соединим исток разрыва с нашим и наш сток со стоком разрыва, будет ровно n+1 ребро и новая компонента сильной связности.
А значит мы доказали переход, а вместе с ним и утверждение.
*/
