class Solution {
public:
    int spanningTree(int V, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> adj(V);

        for(auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int wt = e[2];

            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }

        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;

        vector<bool> visited(V, false);

        int res = 0;

        pq.push({0, 0});

        while(!pq.empty()) {

            auto p = pq.top();
            pq.pop();

            int wt = p.first;
            int u  = p.second;

            if(visited[u]) continue;

            res += wt;
            visited[u] = true;

            for(auto &v : adj[u]) {
                if(!visited[v.first]) {
                    pq.push({v.second, v.first});
                }
            }
        }

        return res;
    }
};