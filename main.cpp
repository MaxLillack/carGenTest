#include "LTest.h"
#include "LTestAssert.h"
#include "configuration.h"
#include "parts.h"
#include "generator.h"
#include "Restriction.h"

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
        LTAssert::False(Conf::containsDerivedPart<parts::ManuelTransmissionBase>());
        return true;
    });

    LTest::addTest("containsDerivedPart() 3", [](){
        using Conf = Config<parts::AutomaticTransmission<4>, parts::Body, parts::ElectroEngine>;
        LTAssert::True(Conf::containsDerivedPart<parts::Transmission>(), "must contain Transmission");
        LTAssert::True(Conf::containsDerivedPart<parts::Engine>(), "must contain Engine");
        LTAssert::True(Conf::containsDerivedPart<parts::Body>(), "must contain Body");
        LTAssert::True(!(Conf::containsDerivedPart<parts::ElectroEngine>()) || isEven(Conf::PreGenCar::gears));
        return true;
    });

    LTest::addTest("GeneratorTest", [](){
        using Conf = Config<parts::Body, parts::ElectroEngine, parts::AutomaticTransmission<4>>;
        using Restr = CarRestrictions<Conf>;
        using Gen = Generator<Conf, Restr, parts::Body, parts::ElectroEngine, parts::AutomaticTransmission<4>>;
        Gen car;
        return true;
    });

    LTest::addTest("CarGeneratorTest", [](){
        using CarGen = CarGenerator<parts::Body, parts::ElectroEngine, parts::AutomaticTransmission<4>>;
        CarGen car;
        return true;
    });

/*
    //has to fail at compile time
    LTest::addTest("GeneratorTest fail", [](){
        using Conf = Config<parts::ElectroEngine, parts::AutomaticTransmission<5>>;
        using Restr = CarRestrictions<Conf>;
        using Gen = Generator<Conf, Restr, parts::ElectroEngine, parts::AutomaticTransmission<5>>;
        Gen car;
        return true;
    });
//*/
/*
    //has to fail at compile time (uneven ger number for electro engine
    LTest::addTest("CarGeneratorTest fail", [](){
        CarGenerator<parts::Body, parts::ElectroEngine, parts::AutomaticTransmission<5>> gen;
        return true;
    });
*/
    LTest::run();
    return 0;
}
