////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_


///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define DIRECTINPUT_VERSION 0x0800


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


//////////////
// INCLUDES //
//////////////
#include <dinput.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	void ResetCursorPos();
	int GetMouseX();
	int GetMouseY();

	bool IsEscapePressed();

	// Movement functions
	bool IsDPressed();
	bool IsAPressed();
	bool IsWPressed();
	bool IsSPressed();
	bool IsUpPressed();
	bool IsDownPressed();

	// Texture selection functions
	bool Is0Pressed();
	bool Is1Pressed();
	bool Is2Pressed();
	bool Is3Pressed();
	bool Is4Pressed();
	bool Is5Pressed();
	bool Is6Pressed();
	bool Is7Pressed();
	bool Is8Pressed();
	bool Is9Pressed();

	// Alternative functions
	bool IsPgUpPressed();
	bool IsPgDownPressed();

private:
	bool ReadKeyboard();
	bool ReadMouse();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
};

#endif