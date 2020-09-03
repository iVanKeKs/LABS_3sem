
#include"LargeInteger.h"

using namespace std;

int main()
{
	try
	{
	    LargeInteger l1("1234546984216485615678", 1);
		cout << l1 << endl;

		LargeInteger l2 = l1.KaratsubaMultiple(l1);
		cout << l2 << endl;

		cout << Factorial(71) << endl;

		cout << BinomialCoefficient(100, 50) << endl;

		cout << Fibonacci(71) << endl;
	}
	catch (LargeIntegerException& exception)
	{
		cout << exception.WhatExceptions() << endl;
	}

	return 0;
}