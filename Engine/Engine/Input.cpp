#include "Input.h"

Engine::Input::Input()
{
	m_Input_Obj = 0;
	mouse = 0;
	keyboard = 0;
	ZeroMemory( buffer, sizeof(buffer));
	ZeroMemory( key_down, sizeof(key_down));
	ZeroMemory(&mouseState, sizeof( DIMOUSESTATE2 ));
}

Engine::Input* Engine::Input::instance()
{
	static Input input;
	return &input;
}

void Engine::Input::init(HINSTANCE &hInst, HWND &hWnd)
{


	DirectInput8Create( hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_Input_Obj,
		NULL);

	m_Input_Obj->CreateDevice( GUID_SysKeyboard,
		&keyboard,
		NULL);

	m_Input_Obj->CreateDevice( GUID_SysMouse,
		&mouse,
		NULL);

	keyboard->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
	mouse->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE );
	keyboard->SetDataFormat(&c_dfDIKeyboard);
	mouse->SetDataFormat(&c_dfDIMouse2);

	
}

void Engine::Input::update()
{
	HRESULT hr;

	hr = mouse->Acquire();

	//check for failure to acquire mouse
	if( FAILED(hr) )
	{
		ZeroMemory(&mouseState, sizeof( DIMOUSESTATE2 ) );  //if mouse fails, clear the memory out
		hr = mouse->Acquire();								//and re-acquire
	}else													//else get the state of the mouse
		hr = mouse->GetDeviceState( sizeof( DIMOUSESTATE2 ), &mouseState); 
	
	hr = keyboard->Acquire();

	if( FAILED(hr) )							//if keyboard fails to acquire
	{
		ZeroMemory(buffer, sizeof(buffer) );	//clear keyboard buffer memory
		hr = keyboard->Acquire();				//and re-acquire
	}else										//else get the state of the keyboard
		hr = keyboard->GetDeviceState( sizeof(buffer),  (LPVOID)&buffer ); 

}


bool Engine::Input::push_button(unsigned char keycode)
{
	
	return ( buffer[keycode] & 0x80 )  != 0;

}

bool Engine::Input::check_button_down(unsigned char keycode)
{
	return key_down[keycode];
}

void Engine::Input::set_button(unsigned char keycode, bool change)
{
	key_down[keycode] = change;
}

long Engine::Input::get_mouseX()		
{
	/***return change in X */
	return mouseState.lX;  
}

long Engine::Input::get_mouseY()
{
	/**return change in Y */
	return mouseState.lY;
}

long Engine::Input::get_mouseZ()
{
	return mouseState.lZ;
}


bool Engine::Input::check_mouse_button(int mouse_button)
{
	return (mouseState.rgbButtons[mouse_button] & 0x80) != 0;

}



void Engine::Input::shutdown()
{
	mouse->Unacquire();
	if(mouse)
	{
		mouse->Release();
		mouse = 0;
	}
	
	
	keyboard->Unacquire();
	if(keyboard)
	{
		keyboard->Release();
		keyboard = 0;
	}
	if(m_Input_Obj != 0)
	{
		m_Input_Obj->Release();
		m_Input_Obj = 0;
	}
}

Engine::Input::~Input()
{

}