#ifndef __SOL_TEXTURE_MANAGER_H__
#define __SOL_TEXTURE_MANAGER_H__

/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 01.06.2004
Last Revised:	01.06.2004

Implementation File: TextureManager.cpp

Notes:
	
*/

/*

  Simple Texture Manager

*/

#define BMP_ID 0x4D42

#include <windows.h>
#include <stdio.h>

#include <gl/gl.h>
#include <gl/glu.h>

#include "Log.h"

namespace Sol
{
	const int MAX_TEXTURE_COUNT = 256;

	//simple struct containing texture data
	struct STextureData
	{
		std::string name;	//texture file name
		//only 24bit BMP implemented

		int width;	//texture width
		int height;	//texture height
		int bpp;	//texture bits per pixel

		unsigned char * texBuffer;	//texture data
		long dataSize;	//size of texture data

		unsigned int glID;	//OpenGL Texture ID

		STextureData():name(""),width(0),height(0),bpp(0),texBuffer(NULL),dataSize(0),glID(0)
		{}

		bool Load(const char * fileName);	//load texture
		void Unload();	//deinitialize

		void Bind()	//bind texture
		{
			glBindTexture(GL_TEXTURE_2D, glID);
		}
	};

	//main manager class

	class CTextureManager
	{
	protected:
		STextureData textures[MAX_TEXTURE_COUNT];	//texture list
		int nTextures;	//current texture count

	public:
		CTextureManager():nTextures(0){}
		~CTextureManager(){}

		bool Init();	//initialize
		bool DeInit();	//deinitialize

		int LoadTexture(const char *fileName);	//load texture from file
		void UnloadAll();	//unload all textures

		void BindTexture(int texID);	//bind selected texture
	};

} //end of namespace Sol

#endif //__SOL_TEXTURE_MANAGER_H__