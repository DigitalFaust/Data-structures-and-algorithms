#ifndef GRAPH_H
#define GRAPH_H

#include<string>
#include<iostream>
using std::string;
using std::ostream;
using std::istream;

namespace kaflanov
{
	class Queue
	{
		public:
			Queue();
			void enqueue(int the_key);
			void dequeue();
			int peek();
			bool is_empty();
			~Queue();
		private:
			struct list
			{
				int key;
				list *next;
			};
			struct node
			{
				list *front;
				list *rear;
				int size;
			};
			node *q;
	};

	class Stack
	{
		public:
			Stack();
			void push(int v);
			int pop();
			void print();
			void clear();
			~Stack();
		private:
			struct node
			{
				int x;
				node *next;
			};
			node **head;
	};

	class Graph
	{
		public:
			enum EDGE_TYPE {TREE, BACK, FORWARD, CROSS, UNCLASSIFIED};
			enum COLOR {BLACK, WHITE, UNCOLORED};
			Graph();
			Graph(bool is_directed);

			Graph(Graph& rght_side);
			Graph& operator=(Graph& rght_side);
			void bfs(int v, string function=" ");
			void connected_components();
			void find_path(int start, int end);
			void twocolor();
			void print_colors();
			void dfs(int v, string function=" ");
			void find_cycles();
			void find_cutnodes();
			void topsort();
			void strong_components();
			void print_strong_comps();
			friend ostream& operator<<(ostream& out, Graph& sample);
			friend istream& operator>>(istream& in, Graph& sample);
			~Graph();
		private:
			void init_graph();
			void print();
			void read();
			void insert_edge(int x, int y);
			void init_search();
			void process_vertex_early(int v);
			void process_edge(int x, int y);
			void process_vertex_late(int v);
			void process_color_edge(int x, int y);
			COLOR complement(COLOR x);
			void print_vertex_color(int v);
			void process_cycle(int x, int y);
			EDGE_TYPE get_edge_type(int x, int y);
			void process_cutnode_early(int v);
			void process_cutnode_edge(int x, int y);
			void process_cutnode_late(int v);
			void sort_vertex_early(int v);
			void sort_edge(int x, int y);
			void sort_vertex_late(int v);
			void process_component_early(int v);
			void process_component_edge(int x, int y);
			void process_component_late(int v);
			void pop_component(int v);
			int vertices;
			int edges;
			int TIME;
			int components_found;
			bool directed;
			bool finished;
			bool bipartition;
			bool *processed;
			bool *discovered;
			int *entry_time;
			int *exit_time;
			int *parent;
			int *low;
			int *scc;
			int *reachable_ancestor;
			int *tree_out_degree;
			COLOR *colors;
			struct edgenode
			{
				int y;
				int weight;
				edgenode *next;
			};
			struct graphnode
			{
				edgenode **edges;
				int *degree;
				int nvertices;
				int nedges;
				bool directed;
			};
			graphnode *g;
			Stack sorted;
			Stack active;
	};
}

#endif //GRAPH_H
