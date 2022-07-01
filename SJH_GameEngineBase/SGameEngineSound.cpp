#include "SGameEngineSound.h"
#include "SGameEngineDebug.h"
#include "SGameEngineString.h"
#include "SGameEnginePath.h"
#include <atlstr.h>

SGameEngineSound::StaticInst::StaticInst()
{
	SGameEngineSound::Init();
}

SGameEngineSound::StaticInst::~StaticInst()
{

}

// Static Var
FMOD::System* SGameEngineSound::m_FmodSystem = nullptr;
SGameEngineSound::StaticInst SGameEngineSound::Inst;
std::map<SGameEngineString, SGameEngineSound*> SGameEngineSound::m_SoundMap;
std::map<SGameEngineString, FMOD::Channel*> SGameEngineSound::m_SoundChannel;

// Static Func
void SGameEngineSound::Release()
{
	std::map<SGameEngineString, SGameEngineSound*>::iterator SoundMapStart = m_SoundMap.begin();
	std::map<SGameEngineString, SGameEngineSound*>::iterator SoundMapEnd = m_SoundMap.end();
	for (; SoundMapStart != SoundMapEnd; ++SoundMapStart)
	{
		delete SoundMapStart->second;
	}
	m_SoundMap.clear();

	m_FmodSystem->release();
	m_FmodSystem->close();
}

// member Var
SGameEngineSound::SGameEngineSound() : m_Sound(nullptr)
{

}

SGameEngineSound::~SGameEngineSound()
{
	// 소멸시 핸들 반납
	if (nullptr != m_Sound)
	{
		m_Sound->release();
		m_Sound = nullptr;
	}
}

// member Func
void SGameEngineSound::Init()
{
	FMOD::System_Create(&m_FmodSystem);

	if (nullptr == m_FmodSystem)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_FmodSystem)");
	}

	if (FMOD_OK != m_FmodSystem->init(32, FMOD_DEFAULT, nullptr))
	{
		SGameEngineDebug::AssertMsg(L"if (FMOD_OK != m_FmodSystem->init(32, FMOD_DEFAULT, nullptr))");
	}
}

void SGameEngineSound::Load(const SGameEngineString& _Path)
{
	SGameEngineSound* NewSound = new SGameEngineSound();
	NewSound->Create(_Path);

	SGameEngineString FileName = SGameEnginePath::IOName(_Path);

	// map 정상적으로 Insert했을경우
	// map은 std::map<iterator, bool>을 반환한다.
	std::pair<std::map<SGameEngineString, SGameEngineSound*>::iterator, bool> Result =
		m_SoundMap.insert(std::map<SGameEngineString, SGameEngineSound*>::value_type(FileName, NewSound));

	if (false == Result.second)
	{
		SGameEngineDebug::AssertMsg(L"if (false == Result.second)");
	}
}

void SGameEngineSound::Update()
{
	// 사운드가 정지하거나 끝난것을 알기위해
	// 현재 함수 실행필요
	if (nullptr != m_FmodSystem)
	{
		m_FmodSystem->update();
	}
}

SGameEngineSound::SGameEngineSoundPlayer SGameEngineSound::Play(const SGameEngineString& _Name)
{
	if (m_SoundMap.end() == m_SoundMap.find(_Name))
	{
		SGameEngineDebug::AssertMsg(L"if (m_SoundMap.end() == m_SoundMap.find(_Name))");
	}

	return m_SoundMap[_Name]->Play();
}

SGameEngineSound::SGameEngineSoundPlayer SGameEngineSound::Play(const SGameEngineString& _Name, bool _Bgm, int _LoopCount)
{
	if (m_SoundMap.end() == m_SoundMap.find(_Name))
	{
		SGameEngineDebug::AssertMsg(L"if (m_SoundMap.end() == m_SoundMap.find(_Name))");
	}

	return m_SoundMap[_Name]->Play(_Name, false, _Bgm, _LoopCount);
}

void SGameEngineSound::Create(const SGameEngineString& _Path)
{
	std::string Path = _Path.wStringToString(CP_UTF8);

	if (FMOD_OK != m_FmodSystem->createSound(Path.c_str(), FMOD_DEFAULT, nullptr, &m_Sound))
	{
		SGameEngineDebug::AssertMsg(L"if (FMOD_OK != m_FmodSystem->createSound(Path.c_str(), FMOD_DEFAULT, nullptr, &m_Sound))");
	}
}

FMOD::Channel* SGameEngineSound::Play()
{
	FMOD::Channel* ReturnCh = nullptr;

	if (FMOD_OK != m_FmodSystem->playSound(m_Sound, nullptr, false, &ReturnCh))
	{
		SGameEngineDebug::AssertMsg(L"if (FMOD_OK != m_FmodSystem->playSound(m_Sound, nullptr, false, &ReturnCh))");
	}

	return ReturnCh;
}

FMOD::Channel* SGameEngineSound::Play(const SGameEngineString& _Name, bool _StaticGubun, bool _Bgm, int _LoopCount)
{
	FMOD::Channel* ReturnChannel = nullptr;

	if (true == _Bgm) // 배경음악인 경우
	{
		if (m_SoundChannel.end() == m_SoundChannel.find(_Name)) // 없는 경우 생성
		{
			if (FMOD_OK != m_FmodSystem->playSound(m_Sound, nullptr, false, &ReturnChannel))
			{
				SGameEngineDebug::AssertMsg(L"FMOD_OK != m_pFmodSystem->playSound(m_pSound, nullptr, false, nullptr)");
			}

			ReturnChannel->setMode(FMOD_LOOP_NORMAL);
			if (FMOD_OK != ReturnChannel->setLoopCount(_LoopCount))
			{
			}

			std::pair<std::map<SGameEngineString, FMOD::Channel*>::iterator, bool> Result =
				m_SoundChannel.insert(std::map<SGameEngineString, FMOD::Channel*>::value_type(_Name, ReturnChannel));

			return ReturnChannel;
		}
		else // 있으면 재생중인지 체크
		{
			bool IsPlaying = false;
			m_SoundChannel[_Name]->isPlaying(&IsPlaying);
			if (true == IsPlaying) // 재생중이면 루프 시작안함
			{
				return nullptr;
			}
			else
			{
				m_FmodSystem->playSound(m_Sound, nullptr, false, &m_SoundChannel[_Name]);
			}

			return nullptr;
		}
	}
	else // 효과음인 경우(루프하지않음)
	{
		if (FMOD_OK != m_FmodSystem->playSound(m_Sound, nullptr, false, &ReturnChannel))
		{
			SGameEngineDebug::AssertMsg(L"FMOD_OK != m_pFmodSystem->playSound(m_pSound, nullptr, false, nullptr)");
		}

		ReturnChannel->setMode(FMOD_LOOP_NORMAL);
		if (FMOD_OK != ReturnChannel->setLoopCount(_LoopCount))
		{
		}

		return ReturnChannel;
	}

	return ReturnChannel;
}
