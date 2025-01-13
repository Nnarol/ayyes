#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/x.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>

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
    Fl_Window* main_win = new Fl_Window(0, 0, 600, 800, "Valami1");
    Fl_Box* box = new Fl_Box(401, 401, 100, 100, "Box");
    MyWindow *window = new MyWindow(0, 0, 400, 400, "Test");
    window->begin();
    window->end();
    //window->show(argc, argv);
    main_win->end();
    main_win->show(argc, argv);
    SDL_Window* sdl_window;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Unable to init", SDL_GetError());
    }
    HWND hwnd = fl_xid(window);
    SDL_PropertiesID props = SDL_CreateProperties();

    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, hwnd);
    //SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, true);
    sdl_window = SDL_CreateWindowWithProperties(props);
    SDL_Renderer* renderer = SDL_CreateRenderer(sdl_window, NULL);
    SDL_RenderClear(renderer);
    SDL_FRect rect;
    rect.x = 250;
    rect.y = 150;
    rect.w = 200;
    rect.h = 200;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);

    SDL_Delay(5000);
    SDL_DestroyWindow(sdl_window);
    SDL_DestroyProperties(props);
    //return Fl::run();
    return 0;
}
