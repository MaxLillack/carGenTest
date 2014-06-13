#include "LTest.h"
#include "LTestAssert.h"
#include "parts.h"
#include "generator.h"

using namespace std;

int main()
{
    LTest::addTest("GeneratorTest", [](){
        Generator<parts::Body, parts::ElectroEngine, parts::ManuelTransmission, parts::CarClassification, parts::AutoPilot> car;
        return true;
    });

     LTest::addTest("containsPart() inBound", [](){
        using Gen = Generator<parts::Body, parts::GasEngine>;
        LTAssert::True(Gen::containsPart<parts::Body>());
        LTAssert::True(Gen::containsPart<parts::GasEngine>());
        LTAssert::False(Gen::containsPart<parts::AutomaticTransmission>());
        return true;
    });

    LTest::addTest("containsPart() Border (one part)", [](){
        using Gen = Generator<parts::Body>;
        LTAssert::True(Gen::containsPart<parts::Body>());
        LTAssert::False(Gen::containsPart<parts::GasEngine>());
        LTAssert::False(Gen::containsPart<parts::AutomaticTransmission>());
        return true;
    });

    LTest::addTest("containsPart() Border (zero parts)", [](){
        using Gen = Generator<>;
        LTAssert::False(Gen::containsPart<parts::Body>());
        LTAssert::False(Gen::containsPart<parts::GasEngine>());
        LTAssert::False(Gen::containsPart<parts::AutomaticTransmission>());
        return true;
    });


    //containsDerivedPart Tests
    LTest::addTest("containsDerivedPart() 1", [](){
        using Gen = Generator<parts::AutomaticTransmission>;
        LTAssert::False(Gen::containsPart<parts::Engine>());
        LTAssert::True(Gen::containsPart<parts::Transmission>());
        return true;
    });


    LTest::run();
    return 0;
}
