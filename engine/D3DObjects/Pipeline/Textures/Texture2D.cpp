#include "Texture2D.h"

Texture2D::Texture2D(const std::string& name, ComPtr<ID3D11Texture2D> texture, D3D11_USAGE usage) :name{ name }, texture{ texture }, usage{ usage }
{

}

