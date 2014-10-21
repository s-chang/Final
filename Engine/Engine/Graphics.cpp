#include "Graphics.h"
#include <fstream>
#include "DX.h"
#include "Cursor.h"

//helper function
std::wstring string2wstring( const std::string word)
{
	int length;
	int slength = (int)word.length() + 1;
	length = MultiByteToWideChar(CP_ACP, 0, word.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[length];
	MultiByteToWideChar(CP_ACP, 0, word.c_str(), slength, buf, length);
	std::wstring wWord(buf);
	delete[] buf;
	return wWord;
}

Engine::Graphics::Graphics()
{}

Engine::Graphics::~Graphics()
{}

Engine::Graphics* Engine::Graphics::instance()
{
	static Graphics instance;
	return &instance;
}

void Engine::Graphics::init()
{
	loadImages();
	loadMesh();

	light.defaultInit();
	light.setLight();

	cam.init(800,600);	
	cam.setProj();
	
	//TODO: create a shader manager
#ifdef _DEBUG
	D3DXCreateEffectFromFile(Engine::DX::instance()->getDevice(),
		L"Shader.fx", 0, 0, D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION,
		0, &m_Effect, &m_EffectError);
#else
	D3DXCreateEffectFromFile(Engine::DX::instance()->getDevice(),
		L"Shader.fx", 0, 0, 0, 0, &m_Effect, &m_ErrorEffect);
#endif

	m_Effect->SetFloatArray("eyePos", (float*)cam.getEyePos(), 3);
	m_Effect->SetFloatArray("lightPos", (float*)light.getPosition(), 3);
	m_Effect->SetFloatArray("ambientLight", (float*)light.getAmbient(), 3);
	m_Effect->SetFloatArray("specularLight", (float*)light.getSpecular(), 3);
	m_Effect->SetFloatArray("diffuseLight", (float*)light.getDiffuse(), 3);
	m_Effect->SetFloatArray("lightAttenuation", (float*)&D3DXVECTOR3(light.getAttenuation0(), light.getAttenuation1(), light.getAttenuation2()), 3);
	
}

void Engine::Graphics::render(Drawable object, Camera *cam)
{
	D3DXMATRIX transMat, scaleMat, rotMat, worldMat;

	D3DXMatrixIdentity(&transMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&worldMat);


	if(!object.get3D())
	{
		D3DXMatrixScaling(&scaleMat, object.getScale().x, object.getScale().y, object.getScale().z);
		D3DXMatrixTranslation(&transMat, object.getTranslate().x, object.getTranslate().y, object.getTranslate().z);
		D3DXMatrixRotationYawPitchRoll(&rotMat, D3DXToRadian(object.getRotate().y),D3DXToRadian(object.getRotate().x), D3DXToRadian(object.getRotate().z));
		D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
		D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

		Engine::DX::instance()->getSprite()->SetTransform(&worldMat);

		Engine::DX::instance()->getSprite()->Draw(
			getTexture(object.getHandle()),
			object.getIsSpriteSheet() ? &object.getRect() : 0,
			object.getIsSpriteSheet() ? &dVec3(object.getWidth() * 0.5f, object.getHeight() * 0.5f, 0.0f) : &dVec3(getInfo(object.getHandle()).Width *0.5f, getInfo(object.getHandle()).Height *0.5f, 0.0f),
			0,
			object.getColor());
	}

	if(object.get3D())
	{
		//camera.setLookAt(object.getTranslate().x, object.getTranslate().y, object.getTranslate().z);
		//camera.setProj(800,600);

		D3DXMATRIX WIT;		

		UINT numPasses = 0;
		m_Effect->Begin(&numPasses, 0);

		Mesh *tempMesh = getMesh(object.getHandle());
		 

		for(UINT i = 0; i < numPasses; i++)
		{
			m_Effect->BeginPass(i);

			D3DXMatrixScaling(&scaleMat, object.getScale().x, object.getScale().y, object.getScale().z);
			D3DXMatrixTranslation(&transMat, object.getTranslate().x, object.getTranslate().y, object.getTranslate().z);
			D3DXMatrixRotationYawPitchRoll(&rotMat, D3DXToRadian(object.getRotate().y),D3DXToRadian(object.getRotate().x), D3DXToRadian(object.getRotate().z));
			D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
			D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

			D3DXMatrixInverse(&WIT, 0, &worldMat);
			D3DXMatrixTranspose(&WIT, &WIT);
			m_Effect->SetMatrix("worldViewProjMat", &(worldMat * cam->getView() * cam->getProjection()));
			m_Effect->SetMatrix("worldInverseTransposeMat", &WIT);
			m_Effect->SetMatrix("worldMat", &worldMat);

			for(DWORD i = 0; i < tempMesh->getNumMaterials(); i++)
			{
				m_Effect->SetValue("ambientMaterial", &tempMesh->getMeshMaterial()[i].Ambient, sizeof(D3DXCOLOR));
				m_Effect->SetValue("diffuseMaterial", &tempMesh->getMeshMaterial()[i].Diffuse, sizeof(D3DXCOLOR));
				m_Effect->SetValue("specularMaterial", &tempMesh->getMeshMaterial()[i].Specular, sizeof(D3DXCOLOR));
				m_Effect->SetFloat("specularPower", tempMesh->getMeshMaterial()[i].Power);
				
				if(object.getHasTexture())
				{
					m_Effect->SetTexture("tex", tempMesh->getMeshTexture()[i]);
					m_Effect->SetBool("isTex", true);
				}else
					m_Effect->SetBool("isTex", false);

				m_Effect->CommitChanges();
				tempMesh->getMesh()->DrawSubset(i);
			}

			m_Effect->EndPass();

			//tempMesh = nullptr;
		}
		m_Effect->End();
	}
}

void Engine::Graphics::shutdown()
{
	for(auto& image: imageStorage)
	{
		SAFE_RELEASE(image.second.texture);
	}
	imageStorage.clear();

	for(auto& mesh: meshStorage)
	{
		mesh.second.shutdown();
	}
	meshStorage.clear();

	SAFE_RELEASE(adjBuffer);
	SAFE_RELEASE(error);
	SAFE_RELEASE(m_EffectError);
	SAFE_RELEASE(m_Effect);

}

void Engine::Graphics::loadImages()
{
	ImageValue temp_storage;

	std::string temp_file_name;
	std::string temp_handle;
	//LPCWSTR rFilename;

	struct temp_Data
	{
		std::string temp_handle;
		std::wstring temp_file_name;
	};

	std::vector<temp_Data> tempStorageData;

	//TODO: read from text file
	std::ifstream file("Textures2D.txt");
	//std::wstring wtemp;

	//read til end of file
	while(!file.eof())
	{
		//store file name and handle to the file in temp variables
		file >> temp_file_name >> temp_handle;

		//create a temporary struct to hold data

		temp_Data some_data;
		some_data.temp_file_name = L"";
		some_data.temp_handle = temp_handle;

		//convert string to LPCWSTR 
		some_data.temp_file_name = std::wstring(temp_file_name.begin(), temp_file_name.end());
		//LPCWSTR stemp = wtemp.c_str();
		//some_data.temp_file_name = stemp;
		//wtemp = string2wstring(temp_file_name);
		//some_data.temp_file_name = wtemp.c_str();


		//push back the data
		tempStorageData.push_back(some_data);


	}
	//end of file, close file
	file.close();

	//Iterate through temporary data storage to create textures
	for(unsigned int i = 0; i < tempStorageData.size(); i++)
	{
		D3DXCreateTextureFromFileEx(Engine::DX::instance()->getDevice(),
			tempStorageData[i].temp_file_name.c_str(), 0, 0, 0, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
			D3DCOLOR_XRGB(255,255,255), &temp_storage.info, 0, &temp_storage.texture);
		//temp_storage.handle = tempStorageData[i].temp_handle;

		imageStorage[tempStorageData[i].temp_handle] = temp_storage;
		//set pointer to nullptr before reusing
		temp_storage.texture = nullptr;
	}

	//TODO sort storage

	//Create Error texture to show errors
	D3DXCreateTextureFromFileEx(Engine::DX::instance()->getDevice(),
		L"error.png", 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255,255,255), &errorinfo, 0, &error);

}

