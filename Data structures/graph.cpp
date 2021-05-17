#include<iostream>
#include<iomanip>
#include"graph.h"
using std::setw;
using std::cout;
using std::endl;
using std::cin;

namespace kaflanov
{
	Queue::Queue()
	{
		q = new node;
		q->front = q->rear = NULL;
		q->size = 0;
	}

	void Queue::enqueue(int the_key)
	{
		list *temp = new list;
		temp->key = the_key;
		
		if(q->rear == NULL)
		{
			q->front = q->rear = temp;
			q->size++;
			return;
		}

		q->rear->next = temp;
		q->rear = temp;
		q->size++;
	}

	void Queue::dequeue()
	{
		if(q->front == NULL)
			return;
		list *temp = q->front;
		q->front = q->front->next;
		if(q->front == NULL)
			q->rear = NULL;
		delete temp;
		q->size--;
	}

	int Queue::peek()
	{
		return q->front->key;
	}

	bool Queue::is_empty()
	{
		return q->front == NULL;
	}

	Queue::~Queue()
	{
		while(!is_empty())
			dequeue();
	}

	Stack::Stack()
	{
		head = new node*;
		*head = new node;
		(*head)->x = 0;
		(*head)->next = NULL;
	}

	void Stack::push(int v)
	{
		Stack::node *new_node = new node;
		new_node->x = v;
		new_node->next = *head;
		*head = new_node;
	}

	int Stack::pop()
	{
		int x = (*head)->x;
		Stack::node *temp = *head;
		(*head) = (*head)->next;

		delete temp;

		return x;
	}

	void Stack::print()
	{
		if((*head)->next == NULL)
			cout << "The stack is empty\n";

		while((*head)->next != NULL)
		{
			cout << (*head)->x << " ";
			*head = (*head)->next;
		}
		cout << endl;
	}
	
	void Stack::clear()
	{
		Stack::node *temp;

		while((*head)->next != NULL)
		{
			temp = (*head)->next;
			delete *head;
			*head = temp;
		}
	}

	Stack::~Stack()
	{
		clear();
	}

	Graph::Graph()
	{
		TIME = 0;
		components_found = 0;
		vertices = 0;
		edges = 0;
		directed = false;
		finished = false;
		bipartition = true;
		g = new graphnode;
		g->nvertices = 0;
		g->nedges = 0;
	}

	Graph::Graph(bool is_directed)
	{
		TIME = 0;
		components_found = 0;
		vertices = 0;
		edges = 0;
		directed = is_directed;
		finished = false;
		bipartition = true;
		g = new graphnode;
		g->nvertices = 0;
		g->nedges = 0;
		g->directed = directed;
	}

	Graph::Graph(Graph& sample)
	{
		vertices = sample.vertices;
		edges = sample.edges;
		TIME = sample.TIME;
		components_found = sample.components_found;
		directed = sample.directed;
		finished = sample.finished;
		bipartition = sample.bipartition;
		g = new graphnode;
		g->nvertices = sample.g->nvertices;
		g->nedges = 0;
		g->directed = sample.g->directed;

		init_graph();

		for(int i = 1; i <= g->nvertices; i++)
		{
			processed[i] = sample.processed[i];
			discovered[i] = sample.discovered[i];
			entry_time[i] = sample.entry_time[i];
			exit_time[i] = sample.exit_time[i];
			parent[i] = sample.parent[i];
			low[i] = sample.low[i];
			scc[i] = sample.scc[i];
			reachable_ancestor[i] = sample.reachable_ancestor[i];
			tree_out_degree[i] = sample.tree_out_degree[i];
			colors[i] = sample.colors[i];
		}

		for(int i = 1; i <= vertices; i++)
		{
			edgenode *p;
			p = sample.g->edges[i];
			while(p != NULL)
			{
				insert_edge(i, p->y);
				p = p->next;
			}
		}
	}

