
#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include <string>
using namespace std;

class IDGenerator {
public:
    static string generate();
    static void init();

private:
    // prevent creating generator
    IDGenerator();
};

#endif
