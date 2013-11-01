// DD2387: Lab 1.1
//
// A simple program which outputs different messages depending on user input. 
//
// Authors: Christoffer Wiss & Martin Pettersson
// Version: 2013-09-11

#include <iostream>
#include <string>
using std::string;

// Entry point of program
int main(int argc, char const *argv[])
{
	string message = "world";
	int number = 1;

	// Check parameters
	switch(argc)
	{ 
		// Two additional arguments : number and string
		case(3):
		{
			message = (*(argv+2));
		}
		// One additional argument : a number or string
		case(2):
		{
			number = std::atoi((*(argv+1)));
			
			// Did atoi return 0 i.e. no number or did we find the number 0?
			if(number == 0)
			{
				if((*argv)[0] == '0')
				{
					message = "";
				}
				else 
				{
					message = (*(argv+1));
					number = 1;
				}
			}
			break;
		}

		default:
		{
			break;
		}
	}

	std::cout << "Hello";
	for(int i = 0; i < number; i++)
	{
		std::cout << " " << message;
	}
	std::cout << "!" << std::endl;
	return 0;
}
