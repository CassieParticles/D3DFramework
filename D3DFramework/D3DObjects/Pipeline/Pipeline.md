Stores a ComPtr to a shader for each programmable pipeline
Stores the bytecode for the vertex shader
Stores primitive type

Has a [[RasterizerState]] for managing the rasterizer
Has a [[Vertex layout]] for the input layout

Has function to compile all shaders, and create all managing objects
Has a function to bind everything within the pipeline

Stores array of [[CBufferBinding]]s, iterates through them when "bind" is called