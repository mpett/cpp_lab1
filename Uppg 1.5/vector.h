/**
 * Description: A dynamic vector class which implements copy, move, initialize_list and 
 *              constructor and destructor. Also implements the copy, initialize_list 
 *              assignment, move,  and [] operator among other. 
 *
 * Author: Martin Pettersson & Christoffer Wiss
 *
 * Version: 2013-10-01
 */

 #include <initializer_list>
 #include <stdexcept>
 #include <algorithm>
 #include <iostream>

 template<class T>

 class Vector
 {
 	public:
 		// Destructor
 		~Vector();

		// Default constructor
 		Vector();

 		// Constructor
 		explicit Vector(const std::size_t size);
 		
 		// Constructor with value and size.
 		explicit Vector(const std::size_t size, const T &value);

 		// Copy-constructor
 		Vector(const Vector<T>& obj);

 		// Move-constructor
 		Vector(Vector<T>&& obj) noexcept;

		// Initializer_list constructor
 		Vector(const std::initializer_list<T> list);
 		
 		// Copy assignment operator
 		Vector &operator=(const Vector<T> &rhs);
 		
 		// Move assignment operator
 		Vector &operator=(Vector<T>&& obj) noexcept;
 		
 		// Index assignment operator
 		T &operator[](std::size_t index);
		
		// Index access operator
 		T const &operator[](std::size_t index) const;
 		
 		// Initializer_list assignment operator
 		Vector &operator= (std::initializer_list<T> list);
 		
		// Copies input element into the position after the last element
		void push_back(const T&);
		
		// Inserts the element at input location and moves all elements
		// to the right
		void insert(std::size_t, const T&);
		
		// Erases the element at input location
		void erase(std::size_t);
		
		// Removes all elements in vector
		void clear();
		
		// Sorts the vector in ascending (true) or descending (false) order.
		// Default sort is ascending if no input is given.
		void sort(bool ascending = true);
		
		// Sorts the vector + removes all duplicant elements. 
		// Default sort is ascending if no input is given.
		void unique_sort(bool ascending = true);
		
		// Returns true if element exists in vector otherwise false.
		bool exists(const T&);
		
		// Returns the size of the vector
		std::size_t size() const;
		
		// Returns the capacity of the vector
		std::size_t capacity() const;
		
		// Returns pointer to location of first element in vector
		T *begin() const;
		
		// Returns pointer to the location of the last constructed element
		T *end() const;
 	
 	private:
 		static std::allocator<T> alloc; // Allocates elements
 		
		// Checks if there is free space left in vector, otherwise reallocates memory
		void chk_n_alloc();			 
		
		// Allocates new memory and copies input into this memory
		std::pair<T*, T*> alloc_n_copy ( const T*, const T*);

		// Destroy the elements and free the space
		void free();
		
		// Get more space and copy existing elements
		void reallocate();

		T *first_element;	// Pointer to first element in vector
		T *first_free;		// Pointer to first free location in vector
		T *cap;				// Pointer to location after the end of the space allocated for the vector
 };

/**
 * Description: A vector class which implements copy, move, initialize_list and 
 *              constructor and destructor. Also implements the copy, initialize_list 
 *              assignment, move,  and [] operator among other. 
 *
 * Author: Martin Pettersson & Christoffer Wiss
 *
 * Version: 2013-10-01
 */

 template <class T> std::allocator<T> Vector<T>::alloc; //Need to define allocator
 
 // Deallocates all elements in vector.
 template <class T> Vector<T>::~Vector()
 {
	free();
 }

