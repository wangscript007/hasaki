#include "logger.h"

int main(int argc, char **args)
{
    HASAKI_INFO("hello {}!", "world");
    HASAKI_ERROR("hello {}!", "world");
    HASAKI_WARN("hello {}", "world");
    return 0;
}

