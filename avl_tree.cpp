#include"avl_tree.h"
using std::cout;
using std::endl;

namespace data_struct
{
	Avl_tree::Avl_tree()
	{
		root = new Avl_tree::node;
		head = new Avl_tree::stack;
		size = 1;
	}

	Avl_tree::Avl_tree(int init_data)
	{
		root = new Avl_tree::node(init_data);
		head = new Avl_tree::stack;
		size = 1;
	}

	void Avl_tree::remove(int the_key)
	{
		node* curr_node = find_node(the_key);

		if(curr_node == NULL)
		{
			cout << "There's not such node\n";
			return;
		}

		node* parent = find_parent(curr_node);
		stack* head = new stack;

		if(is_leaf(curr_node))
		{
			remove_leaf(curr_node, parent);
			delete curr_node;
			curr_node = parent;
			put_in_stack(curr_node);
		}
		else if((curr_node->left == NULL) ^ (curr_node->right == NULL))
		{
			remove_interim(curr_node, parent);
			delete curr_node;
			put_in_stack(curr_node);
		}
		else if((curr_node->left != NULL) && (curr_node->right != NULL))
		{
			node* max_left = find_max(curr_node->left);
			parent = find_parent(max_left);
			curr_node->data = max_left->data;

			if(is_leaf(max_left))
				remove_leaf(max_left, parent);
			else if((max_left->left == NULL) ^ (max_left->right== NULL))
				remove_interim(max_left, parent);
			delete max_left;
			put_in_stack(parent);
		}

		root = balance();
		size--;
	}

	void Avl_tree::insert(int new_key)
	{
		node* new_node = new node(new_key);
		node* i = root;
		node* prev_node = NULL;

		if(!is_stack_empty())
			clear_stack();

		while(i != NULL)
		{
			fix_height(i);
			prev_node = i;
			if(i->data > new_key)
				i = i->left;
			else if(i->data < new_key)
				i = i->right;
			else return;
		}

		if(new_key > prev_node->data)
		{
			prev_node->right = new_node;
			fix_height(prev_node);
		}
		else if(new_key < prev_node->data)
		{
			prev_node->left = new_node;
			fix_height(prev_node);
		}
		
		put_in_stack(new_node);
		root = balance();
		size++;
	}


	bool Avl_tree::is_key(int the_key)
	{
		return the_key == find_node(the_key)->data;
	}

	int Avl_tree::get_max()
	{
		node* max_node = find_max(root);

		return max_node->data;
	}

	int Avl_tree::get_min()
	{
		node* min_node = find_min(root);

		return min_node->data;
	}

	int Avl_tree::get_size()
	{
		return size;
	}

	int Avl_tree::get_height()
	{
		return root->height;
	}

	Avl_tree& Avl_tree::operator=(Avl_tree& rght_side)
	{
		stack* l_store = store(root);
		stack* r_store = store(rght_side.root);
	
		assign(l_store, r_store, root);

		while(!is_empty(l_store))
			delete l_store;

		while(!is_empty(r_store))
			delete r_store;

		return *this;
	}

	ostream& operator<<(ostream& output, Avl_tree& the_root)
	{
		the_root.traverse();

		return output;
	}

	istream& operator>>(istream& input, Avl_tree& the_root)
	{
		int val;
		input >> val;
		the_root.insert(val);

		return input;
	}

	void Avl_tree::grow_tree()
	{
		root->data = 10;
		root->height = 3;

		root->left = new Avl_tree::node;
		root->left->data = 7;
		root->left->height = 2;

		root->left->left = new Avl_tree::node;
		root->left->left->data = 5;
		root->left->left->height = 1;
		root->left->left->left = NULL;
		root->left->left->right = NULL;

		root->left->right = new Avl_tree::node;
		root->left->right->data = 8;
		root->left->right->height = 1;
		root->left->right->left = NULL;
		root->left->right->right = NULL;

		root->right = new Avl_tree::node;
		root->right->data = 21;
		root->right->height = 2;
	
		root->right->left = new Avl_tree::node;
		root->right->left->data = 18;
		root->right->left->height = 1;
		root->right->left->left = NULL;
		root->right->left->right = NULL;

		root->right->right = new Avl_tree::node;
		root->right->right->data = 23;
		root->right->right->height = 1;
		root->right->right->left = NULL;
		root->right->right->right = NULL;
		size = 7;
	}

