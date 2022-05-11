#pragma once

#include <vector>
#include <unordered_map>
#include <crossguid/guid.hpp>
#include <functional>

template<typename T>
class GuidContainer
{
public:
	class Iterator
	{
	public:
		using iterator_category = std::input_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		
		Iterator() = default;
		
		explicit Iterator(GuidContainer* container, size_t index);
		
		Iterator& operator++();
		Iterator operator++(int);
		
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		
		reference operator*();
		pointer operator->();
	
	private:
		GuidContainer* _container = nullptr;
		size_t _index = -1;
	};
	
	~GuidContainer();
	
	xg::Guid addNew(T&& value);
	void addExisting(const xg::Guid& guid, T&& value);
	
	void remove(const xg::Guid& guid);
	
	T* operator[](const xg::Guid& guid);
	
	Iterator begin();
	Iterator end();

private:
	T* _data = nullptr;
	std::vector<bool> _validity;
	
	size_t _capacity = 0;
	
	std::vector<size_t> _availableIndexes;
	std::unordered_map<xg::Guid, size_t> _refToIndex;
	
	void extend();
};

#pragma region iterator
template<typename T>
GuidContainer<T>::Iterator::Iterator(GuidContainer* container, size_t index)
{
	_container = container;
	_index = index;
}

template<typename T>
typename GuidContainer<T>::Iterator& GuidContainer<T>::Iterator::operator++()
{
	do
	{
		_index++;
	}
	while (!_container->_validity[_index] || _index == _container->_capacity);
	
	return *this;
}

template<typename T>
typename GuidContainer<T>::Iterator GuidContainer<T>::Iterator::operator++(int)
{
	GuidContainer<T>::Iterator temp = *this;
	++(*this);
	return temp;
}

template<typename T>
bool GuidContainer<T>::Iterator::operator==(const GuidContainer::Iterator& other) const
{
	return _index == other._index && _container == other._container;
}

template<typename T>
bool GuidContainer<T>::Iterator::operator!=(const GuidContainer::Iterator& other) const
{
	return !this->operator==(other);
}

template<typename T>
typename GuidContainer<T>::Iterator::reference GuidContainer<T>::Iterator::operator*()
{
	return _container->_data[_index];
}

template<typename T>
typename GuidContainer<T>::Iterator::pointer GuidContainer<T>::Iterator::operator->()
{
	return &_container->_data[_index];
}

#pragma endregion

template<typename T>
GuidContainer<T>::~GuidContainer()
{
	std::free(_data);
}

template<typename T>
xg::Guid GuidContainer<T>::addNew(T&& value)
{
	xg::Guid guid = xg::newGuid();
	
	addExisting(guid, std::forward<T>(value));
	
	return guid;
}

template<typename T>
void GuidContainer<T>::addExisting(const xg::Guid& guid, T&& value)
{
	if (_availableIndexes.empty())
	{
		extend();
	}
	
	size_t index = _availableIndexes.back();
	_availableIndexes.pop_back();
	
	T* memory = _data + index;
	new (memory) T(std::forward<T>(value));
	
	_validity[index] = true;
	
	_refToIndex.emplace(guid, index);
}

template<typename T>
void GuidContainer<T>::remove(const xg::Guid& guid)
{
	auto it = _refToIndex.find(guid);
	if (it == _refToIndex.end())
	{
		return;
	}
	
	size_t index = it->second;
	
	T* memory = _data + index;
	memory->~T();

#if _DEBUG
	std::memset(memory, 0xCC, 1 * sizeof(T));
#endif
	
	_validity[index] = false;
	_availableIndexes.push_back(index);
}

template<typename T>
T* GuidContainer<T>::operator[](const xg::Guid& guid)
{
	auto it = _refToIndex.find(guid);
	if (it == _refToIndex.end())
	{
		return nullptr;
	}
	
	return &_data[it->second];
}

template<typename T>
void GuidContainer<T>::extend()
{
	size_t previousCapacity = _capacity;
	
	if (_capacity == 0)
	{
		_data = static_cast<T*>(std::malloc(1 * sizeof(T)));

#if _DEBUG
		std::memset(_data, 0xCC, 1 * sizeof(T));
#endif
		
		_validity.resize(1);
		
		_capacity = 1;
	}
	else
	{
		_capacity *= 2;
		
		_data = static_cast<T*>(std::realloc(_data, _capacity * sizeof(T)));

#if _DEBUG
		std::memset(_data + previousCapacity, 0xCC, previousCapacity * sizeof(T));
#endif
		
		_validity.resize(_capacity);
	}
	
	for (size_t i = _capacity; i > previousCapacity; i--)
	{
		_availableIndexes.push_back(i-1);
	}
}

template<typename T>
typename GuidContainer<T>::Iterator GuidContainer<T>::begin()
{
	size_t firstIndex = _capacity;
	for (size_t i = 0; i < _capacity; i++)
	{
		if (_validity[i])
		{
			firstIndex = i;
			break;
		}
	}
	
	return GuidContainer<T>::Iterator(this, firstIndex);
}

template<typename T>
typename GuidContainer<T>::Iterator GuidContainer<T>::end()
{
	return GuidContainer<T>::Iterator(this, _capacity);
}
