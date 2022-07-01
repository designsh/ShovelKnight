#include "SGameEngineFile.h"

// Static Var

// Static Func

// member Var
SGameEngineFile::SGameEngineFile() : m_Handle(nullptr), m_FileSize(0), m_FilePointer(0)
{

}

SGameEngineFile::SGameEngineFile(const SGameEngineString& _Path) : SGameEnginePath(_Path), m_Handle(nullptr), m_FileSize(0), m_FilePointer(0)
{

}

SGameEngineFile::~SGameEngineFile()
{
	// 소멸시 파일 Close
	FileClose();
}

// member Func
bool SGameEngineFile::IsReadOpen()
{
	return  m_Mode.is_find(L"r");
}

bool SGameEngineFile::IsWriteOpen()
{
	return  m_Mode.is_find(L"w");
}

void SGameEngineFile::FileOpen(const wchar_t* _Mode)
{
	FileClose();

	// 모드 저장
	m_Mode = _Mode;

	_wfopen_s(&m_Handle, c_str(), m_Mode.c_str());
	if (nullptr == m_Handle)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}
	else
	{
		// 파일 크기저장
		fseek(m_Handle, 0, SEEK_END);
		m_FileSize = ftell(m_Handle);
		fseek(m_Handle, 0, SEEK_SET);
	}
}

void SGameEngineFile::FileClose()
{
	if (nullptr != m_Handle)
	{
		fclose(m_Handle);
		m_Handle = nullptr;
	}
}

void SGameEngineFile::Write(void* _Ptr, size_t _Size, size_t _Count)
{
#ifdef _DEBUG
	if (true == IsReadOpen())
	{
		SGameEngineDebug::AssertMsg(L"if (true == IsReadOpen())");
	}
#endif

	// m_Handle이 nullptr(0)이면 해당 프로그램을 터뜨린다.
	if (nullptr == m_Handle)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}
	else // nullptr(0)이 아니면 해당 파일에 Write
	{
		fwrite(_Ptr, _Size, _Count, m_Handle);
	}

	// Write완료 후 현재 커서위치 저장
	CurPostion();
}

void SGameEngineFile::Read(void* _Ptr, size_t _BufferSize, size_t _ReadSize, size_t _Count)
{
	fread_s(_Ptr, _BufferSize, _ReadSize, _Count, m_Handle);

	// Read완료 후 현재 커서위치 저장
	CurPostion();
}

// UNICODE(WIDE BYTE) FILE OPEN
void SGameEngineFile::UniCodeFileOpen(const wchar_t* _Mode)
{
	FileClose();

	// 모드 저장
	m_Mode = _Mode;
	m_Mode += L", ccs=UNICODE";

	_wfopen_s(&m_Handle, c_str(), m_Mode.c_str());
	if (nullptr == m_Handle)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}
	else
	{
		// 파일 크기 저장
		fseek(m_Handle, 0, SEEK_END);
		m_FileSize = ftell(m_Handle);
		fseek(m_Handle, 0, SEEK_SET);
	}
}

// 현재 사용자가 파일을 읽거나 쓰고 있는 바이트 위치를 알 수 있는 함수
size_t SGameEngineFile::CurPostion()
{
	if (nullptr == m_Handle)
	{
		return m_FilePointer;
	}

	// 현재 위치 파일 포인터 저장
	m_FilePointer = ftell(m_Handle);

	return m_FilePointer;
}

// 현재 파일의 총 크기를 저장한다.
size_t SGameEngineFile::FileTotalSize()
{
	if (nullptr == m_Handle)
	{
		return m_FileSize;
	}

	return m_FileSize;
}
