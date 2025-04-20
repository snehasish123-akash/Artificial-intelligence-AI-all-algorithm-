from collections import deque

def bidirectional_search(start, target, graph):
    visited_start = set()
    visited_target = set()
    queue_start = deque()
    queue_target = deque()

    queue_start.append(start)
    queue_target.append(target)
    visited_start.add(start)
    visited_target.add(target)

    depth = 0

    while queue_start and queue_target:
        for _ in range(len(queue_start)):
            vertex = queue_start.popleft()
            if vertex in visited_target:
                return True, depth
            for neighbor in graph[vertex]:
                if neighbor not in visited_start:
                    visited_start.add(neighbor)
                    queue_start.append(neighbor)

        for _ in range(len(queue_target)):
            vertex = queue_target.popleft()
            if vertex in visited_start:
                return True, depth
            for neighbor in graph[vertex]:
                if neighbor not in visited_target:
                    visited_target.add(neighbor)
                    queue_target.append(neighbor)

        depth += 1

    return False, -1

# Input section
num_vertices = int(input("Enter the number of vertices: "))
graph = [[] for _ in range(num_vertices)]

num_edges = int(input("Enter the number of edges: "))
print("Enter the edges (vertex1 vertex2):")
for _ in range(num_edges):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

start_vertex = int(input("Enter the starting vertex: "))
target_vertex = int(input("Enter the target vertex: "))

found, depth = bidirectional_search(start_vertex, target_vertex, graph)

if found:
    print(f"Target vertex found at depth {depth}")
else:
    print("Target vertex not found")
