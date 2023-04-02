#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct FileMode {
    static const constexpr char *read = "rb";
    static const constexpr char *write = "wb";
    static const constexpr char *append = "ab";
    static const constexpr char *readWrite = "rb+";
    static const constexpr char *createWrite = "wb+";
    static const constexpr char *readAppend = "ab+";
};

class Filemanip
{
    private:

    public:

    bool isFileExists(const char *fileSrc)
    {
        FILE *file;

        file = fopen(fileSrc, FileMode::read);
        fclose(file);

        return file != nullptr;
    }

    //Set up a try catch for the methods later on, incase fopen fails;
    void createFile(const char *fileSrc)
    {
        FILE *file;

        file = fopen(fileSrc, FileMode::createWrite);
        fclose(file);
    }

    template<typename T>
    void writeFile(const char *fileSrc, T content)
    {
        FILE *file;

        file = fopen(fileSrc, FileMode::write);
        fwrite(&content, sizeof(T), 1, file);

        fclose(file);
    }

    template<typename T>
    T readFile(const char *fileSrc, T type)
    {
        FILE *file;
        T read;

        file = fopen(fileSrc, FileMode::read);
        fread(&read, sizeof(T), 1, file);
        fclose(file);

        return read;
    }
};
