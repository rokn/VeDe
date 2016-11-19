#include <QString>
#include <QtTest>

class GObjectTest : public QObject
{
    Q_OBJECT

public:
    GObjectTest();

private Q_SLOTS:
    void addChildrenTest();
};

GObjectTest::GObjectTest()
{
}

void GObjectTest::addChildrenTest()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(GObjectTest)

#include "tst_gobjecttest.moc"
