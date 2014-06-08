#include "LTest.h"
#include "LTestAssert.h"
#include "configuration.h"
#include "parts.h"

using namespace std;

int main()
{
    LTest::addTest("test 1", [](){
        Config<parts::Body, parts::Engine> conf;
        LTAssert::True(conf.containsPart<parts::Body>());
        LTAssert::True(conf.containsPart<parts::Engine>());
        LTAssert::False(conf.containsPart<parts::Transmission>());
        return true;
    });

    LTest::run();
    return 0;
}
