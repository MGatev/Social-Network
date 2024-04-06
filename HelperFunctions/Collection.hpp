#pragma once

template <typename T>
class Collection {
protected:
	T* members;
	size_t size;
	size_t capacity;

	void copyFrom(const Collection<T>& other);
	void free();	
	void moveFrom(Collection<T>&& other) noexcept;
	void resize();

public:
	Collection();
	explicit Collection(const size_t size);
	Collection(const Collection<T>& other);
	Collection(Collection<T>&& other) noexcept;
	Collection& operator=(const Collection<T>& other);
	Collection& operator=(Collection<T>&& other) noexcept;

	const T& getTByIndex(const size_t index)const;
	T& getTByIndex(const size_t index);
	size_t getTCount()const;

	void setTByIndex(const T& newMember, const size_t index);
	void setTByIndex(T&& newMember, const size_t index);
	void addT(const T& newMember);
	void addT(T&& newMember);
	void deleteTByIndex(const size_t index);

	T& operator[](size_t index); 
	T operator[](size_t index) const;
};

namespace {
	template <typename T>
	void swap(T& lhs, T& rhs) {
		T temp = lhs;
		lhs = rhs;
		rhs = temp;
	}
}

template <typename T>
void Collection<T>::copyFrom(const Collection<T>& other) {
	capacity = other.capacity;
	size = other.size;
	members = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		members[i] = other.members[i];
	}
}

template <typename T>
void Collection<T>::free() {
	delete[] members;
	members = nullptr;
	size = capacity = 0;
}

template <typename T>
void Collection<T>::moveFrom(Collection&& other) noexcept {
	members = other.members;
	other.members = nullptr;
	size = other.size;
	capacity = other.capacity;
}

template <typename T>
void Collection<T>::resize() {
	T* newCollection = new T[capacity *= 2];

	for (size_t i = 0; i < size; i++)
	{
		newCollection[i] = members[i];
	}

	delete[] members;
	members = newCollection;
	newCollection = nullptr;
}

template <typename T>
Collection<T>::Collection() {
	members = nullptr;
	capacity = 0;
	size = 0;
}

template <typename T>
Collection<T>::Collection(const size_t size) {
	members = new T[size];
	capacity = size;
	this->size = 0;
}

template <typename T>
Collection<T>::Collection(const Collection<T>& other) {
	copyFrom(other);
}

template <typename T>
Collection<T>::Collection(Collection<T>&& other) noexcept {
	moveFrom(std::move(other));
}

template <typename T>
Collection<T>& Collection<T>::operator=(const Collection<T>& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
Collection<T>& Collection<T>::operator=(Collection<T>&& other) noexcept {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <typename T>
const T& Collection<T>::getTByIndex(const size_t index)const {
	if (index >= size)
		throw std::out_of_range("Too big index!");

	return members[index];
}

template <typename T>
T& Collection<T>::getTByIndex(const size_t index){
	if (index >= size)
		throw std::out_of_range("Too big index!");

	return members[index];
}

template <typename T>
size_t Collection<T>::getTCount()const {
	return size;
}

template <typename T>
void Collection<T>::setTByIndex(const T& newMember, const size_t index) {
	if (index >= size)
		throw std::out_of_range("Too big index!");

	members[index] = newMember;
}

template <typename T>
void Collection<T>::setTByIndex(T&& newMember, const size_t index) {
	if (index >= size)
		throw std::out_of_range("Too big index!");

	members[index] = std::move(newMember);
}

template <typename T>
void Collection<T>::addT(const T& newMember) {
	if (capacity == 0)
	{
		members = new T[4];
		capacity = 4;
	}

	if (size == capacity)
		resize();

	members[size++] = newMember;
}

template <typename T>
void Collection<T>::addT(T&& newMember) {
	if (capacity == 0)
	{
		members = new T[4];
		capacity = 4;
	}

	if (size == capacity)
		resize();

	members[size++] = std::move(newMember);
}

template <typename T>
void Collection<T>::deleteTByIndex(const size_t index) {
	if (index >= size)
		throw std::out_of_range("Too big index!");

	members[index] = T();
	swap(members[index], members[--size]);
}

template <typename T>
T& Collection<T>::operator[](size_t index) //������������ ������
{
	return members[index];
}

template <typename T>
T Collection<T>::operator[](size_t index) const //���������� ������ 
{
	return members[index];
}
