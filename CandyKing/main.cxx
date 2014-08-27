#include "OverGame.h"

int main (int argc, char** args)
{
    OverGame overGame;
    overGame.init();
    overGame.initStage1();
    overGame.runStage1();
    overGame.endStage1();
    overGame.end();
    return 0;
}
