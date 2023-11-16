#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cassert>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
    std::cout << "Running short tests..." << std::endl;
	SortedBag sb(relation1);
    std::cout << "Testing add..." << std::endl;
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
    sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

    std::cout << "Testing remove..." << std::endl;
	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

    std::cout << "Testing iterator..." << std::endl;
	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

	std::cout << "Testing least frequent..."<<std::endl;
	TComp l = sb.leastFrequent();
	assert(l == 0 || l == 5 || l == 6 || l == 8 || l == 10);
	sb.add(0);
	sb.add(6);
	sb.add(8);
	sb.add(10);
	l = sb.leastFrequent();
	assert(l == 5);

	SortedBag newSortedBag(relation1);
	l = newSortedBag.leastFrequent();
	assert(l == NULL_TCOMP);
	std::cout<<"Short tests passed!"<<std::endl;

}

