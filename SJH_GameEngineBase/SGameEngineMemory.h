#pragma once
#include <memory>

// �з� : �޸�
// �뵵 : 
// ���� : ���� ���α׷��� ���Ǵ� �޸𸮸� �����ϰų� �ʱ�ȭ ��Ű�� �� ���� �ൿ�� ���ϴ� Ŭ����
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

