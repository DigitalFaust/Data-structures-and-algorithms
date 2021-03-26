#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<iostream>
using std::ostream;
using std::istream;

namespace data_struct
{
	class Linked_list
	{
		public:
			struct node
			{
				int data;
				node *next;
				node& operator=(node& rght_side);
			};
			Linked_list();
			Linked_list(int init_data);
			void insert(int the_data);
			void remove(int the_data);//delete a node storing the argument
			void remove(); //delete the first node
			void traverse() const;
			int get_size();
			node *search_node(int the_data);
			friend istream& operator>>(istream& input, Linked_list& in_list);
			friend ostream& operator<<(ostream& output, const Linked_list& out_list);
			Linked_list& operator=(Linked_list& rght_side);
			~Linked_list();
		private:
			node *get_prev(int data);
			node *get_first();
			node *get_last();
			int size;
			node *the_node;
	};
}

#endif //LINKED_LIST_H
