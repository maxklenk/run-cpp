
#include "Graph.h"

#include <map>
#include <set>
#include <iostream>
#include <memory>

//
// Class Vertex
//


Vertex::Vertex(std::int32_t id)
: m_id{id}
{
}


std::int32_t Vertex::id() const
{
    return m_id;
}




//
// Class Edge
//


Edge::Edge(std::shared_ptr<Vertex> v0, std::shared_ptr<Vertex> v1, std::int32_t weight)
: m_weight{weight}
{
    reset(v0, v1);
}


void Edge::reset(std::shared_ptr<Vertex> v0, std::shared_ptr<Vertex> v1)
{
    if (v0 < v1)
    {
        m_v0 = v0;
        m_v1 = v1;
    }
    else
    {
        m_v0 = v1;
        m_v1 = v0;
    }
}


std::int32_t Edge::weight() const
{
    return m_weight;
}


std::shared_ptr<Vertex> Edge::v0() const
{
    return m_v0;
}


std::shared_ptr<Vertex> Edge::v1() const
{
    return m_v1;
}




//
// Class Graph
//


const std::vector<std::shared_ptr<Vertex> > & Graph::vertices() const
{
    return m_vertices;
}


const std::vector<std::shared_ptr<Edge> > & Graph::edges() const
{
    return m_edges;
}

void Graph::addVertex(std::shared_ptr<Vertex> vertex)
{
    m_vertices.emplace_back(vertex);
}


void Graph::addEdge(std::shared_ptr<Edge> edge)
{
    m_edges.emplace_back(edge);
}

void Graph::merge(std::shared_ptr<Graph> g2)
{
    // Edge id for the purpose of creating a map/set
    using EdgeId = std::pair<std::int32_t, std::int32_t>;
    auto makeId = [](std::shared_ptr<Edge> edge) { return std::make_pair(edge->v0()->id(), edge->v1()->id()); };

    // build map for fast lookup of vertices by id
    auto vertexMap = std::map<int, std::shared_ptr<Vertex> >{};
    for (const auto & vertex : m_vertices)
    {
        vertexMap[vertex->id()] = vertex;
    }

    // build map for fast lookup of edges by ids of its vertices
    auto edgeSet = std::set<EdgeId>{};
    for (const auto & edge : m_edges)
    {
        edgeSet.insert(makeId(edge));
    }

    // merge vertices
    for (const auto & vertex : g2->vertices())
    {
        if (vertexMap.find(vertex->id()) == vertexMap.end())
        {
            vertexMap[vertex->id()] = vertex;
            m_vertices.emplace_back(vertex);
        }
    }

    // merge edges
    for (const auto & edge : g2->edges())
    {
        if (edgeSet.find(makeId(edge)) == edgeSet.end())
        {
            // rewire pointers
            const auto & v0 = vertexMap[edge->v0()->id()];
            const auto & v1 = vertexMap[edge->v1()->id()];
            edge->reset(v0, v1);

            edgeSet.insert(makeId(edge));
            m_edges.emplace_back(edge);
        }
    }

    g2.reset();
}

// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[], int amountNodes)
{
    // Initialize min value
    int min = 1000000;
    int min_index = -1;

    for (int v = 0; v < amountNodes; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v], min_index = v;
        }
    }

    return min_index;
}

void solveMST(int **graph, int parent[], int amountNodes)
{
    //int parent[amountNodes]; // Array to store constructed MST
    int key[amountNodes];   // Key values used to pick minimum weight edge in cut
    bool mstSet[amountNodes];  // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < amountNodes; i++) {
        key[i] = 1000000;
        mstSet[i] = false;
    }


    // Always include first 1st vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < amountNodes - 1; count++) {
        // Pick thd minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet, amountNodes);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < amountNodes; v++) {

            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u, key[v] = graph[u][v];
            }
        }
    }
}

std::shared_ptr<Graph> Graph::minimumSpanningTree() const
{
    // create array representation of graph for faster lookups
    int amountNodes = m_vertices.size();
    int **graph = new int*[amountNodes];

    for (int i = 0; i < amountNodes; i++) {
        graph[i] = new int[amountNodes];
        for (int j = 0; j < amountNodes; j++) {
            graph[i][j] = 0;
        }
    }

    int amountEdges = m_edges.size();
    for (const auto &edge : m_edges) {
        auto from = edge->v0()->id();
        auto to = edge->v1()->id();
        auto weight = edge->weight();
        graph[from][to] = weight;
        graph[to][from] = weight;
    }


    // solve MST (prim)
    int parent[amountNodes];
    solveMST(graph, parent, amountNodes);


    // construct new graph
    auto resultGraph = std::make_unique<Graph>();

    // add nodes
    for (const auto &vertex : m_vertices) {
        resultGraph->addVertex(vertex);
    }

    // add edges
    for (const auto &edge : m_edges) {
        auto from = edge->v0()->id();
        auto to = edge->v1()->id();
        if (parent[from] == to || parent[to] == from) {
            resultGraph->addEdge(edge);
        }
    }

    return std::shared_ptr<Graph>(std::move(resultGraph));
}


std::ostream & operator<<(std::ostream & stream, const Graph & graph)
{
    for (const auto & edge : graph.m_edges)
    {
        stream << "(" << edge->v0()->id() << "," << edge->v1()->id() << ") ";
    }
    return stream;
}
