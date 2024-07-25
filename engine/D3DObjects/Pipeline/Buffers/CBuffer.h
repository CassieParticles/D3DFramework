#pragma once

#include <wrl.h>
#include <string>
#include <d3d11.h>

struct CBufferBinding
{
	int BufferID;
	int StagesBound;
	int cRegister;
};

class CBuffer
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	CBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer, bool dynamic);
	~CBuffer() = default;

	void addBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer, bool dynamic);

	void bindBuffer(int stagesBoundTo, unsigned int sRegister);

	//TODO: Store size of data
	void updateCBuffer(void* data,int size);

	//TODO: Add better way of writing to constant buffer
	ComPtr<ID3D11Buffer>& getBuffer() { return buffer; }
	const std::string& getName() { return name; }
protected:
	std::string name;
	ComPtr<ID3D11Buffer> buffer;

	bool dynamic;
};