#ifndef DEM_STRUCT_DEFINED
typedef struct _dem {
  //width and height
  unsigned int width, height;
  //image data
  unsigned short ** image_data;
} DEM;
#define DEM_STRUCT_DEFINED 1
#endif
