#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Brush_HW04App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void Brush_HW04App::setup()
{
}

void Brush_HW04App::mouseDown( MouseEvent event )
{
}

void Brush_HW04App::update()
{
}

void Brush_HW04App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( Brush_HW04App, RendererGl )
