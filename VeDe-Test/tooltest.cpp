#include "tool.h"
#include "catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;

class ToolMock : public gx::Tool{
public:
    ToolMock(gx::Canvas* canvas) : Tool(canvas){
//        addState("test1", STATE_DEF {canvas->getCursor(); return -1;});
//        addState("test2", STATE_DEF {canvas->getCursor(); return -2;});
//        addTransition(0,QEvent::MouseMove,1);
//        addTransition(1,QEvent::MouseButtonPress,0);
    }
};

TEST_CASE("Tool adds states correctly", "[tools][basetool]") {
    GIVEN("A tool with 2 added states") {
        Mock<gx::Canvas> canvasMock;
        ToolMock tool(&canvasMock.get());

        WHEN("we get their names") {
            QVector<QString> names = tool.getAllStateNames();

            THEN("we expect they are the same as when added") {
                REQUIRE(names.size() == 2);
                REQUIRE(names.at(0) == "test1");
                REQUIRE(names.at(1) == "test2");
            }
        }
    }
}

TEST_CASE("Tool handles events properly", "[tools][basetool]") {
    GIVEN("A tool with 2 states and 2 transitions") {
        Mock<gx::Canvas> canvasMock;
        ToolMock tool(&canvasMock.get());
        Fake(Method(canvasMock, getCursor));

        WHEN("we pass correct events") {
            QEvent moveEvent(QEvent::MouseMove);
            QEvent pressEvent(QEvent::MouseButtonPress);
//            tool.handleEvent(moveEvent);
//            tool.handleEvent(pressEvent);

            THEN("the states should transition") {
                bool transitioned = Verify(Method(canvasMock, getCursor)).Exactly(2);
                REQUIRE(transitioned);
            }
        }

        WHEN("we pass incorrect events") {
            QEvent randomEvent1(QEvent::KeyPress);
            QEvent randomEvent2(QEvent::KeyRelease);
//            tool.handleEvent(randomEvent1);
//            tool.handleEvent(randomEvent2);

            THEN("the states shouldn't transition") {
                bool no_transitions = Verify(Method(canvasMock, getCursor)).Exactly(0);
            }
        }
    }
}
