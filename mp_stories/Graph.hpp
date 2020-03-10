#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  return adjList.at(v.key()).size();
}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {

  // Create a vertex
  V & v = *(new V(key));
  // Insert the vertex into vertexMap and create an empty adjcent key
  vertexMap.insert({key, v});
  adjList.insert({key, std::list<edgeListIter>()});
  // Return the vertex
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {

  // Remove Edges
  for (auto iter = adjList.at(key).begin(); iter != adjList.at(key).end();) {
    Edge e = *(*iter);
    std::string source = e.source().key();
    std::string destination = e.dest().key();
    ++iter;
    removeEdge(source, destination);
  }
  // Remove vertex from the vertexMap
  vertexMap.erase(key);

}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {

  // Create an edge
  E & e = *(new E(v1, v2));
  // Insert the edge in the edge list
  edgeList.push_back(e);
  // Insert the edge in the adj list
  edgeListIter iter = edgeList.begin();
  std::advance(iter, edgeList.size() - 1);
  adjList.at(v1.key()).push_back(iter);
  adjList.at(v2.key()).push_back(iter);
  // Return the edge
  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // Remove edge from adj list
  for (auto iter = adjList.at(key1).begin(); iter != adjList.at(key1).end(); ++iter) {
    Edge e = *(*iter);
    if (e.source().key() == key1 && e.dest().key() == key2) {
      adjList[key1].erase(iter);
      break;
    }
  }
  for (auto iter = adjList.at(key2).begin(); iter != adjList.at(key2).end(); ++iter) {
    Edge e = *(*iter);
    if (e.source().key() == key1 && e.dest().key() == key2) {
      adjList[key2].erase(iter);
      break;
    }
  }
  // Remove edge from edge list
  for (auto iter = edgeList.begin(); iter != edgeList.end(); ++iter) {
    Edge e = *iter;
    if (e.source().key() == key1 && e.dest().key() == key2) {
      edgeList.erase(iter);
      break;
    }
  }
}


/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // Convert edgeListIter to string
  string source = it.get().source().key();
  string destination = it.get().source().key();
  // Call the former removeEdge Function
  removeEdge(source, destination);

}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {

  std::list<std::reference_wrapper<E>> edges;
  for (auto iter : adjList.at(key)) {
    edges.push_back(*iter);
  }
  return edges;

}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // mark = true -> adjList of key1, mark = false -> adjList of key2
  bool mark = (adjList.at(key1).size() < adjList.at(key2).size()) ? true : false;
  // Initialize iterator
  if (mark) {
    for (auto iter : adjList.at(key1)) {
      if (iter->get().source().key() == key1 && iter->get().dest().key() == key2) {
        return true;
      }
    }
  } else {
    for (auto iter : adjList.at(key2)) {
      if (iter->get().source().key() == key1 && iter->get().dest().key() == key2) {
        return true;
      }
    }
  }
  return false;
}
