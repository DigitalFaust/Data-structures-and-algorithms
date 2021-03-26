#ifndef HASHMAP_H
#define HASHMAP_H

#include<iostream>
using std::ostream;
using std::istream;

namespace data_struct
{
	class Hashmap
	{
		public:
			struct list
			{
				int key;
				list* next;
			};
			struct hashmap
			{
				list** arr;
				int size;
				hashmap()
				{
					size = 0;
					arr = new list*[size];
				}
				hashmap(int init_size)
				{
					size = init_size;
					arr = new list*[size];
				}
			};
			Hashmap();
			Hashmap(int init_size);
			int find_pos(int the_key);
			bool is_key(int the_key);
			void insert(int the_key);
			void remove(int the_key);
			friend ostream& operator<<(ostream& output, Hashmap& smpl);
			friend istream& operator>>(istream& input, Hashmap& smpl);
			~Hashmap();
		private:
			bool is_end(list* buck);
			int hash(int the_key);
			list* find_key(int the_key);
			list* find_prev(int the_key);
			void add_to_buck(list* buck, int the_key);
			hashmap* map;
			int size;
	};
}

#endif //HASHMAP_H
