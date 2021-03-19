#include<iostream>
#include<cmath>
#include"tree.h"
using std::cout;
using std::endl;

namespace data_struct
{
	Tree::Tree()
	{
		head = new node;
		head->data = 0;
		head->left = NULL;
		head->parent = NULL;
		head->right = NULL;
		size = 0;
	}

	Tree::Tree(int init_data)
	{
		head = new node;
		head->data = init_data;
		head->left = NULL;
		head->parent = NULL;
		head->right = NULL;
		size = 1;
	}

	void Tree::insert(int the_data)
	{
		if(size == 0 && head->data == 0 && head->parent == NULL)
		{
			head->data = the_data;
			size = 1;
			return;
		}

		node* new_node = new node;
		new_node->data = the_data;
		new_node->left = NULL;
		new_node->right = NULL;

		node* i = head;
		node* prev_node = NULL;

		while(i != NULL)
		{
			prev_node = i;
			if(i->data > the_data)
				i = i->left;
			else if(i->data < the_data)
				i = i->right;
			else return;
		}

		new_node->parent = prev_node;
		if(the_data > prev_node->data)
			prev_node->right = new_node;
		else if(the_data < prev_node->data)
			prev_node->left = new_node;
		size++;
	}

	void Tree::remove(int the_data)
	{
		node* curr = search(the_data);

		if(curr == NULL)
			return;

		if(is_bottom(curr))
		{
			remove_lowest(curr);
			delete curr;
		}
		else if((curr->left == NULL) ^ (curr->right == NULL))
		{
			remove_medium(curr);
			delete curr;
		}
		else if((curr->left != NULL) && (curr->right != NULL))
		{
			node* max_left = get_max(curr->left);
			curr->data = max_left->data;

			if(is_bottom(max_left))
				remove_lowest(max_left);
			else if((max_left->left == NULL) ^ (max_left->right == NULL))
					remove_medium(max_left);
			delete max_left;
		}
		size--;
	}

	bool Tree::is_key(int the_data)
	{
		return the_data == search(the_data)->data;
	}

	int Tree::get_min()
	{
		if(min_node == NULL)
			find_min();

		return min_node->data;
	}

	int Tree::get_max()
	{
		if(max_node == NULL)
			find_max();
		
		return max_node->data;
	}

	int Tree::get_size()
	{
		return size;
	}
	
	int Tree::get_height()
	{
		return static_cast<int>(log(static_cast<double>(size)));
	}

	//beautiful
	Tree& Tree::operator=(Tree& rght_side)
	{
		stack* l_store = store(head);
		stack* r_store = store(rght_side.head);
	
		assign(l_store, r_store, head);

		while(!is_empty(l_store))
			delete l_store;

		while(!is_empty(r_store))
			delete r_store;

		return *this;
	}

	Tree::node& Tree::node::operator=(Tree::node& rght_side)
	{
		this->data = rght_side.data;
		this->left = this->right = this->parent = NULL;

		return *this;
	}

	ostream& operator<<(ostream& output, Tree& out_node)
	{
		out_node.traverse();

		return output;
	}

	istream& operator>>(istream& input, Tree& in_node)
	{
		int val = 0;
		input >> val;
		in_node.insert(val);
		return input;
	}

	void Tree::traverse()
	{
		node* i = head;
		stack* poped = new stack;
		stack* stack_hd = new stack;

		push(stack_hd, i);
		while(i != NULL && !is_empty(stack_hd))
		{
			while(i->left != NULL)
			{
				i = i->left;
				push(stack_hd, i);
			}
			while(!is_empty(stack_hd))
			{
				poped = pop(&stack_hd);
				cout << poped->t_node->data << " ";
				size++;
				if(poped->t_node->right != NULL)
				{
					i = poped->t_node->right;
					push(stack_hd, i);
					break;
				}
			}
		}
		cout << endl;
		delete poped;
		while(!is_empty(stack_hd))
			delete pop(&stack_hd);
	}

	void Tree::push(stack* head, node* the_node)
	{
		stack* new_stack_node = new stack;

		new_stack_node->t_node = head->t_node;
		new_stack_node->next = head->next;

		head->t_node = the_node;
		head->next = new_stack_node;
	}

	Tree::stack* Tree::pop(stack** head)
	{
		stack* poped = new stack;
	
		poped->t_node = (*head)->t_node;
		poped->next = *head;
	
		*head = (*head)->next;
	
		delete poped->next;
		poped->next = NULL;
	
		return poped;
	}

	bool Tree::is_empty(stack* head)
	{
		return head->next == NULL;
	}

	bool Tree::is_bottom(node* the_node)
	{
		return (the_node->left == NULL) && (the_node->right == NULL);
	}

	void Tree::remove_lowest(Tree::node* curr_node)
	{
		if((curr_node->parent->left != NULL) && (curr_node->parent->left->data == curr_node->data))
			curr_node->parent->left = NULL;
		else if((curr_node->parent->right != NULL) && (curr_node->parent->right->data == curr_node->data))
			curr_node->parent->right = NULL;
	}

