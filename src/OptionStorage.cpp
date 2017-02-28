#include "OptionStorage.h"

using namespace bkengine;

std::vector<Resolution> OptionStorage::availableResolutions = {
    {640, 480},
    {800, 600},
    {1024, 768},
    {1280, 960},
    {1400, 1050},
    {1600, 1200}
};
const std::string OptionStorage::TYPE = "OPTIONSTORAGE";

Resolution OptionStorage::getResolution()
{
    return availableResolutions[resolutionIndex];
}

const std::vector<Resolution> &OptionStorage::getAvailableResolutions()
{
    return availableResolutions;
}
