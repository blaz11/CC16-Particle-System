#include "settings.h"

Settings::Settings()
{
    velocityValue = 1;
    liveTime = 1000;
    variation = 10;
    count = 50;
    valocityVector = new glm::vec4(0, 0, 0, 0);
}
