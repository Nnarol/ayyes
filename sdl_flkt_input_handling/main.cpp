#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/gl.h>
#include <FL/x.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>

#include <thread>


SDL_Window* sdl_window;
SDL_Renderer* renderer;
SDL_Texture* img;
int x = 50;
int y = 50;
int dst_x = -1;
int dst_y = -1;
class MyWindow : public Fl_Gl_Window {

public:
    MyWindow(int x, int y, int w, int h, const char* l = 0);
    void draw() FL_OVERRIDE;
    int handle(int event) FL_OVERRIDE;
};

MyWindow::MyWindow(int x, int y, int w, int h, const char* l)
    : Fl_Gl_Window(x, y, w, h, l)
{}


void MyWindow::draw() {

}

int MyWindow::handle(int event)
{
    switch (event)
    {
    case FL_FOCUS:
    case FL_UNFOCUS:
        return 1;
    case FL_PUSH:
        return 1;
    case FL_KEYBOARD:
        SDL_Event kb_event;
        kb_event.type = SDL_EVENT_KEY_DOWN;
        SDL_PushEvent(&kb_event);
        return 1;
    default:
        return Fl_Gl_Window::handle(event);
    }
}

void button_callback(Fl_Widget* w, void* c_s)
{
    fl_alert("Test");
}

void draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    if (dst_x != -1 && dst_y != -1)
    {
        if (dst_x > x)
        {
            x += 1;
        }
        else if (dst_x < x)
        {
            x -= 1;
        }
        if (dst_y > y)
        {
            y += 1;
        }
        else if (dst_y < y)
        {
            y -= 1;
        }
    }
    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 50;
    rect.h = 50;
    SDL_RenderTexture(renderer, img, NULL, &rect);
    SDL_RenderPresent(renderer);
}

void handle_keyboard(SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_LEFT:
        x -= 1;
        break;
    case SDLK_RIGHT:
        x += 1;
        break;
    case SDLK_W:
        y += 1;
        break;
    default:
        break;
    }
}

void handle_mouse(SDL_MouseButtonEvent button)
{
    switch (button.button)
    {
    case SDL_BUTTON_RIGHT:
        dst_x = button.x;
        dst_y = button.y;
        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    Fl_Window* main_win = new Fl_Window(0, 100, 600, 700, "Valami1");
    Fl_Button* button = new Fl_Button(401, 401, 100, 30, "Test");
    button->callback(button_callback);
    MyWindow *window = new MyWindow(0, 0, 400, 400, "Test");
    window->begin();
    window->end();
    main_win->end();
    main_win->show(argc, argv);

    //Fl::focus(window);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Unable to init %s", SDL_GetError());
    }
    HWND hwnd = fl_xid(window);
    SDL_PropertiesID props = SDL_CreateProperties();

    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN, true);
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_ALWAYS_ON_TOP_BOOLEAN, true);
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_PIXEL_FORMAT_HWND_POINTER, hwnd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, hwnd);
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, true);
    sdl_window = SDL_CreateWindowWithProperties(props);
    renderer = SDL_CreateRenderer(sdl_window, NULL);
    SDL_RenderClear(renderer);
    img = IMG_LoadTexture(renderer, "C:\\project\\repository\\ayyes\\sdl_flkt_input_handling\\build\\ship.png");
    
    while (true)
    {
        draw();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            SDL_Log("Type: %u", event.type);
            switch (event.type)
            {
            case SDL_EVENT_KEY_DOWN:
                handle_keyboard(event.key.key);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                handle_mouse(event.button);
                break;
            default:
                break;
            }
        }
        SDL_EventType;
        SDL_Delay(5);
        auto check_val = Fl::check();
        //SDL_Log("fl msg: %d", check_val);
    }

    SDL_DestroyWindow(sdl_window);
    SDL_DestroyProperties(props);   
    return 0;
}
