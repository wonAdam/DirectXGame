#include "Triangle.h"
#include "DXInclude.h"
#include "Camera.h"

Triangle::Triangle(Vector3 position, Vector3 rotation, Vector3 v1, Vector3 v2, Vector3 v3, Color color)
    : GameObject(position, rotation), _v1(v1), _v2(v2), _v3(v3), _color(color)
{
    // 정점 버퍼를 생성합니다 
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(VERTEX) * 3;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    dev->CreateBuffer(&bd, NULL, &pVBuffer);

    // create a triangle using the VERTEX struct
    VERTEX vertexs[] =
    {
        {v1.x, v1.y, v1.z, D3DXCOLOR(color.r, color.g, color.b, color.a)},
        {v2.x, v2.y, v2.z, D3DXCOLOR(color.r, color.g, color.b, color.a)},
        {v3.x, v3.y, v3.z, D3DXCOLOR(color.r, color.g, color.b, color.a)}
    };

    // 정점을 버퍼 
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); // 버퍼를 매핑합니다 
    memcpy(ms.pData, vertexs, sizeof(vertexs)); // 데이터를 복사합니다 
    devcon->Unmap(pVBuffer, NULL);

}

void Triangle::RenderTick()
{
    D3DXMATRIX matTranslate;
    D3DXMatrixTranslation(&matTranslate, _position.x, _position.y, _position.z);

    D3DXMATRIX matRotate;
    D3DXMatrixRotationYawPitchRoll(&matRotate, _rotation.y, _rotation.x, _rotation.z);

    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    matFinal = matRotate * matTranslate * Camera::Get().GetView() * Camera::Get().GetProjection();
    devcon->UpdateSubresource(pCBuffer, 0, 0, &matFinal, 0, 0);

    devcon->Draw(3, 0);
}
