#include "gobject.h"
#include "custompainter.h"
#include "catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;

TEST_CASE("Gobjects add children correctly", "[gobject]")
{
    Mock<gx::CustomPainter> painterMock;
    painterMock.get();
}