	Avl_tree::~Avl_tree()
	{
		node* i = root;
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
				push(bin, poped->root);
				if(poped->root->right != NULL)
				{
					i = poped->root->right;
					push(stack_hd, i);
				}
			}
		}

		delete poped;
		while(!is_empty(stack_hd))
			delete pop(&stack_hd);
		while(!is_empty(bin))
			delete pop(&bin);
		clear_stack();
	}

	Avl_tree::node* Avl_tree::find_node(int the_key)
	{
		if(root == NULL)
		{
			cout << "The tree is empty\n";
			return NULL;
		}
		
		if((the_key > find_max(root)->data || the_key < find_min(root)->data))
		{
			cout << "There's not such data in the tree\n";
			return NULL;
		}
		
		Avl_tree::node* i = root;
		while(!is_leaf(i))
		{
			if(i->data > the_key)
				i = i->left;
			if(i->data < the_key)
				i = i->right;
			if(i->data == the_key)
				return i;
		}

		return NULL;
	}

	void Avl_tree::traverse()
	{
		stack* poped = new stack;
		node* i = root;

		if(!is_stack_empty())
			clear_stack();

		push(i);

		while(i != NULL && !is_stack_empty())
		{
			while(i->left != NULL)
			{
				i = i->left;
				push(i);
			}

			while(!is_stack_empty())
			{
				poped = pop();
				cout << poped->root->data << " ";
				if(poped->root->right != NULL)
				{
					i = poped->root->right;
					push(i);
					break;
				}
			}
		}
		cout << endl;
	}

	Avl_tree::node* Avl_tree::find_parent(Avl_tree::node* the_node)
	{
		Avl_tree::node* parent = root;

		if(the_node->left == NULL && the_node->right == NULL)
		{
			if(root->left->data == the_node->data || root->right->data == the_node->data)
				return parent;
		}
		
		Avl_tree::node* i = root;
		while(i != NULL)
		{
			if(i->data > the_node->data)
				i = i->left;
			else if(i->data < the_node->data)
				i = i->right;
			if(i->data == the_node->data)
				return parent;
			parent = i;
		}

		return parent;
	}

	bool Avl_tree::is_stack_empty()
	{
		return head->next == NULL;
	}

	bool Avl_tree::is_empty(stack* hd)
	{
		return hd->next == NULL;
	}

	void Avl_tree::push(Avl_tree::node* the_node)
	{
		Avl_tree::stack* new_head = new Avl_tree::stack;

		new_head->root = head->root;
		new_head->next = head->next;

		head->root = the_node;
		head->next = new_head;
	}

	void Avl_tree::push(Avl_tree::stack* hd, Avl_tree::node* the_node)
	{
		stack* new_node = new stack;

		new_node->root = hd->root;
		new_node->next = hd->next;

		hd->root = the_node;
		hd->next = new_node;
	}

	Avl_tree::stack* Avl_tree::pop()
	{
		Avl_tree::stack* poped = new Avl_tree::stack;

		poped->root = head->root;
		poped->next = head;

		head = head->next;

		delete poped->next;
		poped->next = NULL;

		return poped;
	}

	Avl_tree::stack* Avl_tree::pop(Avl_tree::stack** hd)
	{
		stack* poped = new stack;

		poped->root = (*hd)->root;
		poped->next = *hd;

		*hd = (*hd)->next;

		delete poped->next;
		poped->next = NULL;

		return poped;
	}

	int Avl_tree::get_height(node* root)
	{
		return root ? root->height : 0;
	}

	int Avl_tree::b_factor(node* root)
	{
		return get_height(root->right) - get_height(root->left);
	}

	void Avl_tree::fix_height(node* root)
	{
		int lh = get_height(root->left);
		int rh = get_height(root->right);
		root->height = (lh > rh ? lh : rh) + 1;
	}

	Avl_tree::node* Avl_tree::left_rot(node* root)
	{
		node* new_root = root->right;
		root->right = new_root->left;
		new_root->left = root;
		fix_height(root);
		fix_height(new_root);
		return new_root;
	}

	Avl_tree::node* Avl_tree::right_rot(node* root)
	{
		node* new_root = root->left;
		root->left = new_root->right;
		new_root->right = root;
		fix_height(root);
		fix_height(new_root);
		return new_root;
	}

	Avl_tree::node* Avl_tree::balance()
	{
		node* poped = NULL;
		node* prev_poped = NULL;

		while(!is_stack_empty())
		{
			poped = pop()->root;
			
			if(poped != NULL && prev_poped != NULL)
			{
				if(prev_poped->data > poped->data)
					poped->right = prev_poped;
				else if(prev_poped->data < poped->data)
					poped->left = prev_poped;
			}
			fix_height(poped);
			if(b_factor(poped) == 2)
			{
				if(b_factor(poped->right) == -1)
					poped->right = right_rot(poped->right);
				poped = left_rot(poped);
			}
			else if(b_factor(poped) == -2)
			{
				if(b_factor(poped->left) == 1)
					poped->left = left_rot(poped->left);
				poped = right_rot(poped);
			}
			prev_poped = poped;
		}

		return poped;
	}

	bool Avl_tree::is_leaf(Avl_tree::node* the_node)
	{
		return (the_node->left == NULL) && (the_node->right == NULL);
	}

	Avl_tree::node* Avl_tree::find_min(Avl_tree::node* the_node)
	{
		if(root == NULL)
		{
			cout << "The tree is empty\n";
			return NULL;
		}

		Avl_tree::node* i = the_node;
		while(i->left != NULL)
			i = i->left;

		return i;
	}

	Avl_tree::node* Avl_tree::find_max(Avl_tree::node* the_node)
	{
		if(root == NULL)
		{
			cout << "The tree is empty\n";
			return NULL;
		}

		Avl_tree::node* i = the_node;
		while(i->right != NULL)
			i = i->right;

		return i;
	}

	void Avl_tree::remove_leaf(Avl_tree::node* curr_node, Avl_tree::node* parent)
	{
		if((parent->left != NULL) && (parent->left->data == curr_node->data))
			parent->left = NULL;
		else if((parent->right != NULL) && (parent->right->data == curr_node->data))
			parent->right = NULL;
	}

	void Avl_tree::remove_interim(Avl_tree::node* curr_node, Avl_tree::node* parent)
	{
		if(parent == NULL)
		{
			if(parent->left != NULL)
				parent = parent->left;
			else if(parent->right != NULL)
				parent = parent->right;
		}
		else if(parent->left != NULL && parent->left->data == curr_node->data)
		{
			if(curr_node->right != NULL)
				parent->left = curr_node->right;
			if(curr_node->left != NULL)
				parent->left = curr_node->left;
		}
		else if(parent->right != NULL && parent->right->data == curr_node->data)
		{
			if(curr_node->right != NULL)
				parent->right = curr_node->right;
			if(curr_node->left != NULL)
				parent->right = curr_node->left;
		}
	}

	void Avl_tree::put_in_stack(Avl_tree::node* curr_node)
	{
		if(root->left == NULL && root->right != NULL)
		{
			push(root);
			push(root->right);
			return;
		}
		else if(root->left != NULL && root->right == NULL)
		{
			push(root);
			push(root->left);
			return;
		}

		Avl_tree::node* i = root;
		while(i != NULL)
		{
			push(i);
			if(i->data > curr_node->data)
				i = i->left;
			else if(i->data < curr_node->data)
				i = i->right;
			else break;
		}
	}

	void Avl_tree::clear_stack()
	{
		stack* temp = NULL;
		while(!is_stack_empty())
		{
			temp = head->next;
			delete head;
			head = temp;
		}
	}
	
	int Avl_tree::stack_size(Avl_tree::stack* hd)
	{
		int s_size = 0;

		while(hd->next != NULL)
		{
			hd = hd->next;
			s_size++;
		}

		return s_size;
	}
	
	Avl_tree::stack* Avl_tree::store(Avl_tree::node* the_node)
	{
		stack* new_stack = new stack;
		stack* poped = new stack;
		stack* storage = new stack;

		push(new_stack, the_node);

		while(the_node != NULL && !is_empty(new_stack))
		{
			while(the_node->left != NULL)
			{
				the_node = the_node->left;
				push(new_stack, the_node);
			}

			while(!is_empty(new_stack))
			{
				poped = pop(&new_stack);
				push(storage, poped->root);
				if(poped->root->right != NULL)
				{
					the_node = poped->root->right;
					push(new_stack, the_node);
					break;
				}
			}
		}
		
		return storage;
	}

	void Avl_tree::assign(Avl_tree::stack* l_store, Avl_tree::stack* r_store, Avl_tree::node* cpy_lts)
	{
		node* bin;
		if(stack_size(r_store) <= stack_size(l_store))
		{
			while(!is_empty(r_store))
				pop(&l_store)->root->data = pop(&r_store)->root->data;
			while(!is_empty(l_store))
			{
				bin  = pop(&l_store)->root;
				remove(bin->data);
			}
		}
		else
		{
			while(!is_empty(l_store))
				pop(&l_store)->root->data = pop(&r_store)->root->data;
			node* new_node;
			while(!is_empty(r_store))
			{
				new_node = pop(&r_store)->root;
				insert(new_node->data);
			}
		}
	}
}
