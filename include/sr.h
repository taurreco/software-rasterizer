
#include <stdint.h>
#include <stddef.h>

#ifndef SR_H
#define SR_H

#define SR_MAX_ATTRIBUTE_COUNT 32                   

#define SR_PRIMITIVE_TYPE_POINT_LIST 0x1
#define SR_PRIMITIVE_TYPE_LINE_LIST 0x2
#define SR_PRIMITIVE_TYPE_LINE_STRIP 0x3
#define SR_PRIMITIVE_TYPE_TRIANGLE_LIST 0x4
#define SR_PRIMITIVE_TYPE_TRIANGLE_STRIP 0x5

#define SR_PRIMITIVE_SIZE_POINT 1
#define SR_PRIMITIVE_SIZE_LINE 2
#define SR_PRIMITIVE_SIZE_TRIANGLE 3

#define SR_CLIP_LEFT_PLANE 1 << 0
#define SR_CLIP_BOTTOM_PLANE 1 << 1
#define SR_CLIP_NEAR_PLANE 1 << 2
#define SR_CLIP_RIGHT_PLANE 1 << 3
#define SR_CLIP_TOP_PLANE 1 << 4

/*********************************************************************
 *                                                                   *
 *                             typedefs                              *
 *                                                                   *
 *********************************************************************/

typedef void (*vs_f)(void* uniform, float* in, float* out);
typedef void (*fs_f)(void* uniform, float* in, uint32_t* out);

/*********************************************************************
 *                                                                   *
 *                      public data structures                       *
 *                                                                   *
 *********************************************************************/

struct sr_std_uniform;      /* hidden from end user bc it uses internal matrix data */

struct sr_framebuffer {
    size_t width, height;                           /* width, height */
    uint32_t* colors;                                 /* colors */
    float* depths;                                    /* depths */
};

struct sr_camera {
    size_t vport, nplane;
    size_t fplane, fov;
};

struct sr_pipeline_context {
    
    struct sr_framebuffer* fbuf;
    struct sr_camera* cam;

    void* uniform;        
    vs_f vs;
    fs_f fs;

    float* pts_in;
    size_t num_pts;
    size_t num_attr_in;
    size_t num_attr_out;

    size_t winding_order;
};

/*********************************************************************
 *                                                                   *
 *                       public declarations                         *
 *                                                                   *
 *********************************************************************/

/* render interface */
void sr_draw_indexed(struct sr_pipeline_context* pipe,  
                     size_t* indices, 
                     size_t num_indices,
                     size_t prim_type);


#endif /* SR_H */
