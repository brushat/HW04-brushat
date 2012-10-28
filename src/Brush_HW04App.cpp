



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
