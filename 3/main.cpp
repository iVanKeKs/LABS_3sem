
#include "TechnicalMethods.h"
#include "Polynomial.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc == 1)
    {
        exit(-1);
    }

	FILE *fileInput;
	if (!(fileInput = fopen(argv[1], "r")))
	{
		cout << "File is not exist \"" << argv[1] <<"\"" << endl;
		exit(1);
	}

	char buff[BUFSIZ],
	     command[BUFSIZ],
         firstArgument[BUFSIZ],
         secondArgument[BUFSIZ];
	
	while (!feof(fileInput))
	{
        ReadFromFile(fileInput, buff);

		if (strlen(buff) > 0)
		{
            ParseInputString(buff, command, firstArgument, secondArgument);

			try
			{
				if (!strcmp("+", command))
				{
					Polynomial leftNode(firstArgument);
					Polynomial rightNode(secondArgument);

					cout << leftNode + rightNode << endl;
				}
				else if (!strcmp("-", command))
				{
					Polynomial leftNode(firstArgument);
					Polynomial rightNode(secondArgument);

					cout << leftNode - rightNode << endl;
				}
				else if (!strcmp("*", command))
				{
					Polynomial leftNode(firstArgument);
					Polynomial rightNode(secondArgument);

					cout << leftNode * rightNode << endl;
				}
				else if (!strcmp("==", command))
				{
					Polynomial leftNode(firstArgument);
					Polynomial rightNode(secondArgument);

					cout << (leftNode == rightNode) << endl;
				}
				else if (!strcmp("!=", command))
				{
					Polynomial leftNode(firstArgument);
					Polynomial rightNode(secondArgument);

					cout << (leftNode != rightNode) << endl;
				}
				else
				{
					cout << "Command \"" << command << "\" not found"<< endl;
				}
			}
			catch (ListForMonomialException &exception)
			{
				cout << exception.WhatException() << endl;
			}
			catch (PolynomialException &exception)
			{
				cout << exception.WhatException() << endl;
			}
			catch (ListForPolynomialException &exception)
			{
				cout << exception.WhatException() << endl;
			}
		}
	}

	return 0;
}