	void Tree::remove_medium(Tree::node* curr_node)
	{
		if(curr_node->parent == NULL)
		{
			if(curr_node->left != NULL)
				head = head->left;
			else if(curr_node->right != NULL)
				head = head->right;
		} 
		else if((curr_node->parent->left != NULL) && (curr_node->parent->left->data == curr_node->data))
		{
			if(curr_node->right != NULL)
			{
				curr_node->parent->left = curr_node->right;
				curr_node->right->parent = curr_node->parent;
			}
			if(curr_node->left != NULL)
			{
				curr_node->parent->left = curr_node->left;
				curr_node->left->parent = curr_node->parent;
			}
		}
		else if((curr_node->parent->right != NULL) && (curr_node->parent->right->data == curr_node->data))
		{
			if(curr_node->right != NULL)
			{
				curr_node->parent->right = curr_node->right;
				curr_node->right->parent = curr_node->parent;
			}
			else if(curr_node->left != NULL)
			{
				curr_node->parent->right = curr_node->left;
				curr_node->left->parent = curr_node->parent;
			}
		}
	}

	Tree::node* Tree::search(int the_data)
	{
		if(head == NULL)
		{
			cout << "The tree is empty\n";
			return NULL;
		}
		
		node* i = head;

		while(!is_bottom(i))
		{
			if(i->data > the_data)
				i = i->left;
			if(i->data < the_data)
				i = i->right;
			if(i->data == the_data)
				return i;
		}

		return NULL;
	}

	Tree::node* Tree::get_min(Tree::node* the_node)
	{
		find_min(the_node);

		return min_node;
	}

	Tree::node* Tree::get_max(Tree::node* the_node)
	{
		find_max(the_node);

		return max_node;
	}
	
	void Tree::find_min()
	{
		if(head == NULL)
			return;

		node* i = head;

		while(i->left != NULL)
			i = i->left;

		min_node = i;
	}

	void Tree::find_max()
	{
		if(head == NULL)
			return;

		node* i = head;

		while(i->right != NULL)
			i = i->right;

		max_node = i;	
	}

	void Tree::find_min(Tree::node* the_node)
	{
		if(head == NULL || the_node == NULL)
			return;

		while(the_node->left != NULL)
			the_node = the_node->left;

		min_node = the_node;
	}

	void Tree::find_max(Tree::node* the_node)
	{
		if(head == NULL || the_node == NULL)
			return;

		while(the_node->right != NULL)
			the_node = the_node->right;

		max_node = the_node;
	}

	int Tree::stack_size(Tree::stack* head)
	{
		int size = 0;

		while(head->next != NULL)
		{
			head = head->next;
			size++;
		}

		return size;
	}

	Tree::stack* Tree::store(Tree::node* root)
	{
		stack* new_stack = new stack;
		stack* poped = new stack;
		stack* storage = new stack;

		push(new_stack, root);

		while(root != NULL && !is_empty(new_stack))
		{
			while(root->left != NULL)
			{
				root = root->left;
				push(new_stack, root);
			}
	
			while(!is_empty(new_stack))
			{
				poped = pop(&new_stack);
				push(storage, poped->t_node);
				if(poped->t_node->right != NULL)
				{
					root = poped->t_node->right;
					push(new_stack, root);
					break;
				}
			}
		}
	
		return storage;
	}
	
	void Tree::assign(Tree::stack* l_store, Tree::stack* r_store, Tree::node* cpy_lts)
	{
		node* bin;

		if(stack_size(r_store) <= stack_size(l_store))
		{
			while(!is_empty(r_store))
				pop(&l_store)->t_node->data = pop(&r_store)->t_node->data;
			while(!is_empty(l_store))
				{
					bin = pop(&l_store)->t_node;
					remove(bin->data);
				}
		}
		else
		{
			while(!is_empty(l_store))
				pop(&l_store)->t_node->data = pop(&r_store)->t_node->data;
	
			node* new_node;
			while(!is_empty(r_store))
			{
				new_node = pop(&r_store)->t_node;
				insert(new_node->data);
			}
		}
	}

	Tree::~Tree()
	{
		node* i = head;
		stack* poped = new stack;
		stack* stack_hd = new stack;
		stack* bin = new stack;

		push(stack_hd, i);
		while(i != NULL && !is_empty(stack_hd))
		{
			while(i->left != NULL)
			{
				i = i->left;
				push(stack_hd, i);
			}
			while(!is_empty(stack_hd))
			{
				poped = pop(&stack_hd);
				push(bin, poped->t_node);
				size++;
				if(poped->t_node->right != NULL)
				{
					i = poped->t_node->right;
					push(stack_hd, i);
				}
			}
		}
		delete poped;
		while(!is_empty(stack_hd))
			delete pop(&stack_hd);
		while(!is_empty(bin))
			delete pop(&bin);
		cout << "Bye\n";
	}
}
