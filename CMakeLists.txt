# MIT License
# 
# Copyright (c) 2020 ZHOU He
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
cmake_minimum_required(VERSION 3.16)

set(projectdir ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE all_src cxx/*.*)
set(cxxdir ${projectdir}/cxx)
foreach(filename ${all_src} )
	get_filename_component(source_dir ${filename} PATH)
	file(RELATIVE_PATH source_dir ${cxxdir} ${source_dir})
	file(TO_NATIVE_PATH ${source_dir} source_dir)
	source_group(${source_dir} FILES ${filename})
endforeach(filename)

set(LLVM_PROJECT "" CACHE PATH "Root path of llvm-project")
set(LLVM_BUILD "" CACHE PATH "Root path of CMAKE build of llvm-project")
if(LLVM_PROJECT STREQUAL "" OR LLVM_BUILD STREQUAL "")
	message("You must specify LLVM_PROJECT & LLVM_BUILD")
endif()
link_directories(${LLVM_BUILD}/lib)

file(GLOB llvm_libs_debug_exp ${LLVM_BUILD}/Debug/lib/*.exp)
file(GLOB llvm_libs_debug ${LLVM_BUILD}/Debug/lib/*.lib)
string(REPLACE ".exp;" ".lib;" llvm_libs_debug_exp "${llvm_libs_debug_exp}")
list(REMOVE_ITEM llvm_libs_debug ${llvm_libs_debug_exp})
file(GLOB llvm_libs_optimized ${LLVM_BUILD}/RelWithDebInfo/lib/*.lib)
string(REPLACE ";" ";optimized;" llvm_libs_optimized "${llvm_libs_optimized}")

add_executable(kun ${all_src})
target_link_libraries(kun PUBLIC debug ${llvm_libs_debug})
target_link_libraries(kun PUBLIC optimized ${llvm_libs_optimized})
target_include_directories(kun PUBLIC ${LLVM_PROJECT}/llvm/include ${LLVM_BUILD}/include ${LLVM_PROJECT}/clang/include ${LLVM_BUILD}/tools/clang/include ${CMAKE_CURRENT_SOURCE_DIR}/cxx/include)
target_include_directories(kun PUBLIC externals/cpp-peglib)