	Graph& Graph::operator=(Graph& sample)
	{
		edges = sample.edges;
		components_found = sample.components_found;
		directed = sample.directed;
		finished = sample.finished;
		bipartition = sample.bipartition;
		g->directed = sample.g->directed;

		if((g->nvertices == 0) || (sample.g->nvertices == 0))
		{
			vertices = sample.vertices;
			init_graph();
			g->nvertices = sample.g->nvertices;

			for(int i = 1; i <= vertices; i++)
			{
				processed[i] = sample.processed[i];
				discovered[i] = sample.discovered[i];
				entry_time[i] = sample.entry_time[i];
				exit_time[i] = sample.exit_time[i];
				parent[i] = sample.parent[i];
				low[i] = sample.low[i];
				scc[i] = sample.scc[i];
				reachable_ancestor[i] = sample.reachable_ancestor[i];
				tree_out_degree[i] = sample.tree_out_degree[i];
				colors[i] = sample.colors[i];
			}

			for(int i = 1; i <= vertices; i++)
			{
				edgenode *p;
				p = sample.g->edges[i];
				while(p != NULL)
				{
					insert_edge(i, p->y);
					p = p->next;
				}
			}

		}
		else if(g->nvertices == sample.g->nvertices)
		{
			for(int i = 1; i <= g->nvertices; i++)
			{
				processed[i] = sample.processed[i];
				discovered[i] = sample.discovered[i];
				entry_time[i] = sample.entry_time[i];
				exit_time[i] = sample.exit_time[i];
				parent[i] = sample.parent[i];
				low[i] = sample.low[i];
				scc[i] = sample.scc[i];
				reachable_ancestor[i] = sample.reachable_ancestor[i];
				tree_out_degree[i] = sample.tree_out_degree[i];
				colors[i] = sample.colors[i];
			}

			for(int i = 1; i <= edges; i++)
			{
				edgenode *p;
				p = sample.g->edges[i];
				while(p != NULL)
				{
					insert_edge(i, p->y);
					p = p->next;
				}
			}
		}
		else
		{
			delete[] processed;
			delete[] discovered;
			delete[] entry_time;
			delete[] exit_time;
			delete[] parent;
			delete[] low;
			delete[] scc;
			delete[] reachable_ancestor;
			delete[] tree_out_degree;
			delete[] colors;
			delete[] g->degree;
			for(int i = 1; i <= g->nvertices; i++)
				delete[] g->edges[i];
			delete[] g->edges;

			vertices = sample.vertices;
			init_graph();
			g->nvertices = sample.g->nvertices;

			for(int i = 1; i <= g->nvertices; i++)
			{
				processed[i] = sample.processed[i];
				discovered[i] = sample.discovered[i];
				entry_time[i] = sample.entry_time[i];
				exit_time[i] = sample.exit_time[i];
				parent[i] = sample.parent[i];
				low[i] = sample.low[i];
				scc[i] = sample.scc[i];
				reachable_ancestor[i] = sample.reachable_ancestor[i];
				tree_out_degree[i] = sample.tree_out_degree[i];
				colors[i] = sample.colors[i];
			}

			for(int i = 1; i <= vertices; i++)
			{
				edgenode *p;
				p = sample.g->edges[i];
				while(p != NULL)
				{
					insert_edge(i, p->y);
					p = p->next;
				}
			}
		}

		return *this;
	}

	void Graph::read()
	{
		cout << "Enter number of edges: ";
		cin >> edges;
		
		cout << "Enter number of vertices: ";
		cin >> vertices;
		g->nvertices = vertices;

		init_graph();

		int x = 0, y = 0;

		for(int i = 1; i <= edges; i++)
		{
			cout << "Enter vertices x and y: ";
			cin >> x >> y;
			insert_edge(x, y);
		}
	}

	void Graph::init_graph()
	{
		processed = new bool[vertices];
		discovered = new bool[vertices];
		entry_time = new int[vertices];
		exit_time = new int[vertices];
		parent = new int[vertices];
		low = new int[vertices];
		scc = new int[vertices];
		reachable_ancestor = new int[vertices];
		tree_out_degree = new int[vertices];
		colors = new COLOR[vertices];
		g->edges = new edgenode*[vertices];
		g->degree = new int[vertices];
	}

