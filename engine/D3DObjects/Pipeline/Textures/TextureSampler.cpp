#include "TextureSampler.h"

TextureSampler::TextureSampler(const std::string& name, ComPtr<ID3D11SamplerState> sampler):name{name},sampler{sampler}
{
}
