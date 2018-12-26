/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Flora License, Version 1.1 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://floralicense.org/license/
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VDRAWABLE_H
#define VDRAWABLE_H
#include <future>
#include "vbrush.h"
#include "vpath.h"
#include "vrle.h"
#include "vraster.h"

class VDrawable {
public:
    enum class DirtyState {
        None = 0x00000000,
        Path = 0x00000001,
        Stroke = 0x00000010,
        Brush = 0x00000100,
        All = (None | Path | Stroke | Brush)
    };
    enum class Type : unsigned char{
        Fill,
        Stroke,
    };
    typedef vFlag<DirtyState> DirtyFlag;
    virtual ~VDrawable() = default;
    void setPath(const VPath &path);
    void setFillRule(FillRule rule) { mFillRule = rule; }
    void setBrush(const VBrush &brush) { mBrush = brush; }
    void setStrokeInfo(CapStyle cap, JoinStyle join, float meterLimit,
                       float strokeWidth);
    void setDashInfo(float *array, uint size);
    void preprocess(const VRect &clip);
    VRle rle();

public:
    struct StrokeInfo {
        std::vector<float> mDash;
        float              width{0.0};
        float              meterLimit{10};
        bool               enable{false};
        CapStyle           cap{CapStyle::Flat};
        JoinStyle          join{JoinStyle::Bevel};
    };
    VBrush            mBrush;
    VPath             mPath;
    RleShare          mRleFuture;
    VRle              mRle;
    StrokeInfo        mStroke;
    DirtyFlag         mFlag{DirtyState::All};
    FillRule          mFillRule{FillRule::Winding};
    VDrawable::Type   mType{Type::Fill};
};

#endif  // VDRAWABLE_H
