//
// Created by tomnir on 10.08.26.
//

#ifndef CG1PROJEKT_RESOURCELOCATOR_H
#define CG1PROJEKT_RESOURCELOCATOR_H
#include <filesystem>
#include "config.h"
class ResourceLocator
{
public:
    static std::filesystem::path getResourcePath(const std::filesystem::path& relativePath);
};


#endif //CG1PROJEKT_RESOURCELOCATOR_H