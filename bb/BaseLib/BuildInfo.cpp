/**
 * \brief  Build information.
 *
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include "BaseLib/BuildInfo.h"

namespace BaseLib
{

namespace BuildInfo
{

    const std::string build_timestamp("");

    const std::string cmake_cxx_compiler("C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin/amd64_x86/cl.exe");
    const std::string cmake_cxx_flags(" /DWIN32 /D_WINDOWS /W3 /GR /EHsc /W3 /wd4290 /wd4267 /wd4996 /bigobj /bigobj /openmp");
    const std::string cmake_cxx_flags_release("/MD /O2 /Ob2 /D NDEBUG /MP");
    const std::string cmake_cxx_flags_debug("/D_DEBUG /MDd /Zi /Ob0 /Od   /MP");

    const std::string git_version_sha1("3994cdf93499830d66be7d49a3f785971d74c0b5");
    const std::string git_version_sha1_short("3994cdf9");

    const std::string git_describe("6.0.4-757-g3994cdf");
    const std::string ogs_version("6.0.4");

    const std::string source_path("D:/ogs");
    const std::string data_path("D:/ogs/Tests/Data");
    const std::string data_binary_path("D:/ogs/bb/Tests/Data");
    const std::string tests_tmp_path("D:/ogs/bb/Tests/");

}
}
