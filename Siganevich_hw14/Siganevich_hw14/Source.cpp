#include "var.h"
#include <string.h>

int main()
{
	var A = 5.75, B = 6, C;
	C = B + A;
	cout << C << endl;
	cout << "====\n";

	myString m = "microsoft";
	myString n = "windows";
	var M = m, N = n;
	cout << M / N << endl << M * N << endl;
	cout << "====\n";
	
	var Q = "10hello";
	Q += 23.56;
	cout << Q << endl;

	return 0;
}