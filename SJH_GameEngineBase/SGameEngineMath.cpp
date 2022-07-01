#include "SGameEngineMath.h"

// Static Var
const FLOAT4 FLOAT4::LEFT = { -1, 0 };
const FLOAT4 FLOAT4::RIGHT = { 1, 0 };
const FLOAT4 FLOAT4::UP = { 0 , -1 };
const FLOAT4 FLOAT4::DOWN = { 0 , 1 };
const FLOAT4 FLOAT4::ZERO = { 0, 0 };
const FLOAT4 FLOAT4::ONE = { 1, 1 };
const FLOAT4 FLOAT4::GRAVITY = { 0.f, 3.0f };

// Pi(원주율) 값 지정(float, double)
float SGameEngineMath::FPI = 3.141592653589793238462643383279502884197169399375105820974944f;
double SGameEngineMath::DPI = 3.141592653589793238462643383279502884197169399375105820974944;

// 라디안 각도(호도법) : 180도 == 3.14(원주율)
// 각도(60분법) -> 라디안각도(호도법)
float SGameEngineMath::FD2R = FPI / 180;
// 라디안각도(호도법) -> 각도(60분법)
float SGameEngineMath::FR2D = 180 / FPI;

// Static Func

// member Var
SGameEngineMath::SGameEngineMath()
{

}

SGameEngineMath::~SGameEngineMath()
{

}

// member Func
Coliison2DCheck::StaticColInst Coliison2DCheck::Inst;
bool (*Coliison2DCheck::ColFunc[(int)COLTYPE::MAX][(int)COLTYPE::MAX])(const Col2DData&, const Col2DData&);


void Coliison2DCheck::Init()
{
	ColFunc[(int)COLTYPE::RECT][(int)COLTYPE::RECT] = RectToRect;
	ColFunc[(int)COLTYPE::RECT][(int)COLTYPE::CIRCLE] = RectToCirCle;
	ColFunc[(int)COLTYPE::RECT][(int)COLTYPE::POINT] = RectToPoint;

	ColFunc[(int)COLTYPE::CIRCLE][(int)COLTYPE::RECT] = CircleToRect;
	ColFunc[(int)COLTYPE::CIRCLE][(int)COLTYPE::CIRCLE] = CircleToCirCle;
	ColFunc[(int)COLTYPE::CIRCLE][(int)COLTYPE::POINT] = CircleToPoint;

	ColFunc[(int)COLTYPE::POINT][(int)COLTYPE::RECT] = PointToRect;
	ColFunc[(int)COLTYPE::POINT][(int)COLTYPE::CIRCLE] = PointToCirCle;
	ColFunc[(int)COLTYPE::POINT][(int)COLTYPE::POINT] = PointToPoint;
}

bool Coliison2DCheck::RectToRect(const Col2DData& _Left, const Col2DData& _Right)
{
	// 	윈도우 좌표계에서의 충돌체의 기준 4가지
	// 현재 비교하려는 충돌체중 _Left가 _Right보다 왼쪽에 위치했을때
	// 현재 비교하려는 충돌체중 _Left가 _Right보다 오른쪽에 위치했을때
	// 	현재 비교하려는 충돌체중 _Left가 _Right보다 위쪽에 위치했을때
	// 	현재 비교하려는 충돌체중 _Left가 _Right보다 아래쪽에 위치했을때
	//////////////////////////////////////////////////////////////////////////////////////////

	// 현재 비교하려는 충돌체중 _Left가 _Right보다 왼쪽에 위치했을때
	// _Left의 오른쪽면(포인트)가 _Right의 왼쪽면(포인트)
	// 보다 작다면 두 충돌체는 충돌하지않음
	if (_Left.Right() < _Right.Left())
	{
		return false;
	}

	// 현재 비교하려는 충돌체중 _Left가 _Right보다 오른쪽에 위치했을때
	// _Left의 왼쪽면(포인트)가 _Right의 오른쪽면(포인트)
	// 보다 크다면 두 충돌체는 충돌하지않음
	if (_Left.Left() > _Right.Right())
	{
		return false;
	}

	// 현재 비교하려는 충돌체중 _Left가 _Right보다 위쪽에 위치했을때
	// _Left의 아래면(포인트)가 _Right의 윗면(포인트)
	// 보다 작다면 두 충돌체는 충돌하지 않음
	if (_Left.Bottom() < _Right.Top())
	{
		return false;
	}

	// 현재 비교하려는 충돌체중 _Left가 _Right보다 아래쪽에 위치했을때
	// _Left의 윗면(포인트)이 _Right의 아래면(포인트)
	// 보다 크다면 두 충돌체는 충돌하지 않음
	if (_Left.Top() > _Right.Bottom())
	{
		return false;
	}

	return true;
}

bool Coliison2DCheck::RectToCirCle(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::RectToPoint(const Col2DData& _Left, const Col2DData& _Right) { return true; }

bool Coliison2DCheck::CircleToRect(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::CircleToCirCle(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::CircleToPoint(const Col2DData& _Left, const Col2DData& _Right) { return true; }

bool Coliison2DCheck::PointToRect(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::PointToCirCle(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::PointToPoint(const Col2DData& _Left, const Col2DData& _Right) { return true; }

//---------------------------------------------------------------------- TileKey ----------------------------------------------------------------------//
TileKey::TileKey()
	: x(0), y(0)
{

}

TileKey::TileKey(int _x, int _y)
	: x(_x), y(_y)
{

}

TileKey::TileKey(FLOAT4 _Value)
	: x(_Value.ix()), y(_Value.iy())
{

}

bool TileKey::operator<(const TileKey& _Other) const
{
	if (y == _Other.y)
	{
		return x < _Other.x;
	}
	return y < _Other.y;
}

TileKey& TileKey::operator+=(const TileKey& _Other)
{
	x += _Other.x;
	y += _Other.y;

	return *this;
}

TileKey TileKey::operator+(const TileKey& _Other)
{
	TileKey Value;
	Value.x = x + _Other.x;
	Value.y = y + _Other.y;

	return Value;
}

TileKey TileKey::operator-(const TileKey& _Other)
{
	TileKey Value;
	Value.x = x - _Other.x;
	Value.y = y - _Other.y;

	return Value;
}

Position TileKey::operator* (const float& _Other)
{
	Position Value = 0.0f;
	Value.x = x * _Other;
	Value.y = y * _Other;

	return Value;
}

bool TileKey::operator== (int _Other)
{
	return x == _Other && y == _Other;
}

bool TileKey::operator==(const TileKey& _Other)
{
	return x == _Other.x && y == _Other.y;
}

FLOAT4 TileKey::GetTileKeyPos()
{
	return FLOAT4(x, y);
}

