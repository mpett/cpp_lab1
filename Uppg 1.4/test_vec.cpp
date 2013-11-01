#include <iostream>
#include <stdexcept>
#include "vector.h"     // inkludera din headerfil här

int main()
{
    // Några saker som ska fungera:
	
    Vector a={1,2,3,4,5,6,7};	// initiering med 7 element, initializer_list


    
    std::cerr << "\nVector a={1,2,3,4,5,6,7}:\t";
    for(std::size_t i = 0; i < a.size(); i++)
    {
    	std::cerr<<a[i];
    }
	

    Vector b(a);           // kopieringskonstruktor
	std::cerr << "\nVector b(a):\t";
    for(std::size_t i = 0; i < b.size(); i++)
    {
    	std::cerr<<b[i]<<",";
    }
    
	Vector c = a;          // kopieringskonstruktor 
    std::cerr << "\nVector c = a:\t";
    for(std::size_t i = 0; i < c.size(); i++)
    {
    	std::cerr<<c[i]<<",";
    }
	
    Vector d(0);	   // Test av nollstor vektor
	std::cerr << "\nVector d(0); d.size():\t";
    std::cerr << d.size();
	std::cerr << "\nsizeof(d):\t";
	std::cerr << sizeof(d);
	
	
    Vector f = {9,8,7,6};
	d = f;	// kopiering av olika stora vektorer, tilldelning genom kopiering
    std::cout << "\nVector f = {9,8,7,6}; d = f:\t";
    for(std::size_t i = 0; i < d.size(); i++)
    {
    	std::cerr<<d[i]<<",";
    }

    const int y = a[3];	// const access []
	std::cerr << "\nconst int y = a[3]: " << y << std::endl; 
	std::cerr << "a[3]: " << a[3] << std::endl; 
    
	int x = 2; 
	a[3] = x;	//non-const tilldelning []
	std::cerr << "\na[3] = x: " << a[3] << std::endl; 
	
    Vector v2;		 // default constructor
	std::cerr << "\nVector v2; v2.size():" << v2.size() << std::endl;
    v2 = {1, 2, 5};
	std::cerr << "v2 = {1, 2, 5};:";
	for(std::size_t i = 0; i < v2.size(); i++)
    {
    	std::cerr<<v2[i]<<",";
    }

    Vector q = a;	
    a[0] = 1;		// ändrar bara elementet i a inte q
	std::cerr << "\nVector q = a; a[0] = 1; q:\t";
	for(std::size_t i = 0; i < q.size(); i++)
    {
    	std::cerr<<q[i]<<",";
    }

    Vector empty = {};

	std::cerr << "\nVector empty = {}; empty.size():" << empty.size() << std::endl;

    a = b;                 // tilldelning genom kopiering

    a[5] = 7;              // tilldelning till element

    const Vector e(10);    // konstant objekt med 10 element
    int i = e[5];          // const int oper[](int) const körs
    i = a[0];              // vektorn är nollindexerad
    i = a[5];              // int oper[](int) körs
	std::cerr << "\n i: " << i << " a[5]: " << a[5] << std::endl;
    a[5]++;                // öka värdet till 6
	std::cerr << "a[5]++; : " << a[5] << std::endl;

    Vector v; 
	std::cerr << "\nVector v; &v: " << &v << std::endl;
	v = v;	// default constructor körs, copy-operatorn körs märker att det är samma objekt, returnerar samma objekt.
	std::cerr << "v = v; &v: " << &v << std::endl;
	
	// test med move constructor
	Vector v_to_move_c = {1,2,3,4,5};
	std::cerr << "&v_to_move_c: " << &v_to_move_c << " v_to_move_c.size(): " << v_to_move_c.size() << std::endl;
	std::cerr << "MOVE CONSTRUCTOR CALLED" << std::endl;
	
	Vector v_to_receive_c(std::move(v_to_move_c));
	std::cerr << "&v_to_move_c: " << &v_to_move_c << " v_to_move_c.size(): " << v_to_move_c.size() << std::endl;
	std::cerr << "&v_to_receive_c: " << &v_to_receive_c << " v_to_move_c.size(): " << v_to_receive_c.size() << std::endl;
	std::cerr << "v_to_receive_c[1]: " << v_to_receive_c[1] << std::endl;
	try {
		std::cerr << "\nTry to access v_to_move_c[1]: ";
		std::cerr << v_to_move_c[1];
	}
	catch (std::out_of_range e) {
        std::cerr << e.what() << std::endl;
    }
	
	// test med move operatorn
	Vector v_to_move_o = {3,4,5,6,7};
	std::cerr << "\n&v_to_move_o: " << &v_to_move_o << " v_to_move_o.size(): " << v_to_move_o.size() << std::endl;
	std::cerr << "MOVE OPERATOR CALLED" << std::endl;
	
	Vector v_to_receive_o = {2,3}; 
	v_to_receive_o = std::move(v_to_move_o);
	std::cerr << "&v_to_move_o: " << &v_to_move_o << " v_to_move_o.size(): " << v_to_move_o.size() << std::endl;
	std::cerr << "&v_to_receive_o: " << &v_to_receive_o << " v_to_move_o.size(): " << v_to_receive_o.size() << std::endl;
	std::cerr << "v_to_receive_o[1]: " << v_to_receive_o[1] << std::endl;
	try {
		std::cerr << "\nTry to access v_to_move_o[1]: ";
		std::cerr << v_to_move_o[1];
	}
	catch (std::out_of_range e) {
        std::cerr << e.what() << std::endl;
    }

	std::cerr << "\nTry to access element outside of e: ";
    try {
        i = e[10];             // försöker hämta element som ligger utanför e
    } catch (std::out_of_range e) {
        std::cout << e.what() << std::endl;
    }
    
    #if 0
    // Diverse saker att testa
    e[5] = 3;              // fel: (kompilerar ej) tilldelning till const
    b = b;                 // hmm: se till att inte minnet som skall behållas frigörs
    #endif
    

    return 0;
}
