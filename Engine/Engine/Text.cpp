#include "Text.h"
#include "DX.h"

Engine::Text::Text()
{
	font = nullptr;
	ZeroMemory(buffer, sizeof(buffer));
	rect.top = rect.bottom = rect.right = rect.left = 0;
	color = D3DCOLOR_ARGB(255,255,255,255);
}

Engine::Text::~Text()
{}

Engine::Text *Engine::Text::instance()
{
	static Text text;
	return &text;
}

void Engine::Text::init()
{
	D3DXCreateFont(Engine::DX::instance()->getDevice(),
		30, 10, FW_NORMAL, 0, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"), &font);
}

void Engine::Text::setText(LPCWSTR text)
{
	swprintf_s(buffer, 256, text);
}

void Engine::Text::setText(int text)
{

	std::wstring temp;
	std::string tempstr;
	char buf[256];
	_itoa_s(text, buf, 256, 16);


	tempstr = buf;
	temp = std::wstring(tempstr.begin(), tempstr.end());
	
	swprintf_s(buffer, 256, temp.c_str());
}

void Engine::Text::render(long top, long left)
{
	rect.top = top;
	rect.left = left;

	font->DrawText(0, buffer, -1, &rect, DT_TOP | DT_LEFT | DT_NOCLIP, color);
}


void Engine::Text::render(long top, long left, wchar_t* words, dColor color)
{
	rect.top = top;
	rect.left = left;
	font->DrawText(0, words, -1, &rect, DT_TOP|DT_LEFT|DT_NOCLIP, color);
}

void Engine::Text::render(long top, long left, std::string word, dColor color)
{
	rect.top = top;
	rect.left = left;
	std::wstring tempWS = L"";
	tempWS = std::wstring(word.begin(),word.end());
	font->DrawText(0, tempWS.c_str() , -1, &rect, DT_TOP|DT_LEFT|DT_NOCLIP, color);
}

void Engine::Text::render(Drawable &word)
{
	font->DrawText(0, word.getPlainText(), -1, &word.getRect(), DT_TOP|DT_LEFT|DT_NOCLIP, word.getColor());
}

void Engine::Text::setColor(dColor color)
{
	this->color = color;
}

void Engine::Text::shutdown()
{
	SAFE_RELEASE(font);
}