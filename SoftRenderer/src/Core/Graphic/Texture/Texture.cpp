#include "Texture.h"

#include "png.h"

#include <setjmp.h>


#define PNG_READ_SUCCESS 0
#define PNG_ERROR_NO_FILE 1
#define PNG_ERROR_NOT_PNG 2
#define PNG_ERROR_CREATE_PNG_STRUCT 3
#define PNG_ERROR_CREATE_INFO_STRUCT 4
#define PNG_ERROR_JMP 5

#define PNG_READ_HEADER 4

int read_chunk_callback(png_structp ptr,png_unknown_chunkp chunk) {
	return 1;
}

void read_row_callback(png_structp ptr,png_uint_32 row,int pass) {

}

int png_read(const char* filename, png_datap data) {
	FILE *fp = fopen(filename,"rb");
	if(fp == NULL) return PNG_ERROR_NO_FILE;

	fseek(fp,0,SEEK_END);
	int fSize = ftell(fp);
	rewind(fp);
	unsigned char* header = (unsigned char*)malloc(PNG_READ_HEADER);
	fread(header,1,PNG_READ_HEADER,fp);
	int is_png = !png_sig_cmp(header,0,PNG_READ_HEADER);
	if(!is_png) return PNG_ERROR_NOT_PNG;

	png_structp png_ptr;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL, NULL, NULL);
	if(!png_ptr) return PNG_ERROR_CREATE_PNG_STRUCT;

	png_infop info_ptr;
	info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr) {
		printf("create info struct failed!\n");
		png_destroy_read_struct(&png_ptr,NULL,NULL);
		return PNG_ERROR_CREATE_INFO_STRUCT;
	}
	png_infop end_info;
	end_info = png_create_info_struct(png_ptr);
	if(!end_info) {
		printf("create end info failed!\n");
		png_destroy_read_struct(&png_ptr,NULL,NULL);
		return PNG_ERROR_CREATE_INFO_STRUCT;
	}
	if(setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr,&info_ptr,&end_info);
		return PNG_ERROR_JMP;
	}
	png_init_io(png_ptr,fp);
	png_set_sig_bytes(png_ptr,PNG_READ_HEADER);
	// png_voidp user_chunk_ptr = png_get_user_chunk_ptr(png_ptr);
	// png_set_read_user_chunk_fn(png_ptr,user_chunk_ptr,read_chunk_callback);
	// png_set_keep_unknown_chunks(png_ptr,PNG_HANDLE_CHUNK_NEVER,NULL,0);

	//png_set_read_status_fn(png_ptr,read_row_callback);

	//low lever read
	png_read_info(png_ptr,info_ptr);
	png_uint_32 width;
	png_uint_32 height;
	int bit_depth;
	int color_type;
	png_get_IHDR(png_ptr,info_ptr,&width,&height,&bit_depth,&color_type,NULL,NULL,NULL);
	// printf("width:%d,height:%d,bit_depth:%d,color_type:%d",width,height,bit_depth,color_type);

	png_bytep raw_data = (png_bytep)malloc(width*height*4*sizeof(png_byte));
	// printf("row bytes:%d\n",png_get_rowbytes(png_ptr,info_ptr));

	png_bytep *row_pointers = (png_bytep*)malloc(height*sizeof(png_bytep));
	for(int i=0; i<height; i++) {
		row_pointers[i] = raw_data+ i* (width * 4);
	}
	png_read_image(png_ptr,row_pointers);

	data->width = width;
	data->height = height;
	data->data = (unsigned char*)raw_data;
	// printf("png_read_success\n");

	//clean
	fclose(fp);
	png_destroy_read_struct(&png_ptr,&info_ptr,&end_info);
	free(row_pointers);

	return PNG_READ_SUCCESS;
}

void Texture::Load(const std::string &path) {
	png_read(path.c_str(), _data);
}

<<<<<<< HEAD
Color Texture::GetColor(const Vector2f &uv, FilterType filter)
{
    auto u = uv.x * (_data->width-1);
    auto v = uv.y * (_data->height-1);
    switch (filter) {
        case Point:
            return Sample((int)(u), (int)(v));
            break;
        case Bilinear:
        {
            int u1 = floor(u);
            int u2 = ceil(u);
            int v1 = floor(v);
            int v2 = ceil(v);
            auto c1 = Sample(u1, v1);
            auto c2 = Sample(u1, v2);
            auto ret1 = Lerp(c1, c2, v - v1);
            c1 = Sample(u2, v1);
            c2 = Sample(u2, v2);
            auto ret2 = Lerp(c1, c2, v - v1);
            return Lerp(ret1, ret2, u - u1);
            break;
        }
        default:
            return Sample((int)(u), (int)(v));
            break;
    }
}

Color Texture::Sample(int x, int y) { 
    Color ret;
    if (_data)
    {
        if (x >= _data->width || y >= _data->height)
            return Color(1.0f, 0.0f, 0, 1);
        
        if (x < 0 || y < 0)
            return Color(0.0f, 1.0f, 0, 1);
        
        auto tmp = 1.0f / 255.0f;
        int idx = x * _data->width * 4 + y * 4;
        ret.r = _data->data[idx] * tmp;
        ret.g = _data->data[idx+1] * tmp;
        ret.b = _data->data[idx+2] * tmp;
        ret.a = 1.0f;
        return ret;
//        return Color(0.0f, 1.0f, 0, 1);
    }
    return ret;
=======
Color Texture::GetColor(const Vector2f &uv) {
	Color ret;
	if (_data) {
		int row = _data->height - (int)(uv.y * (_data->height - 1)) - 1;
		int col = (int)(uv.x * (_data->width - 1));
		int idx = row * _data->width * 4 + col * 4;
		ret.r = _data->data[idx] / 255.0f;
		ret.g = _data->data[idx+1] / 255.0f;
		ret.b = _data->data[idx+2] / 255.0f;
		ret.a = 1.0f;
	}
	return ret;
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
}

