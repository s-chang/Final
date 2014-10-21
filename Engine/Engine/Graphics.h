#pragma once
#include "Drawable.h"

#include <string>
#include <map>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

typedef IDirect3DTexture9* pDirectTexture;
typedef D3DXIMAGE_INFO iInfo;


namespace Engine
{
	class Graphics
	{
	private:
		Camera cam;
		Light light;
		ID3DXBuffer*	m_EffectError;
		ID3DXEffect*	m_Effect;
		D3DXHANDLE		m_tech;
		pBuffer			adjBuffer;

		pDirectTexture error;
		iInfo errorinfo;

		struct ImageValue
		{
			pDirectTexture texture;
			iInfo	info;
		};

		std::map<std::string, ImageValue> imageStorage;
		std::map<std::string, Mesh> meshStorage;

		void loadImages();
		void loadMesh();

		Graphics();
	public:
		static Graphics* instance();
		~Graphics();

		void init();
		void shutdown();

		void render(Drawable object, Camera *cam);
		void Draw2DObject(Drawable & object);
		void drawCursor();

		pDirectTexture getTexture(const std::string handle);
		iInfo getInfo(const std::string handle);
		Mesh* getMesh(const std::string handle);
	};
};
