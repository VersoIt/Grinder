#pragma once
#ifndef _CONTAINER_HPP_
#define _CONTAINER_HPP_

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

		Container(const Container&& container);

		std::vector<T*>& operator = (std::vector<T*>& copy);
		std::vector<T*>& operator = (std::vector<T*>&& copy);

		const std::vector<T*>& getContainer() const { return m_container; }
		std::vector<T*>& getContainer() { return m_container; }

		virtual ~Container();

	private:
		std::vector<T*> m_container;

	};
}

#include "Container.inl"
#endif // _CONTAINER_HPP_