// Default constructor
template <class T> Vector<T>::Vector()
{
	first_element = nullptr;
	first_free    = nullptr;
	cap		    = nullptr;
}

 // Constructor which creates a vector of input size.
 // Initializes each element to default value.
 template <class T> Vector<T>::Vector(const std::size_t size)
 {
	if(size > 0)
	{
		// Allocate space for elements
		T *newData = alloc.allocate(size);
		
		// Initialize elements with default value
		for(std::size_t i = 0; i < size; i++)
	 	{
	 		alloc.construct((newData+i),T());	
	 	}
		
		// Update variables
		first_element = newData;
		first_free    = (first_element + size);
		cap           = (first_element + size);
	}
	else
	{
		first_element = nullptr;
		first_free    = nullptr;
		cap		    = nullptr;
	}
 }

 // Constructor which creates a vector of input size with each 
 // element assigned to input value.
 template <class T> Vector<T>::Vector(const std::size_t size, const T &value)
 {
 	if(size > 0)
	{
		// Allocate space for elements
		T *newData = alloc.allocate(size);
		
		// Initialize elements with 
		for(std::size_t i = 0; i < size; i++)
	 	{
	 		alloc.construct((newData+i),value);		
	 	}
		
		// Update variables
		first_element = newData;
		first_free    = (first_element + size);
		cap           = (first_element + size);
	}
	else
	{
		first_element = nullptr;
		first_free    = nullptr;
		cap           = nullptr;
	}
 }
 
 // Copy-constructor which copies the elements of
 // the new vector from input vector elements.
 template <class T> Vector<T>::Vector(const Vector<T>& obj)
 {
	std::pair<T*,T*> newData = alloc_n_copy(obj.begin(), obj.end());
	first_element = newData.first;
	first_free    = newData.second;
	cap 	         = newData.second;
 }
 
 // Move-constructor which pilfers another object's elements.
 // Remember: order is important since it mirrors the actual constructor calls.
 template <class T> Vector<T>::Vector(Vector<T>&& obj) noexcept: first_element(obj.first_element), first_free(obj.first_free), cap(obj.cap)
 {
 	obj.first_element = nullptr;
	obj.first_free	   = nullptr;
	obj.cap	        = nullptr;
 }
 
 // Initializer list constructor.
 template <class T> Vector<T>::Vector(const std::initializer_list<T> list)
 {
	if(list.size() > 0)
	{
		std::pair<T*,T*> newData = alloc_n_copy(list.begin(), list.end());
		first_element = newData.first;
		first_free    = newData.second;
		cap 	         = newData.second;
	}
	else
	{
		first_element = nullptr;
		first_free    = nullptr;
		cap		    = nullptr;
	}
 }

 // Copy assignment operator.
 // Copies the elements from input to a new obj.
 template <class T> Vector<T> &Vector<T>::operator=(const Vector<T> &rhs)
 {
 	// Make sure that we do not use move operator to ourself 
 	// (that would be weird)
	if(this != &rhs)
	{
		std::pair<T*,T*> newData = alloc_n_copy(rhs.begin(), rhs.end());
		free();
		first_element = newData.first;
		first_free    = newData.second;
		cap		    = newData.second;
 	}
 	return *this;
 }
 
 // Move assignment operator
 template <class T> Vector<T> &Vector<T>::operator=(Vector<T>&& obj) noexcept
 {
 	// Make sure that we do not use move operator to ourself 
 	// (that would be weird)
 	if(this != &obj)
 	{
 		// Release previously allocated resources
 		free();
 		
 		// Pilfer the other object's resources
 		first_element = obj.first_element;
		first_free    = obj.first_free;
		cap           = obj.cap;
 		
 		// Reset other object's resources - leave in destructable state
 		obj.first_element = nullptr;
		obj.first_free	   = nullptr;
		obj.cap           = nullptr;
 	}
 	return *this;
 }
 
 // Index assignment operator
 // Returns a reference value.
 template <class T> T &Vector<T>::operator[](std::size_t index)
 {
 	if(index < size())
	{
	 	return first_element[index];	
	}
	else
	{
		throw std::out_of_range("Error: Trying to access a member out of bounds!");
	}	
 }
 
 // Index access operator
 // Returns a const reference value.
 template <class T> T const &Vector<T>::operator[](std::size_t index) const
 {
	if(index < size())
	{
	 	return first_element[index];	
	}
	else
	{
		throw std::out_of_range("Error: Trying to access member out of bounds!");
	}		
 }
 
 // Initializer_list operator
 // Initializes the vector with the elements supplied by the list.
 // This will change the size of the object and all of its elements.
 template <class T> Vector<T> &Vector<T>::operator=(std::initializer_list<T> list)
 {
	std::pair<T*,T*> newData = alloc_n_copy(list.begin(), list.end());
	free();
	first_element    = newData.first;
	first_free	  = newData.second;
	cap			  = newData.second;

	return *this;
 }

 // Checks if there is free space left in vector, otherwise reallocates memory
 template <class T> void Vector<T>::chk_n_alloc()
 {
	if(size() == capacity()) reallocate();
 }			 

 // Allocates new memory and copies input into this memory
 template <class T> std::pair<T*, T*> Vector<T>::alloc_n_copy ( const T* start_elem, const T* end_elem)
 {
	// Allocate space for nr of input elements
	T *data = alloc.allocate(end_elem - start_elem);
	
	// Returns a pair with pointer to beginning of newly allocated memory chunk
	// and pointer to last element of the destination sequence where elements have been copied
	return {data, std::uninitialized_copy(start_elem, end_elem, data)};
 }

 // Destroy the elements and free the space
 template <class T> void Vector<T>::free()
 {
	// Make sure that we have elements to deallocate
	if(first_element != nullptr)
	{
		// Go through each element backwards, destroying it in the process
		for(T* p = first_free; p != first_element;)
		{
			p--; // Make sure to point on the next element
			alloc.destroy(p);
		}
		// Finally, deallocate the space occupied by the vector
		alloc.deallocate(first_element, (cap - first_element));
	}
 }

 // Get more space and copy existing elements
 template <class T> void Vector<T>::reallocate()
 {
	std::size_t curr_size = size();
	
	// Allocate twice nr of elements if > 0 else allocate space for 1 element
	std::size_t newCapacity = curr_size ? 2*curr_size : 1; 
	
	T *newData = alloc.allocate(newCapacity);
	
	// Move data from old vector space to new (move is much faster than copy)
	T *dest = newData;
	T *src  = first_element;
	for( std::size_t i = 0; i != curr_size; ++i)
	{
		alloc.construct(dest, std::move(*src));
		dest++;
		src++;
	}
	
	free(); // Free up old space
	
	// Update variables
	first_element = newData;
	first_free    = dest;
	cap           = first_element + newCapacity;
 }
 
  // Copies input element into the position after the last element
 template <class T> void Vector<T>::push_back(const T& newElement)
 {
	chk_n_alloc(); // Ensure that there is room for new element
	alloc.construct(first_free, newElement); // Construct a copy of newElement, place it at first_free
	first_free++; 
 }
 
 // Inserts the element at input location and moves all elements
 // to the right
 template <class T> void Vector<T>::insert(std::size_t index, const T& elem)
 {
	if(index <= size())
	{
		// Insertion at end of vector == push_back
		if(index == size())
		{
			push_back(elem);
		}
		else
		{
			std::size_t curr_size = size();
			std::size_t oldCapacity = capacity();
			std::size_t newCapacity;
		
			// Make sure we have room for the new element
			if(curr_size == oldCapacity)
			{
				// Allocate twice nr of elements if > 0 else allocate space for 1 element
				newCapacity = curr_size ? 2*curr_size : 1; 
				
				T *newData = alloc.allocate(newCapacity);
			
				// Move data from old vector space to new (move is much faster than copy)
				T *dest = newData;
				T *src  = first_element;
				for(std::size_t i = 0; i < (curr_size + 1); i++)
				{
					// Copy element to index
					if(i == index)
					{
						alloc.construct(dest, elem);
					}
					else
					{
						alloc.construct(dest, std::move(*src));
						src++;					
					}
					dest++;
				}
			
				free(); // Free up old space
			
				// Update variables
				first_element = newData;
				first_free    = dest;
				cap           = first_element + newCapacity;
			}
			// Use already located space
			else
			{
				for(std::size_t i = (first_free-first_element); i > index; i--)
				{
					alloc.construct((first_element+i), std::move(first_element[i-1]));					
				}
				alloc.construct((first_element+index), elem);
				first_free++;
			}
		}
	}
	else
	{
		throw std::out_of_range("Error: Trying to insert member out of bounds!");
	}
 }

 // Erases the element at input location, moves all elements downwards one step
 template <class T> void Vector<T>::erase(std::size_t index)
 {
	if(index < size())
	{
		std::size_t curr_size = size();
		alloc.destroy((first_element+index));
		// Move all elements one positions downwards in vector
		for(std::size_t i = (index+1); i < curr_size; i++)
		{
			first_element[i-1] = std::move(first_element[i]);  
		}
		first_free--; //Decrease pointer to first free
	}
	else
	{
		throw std::out_of_range("Error: Trying to erase member out of bounds!");
	}
 }

 // Removes all elements in vector, keeps allocated vector space.
 template <class T> void Vector<T>::clear()
 {
	if(first_element != nullptr)
	{
		// Go through each element backwards, destroying it in the process
		for(T* p = first_free; p != first_element;)
		{
			p--; // Make sure to point on the next element
			alloc.destroy(p);
		}
		first_free = first_element;
	}
 }

 // Sorts the vector in ascending (true) or descending (false) order.
 template <class T> void Vector<T>::sort(bool ascending)
 {
	// Sort elements in ascending order <
	if(ascending)
	{
		std::sort(begin(), end());
	}
	// Sort elements in descending order >
	else
	{
		std::sort(begin(), end());
		std::reverse(begin(),end());
	}
 }

 // Sorts the vector + removes all duplicant elements. 
 template <class T> void Vector<T>::unique_sort(bool ascending)
 {
	sort(ascending); // Sort vector so that duplicate elements are next to each other
	T* end_unique = std::unique(begin(), end()); // Reorders elements so that unique elements are before end_unique
	
	// Erase duplicate elements from list
	for(T* p = end_unique; p != first_free; p++)
	{
		alloc.destroy(p);
	}
	first_free = end_unique;
 }

 // Returns true if element exists in vector otherwise false.
 template <class T> bool Vector<T>::exists(const T& value)
 {
	T *result = std::find(begin(), end(), value);
	return (result != end());
 }
 
 // Returns the size of the vector.
 template <class T> std::size_t Vector<T>::size() const
 {
 	return (first_free - first_element);
 }

 // Returns the capacity of the vector
 template <class T> std::size_t Vector<T>::capacity() const
 {
	return (cap - first_element);
 }

 // Returns pointer to location of first element in vector
 template <class T> T *Vector<T>::begin() const
 {
	return first_element;
 }

 // Returns pointer to the location of the last constructed element
 template <class T> T *Vector<T>::end() const
 {
	return first_free;
 }
