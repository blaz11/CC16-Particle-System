#ifndef SETTINGS_H
#define SETTINGS_H

#include <glm/vec4.hpp>


class Settings
{
    public:
        Settings();
        float velocityValue;
        int liveTime;
        int variation;
        int count;
        glm::vec4* valocityVector;
};

#endif // SETTINGS_H
