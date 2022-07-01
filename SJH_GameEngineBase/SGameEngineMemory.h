#pragma once
#include <memory>

// 분류 : 메모리
// 용도 : 
// 설명 : 현재 프로그램의 사용되는 메모리를 복사하거나 초기화 시키는 등 관련 행동을 취하는 클래스
class SGameEngineMemory
{
    private: // Static Var

    public: // Static Func
        template<typename LEFT, typename RIGHT>
        static void Memcopy(LEFT& _Left, RIGHT& _Right)
        {
            memcpy_s(&_Left, sizeof(LEFT), &_Right, sizeof(RIGHT));
        }

        template<typename DATA>
        static void Memzero(DATA& _Data)
        {
            memset(&_Data, 0, sizeof(DATA));
        }

        template<typename DATA>
        static void Memset(DATA& _Data, int _SetValue, size_t _DataSize)
        {
            memset(&_Data, _SetValue, _DataSize);
        }

    private: // member Var

private: // constructer destructer
        SGameEngineMemory();
        ~SGameEngineMemory();

    public: // delete constructer 
        SGameEngineMemory(const SGameEngineMemory& _Other) = delete;
        SGameEngineMemory(const SGameEngineMemory&& _Other) = delete;

    public: // delete operator
        SGameEngineMemory& operator=(const SGameEngineMemory& _Other) = delete;
        SGameEngineMemory& operator=(const SGameEngineMemory&& _Other) = delete;

    public: // member Func

};

