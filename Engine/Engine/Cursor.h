#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <string>

namespace Engine
{
	class Cursor 
	{
	private:
		std::string handle;
		Cursor();	
	public:
		~Cursor();
		static Cursor* instance();
		void update(long x, long y);
		std::string getHandle();
		D3DXVECTOR2	cursorPos;
	};
};
