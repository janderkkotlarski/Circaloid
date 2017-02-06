#include "menu.h"

void menu()
{
    int repeat{1};

    while (repeat != 0)
    {
        Simulation simul;

        repeat = simul.run();
    }
}
