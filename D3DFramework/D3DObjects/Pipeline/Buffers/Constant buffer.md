Used for data that will be constant through execution of the programmable pipeline
Written as explicit specialization of [[Buffer]]
Created through [[ResourceManager]] rather than directly
Usage can only be dynamic or immutable (constant buffers aren't written to by the GPU)
