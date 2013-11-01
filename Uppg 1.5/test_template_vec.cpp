/**
 * Description: Testes the dynamic vector class basic functionalities.
 *
 * Author: Martin Pettersson & Christoffer Wiss
 *
 * Version: 2013-10-01
 */

#include "vector.h"             // inkludera din headerfil här
#include <assert.h>             // assert(b) ger felmeddelande om b falsk

int main()
{
    Vector<double> v;           // ok: defaultkonstruktor ger vektor med flyttal
    
    Vector<char> *a = new Vector<char>[3];  // dynamiskt allokerade ser ut så här
    delete [] a;

    assert(v.size() == 0);      // tom från början
    v.push_back(3.14);          // lägg till ett element sist 
    assert(v.size() == 1);      // nu ligger ett element i vektorn
    
    v.insert(0, 2.10);          // lägg till före element 0, dvs först

    assert(v[0] == 2.10 &&      // hamnade de rätt?
	   v[1] == 3.14);       

    assert(v.size() == 2);      // nu ligger två element i vektorn
    v.sort(false);              // sortera i fallande ordning
    assert(v[0] == 3.14 &&      // hamnade de rätt?
	   v[1] == 2.10);       
    assert(v.size() == 2);      // ingenting ändrat?
    v[1] = 2.11;                // tilldelning av enstaka element;

    const Vector<double> &vc = v;  // skapa konstant referens
    assert(vc.size() == 2);     // ok: ändrar ej vektorn som är konstant
    assert(vc[0] == 3.14 &&     // ok: ändrar ej vektorn som är konstant
	   vc[1] == 2.11);
    
    v.erase(0);                 // ta bort första elementet               
    assert(v.size() == 1);      // rätt antal elelment
    v.clear();                  // töm hela vektorn
    assert(v.size() == 0);      // tom när alla element är borttagna

    // Tests push back
    Vector<int> b = {1,2,3};    // New int vector
    assert(b.size() == 3);        // Size should be 3.
    b.push_back(4);
    assert(b[3] == 4);  
    assert(b.size() == 4);        // Size should be 4.

    // Tests insert
    b.insert(3, 5);
    assert(b[3] == 5);  
    b.insert(4, 6);
    assert(b[4] == 6);  
    assert(b.size() == 6);        // Size should be 6.

    // Tests clear
    size_t capBeforeClear = b.capacity();       // Stores capacity before clear.
    b.clear();                                  // Clears vector b.
    assert(b.size() == 0);                      // Size should be 0.
    assert (capBeforeClear == b.capacity());    // Capacity should be unchanged.

    // Tests sort
    Vector<int> c = {5,3,1,4,2};                // New int vector
    assert(c.size() == 5);                      // Size should be 5.
    c.sort(true);                               // Sorts vector, ascending.
    assert(c.size() == 5);                      // Size should be 5.
    
    assert(c[0] == 1 && c[1] == 2 && c[2] == 3 && c[3] == 4 && c[4] == 5); // Vector should be sorted in ascending order.
    c.sort(false);                               // Sorts vector, descending.
    assert(c.size() == 5);                       // Size should be 5.
    assert(c[0] == 5 && c[1] == 4 && c[2] == 3 && c[3] == 2 && c[4] == 1); // Vector should be sorted in descending order.

    // Tests unique sort
    Vector<int> d = {5,3,5,1,5,4,2,1,4,4,1};     // New int vector
    assert(d.size() == 11);                       // Size should be 11.
    d.unique_sort(true);                         // Unique sort ascending.
    assert(d.size() == 5);                       // Size should be 5.
    assert(d[0] == 1 && d[1] == 2 && d[2] == 3 && d[3] == 4 && d[4] == 5); // Vector should be sorted in ascending order, no duplicates.
    
    d.unique_sort(false);                         // Unique sort descending.
    assert(d.size() == 5);                       // Size should be 5.
    assert(d[0] == 5 && d[1] == 4 && d[2] == 3 && d[3] == 2 && d[4] == 1); // Vector should be sorted in descending order, no duplicates.
    d = {5,3,5,1,5,4,2,1,4,4,1};                    // Reassign int vector d.
    assert(d.size() == 11);                       // Size should be 11.
    d.unique_sort(false);                         // Unique sort descending.
    assert(d.size() == 5);                       // Size should be 5.
    assert(d[0] == 5 && d[1] == 4 && d[2] == 3 && d[3] == 2 && d[4] == 1); // Vector should be sorted in descending order, no duplicates.

    // Test exists
    assert(d.exists(5));                // 5 should be in d.
    assert(d.exists(4));                // 4 should be in d.
    assert(d.exists(3));                // 3 should be in d.
    assert(d.exists(2));                // 2 should be in d.    
    assert(d.exists(1));                // 1 should be in d.
    assert(d.exists(6) == false);                // 6 should not be in d.
    assert(d.exists(11) == false);                // 1415 should not be in d.

    std::cout << "All tests passed. Horray! :D" << std::endl;
        
    // kontrollera att följande rader inte går att kompilera
    //vc[0] = 3.1415;             // fel: tilldelning av konstant objekt
    //Vector<char> c = v;         // fel: tilldelning av olika typer
    //vc.sort();                  // fel: ändrar konstant objekt
    return 0;
}
