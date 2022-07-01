#include "SGameEngineString.h"

// Static Var

// Static Func

// member Var
SGameEngineString::SGameEngineString()
{

}

SGameEngineString::SGameEngineString(const wchar_t* _pString) : m_wString(_pString)
{

}

SGameEngineString::SGameEngineString(const std::wstring& _String) : m_wString(_String)
{

}

SGameEngineString::~SGameEngineString()
{

}

// member Func
std::string SGameEngineString::wStringToString(int _encoding) const
{
	std::string String = "";

	// #include <atlstr.h> ���� �ʿ�
	// A(Ansi), T(Unicode)
	// ANSI : ��Ƽ����Ʈ
	// UNICODE : ���̵����Ʈ
	// ANSI => UNICODE : CA2CT([ANSI ���ڿ�])
	// UNICODE => ANSI : CT2CA([UNICODE ���ڿ�])
	// c_str() : m_wString�� ���ι����� �����ּ� ��ȯ
	String = CT2CA(m_wString.c_str(), _encoding);

	return String;
}

// _String�� std::wstring�� ��ȯ
std::wstring SGameEngineString::StringTowString(std::string _String)
{
	std::wstring wString = L"";

	wString = CA2CT(_String.c_str());

	return wString;
}

void SGameEngineString::SetConvertWideByte(const std::string& _String)
{
	m_wString = CA2CT(_String.c_str());
}

bool SGameEngineString::is_find(const wchar_t* _Text, size_t _StartIndex)
{
	return std::wstring::npos != m_wString.find(_Text, _StartIndex);
}

size_t SGameEngineString::find_first_index(const wchar_t* _Text, size_t _StartIndex)
{
	return m_wString.find(_Text, _StartIndex);
}

size_t SGameEngineString::find_last_index(const wchar_t* _Text, size_t _EndIndex) const
{
	return m_wString.rfind(_Text, _EndIndex);
}

SGameEngineString SGameEngineString::Cut(size_t _StartIndex, size_t _Count)
{
	return m_wString.substr(_StartIndex, _Count);
}

SGameEngineString SGameEngineString::CutIndex(size_t _StartIndex, size_t _EndIndex) const
{
	return m_wString.substr(_StartIndex, _EndIndex - _StartIndex + 1);
}

// Ư�����ڿ� ���� ���ڿ��� �߶󳻾� Vector�� ���� �� ��ȯ 
std::vector<SGameEngineString> SGameEngineString::StringCutVector(const char* _SpecificChar)
{
	// string���� wstring���� ��ȯ�Ͽ� ����
	std::wstring wString = StringTowString(_SpecificChar);

	// ���� �ε���
	size_t PrevIndex = 0;

	// ���� �ε���
	size_t Index = 0;

	// ��ȯ�� ���ͻ���
	std::vector<SGameEngineString> ReturnVector;

	// �ش� ���ڿ����� Ư�����ڸ� ã�Ƴ���
	// �ش� �ε��� �������� ���ڿ��� SubwString�� ������
	// SubwString�� ReturnVector�� �����Ͽ� ��ȯ
	// std::wstring::npos -> ã�¹��ڿ��� ������ std::npos ��ȯ
	while (Index != std::wstring::npos)
	{
		Index = m_wString.find(wString, PrevIndex);
		std::wstring SubwString = m_wString.substr(PrevIndex, Index - PrevIndex);
		ReturnVector.push_back(SubwString);
		PrevIndex = Index + strlen(_SpecificChar);
	}

	// ������ ���� ��ȯ
	return ReturnVector;
}

// Ư�����ڿ� ���� ���ڿ��� �߶󳻾� List�� ���� �� ��ȯ 
std::list<SGameEngineString> SGameEngineString::StringCutList(const char* _SpecificChar)
{
	// string���� wstring���� ��ȯ�Ͽ� ����
	std::wstring wString = StringTowString(_SpecificChar);

	// ���� �ε���
	size_t PrevIndex = 0;

	// ���� �ε���
	size_t Index = 0;

	// ��ȯ�� ����Ʈ����
	std::list<SGameEngineString> ReturnList;

	// �ش� ���ڿ����� Ư�����ڸ� ã�Ƴ���
	// �ش� �ε��� �������� ���ڿ��� SubwString�� ������
	// SubwString�� ReturnList�� �����Ͽ� ��ȯ
	while (Index != std::wstring::npos)
	{
		Index = m_wString.find(wString, PrevIndex);
		std::wstring SubwString = m_wString.substr(PrevIndex, Index - PrevIndex);
		ReturnList.push_back(SubwString);
		PrevIndex = Index + strlen(_SpecificChar);
	}

	return ReturnList;
}

