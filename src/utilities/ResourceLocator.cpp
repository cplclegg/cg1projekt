//
// Created by tomnir on 10.08.26.
//

#include "ResourceLocator.h"
std::filesystem::path ResourceLocator::getResourcePath(const std::filesystem::path& relativePath)
{
    return std::filesystem::path { PROJECT_SOURCE_ROOT/relativePath };
}
