#include "gobject.h"
#include "custompainter.h"
#include "catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;


class GObjectMock : public gx::GObject {
    void paintSelf(gx::CustomPainter& painter) const {
        painter.drawLine(0,0,0,0);
    }
};

TEST_CASE("Gobject adds children correctly", "[gobject]") {
    GIVEN("A gobject with 2 children") {
        std::shared_ptr<GObjectMock> child1(new GObjectMock);
        std::shared_ptr<GObjectMock> child2(new GObjectMock);
        GObjectMock root;
        root.addChildren(child1);
        root.addChildren(child2);

        WHEN("we get the children from the root") {
            auto children = root.getChildren();

            THEN("they must be 2") {

                REQUIRE(children.size() == 2);
            }
        }
    }
}

TEST_CASE("Gobject paints all children", "[gobject]") {
    GIVEN("A gobject wtih one child") {
        Mock<gx::CustomPainter> painterMock;
        Fake(OverloadedMethod(painterMock, drawLine, void(int,int,int,int)));
        GObjectMock root;
        std::shared_ptr<GObjectMock> child(new GObjectMock);
        root.addChildren(child);

        WHEN("paintAll is invoked") {
            root.paintAll(painterMock.get());

            THEN("there must be 2 paintSelf invocations(root,child)") {
                REQUIRE(
                    Verify(
                        OverloadedMethod(
                                painterMock,
                                drawLine,
                                void(int,int,int,int)))
                        .Exactly(2) == true);
            }
        }
    }
    GIVEN("An empty gobject") {
        Mock<gx::CustomPainter> painterMock;
        Fake(OverloadedMethod(painterMock, drawLine, void(int,int,int,int)));
        GObjectMock root;

        WHEN("paintAll is invoked") {
            root.paintAll(painterMock.get());

            THEN("it's paintSelf must be invoked") {
                REQUIRE(
                    Verify(
                        OverloadedMethod(
                                painterMock,
                                drawLine,
                                void(int,int,int,int))) == true);
            }
        }
    }
}
