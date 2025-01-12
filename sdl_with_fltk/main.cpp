#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <math.h>
class MyWindow : public Fl_Gl_Window {

public:
    MyWindow(int x, int y, int w, int h, const char* l = 0);
    void draw() FL_OVERRIDE;
};

MyWindow::MyWindow(int x, int y, int w, int h, const char* l)
    : Fl_Gl_Window(x, y, w, h, l)
{}


void MyWindow::draw() {
    if (!valid()) {
    }

}

int main(int argc, char** argv)
{
    MyWindow *window = new MyWindow(0, 0, 340, 180, "Test");
    window->end();
    window->show(argc, argv);
    return Fl::run();
}
