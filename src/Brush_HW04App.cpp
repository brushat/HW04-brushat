



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
	static const int AppWidth=800;
	static const int AppHeight=600;
	static const int TextureSize=1024;
	
	
};

void Brush_HW04App::setup()
{
	
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
			if(((abs(vec[j].x) - abs(vec[k].x)) < .00001) && ((abs(vec[j].y) - abs(vec[k].y)) < .00001)){
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

	
		
	brushatStarbucks bucksLocs;

	bucksLocs.build(locations, vec.size());

	console() << "output = " << bucksLocs.locations[0].identifier << endl;
	console() << "output = " << bucksLocs.locations[1].identifier << endl;

	Entry* nearest = bucksLocs.getNearest(0,0);

	console() << nearest->identifier << " " << nearest->x << " " << nearest->y << std::endl;
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

}

CINDER_APP_BASIC( Brush_HW04App, RendererGl )
