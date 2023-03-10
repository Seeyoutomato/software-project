
//
// This source file is part of appleseed.
// Visit https://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014-2018 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

// appleseed.renderer headers.
#include "renderer/modeling/camera/icamerafactory.h"

// appleseed.foundation headers.
#include "foundation/memory/autoreleaseptr.h"

// appleseed.main headers.
#include "main/dllsymbol.h"

#include <stdio.h>
#include <string>
#include <cstring>
#include <vector>


// Forward declarations.
namespace foundation { class Dictionary; }
namespace foundation { class DictionaryArray; }
namespace renderer { class Camera; }
namespace renderer { class ParamArray; }

namespace renderer
{

    //
    // Multi lens camera factory.
    //

    class APPLESEED_DLLSYMBOL MultiLensCameraFactory
        : public ICameraFactory
    {
    public:
        // Delete this instance.
        void release() override;

        // Return a string identifying this camera model.
        const char* get_model() const override;

        // Return metadata for this camera model.
        foundation::Dictionary get_model_metadata() const override;

        // Return metadata for the inputs of this camera model.
        foundation::DictionaryArray get_input_metadata() const override;

        // Create a new camera instance.
        foundation::auto_release_ptr<Camera> create(
            const char* name,
            const ParamArray& params) const override;
    };


    typedef struct LensElement
    {
        double radius, thickness, ior, diameter;
        bool is_aperture;

        LensElement() {}

        LensElement(double radius, double thickness, double ior, double diameter, double factor) :
            radius(radius), thickness(thickness), ior(ior), diameter(diameter)
        {
            is_aperture = ior == 0;
            scale(factor);
        }

        void scale(double factor)
        {
            radius = radius * factor;
            thickness = thickness * factor;
            diameter = diameter * factor;
        }

    } LensElement;

    enum class Pupil {entrance, exit};
}   // namespace renderer
