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
	// �Ҹ�� ���� Close
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

	// ��� ����
	m_Mode = _Mode;

	_wfopen_s(&m_Handle, c_str(), m_Mode.c_str());
	if (nullptr == m_Handle)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}
	else
	{
		// ���� ũ������
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

	// m_Handle�� nullptr(0)�̸� �ش� ���α׷��� �Ͷ߸���.
	if (nullptr == m_Handle)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}
	else // nullptr(0)�� �ƴϸ� �ش� ���Ͽ� Write
	{
		fwrite(_Ptr, _Size, _Count, m_Handle);
	}

	// Write�Ϸ� �� ���� Ŀ����ġ ����
	CurPostion();
}

void SGameEngineFile::Read(void* _Ptr, size_t _BufferSize, size_t _ReadSize, size_t _Count)
{
	fread_s(_Ptr, _BufferSize, _ReadSize, _Count, m_Handle);

	// Read�Ϸ� �� ���� Ŀ����ġ ����
	CurPostion();
}

// UNICODE(WIDE BYTE) FILE OPEN
void SGameEngineFile::UniCodeFileOpen(const wchar_t* _Mode)
{
	FileClose();

	// ��� ����
	m_Mode = _Mode;
	m_Mode += L", ccs=UNICODE";

	_wfopen_s(&m_Handle, c_str(), m_Mode.c_str());
	if (nullptr == m_Handle)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}
	else
	{
		// ���� ũ�� ����
		fseek(m_Handle, 0, SEEK_END);
		m_FileSize = ftell(m_Handle);
		fseek(m_Handle, 0, SEEK_SET);
	}
}

// ���� ����ڰ� ������ �аų� ���� �ִ� ����Ʈ ��ġ�� �� �� �ִ� �Լ�
size_t SGameEngineFile::CurPostion()
{
	if (nullptr == m_Handle)
	{
		return m_FilePointer;
	}

	// ���� ��ġ ���� ������ ����
	m_FilePointer = ftell(m_Handle);

	return m_FilePointer;
}

// ���� ������ �� ũ�⸦ �����Ѵ�.
size_t SGameEngineFile::FileTotalSize()
{
	if (nullptr == m_Handle)
	{
		return m_FileSize;
	}

	return m_FileSize;
}
