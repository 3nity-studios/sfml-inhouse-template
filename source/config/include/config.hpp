#pragma once

#include <string>

/**
 * @brief The core configuration of the project
 *
 * This class makes up the library part of the executable, which means that the
 * main logic is implemented here. This kind of separation makes it easy to
 * test the implementation for the executable, because the logic is nicely
 * separated from the command-line logic implemented in the main function.
 */
struct config
{
    /**
     * @brief Simply initializes the name member to the name of the project
     */
    config();

    std::basic_string<char> project_version;
};