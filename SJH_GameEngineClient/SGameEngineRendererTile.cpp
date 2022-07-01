#include "SGameEngineRendererTile.h"
#include "SGameEngineResMgr.h"
#include <SGameEngineWindow.h>
#include <SGameEngineFile.h>

// Static Var

// Static Func

// member Var
SGameEngineRendererTile::SGameEngineRendererTile() 
    : m_Image(nullptr), m_MaxIndex(0), m_TileMaxY(0), m_TileMaxX(0), m_RenderIndex(FLOAT4::ZERO), m_CullActor(nullptr)
{

}

SGameEngineRendererTile::~SGameEngineRendererTile()
{

}

// member Func
void SGameEngineRendererTile::Render()
{
    // ������ �������� ������ ��� �׸���.
    if (nullptr == m_CullActor)
    {
        for (int y = 0; y < (int)m_TilMap.size(); y++)
        {
            for (int x = 0; x < (int)m_TilMap[y].size(); x++)
            {
                if (-1 == m_TilMap[y][x].m_ImageIndex)
                {
                    continue;
                }

                FLOAT4 TilePos = FLOAT4{ x * m_TileSize.ix(), y * m_TileSize.iy() };
                const CutData& Data = m_Image->GetCutData(m_TilMap[y][x].m_ImageIndex);
                FLOAT4 CamPos = GetActor()->GetScene()->GetCamPos();
                FLOAT4 RenderPos = GetActor()->GetPosition() + TilePos - CamPos;
                SGameEngineWindow::GetBackBufferImage().TransparentBlt(RenderPos, m_ImageScale, *m_Image, Data.m_Pos, Data.m_Size);
            }
        }
    }
    // ������ �������� ������ ������ �������� ���ϴ� ũ�⸸ŭ�� �׸���.
    // ��, Ÿ���ε����� �Ѿ�� �ʴ� ���������� �����ϴ�.
    else 
    {
        // �������� ��ġ������ �����´�.
        FLOAT4 TilePos = m_CullActor->GetScene()->GetCamPos();

        // Ÿ���� ũ��� Ÿ���� �ε����� ���Ѵ�.
        FLOAT4 TileIndex = { TilePos.ix() / m_TileSize.ix(), TilePos.iy() / m_TileSize.iy() };

        // �������� �߽����� ũ�⸦ ���Ѵ�.
        int XEnd = TileIndex.ix() + m_RenderIndex.ix();
        int YEnd = TileIndex.iy() + m_RenderIndex.iy();
        int XStart = TileIndex.ix();
        if (0 >= XStart)
        {
            XStart = 0;
        }
        int YStart = TileIndex.iy();
        if (0 >= YStart)
        {
            YStart = 0;
        }

        // �̶� Max ũ�⸦ �Ѿ�� Maxũ��� �ʱ�ȭ�Ѵ�.
        if (m_TileMaxX <= XEnd)
        {
            XEnd = m_TileMaxX;
        }
        if (m_TileMaxY <= YEnd)
        {
            YEnd = m_TileMaxY;
        }

        for (int y = YStart; y < YEnd; y++)
        {
            for (int x = XStart; x < XEnd; x++)
            {
                if (-1 == m_TilMap[y][x].m_ImageIndex)
                {
                    continue;
                }

                FLOAT4 TilePos = FLOAT4{ x * m_TileSize.ix(), y * m_TileSize.iy() };
                const CutData& Data = m_Image->GetCutData(m_TilMap[y][x].m_ImageIndex);
                FLOAT4 CamPos = GetActor()->GetScene()->GetCamPos();
                FLOAT4 RenderPos = GetActor()->GetPosition() + TilePos - CamPos;
                SGameEngineWindow::GetBackBufferImage().TransparentBlt(RenderPos, m_ImageScale, *m_Image, Data.m_Pos, Data.m_Size);
            }
        }
    }
}

void SGameEngineRendererTile::TileMapStart(const SGameEngineString& _TileMapImage, FLOAT4 _TileSize, FLOAT4 _ImageScale, int _SizeX, int _SizeY)
{
    m_TileSize = _TileSize;
    m_ImageScale = _ImageScale;
    m_MaxIndex = _SizeY * _SizeX;
    m_TileMaxX = _SizeX;
    m_TileMaxY = _SizeY;

    m_Image = SGameEngineResMgr::Inst().FindImage(_TileMapImage);
    if (nullptr == m_Image)
    {
        SGameEngineDebug::AssertMsg(L"f (nullptr == m_Image)");
        return;
    }

    m_TilMap.resize(_SizeY);
    for (int i = 0; i < (int)m_TilMap.size(); i++)
    {
        m_TilMap[i].resize(_SizeX);
    }

    for (int y = 0; y < (int)m_TilMap.size(); y++)
    {
        for (int x = 0; x < _SizeX; x++)
        {
            m_TilMap[y][x].m_ParentTile = this;
            m_TilMap[y][x].m_ImageIndex = -1;
        }
    }
}

