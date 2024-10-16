#include <iostream>
#include <set>
#include <random>
#include <cstdlib>
#include <ctime>


struct Maxheap {
    std::vector<int> heap;

    Maxheap(int root) {
        this->heap.push_back(root);
    }

    void insert(int item) {
        this->heap.push_back(item);
        int index = this->heap.size() - 1;

        while (index > 0 && this->heap[index] > this->heap[(index - 1) / 2]) {
            int parent_index = (index - 1) / 2;
            std::swap(this->heap[index], this->heap[parent_index]);
            index = parent_index;
        }
    }

    void heapify_down(int index) {
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int largest = index;

        if (left_child < this->heap.size() && this->heap[left_child] > this->heap[largest]) {
            largest = left_child;
        }

        if (right_child < this->heap.size() && this->heap[right_child] > this->heap[largest]) {
            largest = right_child;
        }

        if (largest != index) {
            std::swap(this->heap[largest], this->heap[index]);
            heapify_down(largest);
        }
    }

    void remove(int index) {
        if (index >= this->heap.size()) {
            std::cout << "Index out of bounds!" << std::endl;
            return;
        }

        if (this->heap.size() == 1) {
            this->heap.pop_back();
            return;
        }

        std::swap(this->heap[index], this->heap.back());
        this->heap.pop_back();

        heapify_down(index);
    }

    void print_heap() {
        for (const int& i : this->heap)
            std::cout << i << " ";
        std::cout << std::endl;
    }
};

struct Hm_item {
    std::string key;
    std::string value;
};

struct Hashmap {
    int max;
    std::unordered_map<std::string, Hm_item> hash_table;

    Hashmap(int max) {
        this->max = max;
    }

    int hash_function(std::string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum += int(key[i]);
        }
        return sum % this->max;
    }

    void insert(std::string key, std::string value) {
        int hash_key = hash_function(key);
        hash_table[key] = Hm_item(key, value);
    }

    void search(std::string key) {
        int hash_key = hash_function(key);
        auto it = hash_table.find(key);

        if (it != hash_table.end()) {
            std::cout << "Found: " << it->second.value << std::endl;
        } else {
            std::cout << "Key not found!" << std::endl;
        }
    }
};

struct Graph {
    std::vector<std::vector<int> > adj_matrix;
    int size;

    Graph(int size) {
        this->size = size;
        adj_matrix.resize(size, std::vector<int>(size, 0));
    }

    void add_edge(int u, int v) {
        if (u >= size || v >= size || u < 0 || v < 0) {
            std::cout << "Invalid vertex index" << std::endl;
            return;
        }

        adj_matrix[u][v] = 1;
        adj_matrix[v][u] = 1;
    }

    void remove_edge(int u, int v) {
        if (u >= size || v >= size || u < 0 || v < 0) {
            std::cout << "Invalid vertex index" << std::endl;
            return;
        }
        adj_matrix[u][v] = 0;
        adj_matrix[v][u] = 0;
    }

    void add_vertex(int v) {
        if (v < this->size) {
            std::cout << "Vertex already exists " << std::endl;
            return;
        }

        int new_size = v + 1;

        for (int i = 0; i < this->size; i++) {
            adj_matrix[i].resize(new_size, 0);
        }

        adj_matrix.resize(new_size, std::vector<int>(new_size, 0));

        this->size = new_size;
    }

    void remove_vertex(int v) {
        if (v >= size || v < 0) {
            std::cout << "Invalid vertex index" << std::endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            adj_matrix[i][v] = 0;
            adj_matrix[v][i] = 0;
        }
    }

    void display() {
        std::cout << "Adjacency Matrix:" << std::endl;
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                std::cout << this->adj_matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void dfs() {
        std::set<int> visited;
        std::stack<int> stack; 

        std::cout << "DFS: " << std::endl;
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                if (adj_matrix[i][j] == 1) {
                    visited.insert(i);
                    stack.push(i);
                    break;
                }
            }
            if (!visited.empty()) break;
        }        
        
        while(!stack.empty()) {
            int node = stack.top(); 
            std::cout << "Visiting node " << node << std::endl;
            stack.pop();
            for (int i = 0; i < this->size; i++) {
                if (adj_matrix[node][i] == 1 && visited.find(i) == visited.end()) {
                    stack.push(i);
                }
            }
            visited.insert(node);
        }
    }

    void bfs() {
        std::set<int> visited;
        std::queue<int> queue; 

        std::cout << "BFS: " << std::endl;
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                if (adj_matrix[i][j] == 1) {
                    visited.insert(i);
                    queue.push(i);
                    break;
                }
            }
            if (!visited.empty()) break;
        }        
        
        while(!queue.empty()) {
            int node = queue.front(); 
            std::cout << "Visiting node " << node << std::endl;
            queue.pop();
            for (int i = 0; i < this->size; i++) {
                if (adj_matrix[node][i] == 1 && visited.find(i) == visited.end()) {
                    queue.push(i);
                }
            }
            visited.insert(node);
        }
    }
};

struct Maze {
    int size;
    std::vector<std::vector<int> > maze;

    Maze(int size) {
        this->size = size;
        this->maze = std::vector<std::vector<int> >(size, std::vector<int>(size, 0));
        carve_paths();
    }
    
    void carve_paths() {
        maze[1][0] = 1;
        maze[1][1] = 1;
        // std::set<std::pair<int, int> > visited;
        // std::queue<std::pair<int, int>> queue;

        // visited.insert({1, 1});
        
        int x = 1;
        int y = 1;
        while (y != size - 1) {
            int dx = 0;
            int dy = 0;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, 1);

            bool orientation = dist(gen);
            bool direction = dist(gen);
            if (orientation) {
                dx = (direction ? 1 : -1);
            } else {
                dy = (direction ? 1 : -1);
            }

            bool in_bounds = (x + dx >= 1 && x + dx < size - 1 && y + dy >= 1 && y + dy < size - 1);
            bool at_exit = (x == size - 2 && y + dy == size - 1);
            // bool not_visited = visited.find({x + dx, y + dy}) == visited.end();

            if (in_bounds || at_exit) {
                x += dx;
                y += dy;
                // visited.insert({x, y});
                maze[x][y] = 1;
            }
        }
    }

    void print_maze() {
        if (this->maze.size() == 0) {
            return;
        }
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                if (this->maze[i][j] == 0) {
                    std::cout << "#";
                } else {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }
    }
};


int main() {
    // Maxheap max_heap(5);
    // max_heap.insert(4);
    // max_heap.insert(3);
    // max_heap.insert(2);
    // max_heap.insert(50);
    // max_heap.insert(40);
    // max_heap.remove(1);
    // max_heap.print_heap();
    // Hashmap hm(1000);
    // hm.insert("apple", "red");
    // hm.insert("paple", "blue");
    // hm.search("apple");
    // hm.search("paple");
    // Graph g(20);
    // g.add_edge(1,2);
    // g.add_edge(1,3);
    // g.add_edge(1,4);
    // g.add_edge(1,5);
    // g.add_edge(5,7);
    // g.add_edge(9,7);
    // g.remove_vertex(3);
    // g.dfs();
    // g.bfs();
    // g.display();

    Maze maze(10);
    maze.print_maze();
    return 0;
}
