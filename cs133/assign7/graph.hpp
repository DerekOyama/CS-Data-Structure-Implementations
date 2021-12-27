#pragma once
/*
 * graph.hpp
 * Adjacency-list graph implementation
 */
#include <climits> // For INT_MAX, INT_MIN
#include <list>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class graph
{
public:
   /* graph(n)
       Construct a graph with n nodes and no edges, initially.
    */
   graph(int n)
   {
      edges.resize(n);
   }

   /* add_edge(a,b)
       Add an edge from node a to node b. Note that self edges are not allowed,
       so attempting add_edge(a,a) should be ignored. Similarly, this is not
       a multigraph, so if an edge a -> b already exists, a second one should
       be ignored.
       Should run in O(E) time in the worst case. 
    */
   void add_edge(int a, int b)
   {
      if (has_edge(a, b) || a == b)
      {
         return;
      }
      edges[a].push_back(b);
   }

   /* has_edge(a,b)
       Returns true if there is an edge from a to b. Should return false if
       either a or b is out-of-range (< 0 or >= count_nodes()).
       Should run in O(E) time.
    */
   bool has_edge(int a, int b)
   {
      if (a >= edges.size() || b >= edges.size())
      {
         return false;
      }
      for (int i : edges[a])
      {
         if (i == b)
         {
            return true;
         }
      }
      return false;
   }

   /* count_nodes()
       Returns the number of nodes in this graph.
       Should run in O(1) time
    */
   int count_nodes()
   {
      return edges.capacity();
   }

   /* count_edges()
       Returns the total number of edges in this graph.
       Should run in O(E) time.
    */
   int count_edges()
   {
      int ans = 0;
      for (vector<int> i : edges)
      {
         ans += i.size();
      }
      return ans;
   }

   /* count_edges(n)
       Returns the number of outbound edges from node n.
       Should run in O(E) time
    */
   int count_edges(int n)
   {
      return edges[n].size();
   }

   /* bfs(n)
       Perform a breadth-first search, starting at node n, and returning a
       vector that gives the distance to every other node. (If a node is 
       unreachable from n, then set its distance to INT_MAX.)
       Should run in O(E + N) time.
    */
   vector<int> bfs(int n)
   {
      //1.  Mark all vertices as *unexplored*.
      //2.  Enqueue the starting vertex
      //3.  While the queue is NOT empty:
      //a.  Let a = Dequeue()
      //b.  (Search) If a is the target node, stop
      //c.  Mark a as *explored*
      //d.  For each vertex b, which is adjacent to a (a ———> b) and is
      //         NOT explored yet:
      //i.  Enqueue(b)
      vector<int> distances(edges.size(), INT_MAX);
      vector<int> parent(edges.size());
      vector<bool> explored(edges.size(), false);
      queue<int> q;
      q.push(n);
      distances[n] = 0;
      do
      {
         int a = q.front();
         q.pop();
         explored[a] = true;
         for (int i : edges[a])
         {
            if (!explored[i])
            {
               parent[i] = a;
               q.push(i);
               distances[i] = distances[parent[i]] +1;
            }
         }
      } while (!q.empty());
      for (int i = 0; i < distances.size(); i++)
      {
         cout << " " << distances[i] << " ";
      }
      return distances;
   }

   /* is_connected(a,b)
       Returns true if a path exists from node a to b. 
       Should run in O(E + N) time.
    */
   bool is_connected(int a, int b)
   {
      vector<bool> explored(edges.size(), false);
      queue<int> q;
      q.push(a);
      while (!q.empty())
      {
         int c = q.front();
         q.pop();
         if (c == b)
         {
            return true;
         }
         explored[c] = true;
         for (int i : edges[c])
         {
            if (!explored[i])
            {
               q.push(i);
            }
         }
      }
      return false;
   }

private:
   vector<std::vector<int>> edges;

   // Add any private data/function members you need.
   // g++ -o assign7_test assign7_test.cpp graph.hpp
};
