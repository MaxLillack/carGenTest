#include "LTest.h"
#include "LTestAssert.h"
#include "configuration.h"
#include "parts.h"

using namespace std;

int main()
{
    LTest::addTest("containsPart() inBound", [](){
        using Conf = Config<parts::Body, parts::GasEngine>;
        LTAssert::True(Conf::containsPart<parts::Body>());
        LTAssert::True(Conf::containsPart<parts::GasEngine>());
        LTAssert::False(Conf::containsPart<parts::AutomaticTransmission<5>>());
        return true;
    });

    LTest::addTest("containsPart() Border (one part)", [](){
        using Conf = Config<parts::Body>;
        LTAssert::True(Conf::containsPart<parts::Body>());
        LTAssert::False(Conf::containsPart<parts::GasEngine>());
        LTAssert::False(Conf::containsPart<parts::AutomaticTransmission<5>>());
        return true;
    });

    LTest::addTest("containsPart() Border (zero parts)", [](){
        using Conf = Config<>;
        LTAssert::False(Conf::containsPart<parts::Body>());
        LTAssert::False(Conf::containsPart<parts::GasEngine>());
        LTAssert::False(Conf::containsPart<parts::AutomaticTransmission<5>>());
        return true;
    });


    //containsDerivedPart Tests
    LTest::addTest("containsDerivedPart() 1", [](){
        using Conf = Config<parts::AutomaticTransmission<5>, parts::GasEngine>;
        LTAssert::False(Conf::containsDerivedPart<parts::Body>());
        LTAssert::True(Conf::containsDerivedPart<parts::GasEngine>());
        LTAssert::True(Conf::containsDerivedPart<parts::Transmission>());
        return true;
    });

    LTest::addTest("containsDerivedPart() 2", [](){
        using Conf = Config<parts::AutomaticTransmission<5>, parts::GasEngine>;
        LTAssert::False(Conf::containsDerivedPart<parts::Body>());
        LTAssert::True(Conf::containsDerivedPart<parts::GasEngine>());
        LTAssert::True(Conf::containsDerivedPart<parts::AutomaticTransmissionBase>());
        LTAssert::False(Conf::containsDerivedPart<parts::ManualTransmissionBase>());
        return true;
    });

    LTest::run();
    return 0;
}
