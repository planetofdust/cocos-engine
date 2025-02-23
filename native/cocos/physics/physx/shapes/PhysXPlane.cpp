/****************************************************************************
 Copyright (c) 2020-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "physics/physx/shapes/PhysXPlane.h"
#include "physics/physx/PhysXUtils.h"
#include "physics/physx/PhysXWorld.h"
#include "physics/physx/shapes/PhysXShape.h"

namespace cc {
namespace physics {

PhysXPlane::PhysXPlane() : _mConstant(0.F),
                           _mNormal(0.F, 1.F, 0.F){};

void PhysXPlane::setConstant(float x) {
    _mConstant = x;
    updateCenter();
}

void PhysXPlane::setNormal(float x, float y, float z) {
    _mNormal = physx::PxVec3{x, y, z};
    updateCenter();
}

void PhysXPlane::onComponentSet() {
    _mShape = PxGetPhysics().createShape(getPxGeometry<physx::PxPlaneGeometry>(), getDefaultMaterial(), true);
    updateCenter();
}

void PhysXPlane::updateScale() {
    updateCenter();
}

void PhysXPlane::updateCenter() {
    auto* node = getSharedBody().getNode();
    auto& geo = getPxGeometry<physx::PxPlaneGeometry>();
    physx::PxTransform local;
    pxSetFromTwoVectors(local.q, physx::PxVec3{1.F, 0.F, 0.F}, _mNormal);
    local.p = _mNormal * _mConstant + _mCenter;
    getShape().setLocalPose(local);
}

} // namespace physics
} // namespace cc
