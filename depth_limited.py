from collections import defaultdict

# Create the graph as a dictionary of lists
graph = defaultdict(list)

def dls(node, target, depth, visited):
    if depth < 0:
        return False

    print(node, end=" ")
    if node == target:
        return True

    visited.add(node)

    for neighbor in graph[node]:
        if neighbor not in visited:
            if dls(neighbor, target, depth - 1, visited):
                return True

    return False

# Input number of vertices and edges
v = int(input("Enter number of vertices: "))
e = int(input("Enter number of edges: "))

# Read all edges
for _ in range(e):
    a, b = map(int, input("Enter edge (a b): ").split())
    graph[a].append(b)
    graph[b].append(a)

# Input start node, target node, and maximum depth
start = int(input("Enter start node: "))
target = int(input("Enter target node: "))
max_depth = int(input("Enter maximum depth: "))

visited = set()

# Run DLS
found = dls(start, target, max_depth, visited)

# Print result
if found:
    print("\nTarget found")
else:
    print("\nTarget not found within depth")
