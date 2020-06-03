//
// A basic, simple example of using the stacktrace library -
// as presented in the "Getting started" section of the official documentation
//

// #define BOOST_STACKTRACE_USE_BACKTRACE
#define BOOST_STACKTRACE_USE_ADDR2LINE 

#include <stacktrace.hpp>
#include <iostream>

// Some whitespace here... scroll down






















































void bar(int n)
{
	if (n <= 0) { 
		// ... somewhere inside the `bar(int)` function that is called recursively:
		std::cout << stacktrace_::stacktrace();
		return;
	}
	bar(n-1);
}
	

int main()
{
	bar(4);
	std::cout << "\nAll done.\n";
}
