#pragma once
#include "SGameEnginePath.h"

// �з� : 
// �뵵 : 
// ���� : 
class SGameEngineFile;
class SGameEngineDirectory : public SGameEnginePath
{
private: // Static Var

public: // Static Func
    static void GetCurrentFolderPath(SGameEngineString& _String);
    static SGameEngineString GetCurrentFolderPath();

private: // member Var
    // ���� ���(�ɼǿ� ���� ������� ����) ��� ���� ����Ʈ�� �����ϴ� ����
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

    // ���� ��ΰ� ������ ��� ������ ���Ϳ� ����
    std::vector<SGameEngineFile> AllFile(const SGameEngineString& _Path, bool _FindChildFolder = false);
    std::vector<SGameEngineFile> FindDirectoryAllFileToVector(const SGameEngineString& _CheckPath = L"*.*");

    // ���� ��ΰ� ������ ��� ������ ���Ϳ� ����
    std::vector<SGameEngineFile> AllFolder();

};

