/**
 * Description: A vector class which implements copy, move, initialize_list and 
 *              constructor and destructor. Also implements the copy, initialize_list 
 *              assignment, move,  and [] operator. 
 *
 * Author: Martin Pettersson & Christoffer Wiss
 *
 * Version: 2013-09-30
 */
 
 #include "vector.h"
 #include <iostream>
 
 // Deallocates all elements in vector.
 Vector::~Vector()
 {
	if(container != nullptr) 
	{
		delete[] container;	
	}	
 }

// Default constructor
Vector::Vector()
{
	vectorSize = 0;
	container = nullptr;
}

 // Constructor which creates a vector of input size.
 // Initializes each element to 0.
 Vector::Vector(const std::size_t size)
 {
	if(size > 0)
	{
	 	container = new unsigned int[size];
	 	for(std::size_t i = 0; i < size; i++)
	 	{
	 		container[i] = 0;		
	 	}
	}
	else
	{
		container = nullptr;
	}
 	vectorSize = size;
 }
 
 // Copy-constructor which copies the elements of
 // the new vector from input vector elements.
 Vector::Vector(const Vector& obj)
 {
	vectorSize = obj.vectorSize;	
	if(vectorSize > 0)
	{
	 	container = new unsigned int[vectorSize];
	 	
	 	for(std::size_t i = 0; i < vectorSize; i++)
	 	{
	 		container[i] = obj.container[i];		
	 	}
	}
	else
	{
		container = nullptr;
	}
 }
 

 // Move-constructor which pilfers another object's elements.
 // Remember: order is important since it mirrors the actual constructor calls.
 Vector::Vector(Vector&& obj) noexcept: container(obj.container), vectorSize(obj.vectorSize)
 {
 	obj.vectorSize = 0;
 	obj.container = nullptr;
 }
 
 // Initializer list constructor.
 Vector::Vector(const std::initializer_list<unsigned int> list)
 {
	vectorSize = list.size();
	if(vectorSize > 0)
	{
		container = new unsigned int[vectorSize];
		std::copy(list.begin(), list.end(), container);
	}
	else
	{
		container = nullptr;
	}
 }

 // Copy assignment operator.
 // Copies the elements from input to a new obj.
 Vector &Vector::operator=(const Vector &rhs)
 {
	// Make sure that we do not use move operator to ourself 
 	// (that would be weird)
	if(this != &rhs)
	{
		vectorSize = rhs.vectorSize;	
		delete[] container;
		if(vectorSize > 0)
		{
			container = new unsigned int[vectorSize];
			
			for(std::size_t i = 0; i < vectorSize; i++)
			{
				container[i] = rhs.container[i];		
			}
		}
		else
		{
			container = nullptr;
		}
 	}
 	return *this;
 }
 
 // Move assignment operator
 Vector &Vector::operator=(Vector&& obj) noexcept
 {
 	// Make sure that we do not use move operator to ourself 
 	// (that would be weird)
 	if(this != &obj)
 	{
 		// Release previously allocated resources
 		delete[] container;
 		vectorSize = 0;
 		
 		// Pilfer the other object's resources
 		container = obj.container;
 		vectorSize = obj.vectorSize;
 		
 		// Reset other object's resources - leave in destructable state
 		obj.container = nullptr;
 		obj.vectorSize = 0;
 	}
 	return *this;
 }
 
 // Index assignment operator
 // Returns a reference value.
 unsigned int &Vector::operator[](std::size_t index)
 {
 	if(index < vectorSize)
	{
	 	return container[index];	
	}
	else
	{
		throw std::out_of_range("Error: Trying to access a member out of bounds!");
	}	
 }
 
 // Index assignment operator
 // Returns a const reference value.
 unsigned int const &Vector::operator[](std::size_t index) const
 {
	if(index < vectorSize)
	{
	 	return container[index];	
	}
	else
	{
		throw std::out_of_range("Error: Trying to access member out of bounds!");
	}		
 }
 
 // Initializer_list operator
 // Initializes the vector with the elements supplied by the list.
 // This will change the size of the object and all of its elements.
 Vector &Vector::operator=(std::initializer_list<unsigned int> list)
 {
	vectorSize = list.size();
	if(container != nullptr)
	{
		delete[] container; 			  // Remove old data
	}

	if(vectorSize > 0)
	{
		container = new unsigned int[vectorSize]; // Initialize new container space
 		std::copy(list.begin(), list.end(), container);
	}
	else
	{
		container = nullptr;
	}
	
	return *this;
 }
 
 // Returns the size of the vector.
 unsigned int Vector::size() const
 {
 	return vectorSize;
 }
