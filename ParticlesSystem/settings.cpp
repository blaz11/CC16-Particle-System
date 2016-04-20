#include "settings.h"

Settings::Settings()
{
    velocityValue = 50;
    liveTime = 100;
    variation = 25;
    count = 2;
    velocityVector = glm::vec4(-1, 0, 0, 0);
    startPosition = glm::vec4(10, 35, 0, 0);
}
