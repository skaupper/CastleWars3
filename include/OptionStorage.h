#ifndef OPTION_STORAGE_H
#define OPTION_STORAGE_H

#include <vector>

#include <bkengine/Storage.h>

#include "Misc.h"


class OptionStorage : public bkengine::Storage
{
    private:
        static std::vector<Resolution> availableResolutions;

    public:
        static const std::string TYPE;
        using Storage::Storage;

        KeyboardLayout player1, player2;
        int resolutionIndex = 2;

        Resolution getResolution();
        const std::vector<Resolution> &getAvailableResolutions();
};

#endif
