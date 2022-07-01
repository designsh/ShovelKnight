#pragma once
#include <list>
#include <vector>
#include <atlstr.h>
#include <string>
#include <iostream>

// �з� : ���ڿ�
// �뵵 : 
// ���� : 
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

    // �ش� ���ڿ� ã���� True, �ƴϸ� False ��ȯ
    bool is_find(const wchar_t* _Text, size_t _StartIndex = 0);

    // ���ڿ��� ù��° �ε������� Ž���Ͽ� _Text�� ã�Ƴ��� ���° �ε������� ��ȯ
    size_t find_first_index(const wchar_t* _Text, size_t _StartIndex = 0);

    // ���ڿ��� ������ �ε������� Ž���Ͽ� _Text�� ã�Ƴ��� ���° �ε������� ��ȯ
    size_t find_last_index(const wchar_t* _Text, size_t _EndIndex = -1) const;

    // _StartIndex���� _Count �ڸ�����ŭ�� ���ڿ��� ��ȯ
    SGameEngineString Cut(size_t _StartIndex, size_t _Count);

    // _StartIndex���� _EndIndex������ ���ڿ��� ��ȯ
    SGameEngineString CutIndex(size_t _StartIndex, size_t _EndIndex) const;

    // Ư�����ڿ� ���� ���ڿ��� �߶󳻾� Vector�� ���� �� ��ȯ 
    std::vector<SGameEngineString> StringCutVector(const char* _SpecificChar);

    // Ư�����ڿ� ���� ���ڿ��� �߶󳻾� List�� ���� �� ��ȯ 
    std::list<SGameEngineString> StringCutList(const char* _SpecificChar);

    // Ư�����ڿ������� Ư�����ڱ��� ������ ���ڿ��� �߶󳻾� Vector�� �����Ͽ� ��ȯ
    std::vector<SGameEngineString> StringCenterCutVector(const char* _StartChar, const char* _EndChar);

    // Ư�����ڿ������� Ư�����ڱ��� ������ ���ڿ��� �߶󳻾� List�� �����Ͽ� ��ȯ
    std::list<SGameEngineString> StringCenterCutList(const char* _StartChar, const char* _EndChar);

    // Ư�����ڸ� ã�Ƽ� ����� �Լ�
    bool EraseFirst(const SGameEngineString& _wString);
    bool EraseLast(const SGameEngineString& _wString);
    void EraseAll(const SGameEngineString& _wString);
};

