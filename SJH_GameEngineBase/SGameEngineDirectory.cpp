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
	// DWORD = unsigned long(아래 버퍼의 실제길이)
	// LPWSTR = wchar_t*(버퍼)
	// MAX_PATH = Windows가 허용하는 경로에대한 Max Length
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
SGameEngineString SGameEngineDirectory::GetPath() const // 현재 자기자신의 경로를 가져온다.
{
	return *this;
}

void SGameEngineDirectory::MoveChildFolder(const SGameEngineString& _FolderName)
{
	// _FolderName 인자가 폴더이름이아닌 경로가 넘어오면 문제발생
	// 경로가 넘어오면 마지막 폴더만 짤라서 붙이면 될거같긴한데....
	// 경로인지 폴더명인지 판단을 어찌해야할지 모르것음....
	SGameEngineString::operator+=(_FolderName + L"\\");

	// 존재하지 않으면 디버그 메세지 띄움
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

	// 현재 폴더이름과 인자로 받은 폴더이름을 받을때까지 반복
	while (FolderName() != _FolderName)
	{
		MoveParentsFolder();
	}
}

// 현재 폴더의 경로는 가지고 있으므로 인자는 받지않는 함수
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

// 현재 폴더의 경로를 가지고 있으나 디렉터리가 존재할 경우 
// 해당 디렉터리 하위 파일까지 찾기 위하여
// 찾고자하는 경로를 인자로 받는다.
std::vector<SGameEngineFile> SGameEngineDirectory::AllFile(const SGameEngineString& _Path, bool _FindChildFolder)
{
	const wchar_t* MyPath = _Path.c_str();

	// 파일 정보를 가져오기위해 _WIN32_FIND_DATAW 구조체 사용
	// 사용할 속성
	// dwFileAttributes : 검색한 파일의 속성(파일 or 디렉터리)
	WIN32_FIND_DATA FileData;
	wchar_t SearchAllFile[256] = { 0, };

	// 모든 파일을 찾기 위해 현재 Path에 "*.*" 추가
	wsprintf(SearchAllFile, L"%s%s", MyPath, L"*.*");

	// HANDLE : 운영체제 내부에 있는 어떤 리소스의 주소를 정수로 치환한 값(윈도우 )
	// INVALID_HANDLE_VALUE : 핸들 초기화 값
	// hFind의 초기값으로 현재경로의 첫번째파일을 줌
	HANDLE hFind = ::FindFirstFile(SearchAllFile, &FileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// 비트 연산자 사용(FILE_ATTRIBUTE_DIRECTORY)해서 파일인지 디렉터리인지 검사
			// HANDLE로 FILE_ATTRIBUTE_DIRECTORY(디렉터리인지) 식별
			if (!(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				// 찾은 파일의 경로를 저장
				SGameEngineString FileName = FileData.cFileName;
				SGameEngineFile NewFile = operator+(FileName);
				ReturnFileVector.push_back(NewFile);
			}
			else
			{
				if (_FindChildFolder == true && FileData.cFileName[0] != L'.')
				{
					// 현재 경로에 디렉토리가 존재하다면
					// 그 디렉토리의 하위파일List도 찾기
					// 현재 경로에 fd.cFileName 추가하여 현재경로를 하위 디렉터리 경로로 옮긴후
					wchar_t ChildPath[256] = { 0, };
					wsprintf(ChildPath, L"%s%s%s", MyPath, FileData.cFileName, L"\\");

					// 재귀함수 실행하여 하위 폴더의 파일리스트 추출
					// 여기서 다시 하위 디렉토리로 이동하려면 옵션 : True로 설정
					// 재귀함수이기 때문에 초기 경로(하위 이동전 경로)의 모든 디렉터리의 하위 파일을 가져올수 있음
					AllFile(ChildPath);
				}
			}
		} while (::FindNextFile(hFind, &FileData));

		// 핸들러 종료
		::FindClose(hFind);
	}

	// 재귀함수를 통해 계속하여 벡터에 삽입해야하므로
	// 헤더파일에 벡터 선언
	// 지역으로쓰면 하위 경로는 따로 벡터를 생성하기때문에 문제 생김
	return ReturnFileVector;
}

// 현재 경로가 가지믄 모든 폴더를 벡터에 저장
std::vector<SGameEngineFile> SGameEngineDirectory::AllFolder()
{
	// 현재 경로의 모든 폴더 리스트를 저장하는 벡터
	std::vector<SGameEngineFile> ReturnFolderVector;

	const wchar_t* MyPath = c_str();
	WIN32_FIND_DATA FileData;
	wchar_t SearchAllFile[256] = { 0, };
	wsprintf(SearchAllFile, L"%s%s", MyPath, L"*.*");

	// 이것도 하위 폴더 이동해야되나?
	HANDLE hFind = ::FindFirstFile(SearchAllFile, &FileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// . : 현재폴더
				// .. : 상위폴더
				// 이므로 벡터에 저장안함
				if (FileData.cFileName[0] != '.')
				{
					// 찾은 파일의 경로를 저장
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
