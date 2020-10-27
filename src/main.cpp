#include "Model/IApplication.h"

int main()
{

    auto app = CreateApplication();
    app->start();
    delete app;

    return 0;
}
