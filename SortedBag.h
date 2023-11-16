#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR
#include <cstdlib>
//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP (-11111)

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	int capacity;
	int count;
	Relation relation;
    TComp* elements;
    int* frequencies;

	void resizeUp();
	void resizeDown();
    void makeRoomToTheRightOfIndex(int index);
    void contractRightOfIndex(int index);

public:
	//constructor
	explicit SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp elem);

	//removes one occurrence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if elem was not part of the sorted bag)
	bool remove(TComp elem);

	//checks if an element appears in the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	// returns TComp with the lowest frequency, any of them if there are more, NULL_TCOMP if the bag is empty
	TComp leastFrequent() const;

	//destructor
	~SortedBag();
};