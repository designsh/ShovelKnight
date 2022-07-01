#pragma once
#include "SGameEnginePath.h"

// 분류 : 
// 용도 : 
// 설명 : 
class SGameEngineFile;
class SGameEngineDirectory : public SGameEnginePath
{
private: // Static Var

public: // Static Func
    static void GetCurrentFolderPath(SGameEngineString& _String);
    static SGameEngineString GetCurrentFolderPath();

private: // member Var
    // 현재 경로(옵션에 따라 하위경로 포함) 모든 파일 리스트를 저장하는 벡터
    std::vector<SGameEngineFile> ReturnFileVector;

public: // constructer destructer
    SGameEngineDirectory();
    ~SGameEngineDirectory();

public: // delete constructer 
    SGameEngineDirectory(const SGameEngineDirectory& _Other) = delete;
    SGameEngineDirectory(const SGameEngineDirectory&& _Other) = delete;

public: // delete operator
    SGameEngineDirectory& operator=(const SGameEngineDirectory& _Other) = delete;
    SGameEngineDirectory& operator=(const SGameEngineDirectory&& _Other) = delete;
    SGameEngineDirectory& operator=(const SGameEngineString& _Other)
    {

    }

public: // member Func
    SGameEngineString GetPath() const;
    void MoveChildFolder(const SGameEngineString& _FolderName);
    void MoveParentsFolder();
    void MoveParentsFolder(const SGameEngineString& _FolderName);
    SGameEngineString FolderName();

    // 현재 경로가 가지는 모든 파일을 벡터에 저장
    std::vector<SGameEngineFile> AllFile(const SGameEngineString& _Path, bool _FindChildFolder = false);
    std::vector<SGameEngineFile> FindDirectoryAllFileToVector(const SGameEngineString& _CheckPath = L"*.*");

    // 현재 경로가 가지믄 모든 폴더를 벡터에 저장
    std::vector<SGameEngineFile> AllFolder();

};

