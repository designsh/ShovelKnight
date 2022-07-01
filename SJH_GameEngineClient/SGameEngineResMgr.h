#pragma once
#include <SGameEngineWinImage.h>
#include <SGameEngineString.h>
#include <map>

// 분류 :
// 용도 : 
// 설명 : 
class SGameEngineResMgr
{
    private: // Static Var

    public: // Static Func
        static SGameEngineResMgr& Inst();

    private: // member Var
        std::map<SGameEngineString, SGameEngineWinImage*> m_Image;

    public: // constructer destructer
        SGameEngineResMgr();
        ~SGameEngineResMgr();

    public: // delete constructer 
        SGameEngineResMgr(const SGameEngineResMgr& _Other) = delete;
        SGameEngineResMgr(const SGameEngineResMgr&& _Other) = delete;

    public: // delete operator
        SGameEngineResMgr& operator=(const SGameEngineResMgr& _Other) = delete;
        SGameEngineResMgr& operator=(const SGameEngineResMgr&& _Other) = delete;

    public: // member Func
        void ImageLoad(const SGameEngineString& _Path);
        SGameEngineWinImage* FindImage(const SGameEngineString& _Name);
        void Release();

};

