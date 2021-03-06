#ifndef LIST
#define LIST

#include "GlobalConstants.h"
#include <assert.h>
#include <string>

/*----------------------------
This is a base class for all the lists this program has
We have used a template to be able to work whith diferent
types of arguments.

The list is dynamic and resizes automatically when inserting elements.
On destruction deletes every dynamic object held.
To prevent this (ie elements held should not be destroyed), call erase in child destructor.

By default, the list orders itself according to the valor returned by getId method of
elements inserted. If you choose to override insert to prevent order, make sure you override
search as well (it is a binary search)
------------------------------*/

//Template for lists
template <class T>
class List
{
public:
	List() : counter(0), list(nullptr) { init(INICIALES); }
	~List() { release(); }

	inline bool full() const  { return (counter == dim); }
	inline bool empty() const { return counter == 0; }
	inline int length() const { return this->counter; }

	T* operator [](int i) { assert(0 <= i && i < counter);  return list[i]; }

	bool insert(T* elem);
	bool destroy(const std::string &id); //Deletes element and erases from list.

	bool search(const std::string &id, int &pos, int &left_key, int &right_key) const;

	void save(const std::string &name);
	bool load(const std::string &name);

protected:
	int counter, dim;
	T** list;

	//Moves the list one space right from pos to end
	void shiftRight(const int pos);
	//Eliminates pointer in pos
	void shiftLeft(const int pos);

	void init(int dim);
	void release();
	void resize(int dim);
};

//It search the position where an element should be,
//makes space for him, and inserts it in this position
template<class T>
bool List<T>::insert(T* elem)
{
	//resize if necessary
	if (full()) resize(dim * 3 / 2 + 1);
	//Look for corresponding position
	int pos;
	int left_key = 0, right_key = counter - 1;
	search(elem->nombre, pos, left_key, right_key);
	//Make space for newcomer
	shiftRight(pos);
	//Insert the elem
	list[pos] = elem;
	counter++;
	return true;
}

//Searchs for the element you choose
//on the list, and deletes it
template<class T>
bool List<T>::destroy(const std::string &id)
{
	int pos;
	int left_key = 0, right_key = counter - 1;
	if (search(id, pos, left_key, right_key))
	{
		assert(0 <= pos && pos < counter);
		delete list[pos];
		shiftLeft(pos);
		counter--;
		return true;
	}
	else return false;
}

//Searchs the position where 
//an element should be
template<class T>
bool List<T>::search(const std::string &id, int &pos, int &left_key, int &right_key) const
{
	if (left_key <= right_key)
	{
		pos = (left_key + right_key) / 2;

		if (list[pos]->nombre == id) return true;

		else if (list[pos]->nombre < id)
			left_key = pos + 1;
		else right_key = pos - 1;

		return search(id, pos, left_key, right_key);
	}
	else
	{
		pos = left_key;
		return false;
	}
}

//Saves all the elements of the list on the
//file you choose, and put the scentinel at
//the end of the file
template<class T>
void List<T>::save(const std::string &name)
{
	std::ofstream file;

	file.open(name);

	for (int i = 0; i < this->length(); i++)
	{
		this->list[i]->save(file);
	}

	file.close();
}

//Loads the elemrnts of the list
//from the file you choose
template<class T>
bool List<T>::load(const std::string &name)
{
	std::ifstream file;
	bool right;
	T* elem;

	file.open(name);

	if (file.is_open())
	{
		right = true;

		for (int i = 0; right; i++)
		{
			elem = new T;

			if (!elem->load(file))
			{
				delete elem;
				right = false;
			}
			else this->insert(elem);
		}

		file.close();

		return true;
	}
	else return false;
}

//It moves every elemnts on the list
//to the right from the position you choose
template<class T>
void List<T>::shiftRight(const int pos)
{
	assert(!full());
	for (int i = counter; i > pos; i--)
	{
		list[i] = list[i - 1];
	}
}

//It moves every elemnts on the list
//to the right from the position you choose
template<class T>
void List<T>::shiftLeft(const int pos)
{
	assert(0 <= pos && pos < counter);
	for (int i = pos; i < counter - 1; i++)
	{
		list[i] = list[i + 1];
	}
}

template<class T>
void List<T>::init(int dim)
{
	assert(list == nullptr);
	if (dim <= 0)
	{
		list = nullptr;
		this->dim = 0;
	}
	else {
		list = new T*[dim];

		for (int i = 0; i < dim; i++)
		{
			list[i] = nullptr;
		}

		this->dim = dim;
	}
	this->counter = 0;
}

template<class T>
void List<T>::release()
{
	if (this->dim != 0)
	{
		for (int i = 0; i < this->counter; i++)
		{
			if (list[i] != nullptr)
			{
				delete list[i];
				list[i] = nullptr;
			}
		}

		delete[] list;
		list = nullptr;
		this->counter = 0;
		this->dim = 0;
	}
}

template<class T>
void List<T>::resize(int dim)
{
	if (dim > this->dim)
	{
		T** newlist = new T*[dim];

		for (int i = 0; i < this->counter; i++)
		{
			newlist[i] = (*this)[i];
		}
		for (int i = this->counter; i < dim; i++)
		{
			newlist[i] = nullptr;
		}
		delete[] list;

		list = newlist;
		this->dim = dim;
	}
}
#endif