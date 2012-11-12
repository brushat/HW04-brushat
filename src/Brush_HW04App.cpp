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
	void render();
	void keyDown(KeyEvent event);
	gl::Texture		mTextTexture;
	string result;
	bool bucks;
private:
	static const int AppWidth=800;
	static const int AppHeight=600;
	static const int TextureSize=1024;
	Surface* mySurface_;
	gl::Texture map;
	
	brushatStarbucks bucksLocs;
	brushatStarbucks census2010;
	brushatStarbucks census2000;

	
	Vec2f			mSize;
	Font			mFont;
};

void Brush_HW04App::setup()
{
	/////////////////////////////////////////////// LOAD MAP /////////////////////////////////////////////////////////////
	mySurface_ = new Surface( TextureSize, TextureSize, true);
	map = loadImage( "../resources/map800.jpg" );
	
	mFont = Font( "Times New Roman", 32 );
	mSize = Vec2f( 800, 600 );
	result = "Click on the map to find the nearest location to your click";
	bucks = true;
	render();
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
	console() << bucksLocs.locsSize << endl;
	console() << "1st Location = " << bucksLocs.locations[0].identifier << endl;
	console() << "2nd Location = " << bucksLocs.locations[1].identifier << endl;
	console() << "Nearest to (.5,.5) = " << endl;
	console() << bucksLocs.getNearest(.5,.5)->identifier << " " << bucksLocs.getNearest(.5,.5)->x << " " << bucksLocs.getNearest(.5,.5)->y << std::endl;
	console() << "" << endl;
	console() << "Census Tester" << endl;
	console() << "First 2000 Data Point = " << census2000.census[0].population << endl;
	console() << "First 2010 Data Point = " << census2010.census[0].population << endl;
	
	
	 
}

void Brush_HW04App::prepareSettings(Settings* settings){
	settings->setWindowSize(AppWidth, AppHeight);
	settings->setResizable(false);
}

void Brush_HW04App::render()
{
	TextBox tbox = TextBox().alignment( TextBox::RIGHT ).font( mFont ).size( Vec2i( mSize.x, 600.0 ) ).text( result );
	tbox.setColor( Color( 1.0f, 0.65f, 0.35f ) );
	tbox.setBackgroundColor( ColorA( 0.0, 0, 0, 1 ) );
	Vec2i sz = tbox.measure();
	mTextTexture = gl::Texture( tbox.render() );
}

void Brush_HW04App::keyDown(KeyEvent event){
	if(event.getChar() == 'b'){
		if(bucks == true)
			bucks = false;
		else bucks = true;
	}
	else if(event.getChar() == 'c'){
		if(bucks == true)
			bucks = false;
		else bucks = true;
	}
}

void Brush_HW04App::mouseDown( MouseEvent event )
{
	int mouseX = event.getX();
	int mouseY = event.getY();

	double currentX = mouseX/800.0;
	double currentY = 1-(mouseY/600.0);

	bucksLocs.getNearest(currentX, currentY);

	console() << bucksLocs.nearest->identifier << endl;
	result = bucksLocs.nearest->identifier;
	render();
	glColor3f(Color(1.0,0.0,0.0));
	gl::drawSolidCircle( Vec2f( ((bucksLocs.nearest ->x * 800.0)), ( (1-(bucksLocs.nearest ->y)) * 600.0) ),  2.0f );
	
	glColor3f(Color(1.0,1.0,1.0));
	gl::draw(map);
	//gl::drawString(result,Vec2f(0,600),Color(1.0,0.0,0.0),Font("Times New Roman", 16));
	
}

void Brush_HW04App::update()
{
}

void Brush_HW04App::draw()
{
	//gl::clear();
	//gl::draw(*mySurface_);
	//gl::draw(map);
	if( mTextTexture )
		gl::draw( mTextTexture );
	
	if(bucks){
		for(int i = 0; i < bucksLocs.locsSize; i++){
			Entry e = bucksLocs.locations[i];
			bucksLocs.drawBucks(e.x,e.y);
		}
	}
	else{
		for(int j = 0; j < census2000.censusSize; j++){
			CensusEntry c = census2000.census[j];
			census2000.drawBucks(c.x,c.y);
		}
	}
	
}

CINDER_APP_BASIC( Brush_HW04App, RendererGl )
