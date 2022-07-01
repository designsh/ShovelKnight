#include "SGameEngineResMgr.h"
#include <SGameEnginePath.h>
#include <SGameEngineDebug.h>

// Static Var

// Static Func
SGameEngineResMgr& SGameEngineResMgr::Inst()
{
	static SGameEngineResMgr SingleInst;
	return SingleInst;
}

// member Var
SGameEngineResMgr::SGameEngineResMgr()
{

}

SGameEngineResMgr::~SGameEngineResMgr()
{
	Release();
}

// member Func
void SGameEngineResMgr::ImageLoad(const SGameEngineString& _Path)
{
	SGameEngineString FileName = SGameEnginePath::IOName(_Path);
	if (nullptr != FindImage(FileName))
	{
		SGameEngineDebug::AssertMsg(L"	if (nullptr != FindImage(FileName))");
		return;
	}

	SGameEngineWinImage* NewImage = new SGameEngineWinImage();
	NewImage->ImageLoad(_Path);
	m_Image.insert(std::map<SGameEngineString, SGameEngineWinImage*>::value_type(FileName, NewImage));
}

SGameEngineWinImage* SGameEngineResMgr::FindImage(const SGameEngineString& _Name)
{
	if (m_Image.end() == m_Image.find(_Name))
	{
		return nullptr;
	}

	// ���ͷ����Ͱ� �ش� ��带 ã�Ƴ��� Second���� ��ȯ�ϴ� �ڵ�
	return m_Image[_Name];
}

void SGameEngineResMgr::Release()
{
	std::map<SGameEngineString, SGameEngineWinImage*>::iterator StartPoint = m_Image.begin();
	std::map<SGameEngineString, SGameEngineWinImage*>::iterator EndPoint = m_Image.end();
	for (; StartPoint != EndPoint; ++StartPoint)
	{
		if (nullptr != StartPoint->second)
		{
			delete StartPoint->second;
			StartPoint->second = nullptr;
		}
	}

	m_Image.clear();
}