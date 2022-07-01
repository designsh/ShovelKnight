#include "SGameEngineDirectory.h"
#include "SGameEngineDebug.h"
#include "SGameEngineFile.h"

#include <Windows.h>
#include <io.h>

// Static Var

// Static Func
void SGameEngineDirectory::GetCurrentFolderPath(SGameEngineString& _String)
{
	_String = GetCurrentFolderPath();
}

SGameEngineString SGameEngineDirectory::GetCurrentFolderPath()
{
	// DWORD = unsigned long(�Ʒ� ������ ��������)
	// LPWSTR = wchar_t*(����)
	// MAX_PATH = Windows�� ����ϴ� ��ο����� Max Length
	wchar_t PathArray[MAX_PATH] = { 0, };

	GetCurrentDirectoryW(MAX_PATH, PathArray);
	SGameEngineString ReturnPath = PathArray;
	ReturnPath += L"\\";

	return ReturnPath;
}

// member Var
SGameEngineDirectory::SGameEngineDirectory() : SGameEnginePath(GetCurrentFolderPath())
{

}

SGameEngineDirectory::~SGameEngineDirectory()
{

}

// member Func
SGameEngineString SGameEngineDirectory::GetPath() const // ���� �ڱ��ڽ��� ��θ� �����´�.
{
	return *this;
}

void SGameEngineDirectory::MoveChildFolder(const SGameEngineString& _FolderName)
{
	// _FolderName ���ڰ� �����̸��̾ƴ� ��ΰ� �Ѿ���� �����߻�
	// ��ΰ� �Ѿ���� ������ ������ ©�� ���̸� �ɰŰ����ѵ�....
	// ������� ���������� �Ǵ��� �����ؾ����� �𸣰���....
	SGameEngineString::operator+=(_FolderName + L"\\");

	// �������� ������ ����� �޼��� ���
	if (false == IsExist())
	{
		SGameEngineDebug::AssertMsg(_FolderName + L"if(false == IsExist())");
	}
}

void SGameEngineDirectory::MoveParentsFolder()
{
	SGameEngineString::operator=(CutIndex(0, find_last_index(L"\\", size() - 2)));
}

SGameEngineString SGameEngineDirectory::FolderName()
{
	return IOName();
}

void SGameEngineDirectory::MoveParentsFolder(const SGameEngineString& _FolderName)
{
	SGameEngineString Name = FolderName();

	// ���� �����̸��� ���ڷ� ���� �����̸��� ���������� �ݺ�
	while (FolderName() != _FolderName)
	{
		MoveParentsFolder();
	}
}

// ���� ������ ��δ� ������ �����Ƿ� ���ڴ� �����ʴ� �Լ�
std::vector<SGameEngineFile> SGameEngineDirectory::FindDirectoryAllFileToVector(const SGameEngineString& _CheckPath)
{
	std::vector<SGameEngineFile> ReturnVector;

	_wfinddata64i32_t fd;

	SGameEngineString Path = c_str();
	Path += _CheckPath;

	intptr_t FindHandle = _wfindfirst(Path.c_str(), &fd);

	if (-1 == FindHandle)
	{
		SGameEngineDebug::AssertMsg(L"if (-1 == HANDLE)");
	}

	do
	{
		if (fd.attrib & _A_SUBDIR)
		{
			FindHandle = _wfindnext(FindHandle, &fd);
			continue;
		}

		SGameEngineString FileName = fd.name;
		SGameEngineFile NewFile = operator+(FileName);

		ReturnVector.push_back(NewFile);

	} while (0 == _wfindnext(FindHandle, &fd));

	_findclose(FindHandle);

	return ReturnVector;
}

