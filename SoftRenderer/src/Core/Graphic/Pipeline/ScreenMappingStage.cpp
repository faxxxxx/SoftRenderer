//
//  ScreenMappingStage.cpp
//  SoftRenderer
//
//  Created by kirk on 2019/11/24.
//  Copyright © 2019 kirk. All rights reserved.
//

#include "ScreenMappingStage.h"

static void ScreenMapping(Vertex &v, int w, int h)
{
    auto halfw = 0.5f * (w - 1);
    auto halfh = 0.5f * (h - 1);
    v.pos.x = v.pos.x * halfw + halfw;
    v.pos.y = v.pos.y * halfh + halfh;
}

bool ScreenMappingStage::Execute(PipelineContex *ctx) {
    auto w = ctx->_pDeviceAPI->PixelWidth();
    auto h = ctx->_pDeviceAPI->PixelHeight();
    auto &verts = ctx->_vertexes;
    for(auto &v : verts) {
        ScreenMapping(v, w, h);
    }
    return true;
}
