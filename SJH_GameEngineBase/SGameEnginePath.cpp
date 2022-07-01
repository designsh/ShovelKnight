#include "SGameEnginePath.h"

// Static Var

// Static Func
bool SGameEnginePath::IsExist(const SGameEngineString& _Path)
{
	return 0 == _waccess(_Path.c_str(), 00);
}

SGameEngineString SGameEnginePath::IOName(const SGameEngineString& _Path)
{
	//m_Path = m_Path.CutIndex(0, m_Path.find_last_index(L"\\", m_Path.size() - 2));
	SGameEngineString ReturnName = _Path.CutIndex(_Path.find_last_index(L"\\", _Path.size() - 2), _Path.size());
	ReturnName.EraseAll(L"\\");
	return ReturnName;
}

// member Var
SGameEnginePath::SGameEnginePath()
{

}

SGameEnginePath::SGameEnginePath(const SGameEngineString& _Path) : SGameEngineString(_Path)
{

}

SGameEnginePath::~SGameEnginePath()
{

}

// member Func
SGameEngineString SGameEnginePath::IOName()
{
	return IOName(*this);
}

bool SGameEnginePath::IsExist()
{
	return IsExist(m_wString.c_str());
}

SGameEngineString SGameEnginePath::GetPath()
{
	return *this;
}
