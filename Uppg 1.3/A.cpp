#include <iostream>

class A {
public:
    A() 
        {std::cout << "The default contructor" << std::endl;}
    A(const A & ref) 
        {std::cout << "The copy contructor" << std::endl; }
    ~A() 
        {std::cout << "The destructor" << std::endl; }
    A(char * s) 
        {std::cout << "Some other constructor " << s << std::endl;}
    A & operator=(const A & s) 
        {std::cout << "The assignment operator" << std::endl; 
         return *this;}
};

void no_ref(A a) {}
void with_ref(const A & a) {}

int main()
{
    std::cout << "A a (\"my name is a\"); - Some other constructor anropas" << std::endl;
    A a("my name is a"); // Some other constructor anropas
    std::cout << std::endl;
    
    std::cout << "A b = a; - Copy constructor anropas" << std::endl;
    A b = a;         	 // vad är skillnaden (copy constructor?)
    std::cout << std::endl;
    
    std::cout << "A c(a); - Copy constructor anropas" << std::endl;
    A c(a);          	 // mellan dessa (copy constructor?)
    std::cout << std::endl;
    
    std::cout << "A d; - default constructor anropas" << std::endl;
    A d;             	 // tre tekniker? (default constructor?)
    std::cout << std::endl;
    
    std::cout << "d = a; - assignment constructor anropas" << std::endl;
    d = a;	     	 // (assignment operator?)
    std::cout << std::endl;

    std::cout << "no_ref(a); - copy constructor och destructor, temporärt objekt skapas (frigörs när out of scope)" << std::endl;
    no_ref(a);       // Bildas temporära objekt? (copy constructor, temporära objekt bildas)
    std::cout << std::endl;
    
    std::cout << "with_ref(a); - inget temporärt objekt skapas" << std::endl;
    with_ref(a);     // Bildas temporära objekt? (reference, inga temporära objekt) 
    std::cout << std::endl;

    std::cout << "A *aa = new A[5]; - default operator*5" << std::endl;
    
    A *aa = new A[5]; // Initialiserar 5 nya A objekt, default constructor * 5?
    std::cout << std::endl;
    
    std::cout << "delete aa; - 1 destructor kall, försöker ta bort ett block men misslyckas ty a[0] pekar på en address 8 bytes in i blocket (8 bytes = long = antal element i blocket)." << std::endl;
    // Ifall delete (aa-8); så kommer blocket att dealloceras (dvs. alla element), kommer få error i valgrind ty deallocerar av fel typ men hela blocket blir ändå deallocerat
    // Inget minne läcks. 
    //delete (aa-8);        // Vad kommer att hända? (kommer deallokera det objekt som aa pekar på aa[0])
    delete aa;
    std::cout << std::endl;
    
    std::cout << "Nu avslutas programmet" << std::endl;
    
    return 0;
}
