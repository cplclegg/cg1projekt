//
// Created by tomnir on 11.07.26.
//

#ifndef CG1PROJEKT_SHADERSOURCE_H
#define CG1PROJEKT_SHADERSOURCE_H
#include <string>
#include <filesystem>
class ShaderSource
{
private:
    std::string sourcePath;
    char* buffer;
    bool loadSuccess;
    char* readSourceFile(const std::filesystem::path&);
public:
    ShaderSource();
    ShaderSource(const std::string&);
    ShaderSource(const ShaderSource&);
    ~ShaderSource();

    void loadSourceFile(const std::string&);
    [[nodiscard]] char* getSourceString() const;
    [[nodiscard]] bool isValid() const;
};


#endif //CG1PROJEKT_SHADERSOURCE_H