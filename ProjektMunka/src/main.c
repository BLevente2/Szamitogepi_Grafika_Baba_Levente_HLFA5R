#include "app.h"

int main(int argc, char* argv[])
{
    App app;
    SDL_Event event;

    init_app(&app, 800, 600);
    while (!app.quit) {
        while (SDL_PollEvent(&event))
            handle_app_events(&app, &event);
        update_app(&app);
        render_app(&app);
    }
    destroy_app(&app);
    return 0;
}