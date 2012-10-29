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
	vector<Entry> vector;

	for(int i = 0; i < n; i++){
		vector.push_back(c[i]);
	}

	for(int j = 0; j < vector.size(); j++){
		for(int k = j+1; k < vector.size(); k++){
			if(((abs(vector[j].x) - abs(vector[k].x)) < .00001) && ((abs(vector[j].y) - abs(vector[k].y)) < .00001)){
				// how to erase a single element from a vector 
				// http://stackoverflow.com/questions/875103/how-to-erase-element-from-stdvector-by-index
				vector.erase(vector.begin() + k);
			}
		}
	}

	// Shuffling a vector
	// http://www.cplusplus.com/forum/general/61397/
	std::random_shuffle(vector.begin(), vector.end());
	locations = new Entry[vector.size()];

	for(int l = 0; l < vector.size(); l++){
		locations[l] = vector[l];
	}

	size = vector.size();
}

Entry* brushatStarbucks::getNearest(double x, double y){
	
	//Entry e = locations[0];
	/*for(int i = 0; i < size; i++){

	}
	return e;*/
}