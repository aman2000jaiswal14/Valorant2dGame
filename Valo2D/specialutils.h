#ifndef SPECIALUTILS_H
#define SPECIALUTILS_H

class SpecialUtils
{
private:
    bool ids[1000] = {false};
public:
    static SpecialUtils& getInstance();
private:
    SpecialUtils();

public:
    int idGenerator();
    void freeId(int id);
};

#endif // SPECIALUTILS_H
