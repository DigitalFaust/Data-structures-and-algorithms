#include"linked_list.h"
#include<iostream>
using std::cout;
using std::endl;

namespace data_struct
{
	Linked_list::Linked_list()
	{
		the_node = new node;
		the_node->data = 1;
		the_node->next = NULL;
		size = 1;
	}

	Linked_list::Linked_list(int init_data)
	{
		the_node = new node;
		the_node->data = init_data;
		the_node->next = NULL;
		size = 1;
	}

	void Linked_list::insert(int the_data)
	{
		node *new_node = new node;
		new_node->data = the_node->data;
		new_node->next = the_node->next;
		the_node->data = the_data;
		the_node->next = new_node;
		size++;
	}

	void Linked_list::remove(int the_data)
	{
		node *prev = get_prev(the_data);
		node *curr = search_node(the_data);

		if(prev == NULL)
			the_node = the_node->next;
		else
			prev->next = curr->next;
		
		size--;
		delete curr;
	}

	void Linked_list::remove()
	{
		node *temp = the_node;
		the_node = the_node->next;
		
		size--;
		delete temp;
	}

	void Linked_list::traverse() const
	{
		node *i = the_node;
		while(i != NULL)
		{
			cout << i->data << " ";
			i = i->next;
		}
		cout << endl;
	}

	int Linked_list::get_size()
	{
		return size;
	}

	Linked_list::node* Linked_list::search_node(int the_data)
	{
		node *i = the_node;

		while(i != NULL)
		{
			if(i->data == the_data)
				return i;
			i = i->next;
		}

		return NULL;
	}

	Linked_list::node* Linked_list::get_prev(int data)
	{
		node *i;

		for(i = the_node; i != NULL; i = i->next)
		{
			if(i == NULL || i->next == NULL)
				return NULL;
			if(i->next->data == data)
				return i;
		}

		return NULL;
	}

	Linked_list::node* Linked_list::get_first()
	{
		node *first_node = the_node;

		return first_node;
	}

	Linked_list::node* Linked_list::get_last()
	{
		node *last_node = the_node;

		while(last_node != NULL)
			last_node = last_node->next;

		return last_node;
	}
	
	Linked_list& Linked_list::operator=(Linked_list& rght_side)
	{
		node *i = the_node;
		node *j = rght_side.the_node;

		if(size <= rght_side.size)
		{
			while(j != NULL)
			{
				i->data = j->data;
				if(i->next == NULL)
					i->next = new node;
				i = i->next;
				j = j->next;
			}
			remove(i->data);
		}
		else
		{
			while(j != NULL)
			{
				i->data = j->data;
				i = i->next;
				j = j->next;
			}
			node* temp;
			node* temp_2 = i;
			while(i->next != NULL)
			{
				temp = i->next;
				delete i;
				i = temp;
			}
			delete i->next;
			temp_2 = get_prev(temp_2->data);
			temp_2->next = NULL;

		}	
		size = rght_side.size;

		return *this;
	}	

	Linked_list::node& Linked_list::node::operator=(Linked_list::node& rght_side)
	{
		cout << "node's assignment\n";

		this->data = rght_side.data;
		this->next = NULL;

		return *this;
	}

	istream& operator>>(istream& input, Linked_list& in_list)
	{
		int val = 0;
		input >> val;
		in_list.insert(val);

		return input;
	}

	ostream& operator<<(ostream& output, const Linked_list& out_list)
	{
		out_list.traverse();

		return output;
	}

	Linked_list::~Linked_list()
	{
		node *i;

		while(the_node != NULL)
		{
			i = the_node->next;
			delete the_node;
			the_node = i;
		}

		delete i;
	}
}