	void Graph::insert_edge(int x, int y)
	{
		Graph::edgenode *p = new Graph::edgenode;
		p->y = y;
		p->weight = 0;
		p->next = g->edges[x];
		g->edges[x] = p;
		g->degree[x]++;

		if(g->directed == false)
		{
			g->directed = true;
			insert_edge(y, x);
			g->directed = false;
		}
		else
			g->nedges++;
	}

	void Graph::print()
	{
		Graph::edgenode *p;

		for(int i = 1; i <= vertices; i++)
		{
			cout << i << ": ";
			p = g->edges[i];
			while(p != NULL)
			{
				cout << p->y << " ";
				p = p->next;
			}
			cout << endl;
		}
	}

	void Graph::init_search()
	{
		for(int i = 1; i <= g->nvertices; i++)
		{
			processed[i] = false;
			discovered[i] = false;
			entry_time[i] = -1;
			exit_time[i] = -1;
			parent[i] = -1;
			reachable_ancestor[i] = -1;
			tree_out_degree[i] = -1;
		}
	}

	void Graph::bfs(int v, string function)
	{
		Queue q;
		Graph::edgenode *p;
		int x = 0, y = 0;

		discovered[v] = true;
		q.enqueue(v);

		while(!q.is_empty())
		{
			x = q.peek();
			q.dequeue();
			if(function != "twocolor")
				process_vertex_early(x);
			p = g->edges[x];
			while(p != NULL)
			{
				y = p->y;

				if((processed[y] == false) || (g->directed))
				{
					if(function == "twocolor")
						process_color_edge(x, y);
					else
						process_edge(x, y);
				}
				if(discovered[y] == false)
				{
					parent[y] = x;
					discovered[y] = true;
					q.enqueue(y);
				}

				p = p->next;
			}
			if(function != "twocolor")
				process_vertex_late(x);
			processed[x] = true;
		}
	}

	void Graph::process_vertex_early(int v)
	{
		cout << "Start processing vertex: " << v << endl;
	}

	void Graph::process_edge(int x, int y)
	{
		cout << "Processed edge: " << x << " - " << y << endl;
	}

	void Graph::process_vertex_late(int v)
	{
		cout << "End processing vertex: " << v << endl;
	}

	void Graph::connected_components()
	{
		int c = 0;

		init_search();
		for(int i = 1; i <= g->nvertices; i++)
		{
			if(discovered[i] == false)
			{
				c++;
				cout << "Component: " << c << endl;
				bfs(i);
			}
		}
	}

	void Graph::find_path(int start, int end)
	{
		if((start == end) || (end == -1))
			cout << start << " ";
		else
		{
			find_path(start, parent[end]);
			cout << end << " ";
		}
	}

	void Graph::twocolor()
	{
		for(int i = 1; i <= g->nvertices; i++)
			colors[i] = UNCOLORED;

		init_search();
		bipartition = true;

		for(int i = 1; i <= g->nvertices; i++)
		{
			if(discovered[i] == false)
			{
				colors[i] = WHITE;
				bfs(i, "twocolor");
			}
		}
	}

	void Graph::process_color_edge(int x, int y)
	{
		if(colors[x] == colors[y])
		{
			cout << "The edge (" << x << ", " << y << ") is not bipartite\n";
			bipartition = false;
		}
		colors[y] = complement(colors[x]);
	}

	Graph::COLOR Graph::complement(COLOR x)
	{
		if(x == BLACK) return WHITE;
		if(x == WHITE) return BLACK;
		return UNCOLORED;
	}

	void Graph::print_colors()
	{
		Graph::edgenode *p;

		for(int i = 1; i <= g->nvertices; i++)
		{
			cout << "(" << i << "|";
			print_vertex_color(i);
			cout << ") : ";
			p = g->edges[i];
			while(p != NULL)
			{
				cout << "(" << p->y << "|";
				print_vertex_color(p->y);
				cout << ") ";
				p = p->next;
			}
			cout << endl;
		}

		if(bipartition == true)
			cout << "\nThe graph is bipartitioned\n";
		else
			cout << "\nThe graph is not bipartitioned\n";
	}

