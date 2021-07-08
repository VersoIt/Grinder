#include <algorithm>

#include "Container.hpp"

namespace EngineComponents
{
	template <class T>
	void Container<T>::push(T* element)
	{
		m_container.push_back(element);
	}

	template <class T>
	Container<T>::Container(const std::vector<T*>& container)
	{
		m_container = container;
	}

	template <class T>
	Container<T>::Container(const std::vector<T*>&& container)
	{
		m_container = container;
	}

	template <class T>
	Container<T>::Container(const Container&& container)
	{
		m_container = std::move(container.m_container);
	}

	template <class T>
	void Container<T>::offend(std::function<void(T*)> func)
	{
		std::for_each(m_container.begin(), m_container.end(), [&](T* element) {func(element); });
	}

	template <class T>
	std::vector<T*>& Container<T>::operator = (std::vector<T*>& copy)
	{
		m_container = copy;
		return m_container;
	}

	template <class T>
	std::vector<T*>& Container<T>::operator = (std::vector<T*>&& copy)
	{
		m_container = std::move(copy);
		return m_container;
	}

	template <class T>
	Container<T>::~Container() { offend([&](T* element) {delete element; }); }
}