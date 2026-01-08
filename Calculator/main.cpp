#include "App.h"

int main()
{
    YIN::App app;

    while (app.App_Runnig())
    {
        app.App_Update();
        app.App_Render();
    }

    return 0;
}