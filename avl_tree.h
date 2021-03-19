#ifndef AVL_TREE_H
#define AVL_TREE_H

#include<iostream>
using std::ostream;
using std::istream;

namespace data_struct
{
	class Avl_tree
	{
		public:
			struct node
			{
				int data;
				node* left;
				node* right;
				int height;
				node() : data(0), left(NULL), right(NULL), height(1) {}
				node(int init_data) : data(init_data), left(NULL), right(NULL), height(1) {}
			};
			Avl_tree();
			Avl_tree(int init_data);
			void remove(int the_key);
			void insert(int new_key);
			bool is_key(int the_key);
			int get_max();
			int get_min();
			int get_size();
			int get_height();
			Avl_tree& operator=(Avl_tree& rght_side);
			friend ostream& operator<<(ostream& output, Avl_tree& the_root);
			friend istream& operator>>(istream& input, Avl_tree& the_root);
			void grow_tree();
			~Avl_tree();
		private:
			struct stack
			{
				node* root;
				stack* next;
			};
			node* find_node(int the_key);
			void traverse();
			node* find_parent(node* the_node);
			bool is_stack_empty();
			bool is_empty(stack* hd);
			void push(node* new_data);
			void push(stack* hd, node* new_data);
			stack* pop();
			stack* pop(stack** hd);
			int get_height(node* root);
			int b_factor(node* root);
			void fix_height(node* root);
			node* left_rot(node* root);
			node* right_rot(node* root);
			node* balance();
			bool is_leaf(node* the_node);
			node* find_min(node* the_node);
			node* find_max(node* the_node);
			void remove_leaf(node* curr_node, node* parent);
			void remove_interim(node* curr_node, node* parent);
			void put_in_stack(node* curr_node);
			void clear_stack();
			int stack_size(stack* hd);
			stack* store(node* root);
			void assign(stack* l_store, stack* r_store, node* cpy_lts);
			node* root;
			stack* head;
			int size;
	};
}

#endif //AVL_TREE_H
