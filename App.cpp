//#include "SortedBag.h"
//#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;
/// ADT  SortedBag –having  elements  of  type TComp,represented  using a  dynamic  array  of <element,   frequency>
/// pairs(or   two   dynamic   arrays),   sorted   using   a   relation  on   the elements.

int main()
{
	testAll();
	testAllExtended();
	
	cout << "Successful execution" << endl;
	system("pause");
}
