#pragma once
#include <math.h>

// 분류 :
// 용도 : 
// 설명 : 
class SGameEngineMath
{
    private: // Static Var

    public:
        static float FPI;
        static double DPI;

        static float FD2R;
        static float FR2D;

    public: // Static Func

    private: // member Var

    public: // constructer destructer
        SGameEngineMath();
        ~SGameEngineMath();

    public: // delete constructer 
        SGameEngineMath(const SGameEngineMath& _Other) = delete;
        SGameEngineMath(const SGameEngineMath&& _Other) = delete;

    public: // delete operator
        SGameEngineMath& operator=(const SGameEngineMath& _Other) = delete;
        SGameEngineMath& operator=(const SGameEngineMath&& _Other) = delete;

    public: // member Func

};

// 4차원 좌표를 나타낼 수 있는 클래스
class FLOAT4
{
public:
    static const FLOAT4 LEFT;
    static const FLOAT4 RIGHT;
    static const FLOAT4 UP;
    static const FLOAT4 DOWN;
    static const FLOAT4 ZERO;
    static const FLOAT4 ONE;
    static const FLOAT4 GRAVITY;
    static const FLOAT4 JUMPPOWER;

public:
    static FLOAT4 AngleToDir2DDeg(float _Degree)
    {
        return AngleToDir2DRad(_Degree * SGameEngineMath::FD2R);
    }

    static FLOAT4 AngleToDir2DRad(float _Radian)
    {
        FLOAT4 ReturnPos = FLOAT4::ZERO;

        // 빗변의 길이가 1인 직각삼각형일때 
        // 코사인(cos) : 밑변 / 빗변(1) => 밑변 => x좌표축의 값
        // 사인(sin) : 높이 / 빗변(1) => 높이 => y좌표축의 값
        ReturnPos.x = cosf(_Radian);
        ReturnPos.y = sinf(_Radian);

        return ReturnPos;
    }

    // 어떤 점을 넣어주면 0,0 기준으로 회전
    static FLOAT4 AngleTo2DDeg(const FLOAT4& _OriPoint, float _Degree)
    {
        return AngleTo2DRad(_OriPoint, _Degree * SGameEngineMath::FD2R);
    }

    static FLOAT4 AngleTo2DRad(const FLOAT4& _OriPoint, float _Radian)
    {
        FLOAT4 ReturnPos;

        ReturnPos.x = (cosf(_Radian) * _OriPoint.x) - (sinf(_Radian) * _OriPoint.y);
        ReturnPos.y = (sinf(_Radian) * _OriPoint.x) + (cosf(_Radian) * _OriPoint.y);

        return ReturnPos;
    }

    static float Len3D(const FLOAT4& _Value)
    {
        return sqrtf((_Value.x * _Value.x) + (_Value.y * _Value.y) + (_Value.z * _Value.z));
    }

    static float Len2D(const FLOAT4& _Value)
    {
        return sqrtf((_Value.x * _Value.x) + (_Value.y * _Value.y));
    }

    static FLOAT4 Normalize2D(const FLOAT4& _Value)
    {
        FLOAT4 ReturnValue = _Value;
        float Len = Len2D(_Value);

        // 현재 Pos에서 Len2D()를 나눈다는 것은
        // 길이가 1인 벡터를 구해내는 공식이다.
        ReturnValue.x = _Value.x / Len;
        ReturnValue.y = _Value.y / Len;
        ReturnValue.z = 0.0f;

        return ReturnValue;
    }

public:
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };

        struct
        {
            float r;
            float g;
            float b;
            float a;
        };
    };

public:
    FLOAT4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
    {

    }

    FLOAT4(float _Value) : x(_Value), y(_Value), z(_Value), w(_Value)
    {

    }

    FLOAT4(float _x, float _y) : x(_x), y(_y), z(0.0f), w(1.0f)
    {

    }

    FLOAT4(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1.0f)
    {

    }

    FLOAT4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
    {

    }

    // int -> float
    FLOAT4(int _Value) : x(static_cast<float>(_Value)), y(static_cast<float>(_Value)), z(static_cast<float>(_Value)), w(static_cast<float>(_Value))
    {

    }

    FLOAT4(int _x, int _y) : x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(0.0f), w(1.0f)
    {

    }

    FLOAT4(int _x, int _y, int _z) : x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(static_cast<float>(_z)), w(1.0f)
    {

    }

    FLOAT4(int _x, int _y, int _z, int _w) : x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(static_cast<float>(_z)), w(static_cast<float>(_w))
    {

    }

