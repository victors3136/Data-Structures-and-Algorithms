#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	explicit SortedBagIterator(const SortedBag& b);
	TComp* current_elem;
	int* current_freq;
    int current_count;


public:
	TComp getCurrent();
	bool valid() const;
	void next();
	void first();
};

