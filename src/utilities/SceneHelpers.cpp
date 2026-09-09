//
// Created by tomnir on 09.09.26.
//

#include "../../include/SceneHelpers.h"

SceneNode SceneHelpers::makeCandleCluster(const Vec3& xzPosition, Renderable& c1, Renderable& c2, Renderable& c3, Renderable& cf)
{
    SceneNode candle1 {c1};
    SceneNode cf1 {cf};
    SceneNode candle2 {c2};
    SceneNode cf2 {cf};
    SceneNode candle3 {c3};
    SceneNode cf3 {cf};
    // offset vectors
    Vec3 c1offset {0.0, 0.23523379862308502f, 0.0};
    Vec3 cf1offset {0.0, 0.225, 0.0};
    Vec3 c2offset {-0.01172077655, 0.14632247388362885,  -0.26494348049};
    Vec3 cf2offset {0.0, 0.125, 0.0};
    Vec3 c3offset {0.28967034816, 0.10961973667144775,  -0.14722788333};
    Vec3 cf3offset {0.0, 0.072, 0.0};
    SceneNode root {};
    root.translate(xzPosition);
    candle1.translate(c1offset);
    cf1.translate(cf1offset);
    candle1.addChild(cf1);
    candle2.translate(c2offset);
    cf2.translate(cf2offset);
    candle2.addChild(cf2);
    candle3.translate(c3offset);
    cf3.translate(cf3offset);
    candle3.addChild(cf3);
    root.addChild(candle1);
    root.addChild(candle2);
    root.addChild(candle3);

    return root;
}
