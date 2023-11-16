#include "SortedBag.h"
#include "SortedBagIterator.h"
#define RESIZE_BOUNDARY 1024
#define default_quantity 1
SortedBag::SortedBag(Relation r)
{
	elements = new TComp[4];
	frequencies = new int[4];
	capacity = 4;
	this->count = 0;
	relation = r;
}

void SortedBag::resizeUp()
{
    /// T(count) = Theta(count);
    /// Space(count) = min(Space(2 * count), Space(count + RESIZE_BOUNDARY))

    if(capacity < RESIZE_BOUNDARY) {
        capacity = (capacity) << 1; /// bitwise shift to the left by 1 is equivalent with multiplication by 2
    }
    else {
        capacity = capacity + RESIZE_BOUNDARY; /// when the size gets very big we do not want to keep doubling the capacity
    }
    auto* new_elements = new TComp[capacity];
    auto* new_freq = new int[capacity];
    for(int index = 0; index < this->count; index ++)
    {
        new_elements[index] = elements[index];
        new_freq[index] = frequencies[index];
    }
    delete[] elements;
    delete[] frequencies;
	elements = new_elements;
	frequencies = new_freq;
}
void SortedBag::resizeDown()
{
    /// T(count) = Theta(count);
    /// Space(count) = Theta(count)
    if (capacity <= 2){ ///Guard against an irreversible reduction to 0 of the bag's cap
        capacity = capacity >> 2; /// bitwise shift to the right by 2 is equivalent with division by 4
	    auto* new_elements = new TComp[capacity];
	    auto* new_freq = new int[capacity];
	    for(int index = 0; index < this->count; index ++)
	    {
		    new_elements[index] = elements[index];
		    new_freq[index] = frequencies[index];
	    }
	    delete[] elements;
	    delete[] frequencies;
	    elements = new_elements;
	    frequencies = new_freq;
    }
}
void SortedBag::makeRoomToTheRightOfIndex(int index)
{
    /// T(count) = roughly O(count);
    /// Space(count) = Theta(1);
    ///Ths method exists only to be called inside the add method and make it more readable;
    /// index is considered a valid position inside the bag or -1 when the whole array needs to be shifted
    for(int jndex = this->count; jndex > index; jndex --)
    {
        elements[jndex] = elements[jndex - 1];
        frequencies[jndex] = frequencies[jndex -1];
    }
}

void SortedBag::add(TComp elem)
{
    /// T(count) = O(count);
    /// Omega(1) <= Space(count) <= min(O(2*count), O(count + RESIZE_BOUNDARY))
    int index;
    for(index = 0; index < (this->count); index ++) {
        if (elements[index] == elem) {
            frequencies[index]++;
            return;
        }
        if(!relation(elements[index], elem))
            break;
    }
    makeRoomToTheRightOfIndex(index);
    elements[index] = elem;
    frequencies[index] = default_quantity;
    (this->count) ++;
    if(this->count == capacity)
        resizeUp();
}
void SortedBag::contractRightOfIndex(int index)
{
    /// T(count) = roughly Theta(n);
    /// Space(count) = Theta(1);
    ///Ths method exists only to be called inside the remove method and make it more readable;
    /// index is considered a valid position inside the bag
    for(int jndex = index; jndex <this->count - 1; jndex ++)
    {
        elements[jndex] = elements[jndex + 1];
        frequencies[jndex] = frequencies[jndex + 1];
    }

}
bool SortedBag::remove(TComp elem)
{
    /// Omega(1) <= T(n) <= O(count * log2(count));
    /// Space(count) = Theta(1)
    int left = 0, right = this->count - 1, middle;
    while(left <= right)
    {
        middle = (left + right)/2;
        if(elements[middle] == elem)
        {
            if(frequencies[middle] <= 1) {
                contractRightOfIndex(middle);
                (this->count) --;
                if(this->count < (capacity >>2))
                    resizeDown();
            }
            else frequencies[middle] --;
            return true;
        }
        if(relation(elem, elements[middle]))
            right = middle - 1;
        else left = middle + 1;
    }
    return false;
}


bool SortedBag::search(TComp elem) const
{
    /// T(n) = Theta(log2(count));
    /// Space(n) = Theta(1)

	if(elem == elements[0])
		return true;
	if(elem == elements[this->count - 1])
		return true;
    if(relation(elem, elements[0]))
        return false;
	if(relation(elements[this->count - 1], elem))
		return false;
	int left = 0;
	int right = this->count - 1;
    int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		if(elements[middle] == elem)
			return true;
		if (relation(elem, elements[middle]))
			right = middle - 1;
		else  /// when (relation(elements[middle], elem)) is true
			left = middle + 1;
	}
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const
{
    /// Omega(1)<=T(count)<=O(log2(count));
    /// Constant space: Space(count) = Theta(1)
	int left = 0;
	int right = this->count - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (elements[middle] == elem)
			return frequencies[middle];
		if (relation(elem, elements[middle]))
			right = middle - 1;
		else  /// when (relation(elements[middle], elem)) is true
			left = middle + 1;
	}
	return 0;
}



int SortedBag::size() const
{
    /// T(count) is O(count);
    /// Space(count) is Theta(1) always 1 int
	int noOfElems = 0;
	for(int index = 0; index < this->count; index ++)
		noOfElems += frequencies[index];
	return noOfElems;
}


bool SortedBag::isEmpty() const
{
    /// Time(count) = Theta(1);
    /// Space(count) = Theta(1) (Can I say this?)
    return (this->count == 0);
}


SortedBagIterator SortedBag::iterator() const
{
    /// Time(count) = Theta(1);
	return SortedBagIterator(*this);
}

TComp SortedBag::leastFrequent() const
{
	/// Time(count) = Theta(count)
	/// Space(count) = Theta(1)

	if(this->count == 0)
		return NULL_TCOMP;
	int min_freq = frequencies[0], index_of_min = 0;
	for(int index = 1; index < this->count; index ++)
		if(frequencies[index] < min_freq)
		{
			min_freq = frequencies[index];
			index_of_min = index;
		}
	return elements[index_of_min];
}


SortedBag::~SortedBag()
{
	delete[] frequencies;
    delete[] elements;
}