void SGameEngineRendererTile::SetTile(const FLOAT4& _CheckPos, int _Index)
{
    //FLOAT4 TileIndex = FLOAT4{ _CheckPos.iy() / m_TileSize.iy(), _CheckPos.ix() / m_TileSize.ix() };
    FLOAT4 TileIndex = FLOAT4{ _CheckPos.ix() / m_TileSize.ix(), _CheckPos.iy() / m_TileSize.iy() };

    // ����ó��(_CheckPos�� ��ǥ�� ���̳ʽ� ���̸� ����)
    if (0 > _CheckPos.iy() || 0 > _CheckPos.ix())
    {
        SGameEngineDebug::AssertMsg(L"if (0 > _CheckPos.iy() || 0 > _CheckPos.ix())");
        return;
    }

    // ����ó��(�ε����� ���� Ÿ�ϸ� ���ε������� ũ�� ����)
    if (_Index >= m_MaxIndex)
    {
        SGameEngineDebug::AssertMsg(L"if (_Index >= m_MaxIndex)");
        return;
    }

    // ����ó��(�ε����� �Ѿ�Ƿ� ����)
    if (m_TileMaxY < TileIndex.iy() || m_TileMaxX < TileIndex.ix())
    {
        SGameEngineDebug::AssertMsg(L"if (m_TileMaxY < TileIndex.iy() || m_TileMaxX < TileIndex.ix())");
        return;
    }

    m_TilMap[TileIndex.iy()][TileIndex.ix()].m_ImageIndex = _Index;
}

void SGameEngineRendererTile::DelTile(const FLOAT4& _CheckPos)
{
    //FLOAT4 tTileIndex = { _CheckPos.iy() / m_TileSize.iy(), _CheckPos.ix() / m_TileSize.ix() };
    FLOAT4 tTileIndex = { _CheckPos.ix() / m_TileSize.ix(), _CheckPos.iy() / m_TileSize.iy() };

    m_TilMap[tTileIndex.iy()][tTileIndex.ix()].m_ImageIndex = -1;
}

void SGameEngineRendererTile::DelTileIndex(const FLOAT4& _CheckPos)
{
    m_TilMap[_CheckPos.iy()][_CheckPos.ix()].m_ImageIndex = -1;
}

int SGameEngineRendererTile::GetTileImageIndex(const FLOAT4& _CheckPos)
{
    return m_TilMap[_CheckPos.iy()][_CheckPos.ix()].m_ImageIndex;
}

FLOAT4 SGameEngineRendererTile::GetTileMaxIndex()
{
    return FLOAT4(m_TileMaxX, m_TileMaxY);
}

FLOAT4 SGameEngineRendererTile::GetCurIndexToPos(const FLOAT4& _CurIndex)
{
    FLOAT4 CurPos = FLOAT4{ _CurIndex.ix() * m_TileSize.ix(), _CurIndex.iy() * m_TileSize.iy() };

    return CurPos;
}

void SGameEngineRendererTile::SaveTile(const SGameEngineString& _pFilePath)
{
    SGameEngineFile _pFile;
    _pFile.m_wString = _pFilePath.m_wString;

    _pFile.FileOpen(L"wb");

    _pFile << m_TileMaxX;
    _pFile << m_TileMaxY;

    // Ÿ�ϸ� ����
    for (int y = 0; y < m_TileMaxY; y++)
    {
        for (int x = 0; x < m_TileMaxX; x++)
        {
            _pFile << m_TilMap[y][x];
        }
    }
}

void SGameEngineRendererTile::LoadTile(const SGameEngineString& _pFilePath)
{
    SGameEngineFile _pFile;
    _pFile.m_wString = _pFilePath.m_wString;

    // ���� ����
    _pFile.FileOpen(L"rb");

    // Ÿ�ϸ� �ѻ����� �б�
    _pFile >> m_TileMaxX;
    _pFile >> m_TileMaxY;

    // ���� ũ�� �ø���
    m_TilMap.resize(m_TileMaxY);
    for (int i = 0; i < m_TileMaxY; i++)
    {
        m_TilMap[i].resize(m_TileMaxX);
    }

    // Ÿ�ϸ� �ε�
    for (int y = 0; y < m_TileMaxY; y++)
    {
        for (int x = 0; x < m_TileMaxX; x++)
        {
            _pFile >> m_TilMap[y][x];
        }
    }
}

void SGameEngineRendererTile::SetCullActor(SGameEngineActor* _CullActor, FLOAT4 _Scale)
{
    m_CullActor = _CullActor;
    m_RenderIndex = _Scale;
}