void Engine::Graphics::loadMesh()
{

	std::string temp_handle;
	std::string temp_filename;

	//Temp struct to hold information
	struct temp_data
	{
		std::string temp_data_handle;
		std::wstring temp_data_filename;
	};

	std::vector<temp_data> temp_data_storage;

	//open file containing data 
	std::ifstream file("Meshes.txt");

	//loop to the end of the file
	while(!file.eof())
	{
		//store file name and handle in temp variables
		file >> temp_filename >> temp_handle ;

		//create instance of temp_data to hold data
		temp_data temp_store;

		//convert string to wstring
		temp_store.temp_data_filename = std::wstring(temp_filename.begin(), temp_filename.end());
		temp_store.temp_data_handle = temp_handle;

		//push object into temp storage
		temp_data_storage.push_back(temp_store);

	}

	//end of file, close file
	file.close();

	//iterate through temp storage to create meshes
	for(unsigned int i = 0; i < temp_data_storage.size(); i++)
	{
		//Temp storage used to load data needed
		std::string tempString;
		Mesh tempMesh;


		//temp_storage = new MeshStorage;
		tempString = temp_data_storage[i].temp_data_handle;
		tempMesh.loadTexturedMesh(temp_data_storage[i].temp_data_filename.c_str(), adjBuffer);

		meshStorage[tempString] = tempMesh;
		//clear temp storage mesh before reuse
		//TODO: FIX MEMORY LEAK
		//temp_storage.mesh.shutdown();	

	}

	//TODO: create an error mesh in case a mesh can't be found

}

