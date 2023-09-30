#include <fstream>

#define _ITERATOR_DEBUG_LEVEL 0
#define BX_CONFIG_DEBUG 0;
#include "bx/bx.h"
#include "bx/readerwriter.h"
#include "bimg/bimg.h"
#include "bgfx/bgfx.h"


//namespace rocket_lab {

	bgfx::ShaderHandle loadShader(const char* _name) {
		char* data = new char[2048];
		std::ifstream file;
		size_t fileSize;
		file.open(_name);
		if (file.is_open()) {
			file.seekg(0, std::ios::end);
			fileSize = file.tellg();
			file.seekg(0, std::ios::beg);
			file.read(data, fileSize);
			file.close();
		}
		const bgfx::Memory* mem = bgfx::makeRef(data, fileSize + 1);
		mem->data[mem->size - 1] = '\0';
		bgfx::ShaderHandle handle = bgfx::createShader(mem);
		bgfx::setName(handle, _name);
		return handle;
	}
//}