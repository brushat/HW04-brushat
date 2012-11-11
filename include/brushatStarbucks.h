/*****
 * Author   : brushat
 * Date     : 2012-10-27
 * Sources  : All code is original
 * Purpose  : 
 *            In your class you should declare all of your methods to be virtual: This is how
 *            polymorphism is accomplished in C++. Do NOT copy the part that says "= 0" that I use
 *            below. That part means that the function, though declared, will not have any implementation.
 * Note     : DO NOT CHANGE THIS FILE!!! 
 */

#pragma once
#include <string>
#include "Starbucks.h"
using namespace std;

class brushatStarbucks : public Starbucks 
{
public:
	brushatStarbucks();
	~brushatStarbucks(void);
	Entry* locations;
	vector<Entry> vectLocs;
	int vecLocsSize;
	int locsSize; //the size of our locations unsorted array

	/* Note: If you detect that two items have the same coordinates, then do not add the new item
	 *       that has the same coordinates as another item. This is guaranteed to happen, by the way,
	 *       because some Starbucks locations are listed in the database twice. We will define two locations
	 *       to be the "same location" if both |x1 - x2| <= 0.00001 and |y1 - y2| < 0.00001
	 */
	void build(Entry* c, int n);
	
	/*
	 * Return a pointer to the entry that is closest to the given coordinates. Your
	 *  answer may be approximate, but then you will lose points on the "Accuracy" quality measure
	 */
	Entry* getNearest(double x, double y);

};