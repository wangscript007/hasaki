#include "logger.h"

int main(int argc, char **args)
{
    HASAKI_INFO("hello {}!", "world");
    HASAKI_ERROR("hello {}!", "world");
    return 0;
}