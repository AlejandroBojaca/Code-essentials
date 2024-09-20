import random


def heuristic(next, dest):
    return abs(next.x - dest.x) + abs(next.y - dest.y)

def a_star_search(traffic_grid, src, dest):
    queue = PriorityQueue()
    queue.push(0, src)
    predecessors = { src: None }
    costs = { src: 0 } 
    visited = set()

    while not queue.empty():
        current = queue.pop()
        if current == dest:
            break
        if current in visited:
            continue
        visited.add(current)
        neighbors = traffic_grid.neighbors(current)
        for neighbor in neighbors:
            total_cost = costs[current] + neighbor.cost()
            if total_cost < costs.get(neighbor, float('inf')):
                costs[neighbor] = total_cost
                priority = heuristic(neighbor, dest) + total_cost
                queue.push(priority, neighbor)
                predecessors[neighbor] = current

    pred = dest
    path = []
    while pred is not None:
        print(pred)
        path.append(pred)
        pred = predecessors.get(pred, None)

    path.reverse()
    return path


class PriorityQueue:
    def __init__(self):
        self.elements = []

    def empty(self):
        return len(self.elements) == 0

    def push(self, priority, item):
        self.elements.append((priority, item))

    def pop(self):
        if self.empty():
            return None
        minimum = 0
        for i in range(len(self.elements)):
            if self.elements[i][0] < self.elements[minimum][0]:
                minimum = i
        item = self.elements[minimum]
        del self.elements[minimum]
        return item[1]


class Tile:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def cost(self):
        random.seed(hash(self))
        bucket = random.randint(1, 2)
        cost = random.randint(1, 5)
        if bucket == 2:
            cost = random.randint(15, 20)
        return cost

    def __eq__(self, other):
        if other is None:
            return False
        if type(other) is tuple:
            return self.x == other[0] and self.y == other[1]
        else:
            return self.x == other.x and self.y == other.y

    def __hash__(self):
        return (self.x * 1000) + self.y

    def __repr__(self):
        return f"({self.x}, {self.y})"


class TrafficGrid:
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def in_bounds(self, tile):
        return 0 <= tile.x < self.width and 0 <= tile.y < self.height

    def neighbors(self, tile):
        neighbors = [
            Tile(tile.x + 1, tile.y),
            Tile(tile.x - 1, tile.y),
            Tile(tile.x, tile.y - 1),
            Tile(tile.x, tile.y + 1),
        ]
        results = filter(self.in_bounds, neighbors)
        return results

    def __repr__(self):
        s = ""
        for y in range(self.height - 1, -1, -1):
            for x in range(self.width):
                t = Tile(x, y)
                s += f"[{t.cost():02d}]"
            s += "\n"
        return s
    


run_cases = [
    ((4, 4), (0, 0), (3, 3), [(0, 0), (0, 1), (1, 1), (2, 1), (2, 2), (3, 2), (3, 3)]),
    (
        (8, 8),
        (0, 4),
        (7, 4),
        [
            (0, 4),
            (0, 3),
            (0, 2),
            (0, 1),
            (1, 1),
            (2, 1),
            (2, 2),
            (3, 2),
            (4, 2),
            (5, 2),
            (6, 2),
            (7, 2),
            (7, 3),
            (7, 4),
        ],
    ),
]

submit_cases = run_cases + [
    (
        (10, 10),
        (0, 0),
        (9, 9),
        [
            (0, 0),
            (0, 1),
            (1, 1),
            (2, 1),
            (2, 2),
            (2, 3),
            (2, 4),
            (2, 5),
            (3, 5),
            (4, 5),
            (5, 5),
            (5, 6),
            (5, 7),
            (5, 8),
            (6, 8),
            (6, 9),
            (7, 9),
            (8, 9),
            (9, 9),
        ],
    ),
]


def test(traffic_grid_inputs, src_tile_inputs, dest_tile_inputs, expected_path):
    print("---------------------------------")
    try:
        traffic_grid = TrafficGrid(*traffic_grid_inputs)
        src_tile = Tile(*src_tile_inputs)
        dest_tile = Tile(*dest_tile_inputs)
        print(
            f"TrafficGrid: width: {traffic_grid.width}, height: {traffic_grid.height}"
        )
        print(traffic_grid)
        print(f"Shortest Path from {src_tile} to {dest_tile}")
        print(f"Expected: {expected_path}")
        actual_path = a_star_search(traffic_grid, src_tile, dest_tile)
        print(f"Actual: {actual_path}\n")
        if actual_path != expected_path:
            print("Fail")
            return False
        print("Pass")
        return True
    except Exception as e:
        print(f"Error: {e}")
        print("Fail")
        return False


def main():
    passed = 0
    failed = 0
    for test_case in test_cases:
        correct = test(*test_case)
        if correct:
            passed += 1
        else:
            failed += 1
    if failed == 0:
        print("============= PASS ==============")
    else:
        print("============= FAIL ==============")
    print(f"{passed} passed, {failed} failed")


test_cases = submit_cases
if "__RUN__" in globals():
    test_cases = run_cases

main()