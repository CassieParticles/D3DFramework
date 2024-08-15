Stores an array of ComPtrs to render target views
Stores an array of ComPtrs to textures the RTVs are bound to
Stores an array of clear colours for each render target view
Stores a ComPtr to a depth stencil view
Stores a ComPtr to a texture the DSV is bound to
Has a function to add a RTV/DSV
	Function can take an existing texture and make an RTV around it
	Function can take parameters and create a RTV of it's own
Has a function to bind views to the output merger
Has a function to clear each of the views
Has a function to get a pointer to the textures