pDirectTexture Engine::Graphics::getTexture(const std::string handle)
{
	if (imageStorage.find(handle) != imageStorage.end())
		return imageStorage[handle].texture;
	else
		return error;
}

iInfo Engine::Graphics::getInfo(const std::string handle)
{
	if (imageStorage.find(handle) != imageStorage.end())
		return imageStorage[handle].info;
	else
		return errorinfo;
}

Mesh* Engine::Graphics::getMesh(const std::string handle)
{
	if (meshStorage.find(handle) != meshStorage.end())
		return &meshStorage[handle];
	else
		return NULL;
}

void Engine::Graphics::Draw2DObject(Drawable & object){
	D3DXMATRIX transMat, scaleMat, rotMat, worldMat;

	D3DXMatrixIdentity(&transMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&worldMat);

	D3DXMatrixScaling(&scaleMat, object.getScale().x, object.getScale().y, object.getScale().z);
	D3DXMatrixTranslation(&transMat, object.getTranslate().x, object.getTranslate().y, object.getTranslate().z);
	D3DXMatrixRotationYawPitchRoll(&rotMat, D3DXToRadian(object.getRotate().y),D3DXToRadian(object.getRotate().x), D3DXToRadian(object.getRotate().z));
	D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
	D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

	Engine::DX::instance()->getSprite()->SetTransform(&worldMat);

	Engine::DX::instance()->getSprite()->Draw(
		getTexture(object.getHandle()),
		object.getIsSpriteSheet() ? &object.getRect() : 0,
		object.getIsSpriteSheet() ? &dVec3(object.getWidth() * 0.5f, object.getHeight() * 0.5f, 0.0f) : &dVec3(getInfo(object.getHandle()).Width *0.5f, getInfo(object.getHandle()).Height *0.5f, 0.0f),
		0,
		object.getColor());
}

void Engine::Graphics::drawCursor(){
	Cursor* c = Engine::Cursor::instance();

	D3DXMATRIX transMat, scaleMat, rotMat, worldMat;

	D3DXMatrixIdentity(&transMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&worldMat);

	D3DXMatrixScaling(&scaleMat, 1, 1, 1);
	D3DXMatrixTranslation(&transMat, c->cursorPos.x, c->cursorPos.y, 0);
	D3DXMatrixRotationYawPitchRoll(&rotMat, 0,0, 0);
	D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
	D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

	Engine::DX::instance()->getSprite()->SetTransform(&worldMat);

	Engine::DX::instance()->getSprite()->Draw(
		getTexture(c->getHandle()), 0,
		&dVec3(getInfo(c->getHandle()).Width *0.5f, getInfo(c->getHandle()).Height *0.5f, 0.0f), 0,
		D3DCOLOR_ARGB(255,255,255,255));
}