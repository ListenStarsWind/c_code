#pragma once

#include"version_control.h"
#include<assert.h>
#include<algorithm>
#include"reverse_iterator.h"

namespace wind {

	template<class T>
	struct __list_node_base {
		T _val;
		__list_node_base<T>* _prev;
		__list_node_base<T>* _next;

		__list_node_base(const T& val = T())
			:_val(val)
			, _prev(nullptr)
			, _next(nullptr)
		{}
	};

	template<class T, class ref, class ptr>
	struct __list_iterator_base {
		typedef __list_node_base<T> node;
		typedef __list_iterator_base<T, ref, ptr> self;

		node* _ptr;

		__list_iterator_base(node* ptr)
			:_ptr(ptr)
		{}

		__list_iterator_base(const self& obj)
			:_ptr(obj._ptr)
		{}

		self& operator++()
		{
			_ptr = _ptr->_next;
			return *this;
		}

		self& operator++(int)
		{
			self ret = *this;
			_ptr = _ptr->_next;
			return ret;
		}

		self& operator--()
		{
			_ptr = _ptr->_prev;
			return *this;
		}

		self& operator--(int)
		{
			self ret = *this;
			_ptr = _ptr->_prev;
			return ret;
		}

		ref operator*() const
		{
			return _ptr->_val;
		}

		ptr operator->()const
		{
			return &(_ptr->_val);
		}

		bool operator!=(const self& obj)const
		{
			if (_ptr != obj._ptr)
				return true;
			else
				return false;
		}

		bool operator==(const self& obj)const
		{
			if (*this != obj)
				return false;
			else
				return true;
		}
	};

	template<class T>
	class list {
		typedef __list_node_base<T> node;

		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;

		typedef const T& const_reference;
		typedef const T* const_pointer;

		
		node* __init_head_node()
		{
			node* head = new node();
			head->_prev = head;
			head->_next = head;
			head->_val = T();
			return head;
		}
	public:
		typedef __list_iterator_base<value_type, reference, pointer> iterator;
		typedef __list_iterator_base<value_type, const_reference, const_pointer> const_iterator;

		typedef __reverse_iterator<iterator, reference, pointer> reverse_iterator;
		typedef __reverse_iterator<const_iterator, const_reference, const_pointer> const_reverse_iterator;

		list()
			:_head(__init_head_node())
			, _size(0)
		{}

		void push_back(const T& val)
		{
			node* oldTail = _head->_prev;
			node* newNode = new node(val);
			newNode->_next = _head;
			newNode->_prev = oldTail;
			oldTail->_next = newNode;
			_head->_prev = newNode;
			_size++;
		}

		iterator begin()
		{
			return _head->_next;
		}

		iterator end()
		{
			return _head;
		}

		const_iterator begin()const
		{
			return _head->_next;
		}

		const_iterator end()const
		{
			return _head;
		}

#ifdef USING_SGI_STYLE

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{	
			return reverse_iterator(begin());
		}

		const_reverse_iterator rbegin()const
		{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator rend()const
		{
			return const_reverse_iterator(begin());
		}

#else

		reverse_iterator rbegin()
		{
			iterator it = end();
			return reverse_iterator(--it);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin()const
		{
			const_iterator it = end();
			return const_reverse_iterator(--it);
		}

		const_reverse_iterator rend()const
		{
			return const_reverse_iterator(end());
		}

#endif

		bool empty()const
		{
			if (begin() == end())
				return true;
			else
				return false;
		}

		size_t size()const
		{
			return _size;
		}

		iterator insert(iterator pos, const T& val)
		{
			node* curr = pos._ptr;
			node* prev = curr->_prev;
			node* newNode = new node(val);
			newNode->_prev = prev;
			newNode->_next = curr;
			curr->_prev = newNode;
			prev->_next = newNode;
			_size++;
			return newNode;
		}

		iterator erase(iterator pos)
		{
			assert(!empty());
			node* curr = pos._ptr;
			node* prev = curr->_prev;
			node* next = curr->_next;
			prev->_next = next;
			next->_prev = prev;
			delete curr;
			_size--;
			return next;
		}

		void pop_back()
		{
			erase(--end());
		}

		void push_front(const T& val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(--end());
		}

		void clean()
		{
			list::iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		~list()
		{
			clean();
			delete _head;
		}

		list(const list& l)
			:_head(__init_head_node())
			, _size(0)
		{
			for (const auto& e : l)
			{
				push_back(e);
			}
		}

		list& operator=(const list& l)
		{
			if (this != &l)
			{
				clean();
				for (auto& e : l)
				{
					push_back(e);
				}
			}
			return *this;
		}

		void swap(const list& l)
		{
			std::swap(_head, l._head);
			std::swap(_size, l._size);
		}

	private:
		node* _head;
		size_t _size;
	};
}