	void Graph::print_vertex_color(int v)
	{
		if(colors[v] == BLACK) cout << "BLACK";
		if(colors[v] == WHITE) cout << "WHITE";
		if(colors[v] == UNCOLORED) cout << "UNCOLORED";
	}

	void Graph::dfs(int v, string function)
	{
		Graph::edgenode *p;
		int y = 0;

		discovered[v] = true;
		TIME++;
		entry_time[v] = TIME;
		if(function == " ")
			process_vertex_early(v);
		if(function == "find_cycles")
		{
			process_vertex_early(v);
			if(finished) return;
		}
		if(function == "find_cutnodes")
			process_cutnode_early(v);
		if(function == "topsort")
			sort_vertex_early(v);
		if(function == "strong_components")
			process_component_early(v);
		p = g->edges[v];
		while(p != NULL)
		{
			y = p->y;

			if(discovered[y] == false)
			{
				parent[y] = v;
				if(function == " ")
					process_edge(v, y);
				if(function == "find_cycles")
					process_cycle(v, y);
				if(function == "find_cutnodes")
					process_cutnode_edge(v, y);
				if(function == "topsort")
					sort_edge(v, y);
				if(function == "strong_components")
					process_component_edge(v, y);
				dfs(y, function);
			}
			else if((processed[y] == false) || g->directed)
			{
				if(function == " ")
					process_edge(v, y);
				if(function == "find_cycles")
					process_cycle(v, y);
				if(function == "find_cutnodes")
					process_cutnode_edge(v, y);
				if(function == "topsort")
					sort_edge(v, y);
				if(function == "strong_components")
					process_component_edge(v, y);
			}
			if(function == "find_cycles")
				if(finished) return;
			p = p->next;
		}

		TIME++;
		exit_time[v] = TIME;
		if(function == " " || function == "find_cycles")
			process_vertex_late(v);
		if(function == "find_cutnodes")
			process_cutnode_late(v);
		if(function == "topsort")
			sort_vertex_late(v);
		if(function == "strong_components")
			process_component_late(v);
		processed[v] = true;
	}

	void Graph::find_cycles()
	{
		init_search();

		for(int i = 1; i <= g->nvertices; i++)
		{
			if(discovered[i] == false)
				dfs(i, "find_cycles");
		}
	}

	void Graph::process_cycle(int x, int y)
	{
		Graph::EDGE_TYPE type;

		type = get_edge_type(x, y);

		if(type == BACK || type == CROSS)
		{
			cout << "Cycle found from " << y << " to " << x << " : ";
			find_path(y, x);
			cout << endl;
			finished = true;
		}
	}

	Graph::EDGE_TYPE Graph::get_edge_type(int x, int y)
	{
		if(parent[y] == x) return TREE;
		if((discovered[y] == true) && (processed[y] == false)) return BACK;
		if((processed[y] == true) && (entry_time[y] > entry_time[x])) return FORWARD;
		if((processed[y] == true) && (entry_time[y] < entry_time[x])) return CROSS;
		cout << "\nThe edge (" << x << ", " << y << ") is unclassified\n";
		return UNCLASSIFIED;
	}

	void Graph::find_cutnodes()
	{
		init_search();

		for(int i = 1; i <= g->nvertices; i++)
		{
			if(discovered[i] == false)
				dfs(i, "find_cutnodes");
		}
	}

	void Graph::process_cutnode_early(int v)
	{
		reachable_ancestor[v] = v;
	}

	void Graph::process_cutnode_edge(int x, int y)
	{
		Graph::EDGE_TYPE type;

		type = get_edge_type(x, y);

		if(type == TREE)
			tree_out_degree[x]++;

		if(type == BACK && parent[x] != y)
			if(entry_time[y] < entry_time[reachable_ancestor[x]])
				reachable_ancestor[x] = y;
	}

