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

	// #include <atlstr.h> 선언 필요
	// A(Ansi), T(Unicode)
	// ANSI : 멀티바이트
	// UNICODE : 와이드바이트
	// ANSI => UNICODE : CA2CT([ANSI 문자열])
	// UNICODE => ANSI : CT2CA([UNICODE 문자열])
	// c_str() : m_wString의 내부버퍼의 시작주소 반환
	String = CT2CA(m_wString.c_str(), _encoding);

	return String;
}

// _String을 std::wstring로 변환
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

// 특정문자에 따라 문자열을 잘라내어 Vector에 저장 후 반환 
std::vector<SGameEngineString> SGameEngineString::StringCutVector(const char* _SpecificChar)
{
	// string형을 wstring으로 변환하여 저장
	std::wstring wString = StringTowString(_SpecificChar);

	// 이전 인덱스
	size_t PrevIndex = 0;

	// 현재 인덱스
	size_t Index = 0;

	// 반환할 벡터생성
	std::vector<SGameEngineString> ReturnVector;

	// 해당 문자열에서 특정문자를 찾아낸뒤
	// 해당 인덱스 전까지의 문자열을 SubwString에 저장후
	// SubwString를 ReturnVector에 저장하여 반환
	// std::wstring::npos -> 찾는문자열이 없으면 std::npos 반환
	while (Index != std::wstring::npos)
	{
		Index = m_wString.find(wString, PrevIndex);
		std::wstring SubwString = m_wString.substr(PrevIndex, Index - PrevIndex);
		ReturnVector.push_back(SubwString);
		PrevIndex = Index + strlen(_SpecificChar);
	}

	// 생성된 벡터 반환
	return ReturnVector;
}

// 특정문자에 따라 문자열을 잘라내어 List에 저장 후 반환 
std::list<SGameEngineString> SGameEngineString::StringCutList(const char* _SpecificChar)
{
	// string형을 wstring으로 변환하여 저장
	std::wstring wString = StringTowString(_SpecificChar);

	// 이전 인덱스
	size_t PrevIndex = 0;

	// 현재 인덱스
	size_t Index = 0;

	// 반환할 리스트생성
	std::list<SGameEngineString> ReturnList;

	// 해당 문자열에서 특정문자를 찾아낸뒤
	// 해당 인덱스 전까지의 문자열을 SubwString에 저장후
	// SubwString를 ReturnList에 저장하여 반환
	while (Index != std::wstring::npos)
	{
		Index = m_wString.find(wString, PrevIndex);
		std::wstring SubwString = m_wString.substr(PrevIndex, Index - PrevIndex);
		ReturnList.push_back(SubwString);
		PrevIndex = Index + strlen(_SpecificChar);
	}

	return ReturnList;
}

// 특정문자에서부터 특정문자까지 사이의 문자열을 잘라내어 Vector에 저장하여 반환
std::vector<SGameEngineString> SGameEngineString::StringCenterCutVector(const char* _StartChar, const char* _EndChar)
{
	std::wstring wStringStart = StringTowString(_StartChar);
	std::wstring wStringEnd = StringTowString(_EndChar);

	// 반환할 벡터 생성
	std::vector<SGameEngineString> ReturnVector;

	// 이전 인덱스
	size_t PrevSIndex = 0;
	size_t PrevEIndex = 0;

	// 현재 인덱스
	size_t StartIndex = 0;
	size_t EndIndex = 0;

	// 현재 문자열 길이 Get
	size_t CurwStrSize = m_wString.size();

	// 해당 문자열에서 특정문자에서 특정문자사이의
	// 문자열을 가져와서
	// SubwString에 저장후
	// SubwString을 ReturnVector에 push_back한뒤
	// ReturnVector를 반환해준다.
	while (EndIndex < (CurwStrSize - 1))
	{
		// 특정문자를 못찾으면 std::wstring::npos 반환
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

// 특정문자에서부터 특정문자까지 사이의 문자열을 잘라내어 List에 저장하여 반환
std::list<SGameEngineString> SGameEngineString::StringCenterCutList(const char* _StartChar, const char* _EndChar)
{
	std::wstring wStringStart = StringTowString(_StartChar);
	std::wstring wStringEnd = StringTowString(_EndChar);

	// 이전 인덱스
	size_t PrevSIndex = 0;
	size_t PrevEIndex = 0;

	// 현재 인덱스
	size_t StartIndex = 0;
	size_t EndIndex = 0;

	// 반환할 리스트 생성
	std::list<SGameEngineString> ReturnList;

	// 현재 문자열 길이 Get
	size_t CurwStrSize = m_wString.size();

	// 해당 문자열에서 특정문자에서 특정문자사이의
	// 문자열을 가져와서
	// SubwString에 저장후
	// SubwString을 ReturnList에 push_back한뒤
	// ReturnList를 반환해준다.
	while (EndIndex < (CurwStrSize - 1))
	{
		// 특정문자를 못찾으면 std::wstring::npos 반환
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
	// EraseFirst()가 실패할때까지 반복
	while (EraseFirst(_wString));
}