// Ư�����ڿ������� Ư�����ڱ��� ������ ���ڿ��� �߶󳻾� Vector�� �����Ͽ� ��ȯ
std::vector<SGameEngineString> SGameEngineString::StringCenterCutVector(const char* _StartChar, const char* _EndChar)
{
	std::wstring wStringStart = StringTowString(_StartChar);
	std::wstring wStringEnd = StringTowString(_EndChar);

	// ��ȯ�� ���� ����
	std::vector<SGameEngineString> ReturnVector;

	// ���� �ε���
	size_t PrevSIndex = 0;
	size_t PrevEIndex = 0;

	// ���� �ε���
	size_t StartIndex = 0;
	size_t EndIndex = 0;

	// ���� ���ڿ� ���� Get
	size_t CurwStrSize = m_wString.size();

	// �ش� ���ڿ����� Ư�����ڿ��� Ư�����ڻ�����
	// ���ڿ��� �����ͼ�
	// SubwString�� ������
	// SubwString�� ReturnVector�� push_back�ѵ�
	// ReturnVector�� ��ȯ���ش�.
	while (EndIndex < (CurwStrSize - 1))
	{
		// Ư�����ڸ� ��ã���� std::wstring::npos ��ȯ
		StartIndex = m_wString.find(wStringStart, PrevSIndex);
		EndIndex = m_wString.find(wStringEnd, PrevEIndex);

		if (EndIndex == std::wstring::npos || StartIndex == std::wstring::npos)
		{
			break;
		}

		std::wstring SubwString = m_wString.substr(StartIndex + strlen(_StartChar), (EndIndex - strlen(_EndChar) - PrevEIndex));
		ReturnVector.push_back(SubwString);
		PrevSIndex = StartIndex + strlen(_StartChar);
		PrevEIndex = EndIndex + strlen(_EndChar);
	}

	return ReturnVector;
}

// Ư�����ڿ������� Ư�����ڱ��� ������ ���ڿ��� �߶󳻾� List�� �����Ͽ� ��ȯ
std::list<SGameEngineString> SGameEngineString::StringCenterCutList(const char* _StartChar, const char* _EndChar)
{
	std::wstring wStringStart = StringTowString(_StartChar);
	std::wstring wStringEnd = StringTowString(_EndChar);

	// ���� �ε���
	size_t PrevSIndex = 0;
	size_t PrevEIndex = 0;

	// ���� �ε���
	size_t StartIndex = 0;
	size_t EndIndex = 0;

	// ��ȯ�� ����Ʈ ����
	std::list<SGameEngineString> ReturnList;

	// ���� ���ڿ� ���� Get
	size_t CurwStrSize = m_wString.size();

	// �ش� ���ڿ����� Ư�����ڿ��� Ư�����ڻ�����
	// ���ڿ��� �����ͼ�
	// SubwString�� ������
	// SubwString�� ReturnList�� push_back�ѵ�
	// ReturnList�� ��ȯ���ش�.
	while (EndIndex < (CurwStrSize - 1))
	{
		// Ư�����ڸ� ��ã���� std::wstring::npos ��ȯ
		StartIndex = m_wString.find(wStringStart, PrevSIndex);
		EndIndex = m_wString.find(wStringEnd, PrevEIndex);

		if (EndIndex == std::wstring::npos || StartIndex == std::wstring::npos)
		{
			break;
		}

		std::wstring SubwString = m_wString.substr(StartIndex + strlen(_StartChar), (EndIndex - strlen(_EndChar) - PrevEIndex));
		ReturnList.push_back(SubwString);
		PrevSIndex = StartIndex + strlen(_StartChar);
		PrevEIndex = EndIndex + strlen(_EndChar);
	}

	return ReturnList;
}

// 
bool SGameEngineString::EraseFirst(const SGameEngineString& _wString)
{
	size_t Index = find_first_index(_wString.c_str());

	if (Index == std::wstring::npos)
	{
		return false;
	}

	m_wString.erase(Index, _wString.size());

	return true;
}

bool SGameEngineString::EraseLast(const SGameEngineString& _wString)
{
	size_t Index = find_last_index(_wString.c_str());

	if (Index == std::wstring::npos)
	{
		return false;
	}

	m_wString.erase(Index, _wString.size());

	return true;
}

void SGameEngineString::EraseAll(const SGameEngineString& _wString)
{
	// EraseFirst()�� �����Ҷ����� �ݺ�
	while (EraseFirst(_wString));
}



