#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>


enum insertion_mode 
{
    AUTOMATIC,
    MANUAL
};
    
enum insertion_polarity
{
    LEFT,
    RIGHT
};

enum insertion_direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

struct config
{
    enum insertion_mode mode;
    enum insertion_polarity polarity;

};

bool load_config_file(const char* file);

#endif // CONFIG_H