// ���� ������ ��θ� ������ ������ ���͸��� ������ ��� 
// �ش� ���͸� ���� ���ϱ��� ã�� ���Ͽ�
// ã�����ϴ� ��θ� ���ڷ� �޴´�.
std::vector<SGameEngineFile> SGameEngineDirectory::AllFile(const SGameEngineString& _Path, bool _FindChildFolder)
{
	const wchar_t* MyPath = _Path.c_str();

	// ���� ������ ������������ _WIN32_FIND_DATAW ����ü ���
	// ����� �Ӽ�
	// dwFileAttributes : �˻��� ������ �Ӽ�(���� or ���͸�)
	WIN32_FIND_DATA FileData;
	wchar_t SearchAllFile[256] = { 0, };

	// ��� ������ ã�� ���� ���� Path�� "*.*" �߰�
	wsprintf(SearchAllFile, L"%s%s", MyPath, L"*.*");

	// HANDLE : �ü�� ���ο� �ִ� � ���ҽ��� �ּҸ� ������ ġȯ�� ��(������ )
	// INVALID_HANDLE_VALUE : �ڵ� �ʱ�ȭ ��
	// hFind�� �ʱⰪ���� �������� ù��°������ ��
	HANDLE hFind = ::FindFirstFile(SearchAllFile, &FileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// ��Ʈ ������ ���(FILE_ATTRIBUTE_DIRECTORY)�ؼ� �������� ���͸����� �˻�
			// HANDLE�� FILE_ATTRIBUTE_DIRECTORY(���͸�����) �ĺ�
			if (!(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				// ã�� ������ ��θ� ����
				SGameEngineString FileName = FileData.cFileName;
				SGameEngineFile NewFile = operator+(FileName);
				ReturnFileVector.push_back(NewFile);
			}
			else
			{
				if (_FindChildFolder == true && FileData.cFileName[0] != L'.')
				{
					// ���� ��ο� ���丮�� �����ϴٸ�
					// �� ���丮�� ��������List�� ã��
					// ���� ��ο� fd.cFileName �߰��Ͽ� �����θ� ���� ���͸� ��η� �ű���
					wchar_t ChildPath[256] = { 0, };
					wsprintf(ChildPath, L"%s%s%s", MyPath, FileData.cFileName, L"\\");

					// ����Լ� �����Ͽ� ���� ������ ���ϸ���Ʈ ����
					// ���⼭ �ٽ� ���� ���丮�� �̵��Ϸ��� �ɼ� : True�� ����
					// ����Լ��̱� ������ �ʱ� ���(���� �̵��� ���)�� ��� ���͸��� ���� ������ �����ü� ����
					AllFile(ChildPath);
				}
			}
		} while (::FindNextFile(hFind, &FileData));

		// �ڵ鷯 ����
		::FindClose(hFind);
	}

	// ����Լ��� ���� ����Ͽ� ���Ϳ� �����ؾ��ϹǷ�
	// ������Ͽ� ���� ����
	// �������ξ��� ���� ��δ� ���� ���͸� �����ϱ⶧���� ���� ����
	return ReturnFileVector;
}

// ���� ��ΰ� ������ ��� ������ ���Ϳ� ����
std::vector<SGameEngineFile> SGameEngineDirectory::AllFolder()
{
	// ���� ����� ��� ���� ����Ʈ�� �����ϴ� ����
	std::vector<SGameEngineFile> ReturnFolderVector;

	const wchar_t* MyPath = c_str();
	WIN32_FIND_DATA FileData;
	wchar_t SearchAllFile[256] = { 0, };
	wsprintf(SearchAllFile, L"%s%s", MyPath, L"*.*");

	// �̰͵� ���� ���� �̵��ؾߵǳ�?
	HANDLE hFind = ::FindFirstFile(SearchAllFile, &FileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// . : ��������
				// .. : ��������
				// �̹Ƿ� ���Ϳ� �������
				if (FileData.cFileName[0] != '.')
				{
					// ã�� ������ ��θ� ����
					SGameEngineString FolderName = FileData.cFileName;
					SGameEngineFile NewFile = operator+(FolderName);
					NewFile += L"\\";
					ReturnFolderVector.push_back(NewFile);
				}
			}
		} while (::FindNextFile(hFind, &FileData));

		::FindClose(hFind);
	}

	return ReturnFolderVector;
}
