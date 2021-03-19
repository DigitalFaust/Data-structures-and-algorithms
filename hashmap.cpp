#include"hashmap.h"
using std::cout;
using std::cin;
using std::endl;

namespace data_struct
{
	Hashmap::Hashmap()
	{
		size = 1;
		map = new hashmap;
		map->arr[0] = new list;
		map->arr[0]->key = 0;
		map->arr[0]->next = NULL;
	}

	Hashmap::Hashmap(int init_size)
	{
		size = init_size;
		map = new hashmap(size);
		for(int i = 0; i < size; i++)
		{
			map->arr[i] = new Hashmap::list;
			map->arr[i]->key = 0;
			map->arr[i]->next = NULL;
		}
	}

	int Hashmap::find_pos(int the_key)
	{
		int pos = hash(the_key);
		int absnc = -1;

		if(pos >= size)
			return absnc;

		Hashmap::list* i = map->arr[pos];

		while(!is_end(i))
		{
			if(i->key == the_key)
				return pos;
			i = i->next;
		}

		return absnc;
	}

	bool Hashmap::is_key(int the_key)
	{
		return the_key == find_key(the_key)->key;
	}

	void Hashmap::insert(int the_key)
	{
		int pos = hash(the_key);

		add_to_buck(map->arr[pos], the_key);
	}

	void Hashmap::remove(int the_key)
	{
		Hashmap::list* prev_node = find_prev(the_key);

		if(prev_node == NULL)
		{
			Hashmap::list* temp = find_key(the_key);
			Hashmap::list* del = temp->next;
			temp->key = temp->next->key;
			temp->next = temp->next->next;
			delete del;
			return;
		}

		Hashmap::list* temp = prev_node->next->next;
		delete prev_node->next;
		prev_node->next = temp;
	}

	ostream& operator<<(ostream& output, Hashmap& smpl)
	{
		int i = 0;
		Hashmap::list* itr = NULL;
		
		while(i < smpl.size)
		{
			itr = smpl.map->arr[i];
			cout << i << ": ";
			while(!smpl.is_end(itr))
			{
				output << itr->key << " ";
				itr = itr->next;
			}
			output << endl;
			i++;
		}

		return output;
	}

	istream& operator>>(istream& input, Hashmap& smpl)
	{
		int val = 0;
		input >> val;
		smpl.insert(val);

		return input;
	}

	Hashmap::~Hashmap()
	{
		for(int i = 0; i < size; i++)
			delete[] map->arr[i];
		delete[] map->arr;
		delete map;
	}

	bool Hashmap::is_end(Hashmap::list* buck)
	{
		return buck->next == NULL;
	}

	int Hashmap::hash(int the_key)
	{
		return the_key % size;
	}

	Hashmap::list* Hashmap::find_key(int the_key)
	{
		int pos = hash(the_key);

		if(pos >= size)
			return NULL;
		
		Hashmap::list* i = map->arr[pos];

		while(!is_end(i))
		{
			if(i->key == the_key)
				return i;
			i = i->next;
		}
		
		return NULL;
	}

	Hashmap::list* Hashmap::find_prev(int the_key)
	{
		int pos = find_pos(the_key);

		if(pos < 0)
			return NULL;

		Hashmap::list* i = map->arr[pos];

		while(!is_end(i))
		{
			if(i->next->key == the_key)
				return i;
			i = i->next;
		}
			
		return NULL;
	}

	void Hashmap::add_to_buck(Hashmap::list* buck, int the_key)
	{
		Hashmap::list* new_node = new Hashmap::list;

		new_node->key = buck->key;
		new_node->next = buck->next;

		buck->key = the_key;
		buck->next = new_node;
	}
}