public:
    int ix() const
    {
        return static_cast<int>(x);
    }
    int iy() const
    {
        return static_cast<int>(y);
    }
    int iz() const
    {
        return static_cast<int>(z);
    }
    int iw() const
    {
        return static_cast<int>(w);
    }

    int HarfX() const
    {
        return static_cast<int>(x * 0.5f);
    }
    int HarfY() const
    {
        return static_cast<int>(y * 0.5f);
    }
    int HarfZ() const
    {
        return static_cast<int>(z * 0.5f);
    }
    int HarfW() const
    {
        return static_cast<int>(w * 0.5f);
    }

    float fHarfX() const
    {
        return x * 0.5f;
    }
    float fHarfY() const
    {
        return y * 0.5f;
    }
    float fHarfZ() const
    {
        return z * 0.5f;
    }
    float fHarfW() const
    {
        return w * 0.5f;
    }

    FLOAT4 hfloat4() const
    {
        return { fHarfX(), fHarfY() };
    }

public:
    // 속성 중 하나라도 0이 있으면 True 반환
    bool IsZero2D() const
    {
        return x == 0 || y == 0;
    }

    bool IsZero() const
    {
        return x == 0 || y == 0 || z == 0;
    }

public:
    bool operator==(const FLOAT4& _Other) const
    {
        return x == _Other.x && y == _Other.y;
    }

    bool operator!=(const FLOAT4& _Other) const
    {
        return x != _Other.x || y != _Other.y;
    }

    bool operator<=(const FLOAT4& _Other) const
    {
        return x <= _Other.x || y <= _Other.y;
    }

    bool operator>=(const FLOAT4& _Other) const
    {
        return x >= _Other.x || y >= _Other.y;
    }

    FLOAT4 operator+(const FLOAT4& _Other) const
    {
        FLOAT4 ReturnVector;
        ReturnVector.x = x + _Other.x;
        ReturnVector.y = y + _Other.y;
        ReturnVector.z = z + _Other.z;
        ReturnVector.w = w + _Other.w;
        return ReturnVector;
    }

    FLOAT4& operator+=(const FLOAT4& _Other)
    {
        x += _Other.x;
        y += _Other.y;
        z += _Other.z;
        w += _Other.w;
        return *this;
    }

    FLOAT4& operator-=(const FLOAT4& _Other)
    {
        x -= _Other.x;
        y -= _Other.y;
        z -= _Other.z;
        w -= _Other.w;
        return *this;
    }

    FLOAT4 operator-(const FLOAT4& _Other) const
    {
        FLOAT4 ReturnVector;
        ReturnVector.x = x - _Other.x;
        ReturnVector.y = y - _Other.y;
        ReturnVector.z = z - _Other.z;
        ReturnVector.w = w - _Other.w;
        return ReturnVector;
    }

    FLOAT4 operator*(const float& _Value) const
    {
        FLOAT4 ReturnVector;
        ReturnVector.x = x * _Value;
        ReturnVector.y = y * _Value;
        ReturnVector.z = z * _Value;
        ReturnVector.w = w * _Value;
        return ReturnVector;
    }

    FLOAT4 operator*(const FLOAT4& _Value) const
    {
        FLOAT4 ReturnVector;
        ReturnVector.x = x * _Value.x;
        ReturnVector.y = y * _Value.y;
        ReturnVector.z = z * _Value.z;
        ReturnVector.w = w * _Value.w;
        return ReturnVector;
    }

public:
    // 2D 좌표계에서의 벡터의 길이를 반환하는 함수
    float GetLen()
    {
        return Len2D(*this);
    }

    // 2D 좌표계에서의 벡터의 단위벡터를 반환하는 함수
    FLOAT4 GetNormalize2D() const
    {
        return Normalize2D(*this);
    }

    // 2D 좌표계에서의 벡터의 단위벡터를 저장하는 함수
    // *this를 인자를 넘겨주고 함수를 통해 반환된값을
    // 다시 *this에 넣어줌으로써 자기자신의 값을 변환한다.
    void Normalize()
    {
        *this = Normalize2D(*this);
    }

    static FLOAT4 LerpMax(const FLOAT4& _Start, const FLOAT4& _End, float _Ratio)
    {
        if (0 >= _Ratio)
        {
            _Ratio = 0.0f;
        }

        if (1.0f <= _Ratio)
        {
            _Ratio = 1.0f;
        }

        return Lerp2D(_Start, _End, _Ratio);
    }

    static FLOAT4 Lerp2D(const FLOAT4& _Start, const FLOAT4& _End, float _Ratio)
    {
        FLOAT4 ReturnValue;
        // p1 _Start
        // p2 _End
        // d1 _Ratio
        ReturnValue.x = (1 - _Ratio) * _Start.x + _Ratio * _End.x;
        ReturnValue.y = (1 - _Ratio) * _Start.y + _Ratio * _End.y;

        return ReturnValue;
    }
};

