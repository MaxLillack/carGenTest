#include "LTest.h"
#include "LTestAssert.h"
#include "configuration.h"
#include "parts.h"

using namespace std;

int main()
{
    LTest::addTest("containsPart() inBound", [](){
        Config<parts::Body, parts::Engine> conf;
        LTAssert::True(conf.containsPart<parts::Body>());
        LTAssert::True(conf.containsPart<parts::Engine>());
        LTAssert::False(conf.containsPart<parts::Transmission>());
        return true;
    });

    LTest::addTest("containsPart() Border (one part)", [](){
        Config<parts::Body> conf;
        LTAssert::True(conf.containsPart<parts::Body>());
        LTAssert::False(conf.containsPart<parts::Engine>());
        LTAssert::False(conf.containsPart<parts::Transmission>());
        return true;
    });

    LTest::addTest("containsPart() Border (zero parts)", [](){
        Config<> conf;
        LTAssert::False(conf.containsPart<parts::Body>());
        LTAssert::False(conf.containsPart<parts::Engine>());
        LTAssert::False(conf.containsPart<parts::Transmission>());
        return true;
    });

    LTest::run();
    return 0;
}
