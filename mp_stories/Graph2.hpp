#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_map>
#include "Graph.h"

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::unordered_map<std::string, std::string> previous;
  std::unordered_map<std::string, int> distance;
  for (std::pair<std::string, V &> elem : vertexMap) {
    previous.insert(std::pair<std::string, std::string>(elem.first, ""));
    distance.insert(std::pair<string, int>(elem.first, INT_MAX));
  }
  std::queue<std::string> q;
  q.push(start);
  distance[start] = 0;
  while (!q.empty()) {
    std::string curr = q.front();
    q.pop();
    for (E_byRef e : incidentEdges(curr)) {
      std::string curr_next = e.get().dest().key() == curr ? e.get().source().key() : e.get().dest().key();
      if (distance[curr_next] > distance[curr]) {
        q.push(curr_next);
        previous[curr_next] = curr;
        distance[curr_next] = distance[curr] + 1;
      }
    }
  }
  std::list<std::string> path;
  std::string node = end;
  while (node != "") {
    path.push_front(node);
    node = previous[node];
  }
  return path;
}
