#include <iostream>
#include "Filemanip.h"

int main()
{

    Filemanip file;

    char name[10] = "Teste";

    file.setDir("Teste");

    std::cout<<file.newFile("Teste.txt");

}
