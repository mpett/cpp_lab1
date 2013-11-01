/**
 * Description: A vector class which implements copy, move, initialize_list and 
 *              constructor and destructor. Also implements the copy, initialize_list 
 *              assignment, move,  and [] operator. 
 *
 * Author: Martin Pettersson & Christoffer Wiss
 *
 * Version: 2013-09-30
 */
 
 #pragma once
 #include <initializer_list>
 #include <stdexcept>
 #include <algorithm>
 
 class Vector
 {
 	public:
 		// Destructor
 		~Vector();

		// Default constructor
 		Vector();

 		// Constructor
 		explicit Vector(const std::size_t size);
 		
 		// Copy-constructor
 		Vector(const Vector& obj);

 		// Move-constructor
 		Vector(Vector&& obj) noexcept;

		// Initializer_list constructor
 		Vector(const std::initializer_list<unsigned int> list);
 		
 		// Copy assignment operator
 		Vector &operator=(const Vector &rhs);
 		
 		// Move assignment operator
 		Vector &operator=(Vector&& obj) noexcept;
 		
 		// Index assignment operator
 		unsigned int &operator[](std::size_t index);
		
		// Index access operator
 		unsigned int const &operator[](std::size_t index) const;
 		
 		// Initializer_list assignment operator
 		Vector &operator= (std::initializer_list<unsigned int> list);
 		
 		// Returns the size of the vector
 		unsigned int size() const;
 	
 	private:
 		unsigned int *container;
 		unsigned int vectorSize;
 };
