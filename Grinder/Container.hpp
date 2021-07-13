#pragma once
#ifndef _CONTAINER_HPP_
#define _CONTAINER_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

namespace EngineComponents
{
	template<class T>
	class Container
	{
	public:
		virtual void push(T* element);

		virtual void offend(std::function<void(T*)> func);

		Container() : m_container{}
		{
		}

		Container(const std::vector<T*>& container);
		Container(const std::vector<T*>&& container);

		Container(const Container&& container) noexcept;

		std::vector<T*>& operator = (std::vector<T*>& copy);
		std::vector<T*>& operator = (std::vector<T*>&& copy);

		const std::vector<T*>& getContainer() const { return m_container; }
		std::vector<T*>& getContainer() { return m_container; }

		virtual ~Container();

	private:
		std::vector<T*> m_container;

	};

	/*
	* Initialiaztion
	*/

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
	Container<T>::Container(const Container&& container) noexcept
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
#endif // _CONTAINER_HPP_