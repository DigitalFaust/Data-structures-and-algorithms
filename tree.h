#ifndef TREE_H
#define TREE_H

#include<iostream>
using std::ostream;
using std::istream;

namespace data_struct
{
	class Tree
	{
		public:
			struct node
			{
				int data;
				node* left;
				node* parent;
				node* right;
				node& operator=(node& rght_side);
			};
			Tree();
			Tree(int init_data);
			void insert(int the_data);
			void remove(int the_data);
			bool is_key(int the_data);
			int get_min();
			int get_max();
			int get_size();
			int get_height();
			Tree& operator=(Tree& rght_side);
			friend ostream& operator<<(ostream& output, Tree& out_node);
			friend istream& operator>>(istream& input, Tree& in_node);
			~Tree();
		private:
			struct stack
			{
				node* t_node;
				stack* next;
			};
			void traverse();
			void push(stack* head, node* the_node);
			stack* pop(stack** head);
			bool is_empty(stack* head);
			bool is_bottom(node* the_node);
			void remove_lowest(node* curr_node);
			void remove_medium(node* curr_node);
			node* search(int the_data);
			node* get_min(node* the_node);
			node* get_max(node* the_node);
			void find_min();
			void find_max();
			void find_min(node* the_node);
			void find_max(node* the_node);
			int stack_size(stack* head);
			stack* store(node* root);
			void assign(stack* l_store, stack* r_store, node* cpy_lts);
			node* head;
			node* min_node = NULL;
			node* max_node = NULL;
			int size;
	};
}

#endif //TREE_H
