/*****
 * Author   : brushat
 * Date     : 2012-10-27
 * Sources  : Basic layout and some variables come from Dr. Brinkman and A little from Adam Brush
 *			  specifically, I added buildBucks and buildCensus which ended up being the same thing
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

using namespace ci;
using namespace ci::app;
using namespace std;

brushatStarbucks::brushatStarbucks(){

}

brushatStarbucks::~brushatStarbucks(void){

}

/**
 * Build the array of entries for starbucks locations and update the variables we will use
 * 
 * @param c a pointer to the first bucks point in an array
 * @param n the total number of points in the array
 */
void brushatStarbucks::build(Entry* c, int n){
	
	locations = new Entry[n];

	for(int i = 0; i < n-1; i++){
		locations[i] = c[i];
		vectLocs.push_back(c[i]);
	}
	locsSize = n;
	vecLocsSize = vectLocs.size();
}
/**
* Build the census array of all of the census points
* 
* @param c a pointer to the first census point in an array
* @param n the total number of points in the array
*/
 void brushatStarbucks::buildCensus(CensusEntry* c, int n){

	 census = new CensusEntry[n];

	 for(int i = 0; i < n-1; i++){
		 census[i] = c[i];
		 censVec.push_back(c[i]);
	 }
	 censusSize = n;
	 censVecSize = censVec.size();
 }
/**
 * Return the entry for the nearest starbuck to the x and y coordinates specified
 * 
 * x the x coordinate of the location
 * y the y coordinate of the location
 */
Entry* brushatStarbucks::getNearest(double x, double y){
	
	double nearestDist = 100.0;
	for(int i = 0; i < vecLocsSize-1; i++){
		double curX = vectLocs[i].x;
		double curY = vectLocs[i].y;
		// Based on the distance formula... http://www.purplemath.com/modules/distform.htm
		double nextDist = sqrt((curX-x)*(curX-x) + (curY-y)*(curY-y));
		if(nextDist < nearestDist){
			nearestDist = nextDist;
			nearest = &locations[i];
		}
	}
	return nearest;
	
}
/*
* Draw a starbucks location based on the x and y coordinate of the location
* the location must be translated to draw on the cinder map
* 
* x the x coordinate of the location
* y the y coordinate of the location
**/
void brushatStarbucks::drawBucks(double x, double y){

	glColor3f(Color(0,0,1));
	
	double mapx = x*800;
	double mapy = (1-y)*600;
	gl::drawSolidCircle( Vec2f( mapx, mapy ), 1.0f);

	glColor3f(Color(1,1,1));
}

void brushatStarbucks::drawCensus(double x, double y){

}
	
