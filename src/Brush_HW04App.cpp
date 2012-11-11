/*****
 * Author   : brushat
 * Date     : 2012-11-08
 * Sources  : All code is original
 * Purpose  : 
 *           The main class that goes and gets all of the necessary data and draws everything
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
#include "..\include\Resources.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class Brush_HW04App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);

private:
	static const int AppWidth=600;
	static const int AppHeight=600;
	static const int TextureSize=1024;
	Surface* mySurface_;
	gl::Texture map;
	
	brushatStarbucks bucksLocs;
	brushatStarbucks census2010;
	brushatStarbucks census2000;
};

void Brush_HW04App::setup()
{
	/////////////////////////////////////////////// LOAD MAP /////////////////////////////////////////////////////////////
	mySurface_ = new Surface( TextureSize, TextureSize, true);
	map = loadImage( "../resources/map.jpg" );
	

	/////////////////////////////////////////////// CREATE STARBUCKS ARRAY ///////////////////////////////////////////////
	ifstream in("..\\resources\\Starbucks_2006.csv");

	vector<Entry> vec;

	if(in.fail()){
		console() << "failed to open file" << std::endl;
		return;
	}

	string line;
	do{
		Entry e;

		getline(in, line, ',');
		e.identifier = line;

		in.get();
		in >> e.x;

		in.get();
		in >> e.y;

		vec.push_back(e);
	}
	while(!in.eof());
	
	for(int j = 0; j < vec.size(); j++){
		// I think this may violate my theta(N) claimed in the first 
		for(int k = j+1; k < vec.size(); k++){
			if((abs(vec[j].x- vec[k].x) < .00001) && (abs(vec[j].y - vec[k].y) < .00001)){
				// how to erase a single element from a vector 
				// http://stackoverflow.com/questions/875103/how-to-erase-element-from-stdvector-by-index
				vec.erase(vec.begin() + k);
			}
		}
	}
	
	// Shuffling a vector
	// http://www.cplusplus.com/forum/general/61397/
	std::random_shuffle(vec.begin(), vec.end());

	
	Entry *locations = new Entry[vec.size()];

	for(int i = 0; i < (vec.size()-1); i++){
		locations[i] = vec.at(i);
	}
		

	bucksLocs.build(locations, vec.size());

	delete[] locations;

	
	/////////////////////////////////////////////// CREATE CENSUS DATA /////////////////////////////////////////////////////
	/////////////////////////////////////////////// CREATE CENSUS 2000 /////////////////////////////////////////////////////
	ifstream cin00("..\\resources\\Census_2000.csv");

	vector<CensusEntry> vec00;
	string junk1;
	

	if(cin00.fail()){
		console() << "failed to open file" << std::endl;
		return;
	}
	
	do{
		CensusEntry e;
		for(int i = 0; i <= 3; i++){
			getline(cin00, junk1, ',');
		}
		cin00 >> e.population;
		cin00.get();
		cin00 >> e.x;
		cin00.get();
		cin00 >> e.y;
		vec00.push_back(e);

	}
	while(!cin00.eof());

	CensusEntry* census00 = new CensusEntry[vec00.size()];
	for(int i = 0; i < vec00.size(); i++){
		census00[i] = vec00.at(i);
	}
	census2000.buildCensus(census00, vec00.size());

	/////////////////////////////////////////////// CREATE CENSUS 2010 /////////////////////////////////////////////////////
	ifstream cin10("..\\resources\\Census_2010.csv");

	vector<CensusEntry> vec10;
	string junk2;

	if(cin10.fail()){
		console() << "failed to open file" << std::endl;
		return;
	}
	
	do{
		CensusEntry e;
		for(int i = 0; i <= 3; i++){
			getline(cin10, junk2, ',');
		}
		cin10 >> e.population;
		cin10.get();
		cin10 >> e.x;
		cin10.get();
		cin10 >> e.y;
		vec10.push_back(e);

	}
	while(!cin10.eof());

	CensusEntry* census10 = new CensusEntry[vec10.size()];
	for(int i = 0; i < vec10.size(); i++){
		census10[i] = vec10.at(i);
	}
	census2010.buildCensus(census10, vec10.size());

	/////////////////////////////////////////////// TESTER AREA /////////////////////////////////////////////////////////////
	console() << "Starbucks location Tester" << endl;
	console() << "1st Location = " << bucksLocs.locations[0].identifier << endl;
	console() << "2nd Location = " << bucksLocs.locations[1].identifier << endl;
	console() << "Nearest to (.5,.5) = " << endl;
	console() << bucksLocs.getNearest(.5,.5)->identifier << " " << bucksLocs.getNearest(.5,.5)->x << " " << bucksLocs.getNearest(.5,.5)->y << std::endl;
	console() << "" << endl;
	console() << "Census Tester" << endl;
	console() << "First 2000 Data Point = " << census2000.census[0].population << endl;
	console() << "First 2010 Data Point = " << census2010.census[0].population << endl;
	gl::draw(*mySurface_);
	
	 
}

void Brush_HW04App::prepareSettings(Settings* settings){
	settings->setWindowSize(AppWidth, AppHeight);
	settings->setResizable(false);
}

void Brush_HW04App::mouseDown( MouseEvent event )
{
}

void Brush_HW04App::update()
{
}

void Brush_HW04App::draw()
{
	gl::draw(map); 

	Entry e = bucksLocs.locations[0];
	bucksLocs.drawBucks(e.x,e.y);
}

CINDER_APP_BASIC( Brush_HW04App, RendererGl )
