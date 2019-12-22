//
//  ScreenMappingStage.hpp
//  SoftRenderer
//
//  Created by kirk on 2019/11/24.
//  Copyright © 2019 kirk. All rights reserved.
//

#pragma once
#include "PipelineStage.h"

class ScreenMappingStage : public PipelineStage {
 public:
    virtual bool Execute(PipelineContex *ctx) override;
};
