
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int bfs(int start_x, int start_y, int target_x, int target_y, const vector<vector<int>>& grid, int m, int n) {
    if (start_x == target_x && start_y == target_y) return 0;
    
    vector<vector<int>> dist(m, vector<int>(n, -1));
    queue<pair<int, int>> q;
    
    dist[start_x][start_y] = 0;
    q.push({start_x, start_y});
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                grid[nx][ny] != 1 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                
                if (nx == target_x && ny == target_y) {
                    return dist[nx][ny];
                }
                
                q.push({nx, ny});
            }
        }
    }
    
    return -1; // No path found
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> grid(m, vector<int>(n));
    
    pair<int, int> start, end;
    vector<pair<int, int>> umbrellas;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            
            if (grid[i][j] == 2) {
                start = {i, j};
            } else if (grid[i][j] == 3) {
                end = {i, j};
            } else if (grid[i][j] == 4) {
                umbrellas.push_back({i, j});
            }
        }
    }
    
    int min_distance = INT_MAX;
    
    for (const auto& umbrella : umbrellas) {
        int dist_to_umbrella = bfs(start.first, start.second, umbrella.first, umbrella.second, grid, m, n);
        int dist_to_home = bfs(umbrella.first, umbrella.second, end.first, end.second, grid, m, n);
        
        if (dist_to_umbrella != -1 && dist_to_home != -1) {
            min_distance = min(min_distance, dist_to_umbrella + dist_to_home);
        }
    }
    
    cout << min_distance << endl;
    
    return 0;
}
