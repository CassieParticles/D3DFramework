cmake_minimum_required (VERSION 3.8)

list(APPEND Engine "engine/exampleFile.cpp")

add_library(D3D11Framework ${Engine})

#Add GLFW for windows
add_library(GLFW STATIC IMPORTED GLOBAL)
set_property(TARGET GLFW PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/libraries/GLFW/glfw3.lib")
target_link_libraries(D3D11Framework GLFW)

#Add Direct3D11
find_library("d3d11.lib" PATH "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("dxgi.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("d3dcompiler.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("winmm.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("dxguid.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")

target_link_libraries(D3D11Framework d3d11)
target_link_libraries(D3D11Framework dxgi)
target_link_libraries(D3D11Framework d3dcompiler)
target_link_libraries(D3D11Framework winmm)
target_link_libraries(D3D11Framework dxguid)

#Include all additional header files
target_include_directories(D3D11Framework PUBLIC "${CMAKE_CURRENT_LIST_DIR}/libraries/includes")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET D3D11Framework PROPERTY CXX_STANDARD 20)
endif()
