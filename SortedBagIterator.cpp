#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b)
{
    current_elem = bag.elements;
    current_freq = bag.frequencies;
	current_count = 0;
}

TComp SortedBagIterator::getCurrent() {
    if (!valid()){
        throw std::exception(); /// I do not understand why I cannot add a message here
    }
    return *current_elem;
}

bool SortedBagIterator::valid() const {
	int last_position = bag.count - 1;
	if(current_elem < bag.elements || (&bag.elements[last_position]) < current_elem)
		return false;
	/// we not know that current_elem points to a valid element inside the bag
	if(current_count < 0 || *current_freq <= current_count)
		return false;
	return true;
}

void SortedBagIterator::next() {
    if(!valid())
        throw std::exception();
	if(current_count < *current_freq - 1)
		current_count ++;
	else
		{
            current_elem ++;

            current_freq ++;

			current_count = 0;
		}
}

void SortedBagIterator::first() {
	current_elem = bag.elements;
	current_freq = bag.frequencies;
	current_count = 0;
}

