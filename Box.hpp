#pragma once
#include <cstddef>
#include <iostream>
#include <ostream>

template <typename T> class Box
{
public:
	Box() : m_ptr(new T) {}
	Box(const T &v) : m_ptr(new T(v)) {}
	Box(const Box &other) : m_ptr(new T(*other.m_ptr)) {}
	~Box() { delete m_ptr; }

	Box &operator=(const Box &other)
	{
		if (this == &other)
			return *this;
		delete m_ptr;
		m_ptr = new T(*other.m_ptr);
		return *this;
	}
	T &operator=(const T &value)
	{
		*m_ptr = value;
		return *m_ptr;
	}
	T &operator*() { return *m_ptr; }
	const T &operator*() const { return *m_ptr; }
	T &operator->() { return *this; }
	const T &operator->() const { return *this; }

private:
	T *m_ptr;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Box<T> &box)
{
	os << *box;
	return os;
}

template <typename T> class Rc
{
public:
	Rc() : m_ptr(new T), m_count(new std::size_t(1)) {}
	Rc(const T &value) : m_ptr(new T(value)), m_count(new std::size_t(1)) {}
	Rc(const Rc &other) : m_ptr(other.m_ptr), m_count(other.m_count)
	{
		*m_count += 1;
	}
	~Rc()
	{
		*m_count -= 1;
		if (*m_count == 0) {

			delete m_ptr;
			delete m_count;
		}
	}
	Rc &operator=(const Rc &other)
	{
		if (this == &other)
			return *this;
		*m_ptr = *other.m_ptr;
		m_count = other.m_count;
		*m_count += 1;
	}
	T &operator=(const T &value)
	{
		*m_ptr = value;
		return *m_ptr;
	}
	T &operator*() { return *m_ptr; }
	const T &operator*() const { return *m_ptr; }
	T &operator->() { return *m_ptr; }
	const T &operator->() const { return *m_ptr; }

private:
	T *m_ptr;
	std::size_t *m_count;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Rc<T> &rc)
{
	os << *rc;
	return os;
}
