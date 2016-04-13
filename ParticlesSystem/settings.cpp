#include "settings.h"

Settings::Settings()
{
    velocityValue = 20;
    liveTime = 100;
    variation = 10;
    count = 50;
    valocityVector = new glm::vec4(1, 0, 0, 0);
}
