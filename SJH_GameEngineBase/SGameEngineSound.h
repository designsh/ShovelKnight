#pragma once
#include "fmod.hpp"
#include "SGameEngineDebug.h"
#include <map>

#ifdef DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

// �з� :
// �뵵 : 
// ���� : 
class SGameEngineString;
class SGameEngineSound
{
    public:
        class SGameEngineSoundPlayer
        {
            friend SGameEngineSound;

            private:
                FMOD::Channel* m_Channel;

            public:
                void Stop() // ����
                {
                    if (nullptr == m_Channel)
                    {
                        SGameEngineDebug::AssertMsg(L"if (nullptr == m_Channel)");
                    }

                    m_Channel->stop();
                }

                bool IsPlaying(bool _Playing) // ��������� üũ
                {
                    if (nullptr == m_Channel)
                    {
                        SGameEngineDebug::AssertMsg(L"if (nullptr == m_Channel)");
                    }

                    m_Channel->isPlaying(&_Playing);

                    return _Playing;
                }

            public:
                SGameEngineSoundPlayer() : m_Channel(nullptr)
                {

                }

            private:
                SGameEngineSoundPlayer(FMOD::Channel* _Channel)
                    : m_Channel(_Channel)
                {

                }
        };

    private:
        class StaticInst
        {
            friend SGameEngineSound;

            private:
                StaticInst();
                ~StaticInst();
        };

    private: // Static Var
        friend StaticInst;

        static FMOD::System* m_FmodSystem;
        static std::map<SGameEngineString, SGameEngineSound*> m_SoundMap;
        static std::map<SGameEngineString, FMOD::Channel*> m_SoundChannel;
        static StaticInst Inst;

    public: // Static Func
        static void Init();
        static void Update();
        static void Release();
        static void Load(const SGameEngineString& _Path);
        static SGameEngineSoundPlayer Play(const SGameEngineString& _Name);
        static SGameEngineSoundPlayer Play(const SGameEngineString& _Name, bool _Bgm, int _LoopCount);
        
    private: // member Var
        FMOD::Sound* m_Sound;

    public: // constructer destructer
        SGameEngineSound();
        ~SGameEngineSound();

    public: // delete constructer 
        SGameEngineSound(const SGameEngineSound& _Other) = delete;
        SGameEngineSound(const SGameEngineSound&& _Other) = delete;

    public: // delete operator
        SGameEngineSound& operator=(const SGameEngineSound& _Other) = delete;
        SGameEngineSound& operator=(const SGameEngineSound&& _Other) = delete;

    public: // member Func
        void Create(const SGameEngineString& _Path);
        FMOD::Channel* Play(); // ������ ���(�ݺ�����)
        FMOD::Channel* Play(const SGameEngineString& _Name, bool _StaticGubun, bool _Bgm, int _LoopCount = 1); // ���(�ݺ�����)



};

using SoundPlayer = SGameEngineSound::SGameEngineSoundPlayer;

