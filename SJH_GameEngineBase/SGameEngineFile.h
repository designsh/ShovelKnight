#pragma once
#include "SGameEnginePath.h"
#include "SGameEngineDebug.h"
#include <map>
#include <iostream>

// 분류 : 파일입출력
// 용도 : 
// 설명 : 파일이 할 수 있는일을 모아놓은 클래스
class SGameEngineFile : public SGameEnginePath
{
private: // Static Var

public: // Static Func

public: // member Var
    FILE* m_Handle;
    SGameEngineString m_Mode;
    size_t m_FileSize;
    size_t m_FilePointer;

public: // constructer destructer
    SGameEngineFile();
    SGameEngineFile(const SGameEngineString& _Path);
    ~SGameEngineFile();

public: // delete constructer 
    SGameEngineFile(const SGameEngineFile& _Other) : SGameEnginePath(_Other), m_Handle(nullptr), m_FileSize(0), m_FilePointer(0)
    {

    }

    SGameEngineFile(const SGameEngineFile&& _Other) noexcept : SGameEnginePath(_Other), m_Handle(nullptr), m_FileSize(0), m_FilePointer(0)
    {

    }

public: // delete operator
    SGameEngineFile& operator=(const SGameEngineFile& _Other) = delete;
    SGameEngineFile& operator=(const SGameEngineFile&& _Other) = delete;

    // member Func
public: // Mode Check Function
    bool IsReadOpen();
    bool IsWriteOpen();

public: // File Open & File Close
    void FileOpen(const wchar_t* _Mode);
    void FileClose();

public: // File Write Function
    template<typename T>
    void operator << (T& _Value)
    {
        Write(&_Value, sizeof(_Value), 1);
    }

    template<>
    void operator << (SGameEngineString& _Value)
    {
        std::string Convert = _Value.wStringToString();

        int Size = (int)Convert.size();

        Write(&Size, sizeof(int), 1);
        Write((void*)Convert.c_str(), Size, 1);
    }

    // GameString을 받아오므로 class를 타입으로 설정
    template <typename FIRST, class SECOND>
    void operator << (std::map<FIRST, SECOND>& _MapData)
    {
        // Size 저장
        int MapDataTotalSize = (int)_MapData.size();
        operator<<(MapDataTotalSize);

        // iterator를 통해 맵(각 트리노드)에 접근하여 각각 Key와 Value 값을 저장
        typename std::map<FIRST, SECOND>::iterator StartPoint = _MapData.begin();
        typename std::map<FIRST, SECOND>::iterator EndPoint = _MapData.end();

        for (; StartPoint != EndPoint; ++StartPoint)
        {
            FIRST Key = StartPoint->first;
            SECOND Value = StartPoint->second;

            operator<<(Key);
            operator<<(Value);
        }
    }

    template<typename T>
    void WriteType(T& _Value, size_t _Count = 1)
    {
        Write(&_Value, sizeof(_Value), _Count);
    }

    void Write(void* _Ptr, size_t _Size, size_t _Count = 1);

public: // File Read Function
    template<typename T>
    void operator >> (T& _Value)
    {
        Read(&_Value, sizeof(_Value), sizeof(_Value), 1);
    }

    template<>
    void operator >> (SGameEngineString& _Value)
    {
        int Size = 0;

        Read(&Size, sizeof(int), sizeof(int), 1);
        if (0 >= Size)
        {
            SGameEngineDebug::AssertMsg(L"Read Size if (0 >= Size)");
        }

        std::string ReadBuffer;
        ReadBuffer.resize(Size);
        Read(&ReadBuffer[0], Size, Size, 1);
        _Value.SetConvertWideByte(ReadBuffer);
    }

    // GameString을 받아오므로 class를 타입으로 설정
    template <typename FIRST, class SECOND>
    void operator >> (std::map<FIRST, SECOND>& _MapData)
    {
        // Size 저장
        int MapDataTotalSize;
        operator>>(MapDataTotalSize);

        for (int i = 0; i < MapDataTotalSize; ++i)
        {
            FIRST Key;
            operator>>(Key);

            SECOND Value;
            operator>>(Value);

            // 래퍼런스로 인자를 받기 때문에 지역내에서 값을 변경하여 원본에 영향을 끼칠수 있다.
            _MapData.insert(std::map<FIRST, SECOND>::value_type(Key, Value));
        }
    }

    template<typename T>
    void ReadType(T& _Value, size_t _Count = 1)
    {
        Read(&_Value, sizeof(_Value), sizeof(_Value), _Count);
    }

    void Read(void* _Ptr, size_t _BufferSize, size_t _ReadSize, size_t _Count = 1);

    // UNICODE(Wide Byte File) File Open
public:
    void UniCodeFileOpen(const wchar_t* _Mode);

    // File의 현재 크기와 파일 포인터의 위치를 알아내는 함수
public:
    size_t CurPostion();
    size_t FileTotalSize();
};

