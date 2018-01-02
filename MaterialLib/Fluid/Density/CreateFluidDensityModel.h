/*!
   \file  CreateFluidDensityModel.h
   \brief create an instance of a fluid density class.

   \copyright
    Copyright (c) 2012-2018, OpenGeoSys Community (http://www.opengeosys.org)
               Distributed under a Modified BSD License.
               See accompanying file LICENSE.txt or
               http://www.opengeosys.org/project/license
*/
#pragma once

#include <memory>

#include "BaseLib/ConfigTree.h"

#include "MaterialLib/Fluid/FluidProperty.h"

namespace MaterialLib
{
namespace Fluid
{
/// Create a density model
/// \param config  ConfigTree object has a tag of `<density>`
std::unique_ptr<FluidProperty> createFluidDensityModel(
    BaseLib::ConfigTree const& config);
}
}  // end namespace
