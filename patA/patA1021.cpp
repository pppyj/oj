#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 100001;
vector<int> G[MAXN];

bool isRoot[MAXN] = {false};
int father[MAXN];

int findFather(int x) {
    int a = x;
    while(x != father[x]) x = father[x];
    while(a != father[a]) {
        int z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

void Union(int a, int b) {
    int faA = findFather(a);
    int faB = findFather(b);
    if(faA != faB) father[faA] = faB;
}

void init(int n) {
    for(int i = 1; i <= n; i++)
        father[i] = i;
}

int calBlock(int n) {
    int block = 0;
    for(int i = 1; i <= n; i++) isRoot[findFather(i)] = true;
    for(int i = 1; i <= n; i++) block += isRoot[i];
    return block;
}

int maxH = 0;
vector<int> temp, ans;

void DFS(int u, int h, int pre) {
    if(h > maxH) {
        temp.clear();
        temp.push_back(u);
        maxH = h;
    } else if(h == maxH)
        temp.push_back(u);
    for(int i = 0; i < (int)G[u].size(); i++) {
        if(G[u][i] == pre) continue;
        DFS(G[u][i], h + 1, u);
    }
}

int main() {
    int a, b, n;
    scanf("%d", &n);
    init(n);
    for(int i = 1; i < n; i++) {
        scanf("%d%d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
        Union(a, b);
    }
    int block = calBlock(n);
    if(block != 1) printf("Error: %d components\n", block);
    else {
        DFS(1, 1, -1);
        ans = temp;
        DFS(ans[0], 1, -1);
        for(int i = 0; i < (int)temp.size(); i++) {
            ans.push_back(temp[i]);
        }
        sort(ans.begin(), ans.end());
        printf("%d\n", ans[0]);
        for(int i = 1; i < (int)ans.size(); i++)
            if(ans[i] != ans[i - 1]) printf("%d\n", ans[i]);
    }
    return 0;
}