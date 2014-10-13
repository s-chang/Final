#pragma once
#define _CTR_SECURE_NO_WARNINGS

#include <d3dx9.h>
#include <stdio.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <string>
#include "Drawable.h"

#define MAX_BUFFER 256

typedef ID3DXFont* pFont;
typedef D3DCOLOR dColor;

namespace Engine
{
	class Text
	{
	private:

		RECT rect;

		wchar_t buffer[MAX_BUFFER];
		dColor color;

		Text();

	public:
		~Text();
		pFont font;
		static Text* instance();

		void init();

		/**
		Name:		setText
		Parameters:	LPCWSTR text - the string to be drawn
		Return:		void
		Description: Sets the buffer to the given text.
		*/
		void setText(LPCWSTR text);

		void setText(int num);

		/**
		Name:		render
		Parameters:	long top - the top of the text placement
					long left - the left of the text placement
		Return:		void
		Description: Renders the text at the location of top and left
		*/
		void render(long top, long left);

		/**
		Name:		render
		Parameters: long top - the top of the text placement
					long left - the left of the text placement
					wchar_t word - the word to be drawn
					D3DCOLOR color - the color the text will be
		Return:		void
		Description: Draws the given text at the location of top and left in the given color
		*/
		void render(long top, long left, wchar_t* word, dColor color);
		void render(long top, long left, std::string word, dColor color);
		void render(Drawable &word);

		/**
		Name:		setColor
		Parameter:	D3DCOLOR color
		return:		void
		description: changes the color of the text.
		*/

		void setColor(dColor color);


		void shutdown();

		//TODO: read text from file.

	};
};