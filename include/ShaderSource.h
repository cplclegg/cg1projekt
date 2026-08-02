//
// Created by tomnir on 11.07.26.
//

#ifndef CG1PROJEKT_SHADERSOURCE_H
#define CG1PROJEKT_SHADERSOURCE_H
#include <string>

class ShaderSource
{
private:
    std::string sourcePath;
    char* buffer;
    static char* readSourceFile(const std::string&);
public:
    ShaderSource();
    ShaderSource(const std::string&);
    ShaderSource(const ShaderSource&);
    ~ShaderSource();

    void loadSourceFile(const std::string&);
    char* getSourceString() const;
};


#endif //CG1PROJEKT_SHADERSOURCE_H