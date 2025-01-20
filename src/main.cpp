#include "App.hpp"

int main(int argc, char* argv[])
{
    tlr::AppConfig appConfig =
    {
        .windowWidth = 800,
        .windowHeight = 600,
        .windowPosX = 100,
        .windowPosY = 100,
        .numberCount = 107,
        .swapTimeInMillis = 5
    };

    tlr::App app(appConfig);
    app.Run();
    
    return 0;
}