#include "App.h"

int main()
{
    App app;

    while (app.App_Runnig())
    {
        app.App_Update();
        app.App_Render();
    }

    return 0;
}