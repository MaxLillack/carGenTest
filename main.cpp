#include "LTest.h"
#include "LTestAssert.h"
#include "parts.h"
#include "generator.h"
#include "dsl.h"

using namespace std;


class DEADDSL{};

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

    LTest::addTest("DSL1", [](){
        using Gen = DSL<EcoLine>;
        Gen test;
        return true;
    });


    LTest::addTest("DSL2", [](){
        using Gen= typename DSL<EcoLine>::Gen<>;
        LTAssert::True(Gen::containsPart<parts::Engine>());
        LTAssert::True(Gen::containsPart<parts::ElectroEngine>());
        LTAssert::False(Gen::containsPart<parts::GasEngine>());
        return true;
    });

    LTest::addTest("DSL3", [](){
        using Gen= typename DSL<EcoLine>::Gen<parts::GasEngine>;
        LTAssert::True(Gen::containsPart<parts::Engine>());
        LTAssert::True(Gen::containsPart<parts::ElectroEngine>());
        LTAssert::True(Gen::containsPart<parts::GasEngine>());
        return true;
    });

/*
    //must not compile: "Unknown DSLClass handling. The is no DSL specialization for given class"
    LTest::addTest("DSL4", [](){
        using Gen= typename DSL<DEADDSL>::Gen<>;
        return true;
    });
//*/

/*
    //must not compile: "Gas is not Eco"
    LTest::addTest("DSL5", [](){
        using Gen= typename DSL<StrictEcoLine>::Gen<parts::GasEngine>;
        return true;
    });
//*/

    LTest::addTest("DSL6", [](){
        using Gen= typename DSL<StrictEcoLine>::Gen<>;
        LTAssert::True(Gen::containsPart<parts::Engine>());
        LTAssert::True(Gen::containsPart<parts::ElectroEngine>());
        LTAssert::False(Gen::containsPart<parts::GasEngine>());
        return true;
    });

    LTest::addTest("DSL Part Reduce", [](){
        using Gen= typename DSL<StrictEcoLine, EcoLine>::Gen<>;
        LTAssert::True(Gen::containsPart<parts::Engine>());
        LTAssert::True(Gen::containsPart<parts::ElectroEngine>());
        LTAssert::False(Gen::containsPart<parts::GasEngine>());
        return true;
    });

    LTest::run();
    return 0;
}
