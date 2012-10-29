/*****
 * Author   : brushat
 * Date     : 2012-10-27
 * Sources  : Basic layout and some variables come from Dr. Brinkman
 * Purpose  : 
 *            In your class you should declare all of your methods to be virtual: This is how
 *            polymorphism is accomplished in C++. Do NOT copy the part that says "= 0" that I use
 *            below. That part means that the function, though declared, will not have any implementation.
 * Note     : DO NOT CHANGE THIS FILE!!! 
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/gl/Texture.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "cinder/Text.h"
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/Text.h"
#include "brushatStarbucks.h"
#include "Starbucks.h"
#include <math.h>

using namespace std;


brushatStarbucks::brushatStarbucks(){

}

brushatStarbucks::~brushatStarbucks(void){

}

void brushatStarbucks::build(Entry* c, int n){
	
	locations = new Entry[n];

	for(int i = 0; i < n-1; i++){
		locations[i] = c[i];
	}
	
	size = n;
}

Entry* brushatStarbucks::getNearest(double x, double y){
	
	Entry* nearest = new Entry();
	Entry current = locations[0];
	
	int shortest = sqrt((current.x-x)*(current.x-x) + (current.y-y)*(current.y-y));
	for(int i = 0; i < size-1; i++){
		int nextDist = sqrt((locations[i].x-x)*(locations[i].x-x) + (locations[i].y-y)*(locations[i].y-y));
		if(nextDist < shortest){
			shortest = nextDist;
			current = locations[i];
		}
	}
	*nearest = current;
	return nearest;
	
}
	
