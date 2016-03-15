#pragma once

#include "pfx.h"

#include <ncurses.h>

namespace gfx {
	typedef enum{
		BUF_ACT_CLEAR_DISP = 0x01,
		BUF_ACT_CLEAR_STEN = 0x02,
	} BufferAction_t;

	typedef struct{
		uint8_t display, stencil;

		int operator<<(const uint8_t c)
		{
			this->display = c;
			return ++this->stencil;
		}
		int operator++()
		{
			return ++this->stencil;
		}
	} glyph_t;

	typedef struct{
		glyph_t **data;
		uint16_t width, height;

		glyph_t* operator[](const int x){ return data[x]; }

		void action(BufferAction_t action)
		{
			// clearing behaviors
			if(BIT_SET(action, BUF_ACT_CLEAR_DISP))
			for(int i = this->width; i--;){
				for(int j = this->height; j--;){
					data[i][j].display = 0;
				}
			}
			
			if(BIT_SET(action, BUF_ACT_CLEAR_STEN))
			for(int i = this->width; i--;){
				for(int j = this->height; j--;){
					this->data[i][j].stencil = 0;
				}
			}
		};
	} Buffer_t;

	extern Buffer_t CUR_BUF;

	//    ___             _   _             
	//   | __|  _ _ _  __| |_(_)___ _ _  ___
	//   | _| || | ' \/ _|  _| / _ \ ' \(_-<
	//   |_| \_,_|_||_\__|\__|_\___/_||_/__/
	//                                      
	static Buffer_t BufferAlloc(int width, int height);
	static void     BufferFree(Buffer_t*);
}
