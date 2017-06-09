/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 01.06.2004
Last Revised:	02.06.2004

This is an Implementation File:

Notes:
	
*/

/*

  Simple Texture Manager

*/

#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <string>

#include "Log.h"
#include "TextureManager.h"

namespace Sol
{
	//=============================================
	//Function: Load()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 02.06.2004
	//
	//Returns: true on success, false on failure
	//Parameters: file name
	//Description:
	//	Creates new texture from given file (24bit BMP only)
	//=============================================
	bool STextureData::Load(const char * fileName)
	{
		if(texBuffer != NULL)	//overwriting over an existing texture
		{
			Unload();	//unload first
		}

		//load image

		name = fileName;

		FILE *fIn = fopen(fileName, "rb");	//open texture file in read-binary mode

		BITMAPFILEHEADER imgHeader;	//file header for .bmp file
		BITMAPINFOHEADER imgInfo;	//info header for .bmp

		//::fseek(fIn, grpHeader->offsetImageData ,SEEK_SET);	//goto beginnig of image data

		::fread(&imgHeader,sizeof(BITMAPFILEHEADER), 1, fIn);	//read bitmap file header

		if(imgHeader.bfType != BMP_ID) //is a valid BMP file
		{
			log.Error("STextureData::Load() - file is not a valid BMP image");
			::fclose(fIn);
			return false;
		}

		::fread(&imgInfo,sizeof(BITMAPINFOHEADER),1,fIn);	//read image info header

		//set reading pointer onto beginning of the image data
		//::fseek(fIn, grpHeader->offsetImageData ,SEEK_SET);	//goto beginnig of BMP header data
		::fseek(fIn,(imgHeader.bfOffBits /*+ sizeof(grpHeader)*/),SEEK_SET);	//jump to the beginning of BMP image data
		
		//set image properties
		width = imgInfo.biWidth;	//width
		height = imgInfo.biHeight;	//height
		bpp = imgInfo.biBitCount;	//bits per pixel

		log << "STextureData::Load() - Image widht: " << width <<" height: " << height <<" bpp: " << bpp <<"\n";

		texBuffer = new byte[(width * height * (bpp/8))];	//create buffer for image data

		if(texBuffer == NULL)	//failed to allocate memory
		{
			log.Error("STextureData::Load() - error allocating %d bytes of memory required for reading image", (width*height*bpp/8));
			::fclose(fIn);
			return false;
		}

		::fread(texBuffer, 1, imgInfo.biSizeImage, fIn);	//read image data

		dataSize = imgInfo.biSizeImage;

		if(texBuffer == NULL)	//failed to read image data
		{
			log.Error("STextureData::Load() - error reading image data\n");
		//	delete[] texBuffer;	//free used memory
			::fclose(fIn);
			return false;
		}

		//make texture

		glGenTextures(1, &glID); //generate textures
		glBindTexture(GL_TEXTURE_2D, glID);// bind

		log <<"Texture GL ID: " << glID <<"\n";

		//texture wrapping
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//texture filters
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		//generate texture
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, width, height,0, GL_RGB, GL_UNSIGNED_BYTE ,texBuffer);

		int mode = GL_RGB8;
		int mode2 = GL_BGR_EXT;
		if ((bpp/8)==4) mode = GL_RGBA8;
		if ((bpp/8)==4) mode2 = GL_BGRA_EXT;

		gluBuild2DMipmaps(GL_TEXTURE_2D, mode, width, height, mode2, GL_UNSIGNED_BYTE, texBuffer);
			
		::fclose(fIn);

		return true;
	}

	//=============================================
	//Function: Unload()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Deletes current texture and frees all resources
	//=============================================
	void STextureData::Unload()
	{
		if(texBuffer != NULL)	//still have texture data
		{
			delete[] texBuffer;	//delete image data
			texBuffer = NULL;	//set it to NULL for safety
		}

		dataSize = width = height = bpp = 0;

		//unbind texture!!!

	}


	//=============================================
	//TextureManager Functions
	//=============================================


	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: true on success; false on failure
	//Parameters: none
	//Description:
	//	Initializes Texture Manager
	//=============================================
	bool CTextureManager::Init()
	{
		log <<"CTextureManager::Init() - Initializing Texture Manager\n";
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: true on success; false on failure
	//Parameters: none
	//Description:
	//	Deinitializes Texture Manager, deletes all textures
	//=============================================
	bool CTextureManager::DeInit()
	{
		log <<"CTextureManager::DeInit() - Deinitializing Texture Manager\n";
		UnloadAll();	//unload all textures
		return true;
	}

	//=============================================
	//Function: LoadTexture()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: texture handle
	//Parameters: texture file name
	//Description:
	//	Loads a texture from file, and returns it`s handle. -1 if error occured.
	//=============================================
	int CTextureManager::LoadTexture(const char * fileName)
	{
		if( nTextures >= MAX_TEXTURE_COUNT )	//no place for new sprite
		{
			log.Error("CTextureManager::LoadTexture() - Texture limit of %d exceeded while loading texture %s", MAX_TEXTURE_COUNT, fileName);
			return -1;	//failure
		}

		//check if we already had loaded a texture with given name
		for(int i = 0 ; i < nTextures; ++i)
		{
			if(textures[i].name == std::string(fileName))	//found loaded one
			{
				return i;	//return valid handle
			}
		}

		if( !textures[nTextures].Load(fileName) )	//loading texture
		{
			log.Error("CTextureManager::LoadTexture() - Failed to load texture %s", fileName);
			//error handling
			return -1;
		}

		++nTextures;	//we`ve got a new texture => increment texture cout
		log <<"CTextureManager::LoadTexture() - loaded texture [" << fileName <<"] at position " << nTextures <<")\n";
		return (nTextures - 1);
	}

	//=============================================
	//Function: UnloadAll()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Deletes all textures
	//=============================================
	void CTextureManager::UnloadAll()
	{
		if(nTextures != 0)	//some textures remaining??
		{
			log << "CTextureManager::UnloadAll() - unloading all textures\n";
			for(int i = 0 ; i < nTextures ; i++)
			{
				textures[i].Unload();	//deinitialize texture
			}
			nTextures = 0;	//all textures unloaded
		}
	}

	//=============================================
	//Function: BindTexture()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: nothing
	//Parameters: texture handle
	//Description:
	//	Binds texture
	//=============================================
	void CTextureManager::BindTexture(int texID)
	{
		if(!((texID >= nTextures) && (texID < 0)))	//valid handle
		{
			textures[texID].Bind();	//bind texture
		}
	}


} //end of namespace Sol