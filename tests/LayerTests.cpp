#include "TestDummies.h"
#include <CppUTest/TestHarness.h>

TEST_GROUP(GeneralLayer) {
};

TEST(GeneralLayer, LayerRenderingTest) {
    CallTracer ct;
    auto layer = std::make_unique<Layer<TestWidget, TestHandlerContext, NonModalLayerCreateRequest, TestInteractor>>(
                NonModalLayerCreateRequest{Widget{}, NonModalLayerCreateRequest::Payload{&ct}});

    layer->draw(TestRenderer{}, TestFont{});

    CHECK_EQUAL(2, ct.log.size());
    STRCMP_EQUAL("TestWidget::render", ct.log[0].c_str());
    STRCMP_EQUAL("TestInteractor::render", ct.log[1].c_str());

    ct.log.clear();
}
