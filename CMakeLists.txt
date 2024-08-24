list(APPEND Engine "engine/Engine/Window.cpp")
list(APPEND Engine "engine/Engine/TimeManager.cpp")
list(APPEND Engine "engine/Engine/Timer.cpp")
list(APPEND Engine "engine/Engine/Delay.cpp")

list(APPEND Engine "engine/Engine/Input/Input.cpp")
list(APPEND Engine "engine/Engine/Input/InputAction.cpp")
list(APPEND Engine "engine/Engine/Input/InputActionManager.cpp")

list(APPEND Engine "engine/D3DObjects/RenderTarget.cpp")
list(APPEND Engine "engine/D3DObjects/Device.cpp")
list(APPEND Engine "engine/D3DObjects/Mesh.cpp")

list(APPEND Engine "engine/D3DObjects/Pipeline/Pipeline.cpp")
list(APPEND Engine "engine/D3DObjects/Pipeline/RasterizerState.cpp")
list(APPEND Engine "engine/D3DObjects/Pipeline/VertexLayout.cpp")
list(APPEND Engine "engine/D3DObjects/Pipeline/CBuffer.cpp")

list(APPEND Engine "engine/DataManagers/CBufferManager.cpp")

add_library(D3D11Framework ${Engine})


#Include all additional header files
target_include_directories(D3D11Framework PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

target_include_directories(D3D11Framework PUBLIC "${CMAKE_CURRENT_LIST_DIR}/libraries/includes")


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