	void Graph::process_cutnode_late(int v)
	{
		bool root;
		int time_v = 0, time_parent_v;

		if(parent[v] < 1)
		{
			if(tree_out_degree[v] > 1)
				cout << "Root cutnode: " << v << endl;
			return;
		}

		root = (parent[parent[v]] < 1);

		if(reachable_ancestor[v] == parent[v] && !root)
			cout << "Parent cutnode: " << parent[v] << endl;
		if(reachable_ancestor[v] == v)
		{
			cout << "Bridge cutnode: " << parent[v] << endl;
			if(tree_out_degree[v] > 1)
				cout << "Bridge cutnode: " << parent[v] << endl;
		}

		time_v = entry_time[reachable_ancestor[v]];
		time_parent_v = entry_time[reachable_ancestor[parent[v]]];

		if(time_v < time_parent_v)
			reachable_ancestor[parent[v]] = reachable_ancestor[v];
	}

	void Graph::topsort()
	{
		init_search();

		for(int i = 1; i <= g->nvertices; i++)
		{
			if(discovered[i] == false)
				dfs(i, "topsort");
		}

		sorted.print();
	}

	void Graph::sort_vertex_early(int v)
	{
		cout << "Processing vertex: " << v << endl;
	}

	void Graph::sort_edge(int x, int y)
	{
		Graph::EDGE_TYPE type;

		type = get_edge_type(x, y);

		if(type == BACK)
			cout << "Warning! Found cycle (" << x << ", " << y << ")\n";
	}

	void Graph::sort_vertex_late(int v)
	{
		sorted.push(v);
	}

	void Graph::strong_components()
	{
		for(int i = 1; i <= g->nvertices; i++)
		{
			low[i] = i;
			scc[i] = -1;
		}

		init_search();
		components_found = 0;

		for(int i = 1; i <= g->nvertices; i++)
		{
			if(discovered[i] == false)
				dfs(i, "strong_components");
		}
	}

	void Graph::process_component_early(int v)
	{
		cout << "Processed vertex: " << v << endl;
		active.push(v);
	}

	void Graph::process_component_edge(int x, int y)
	{
		Graph::EDGE_TYPE type;

		type = get_edge_type(x, y);

		if(type == BACK)
			if(entry_time[y] < entry_time[low[x]])
				low[x] = y;

		if(type == CROSS)
			if(scc[y] == -1)
				if(entry_time[y] < entry_time[low[x]])
					low[x] = y;
	}

	void Graph::process_component_late(int v)
	{
		if(low[v] == v)
			pop_component(v);

		if(entry_time[low[v]] < entry_time[low[parent[v]]])
			low[parent[v]] = low[v];
	}

	void Graph::pop_component(int v)
	{
		int t = 0;

		components_found++;
		scc[v] = components_found;
		while((t = active.pop()) != v)
			scc[t] = components_found;
	}

	void Graph::print_strong_comps()
	{
		cout << "|";
		for(int i = 1; i <= g->nvertices; i++)
			cout << setw(3) << i << "|";
		cout << endl;

		cout << "|";
		for(int i = 1; i <= g->nvertices; i++)
			cout << setw(3) << scc[i] << "|";
		cout << endl;
	}

	ostream& operator<<(ostream& out, Graph& sample)
	{
		sample.print();

		return out;
	}

	istream& operator>>(istream& in, Graph& sample)
	{
		sample.read();

		return in;
	}

	Graph::~Graph()
	{
		delete[] processed;
		delete[] discovered;
		delete[] entry_time;
		delete[] exit_time;
		delete[] parent;
		delete[] low;
		delete[] scc;
		delete[] reachable_ancestor;
		delete[] tree_out_degree;
		delete[] colors;
		for(int i = 1; i <= g->nvertices; i++)
		{
			delete[] g->edges[i];
		}
		delete[] g->edges;
		delete[] g->degree;
		delete g;
	}
}
