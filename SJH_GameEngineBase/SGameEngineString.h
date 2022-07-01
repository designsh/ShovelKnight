#pragma once
#include <list>
#include <vector>
#include <atlstr.h>
#include <string>
#include <iostream>

// 분류 : 문자열
// 용도 : 
// 설명 : 
class SGameEngineString
{
private: // Static Var

public: // Static Func
    template <typename Type>
    static SGameEngineString ToString(const Type& _Data)
    {
        SGameEngineString String;
        String += SGameEngineString(std::to_wstring(_Data));
        return String;
    }

public: // member Var
    std::wstring m_wString;

public: // constructer destructer
    SGameEngineString();
    SGameEngineString(const wchar_t* _pString);
    SGameEngineString(const std::wstring& _String);
    ~SGameEngineString();

public: // delete constructer 
    SGameEngineString(const SGameEngineString& _Other) : m_wString(_Other.m_wString)
    {

    }

    SGameEngineString(const SGameEngineString&& _Other) noexcept : m_wString(_Other.m_wString)
    {

    }

    SGameEngineString(int _Other) noexcept : m_wString()
    {
        *this = ToString(_Other);
    }

public: // delete operator
    SGameEngineString& operator=(const SGameEngineString& _Other)
    {
        m_wString = _Other.m_wString;

        return *this;
    }

    SGameEngineString& operator=(const SGameEngineString&& _Other) noexcept
    {
        m_wString = _Other.m_wString;

        return *this;
    }

    SGameEngineString& operator=(int _Value)
    {
        m_wString = std::to_wstring(_Value);

        return *this;
    }

    SGameEngineString operator+(const SGameEngineString& _Other) const
    {
        std::wstring wString = m_wString;
        wString += _Other.m_wString;
        return wString;
    }

    SGameEngineString& operator+=(const SGameEngineString& _Other)
    {
        m_wString += _Other.m_wString;
        return *this;
    }

    bool operator!=(const SGameEngineString& _Other) const
    {
        return m_wString != _Other.m_wString;
    }

    bool operator==(const SGameEngineString& _Other) const
    {
        return m_wString == _Other.m_wString;
    }

    bool operator>(const SGameEngineString& _Other) const
    {
        return m_wString > _Other.m_wString;
    }

    bool operator<(const SGameEngineString& _Other) const
    {
        return m_wString < _Other.m_wString;
    }

    wchar_t& operator[](size_t _Index)
    {
        return m_wString[_Index];
    }

    size_t size() const
    {
        return m_wString.size();
    }

    void resize(size_t _Size)
    {
        return m_wString.resize(_Size);
    }

    void reserve(size_t _Size)
    {
        return m_wString.reserve(_Size);
    }

    const wchar_t* c_str() const
    {
        return m_wString.c_str();
    }

public: // member Func
    std::string wStringToString(int _encoding = CP_ACP) const;
    std::wstring StringTowString(std::string _String);
    void SetConvertWideByte(const std::string& _String);

    // 해당 문자열 찾으면 True, 아니면 False 반환
    bool is_find(const wchar_t* _Text, size_t _StartIndex = 0);

    // 문자열의 첫번째 인덱스부터 탐색하여 _Text를 찾아내어 몇번째 인덱스인지 반환
    size_t find_first_index(const wchar_t* _Text, size_t _StartIndex = 0);

    // 문자열의 마지막 인덱스부터 탐색하여 _Text를 찾아내어 몇번째 인덱스인지 반환
    size_t find_last_index(const wchar_t* _Text, size_t _EndIndex = -1) const;

    // _StartIndex부터 _Count 자리수만큼의 문자열을 반환
    SGameEngineString Cut(size_t _StartIndex, size_t _Count);

    // _StartIndex부터 _EndIndex까지의 문자열을 반환
    SGameEngineString CutIndex(size_t _StartIndex, size_t _EndIndex) const;

    // 특정문자에 따라 문자열을 잘라내어 Vector에 저장 후 반환 
    std::vector<SGameEngineString> StringCutVector(const char* _SpecificChar);

    // 특정문자에 따라 문자열을 잘라내어 List에 저장 후 반환 
    std::list<SGameEngineString> StringCutList(const char* _SpecificChar);

    // 특정문자에서부터 특정문자까지 사이의 문자열을 잘라내어 Vector에 저장하여 반환
    std::vector<SGameEngineString> StringCenterCutVector(const char* _StartChar, const char* _EndChar);

    // 특정문자에서부터 특정문자까지 사이의 문자열을 잘라내어 List에 저장하여 반환
    std::list<SGameEngineString> StringCenterCutList(const char* _StartChar, const char* _EndChar);

    // 특정문자를 찾아서 지우는 함수
    bool EraseFirst(const SGameEngineString& _wString);
    bool EraseLast(const SGameEngineString& _wString);
    void EraseAll(const SGameEngineString& _wString);
};

