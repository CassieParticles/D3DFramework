Mesh stores the bare minimum vertex data needed to be rendered
Contains an array of vertex buffers
	Uses array instead of a vector because all vertex slots need to be written to
Contains array of vertex strides (size of each vertex in bytes)
Contains array of vertex offsets (how far the first vertex is in bytes)

Stores index buffer
