#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
class stack
{
public:
	stack();
	~stack();
	stack(stack<T> const&);
	stack& operator=(stack<T> const&);
	size_t count() const;
	size_t array_size() const;
	void push(T const&);
	T pop();
	T last()const;
	void print(std::ostream&stream)const;
	friend std::ostream&operator << (std::ostream&stream, const stack<T>&);
	void swap(stack<T>&);
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};

template <typename T>
stack<T>::stack() : array_{ nullptr }, array_size_{ 0 }, count_{ 0 } {}
template <typename T>
stack<T>::~stack()
{
	delete[] array_;
}
template <typename T>
stack<T>::stack(stack<T> const& other)
{
	array_size_ = other.array_size_;
	count_ = other.count_;	
	std::copy(other.array_, other.array_ + count_, array_);
}
template <typename T>
auto stack<T>::operator=(stack<T> const & other) -> stack&
{
	if (&other != this)
		stack(other).swap(*this);
	return *this;
}
template <typename T>
size_t stack<T>::array_size() const
{
	return array_size_;
}
template <typename T>
size_t stack<T>::count() const
{
	return count_;
}
template <typename T>
void stack<T>::push(T const & value)
{
	if (array_size_ == 0)
	{
		array_size_ = 1;
		array_ = new T[array_size_]();
	}
	else if (array_size_ == count_)
	{
		array_size_ *= 2;
		T * new_array = new T[array_size_]();
		std::copy(array_, array_ + count_, new_array);
		delete[] array_;
		array_ = new_array;
	}
	array_[count_++] = value;
}
template <typename T>
T stack<T>::pop()
{
	if (count_ == 0)
		throw std::logic_error("Stack is empty");
	else
	{
		T * new_array = new T[array_size_]();
		T value = array_[--count_];
		std::copy(array_, array_ + count_, new_array);
		delete[] array_;
		array_ = new_array;
		return value;
	}
}
template <typename T>
T stack<T>::last()const
{
	if (count_ == 0)
		throw std::logic_error("Stack is empty");
	else return array_[count_ - 1];
}
template <typename T>
void stack<T>::print(std::ostream&stream)const
{
	for (unsigned int i = 0; i < count_; ++i)
		stream << array_[i] << " ";
	stream << std::endl;
}
template <typename T>
std::ostream& operator << (std::ostream&stream, const stack<T>&stack_)
{
	return stack_.print(stream);
}
template <typename T>
void stack<T>::swap(stack<T>& other)
{
	std::swap(array_, other.array_);
	std::swap(array_size_, other.array_size_);
	std::swap(count_, other.count_);
}
