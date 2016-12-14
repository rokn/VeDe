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
        root.addChild(child1);
        root.addChild(child2);

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
        Fake(OverloadedMethod(painterMock, drawLine, void(float,float,float,float)));
        GObjectMock root;
        std::shared_ptr<GObjectMock> child(new GObjectMock);
        root.addChild(child);

        WHEN("paintAll is invoked") {
            root.paintAll(painterMock.get());

            THEN("there must be 2 paintSelf invocations(root,child)") {
                bool ranTwice = Verify(
                        OverloadedMethod(
                                painterMock,
                                drawLine,
                                void(float,float,float,float)))
                        .Exactly(2);
                REQUIRE(ranTwice);
            }
        }
    }
    GIVEN("An empty gobject") {
        Mock<gx::CustomPainter> painterMock;
        Fake(OverloadedMethod(painterMock, drawLine, void(float,float,float,float)));
        GObjectMock root;

        WHEN("paintAll is invoked") {
            root.paintAll(painterMock.get());

            THEN("it's paintSelf must be invoked") {
                bool hasInvoked = Verify(
                        OverloadedMethod(
                                painterMock,
                                drawLine,
                                void(float,float,float,float)));
                REQUIRE(hasInvoked);
            }
        }
    }
}

TEST_CASE("Gobject can find a child", "[gobject]") {
    GIVEN("A gobject wtih a child with a child") {
        GObjectMock root;
        std::shared_ptr<GObjectMock> child1(new GObjectMock);
        std::shared_ptr<GObjectMock> child2(new GObjectMock);
        child1->setId(1);
        child2->setId(2);
        root.addChild(child1);
        child1->addChild(child2);

        WHEN("findInChildren(1) is invoked") {
            gx::GObject* found = root.findInChildren(1);

            THEN("The gobject child must be found") {
                REQUIRE(found->getId() == 1);
            }
        }

        WHEN("findInChildren(2) is invoked") {
            gx::GObject* found = root.findInChildren(2);

            THEN("The gobject child's child must be found") {
                REQUIRE(found->getId() == 2);
            }
        }
    }
}
