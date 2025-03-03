#pragma once
#include <Render/RendererManager.h>
#include <vector>
#include <Object/DataStructures.h>



class Object
{
public:
	Object(std::vector<Vertex> pArrayVertexData, std::vector<uint32_t>  indexData);
	~Object() = default;

	void SetProps();
	void SetPosition(XMFLOAT3 position) { mWorldData.Position = position; }
	void SetRotation(XMFLOAT3 rotation) { mWorldData.Rotation = rotation; }
	void SetScale(XMFLOAT3 scale) { mWorldData.Scale = scale; }

	void UpdateMatrix(XMMATRIX view, XMMATRIX projection);
	uint32_t GetIndexCount() const { return mIndexCount; }
private:
	ComPtr<ID3D11Buffer> mVertexBuffer;
	ComPtr<ID3D11Buffer> mIndexBuffer;
	uint32_t mIndexCount;

	ComPtr<ID3D11Buffer> mConstantBuffer;
	WorldData mWorldData;
	TransformData mTransformData;

};
	