typedef FLOAT4 Vector;
typedef FLOAT4 Position;
typedef FLOAT4 Scale;
typedef FLOAT4 FRect;
typedef FLOAT4 Color;

enum class COLTYPE
{
    RECT,      // 사각형
    CIRCLE,   // 원(타원X)
    POINT,    // 점
    MAX      // 
};

class Col2DData
{
public: // 
    FLOAT4 m_Pos;
    FLOAT4 m_Size;

public:
    float Left() const
    {
        return m_Pos.x - m_Size.fHarfX();
    }

    float Right() const
    {
        return m_Pos.x + m_Size.fHarfX();
    }

    float Top() const
    {
        return m_Pos.y - m_Size.fHarfY();
    }

    float Bottom() const
    {
        return m_Pos.y + m_Size.fHarfY();
    }

    int iLeft() const
    {
        return static_cast<int>(Left());
    }

    int iRight() const
    {
        return static_cast<int>(Right());
    }

    int iTop() const
    {
        return static_cast<int>(Top());
    }

    int iBottom() const
    {
        return static_cast<int>(Bottom());
    }

    FLOAT4 LeftPoint() const
    {
        return { Left(), m_Pos.y };
    }

    FLOAT4 RightPoint() const
    {
        return { Right(), m_Pos.y };
    }

    FLOAT4 TopPoint() const
    {
        return { m_Pos.x, Top() };
    }

    FLOAT4 BottomPoint() const
    {
        return { m_Pos.x, Bottom() };
    }
};

class Coliison2DCheck
{
private:
    class StaticColInst
    {
        friend Coliison2DCheck;

        private:
            StaticColInst()
            {
                Coliison2DCheck::Init();
            }

            ~StaticColInst()
            {

            }
    };

public: // 함수 포인터 이용
    // 이유 : 1. switch 문에 비해 비교를 하지않아 속도가 빠르다.
    //           2. 가독성에 도움을 준다.
    //           3. 중복된 코드를 여러번 작성할 이유가 없어진다.
    static bool (*ColFunc[(int)COLTYPE::MAX][(int)COLTYPE::MAX])(const Col2DData&, const Col2DData&);

private:
    friend StaticColInst;
    static StaticColInst Inst;
    
public:
    static void Init();

public:
    static bool RectToRect(const Col2DData& _Left, const Col2DData& _Right);
    static bool RectToCirCle(const Col2DData& _Left, const Col2DData& _Right);
    static bool RectToPoint(const Col2DData& _Left, const Col2DData& _Right);

    static bool CircleToRect(const Col2DData& _Left, const Col2DData& _Right);
    static bool CircleToCirCle(const Col2DData& _Left, const Col2DData& _Right);
    static bool CircleToPoint(const Col2DData& _Left, const Col2DData& _Right);

    static bool PointToRect(const Col2DData& _Left, const Col2DData& _Right);
    static bool PointToCirCle(const Col2DData& _Left, const Col2DData& _Right);
    static bool PointToPoint(const Col2DData& _Left, const Col2DData& _Right);

private: // 객체화를 막기위하여 순수가상함수로 선언
    virtual ~Coliison2DCheck() {}
};

// 타일맵 전용 타일키
class TileKey
{
public:
    int x;
    int y;

public:
    TileKey();
    TileKey(int _x, int _y);
    TileKey(FLOAT4 _Value);

public:
    bool operator<(const TileKey& _Other) const;
    TileKey& operator+=(const TileKey& _Other);
    TileKey operator+(const TileKey& _Other);
    TileKey operator-(const TileKey& _Other);
    Position operator* (const float& _Other);
    bool operator== (int _Other);
    bool operator==(const TileKey& _Other);

public:
    FLOAT4 GetTileKeyPos();
};
