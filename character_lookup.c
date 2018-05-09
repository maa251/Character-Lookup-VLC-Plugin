/*****************************************************************************
 * character_lookup.c : A filter that allows the user to lookup characters
 * based on facial recognition.
 *****************************************************************************

 *****************************************************************************
 * Copyright (C) 2018 Marouf Al Arnaout
 *
 * Authors: Marouf Al Arnaout <marnaout96@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# define N_(str) (str)
#endif

#include <limits.h>
#include <errno.h>

#include <vlc_common.h>
#include <vlc_plugin.h>
#include <vlc/libvlc_version.h>

#if LIBVLC_VERSION_MAJOR == 2 && LIBVLC_VERSION_MINOR == 1
# include "vlc_interface-2.1.0-git.h"
#elif LIBVLC_VERSION_MAJOR == 2 && LIBVLC_VERSION_MINOR == 2
# include "vlc_interface-2.2.0-git.h"
#elif LIBVLC_VERSION_MAJOR >= 3 && LIBVLC_VERSION_MINOR >= 0
# include <vlc_interface.h>
#else
# error "VLC version " LIBVLC_VERSION_MAJOR "." LIBVLC_VERSION_MINOR " is too old and won't be supported"
#endif

#include <vlc_filter.h>
#include <vlc_picture.h>
//#include "filter_picture.h"
#include <vlc_image.h>
#include <vlc_strings.h>
#include <vlc_fs.h>
#include <vlc_input.h>
#include <vlc_aout.h>
#include <vlc_vout.h>
#include <vlc_vout_osd.h>
#include <vlc_playlist.h>
#include <vlc_keys.h>





#define CFG_PREFIX "scene-"

/* Variables Declerations */
static bool take_pic = true;



/* Forward declarations */
static int Open(vlc_object_t *);
static void Close(vlc_object_t *);
static int OpenInterface(vlc_object_t *);
static void CloseInterface(vlc_object_t *);
static picture_t *Filter( filter_t *, picture_t * );
static void SavePicture( filter_t *, picture_t *);
static void CreatePicture(filter_t *, picture_t *);


/* Module descriptor */
vlc_module_begin()
    set_shortname(N_("Character"))
    set_description(N_("Character Lookup"))
#if LIBVLC_VERSION_MAJOR == 2
    set_capability("video filter2", 0)
#elif LIBVLC_VERSION_MAJOR >= 3
    set_capability("video filter", 0)
#endif
    set_callbacks(Open, Close)
    set_category(CAT_VIDEO)
    set_subcategory(SUBCAT_VIDEO_VFILTER)
    add_submodule()
        set_capability("interface", 0)
        set_category(CAT_INTERFACE)
        set_subcategory(SUBCAT_INTERFACE_CONTROL)
        set_callbacks(OpenInterface, CloseInterface)
vlc_module_end()

/* Internal state for an instance of the module */
struct intf_sys_t
{
    char *who;
};

static const char *const ppsz_vfilter_options[] = {
    "format", "width", "height", "ratio", "prefix", "path", "replace", NULL
};

typedef struct scene_t {
    picture_t       *p_pic;
    video_format_t  format;
} scene_t;

/*****************************************************************************
 * struct filter_sys_t: private data
 *****************************************************************************/
struct filter_sys_t
{
    image_handler_t *p_image;
    scene_t scene;

    char *psz_path;
    char *psz_prefix;
    char *psz_format;
    vlc_fourcc_t i_format;
    int32_t i_width;
    int32_t i_height;
    int32_t i_ratio;  /* save every n-th frame */
    int32_t i_frames; /* frames count */
    bool  b_replace;
};

static intf_thread_t *p_intf = NULL;

/*****************************************************************************
 * KeyEvent: Callback function for a keypress
 * Checks if keypress is equal to specified keyID and sets 
 * the take_pic bool to true if it is
 *****************************************************************************/
static int KeyEvent( vlc_object_t *libvlc, char const *psz_var,
vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    //CHECK HERE
    take_pic = true;
    openGui("","");
}

static int OpenInterface(vlc_object_t *p_this)
{
    p_intf = (intf_thread_t*) p_this;

    // Set keyboard input callback
    var_AddCallback(p_intf->p_libvlc, "key-pressed", KeyEvent, NULL );
    openGui("","");

    return VLC_SUCCESS;
}

static void CloseInterface(vlc_object_t *p_this)
{
    // UNUSED(p_this);

    p_intf = NULL;
}





/*****************************************************************************
 * Open (Create): initialize and set pf_video_filter()
 * Modified from scene.c
 *****************************************************************************/
static int Open( vlc_object_t *p_this )
{
    // Initialize necessary components for saving frames as images
    // Unchanged from scene.c
    filter_t *p_filter = (filter_t *)p_this;
    struct filter_sys_t *p_sys;

    const vlc_chroma_description_t *p_chroma =
        vlc_fourcc_GetChromaDescription( p_filter->fmt_in.video.i_chroma );
    if( p_chroma == NULL || p_chroma->plane_count == 0 )
        return VLC_EGENERIC;

    config_ChainParse( p_filter, CFG_PREFIX, ppsz_vfilter_options,
                       p_filter->p_cfg );

    p_filter->p_sys = p_sys = calloc( 1, sizeof( struct filter_sys_t ) );
    if( p_filter->p_sys == NULL )
        return VLC_ENOMEM;

    p_sys->p_image = image_HandlerCreate( p_this );
    if( !p_sys->p_image )
    {
        msg_Err( p_this, "Couldn't get handle to image conversion routines." );
        free( p_sys );
        return VLC_EGENERIC;
    }

    // Set Image Format to JPEG
    p_sys->psz_format = "png";
    p_sys->i_format = image_Type2Fourcc( p_sys->psz_format );
    if( !p_sys->i_format )
    {
        msg_Err( p_filter, "Could not find FOURCC for image type '%s'",
                 p_sys->psz_format );
        image_HandlerDelete( p_sys->p_image );
        free( p_sys->psz_format );
        free( p_sys );
        return VLC_EGENERIC;
    }
    //Initilialize properties of saved image
    p_sys->i_width = -1;
    p_sys->i_height = -1;
    p_sys->i_ratio = 1; // TODO: Remove i_ratio as it is no longer used
    p_sys->b_replace = true;
    p_sys->psz_prefix = "scene";
    p_sys->psz_path = "";

    p_filter->pf_video_filter = Filter;

    //vlc_mutex_init( &p_sys->lock );

    

    return VLC_SUCCESS;
}

/*****************************************************************************
 * Filter: Apply filtering logic to picture.
 *****************************************************************************/
static picture_t *Filter( filter_t *p_filter, picture_t *p_pic )
{
    
    // SnapshotRatio( p_filter, p_pic ); // Line from scene.c that isn't needed
    //CreatePicture(p_filter, p_pic);
    if (take_pic) 
        {
            take_pic = false;
            CreatePicture(p_filter, p_pic);
            
        }

    //Do Nothing until we get appropriate keyboard input
    return p_pic;
}

/*****************************************************************************
 * CreatePicture: Creates and saves the picture from the picture_t data
 * Modified from SnapshotRatio in scene.c
 *****************************************************************************/
static void CreatePicture(filter_t *p_filter, picture_t *p_pic)
{
    struct filter_sys_t *p_sys = (struct filter_sys_t *)p_filter->p_sys;
    if( !p_pic ) return;

    if( p_sys->scene.p_pic )
        picture_Release( p_sys->scene.p_pic );

    if( (p_sys->i_width <= 0) && (p_sys->i_height > 0) )
    {
        p_sys->i_width = (p_pic->format.i_width * p_sys->i_height) / p_pic->format.i_height;
    }
    else if( (p_sys->i_height <= 0) && (p_sys->i_width > 0) )
    {
        p_sys->i_height = (p_pic->format.i_height * p_sys->i_width) / p_pic->format.i_width;
    }
    else if( (p_sys->i_width <= 0) && (p_sys->i_height <= 0) )
    {
        p_sys->i_width = p_pic->format.i_width;
        p_sys->i_height = p_pic->format.i_height;
    }

    p_sys->scene.p_pic = picture_NewFromFormat( &p_pic->format );
    if( p_sys->scene.p_pic )
    {
        picture_Copy( p_sys->scene.p_pic, p_pic );
        SavePicture( p_filter, p_sys->scene.p_pic );
    }
}

/*****************************************************************************
 * Save Picture to disk
 * Modified from scene.c
 *****************************************************************************/
static void SavePicture( filter_t *p_filter, picture_t *p_pic )
{
    struct filter_sys_t *p_sys = (struct filter_sys_t *)p_filter->p_sys;
    video_format_t fmt_in, fmt_out;
    char *psz_filename = NULL;
    char *psz_temp = NULL;
    int i_ret;

    memset( &fmt_out, 0, sizeof(video_format_t) );

    /* Save snapshot psz_format to a memory zone */
    fmt_in = p_pic->format;
    fmt_out.i_sar_num = fmt_out.i_sar_den = 1;
    fmt_out.i_width = p_sys->i_width;
    fmt_out.i_height = p_sys->i_height;
    fmt_out.i_chroma = p_sys->i_format;

    /*
     * Save the snapshot to a temporary file and
     * switch it to the real name afterwards.
     */
    if( p_sys->b_replace )
        i_ret = asprintf( &psz_filename, "%s" DIR_SEP "%s.%s",
                          p_sys->psz_path, p_sys->psz_prefix,
                          p_sys->psz_format );
    else
        i_ret = asprintf( &psz_filename, "%s" DIR_SEP "%s%05d.%s",
                          p_sys->psz_path, p_sys->psz_prefix,
                          p_sys->i_frames, p_sys->psz_format );

    if( i_ret == -1 )
    {
        msg_Err( p_filter, "could not create snapshot %s", psz_filename );
        goto error;
    }

    i_ret = asprintf( &psz_temp, "%s.swp", psz_filename );
    if( i_ret == -1 )
    {
        msg_Err( p_filter, "could not create snapshot temporarily file %s", psz_temp );
        goto error;
    }

    /* Save the image */
    i_ret = image_WriteUrl( p_sys->p_image, p_pic, &fmt_in, &fmt_out,
                            psz_temp );
    if( i_ret != VLC_SUCCESS )
    {
        msg_Err( p_filter, "could not create snapshot %s", psz_temp );
    }
    else
    {
        /* switch to the final destination */
#if defined (_WIN32) || defined(__OS2__)
        vlc_unlink( psz_filename );
#endif
        i_ret = vlc_rename( psz_temp, psz_filename );
        if( i_ret == -1 )
        {
            msg_Err( p_filter, "could not rename snapshot %s: %s",
                     psz_filename, vlc_strerror_c(errno) );
            goto error;
        }
    }

error:
    free( psz_temp );
    free( psz_filename );
}

/*****************************************************************************
 * Close (Destroy): destroy video filter method
 * Modified from scene.c
 *****************************************************************************/
static void Close( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t *)p_this;
    struct filter_sys_t *p_sys = p_filter->p_sys;

    image_HandlerDelete( p_sys->p_image );

    if( p_sys->scene.p_pic )
        picture_Release( p_sys->scene.p_pic );
    free( p_sys->psz_format );
    free( p_sys->psz_prefix );
    free( p_sys->psz_path );
    free( p_sys );
}

/*****************************************************************************
 * OpenGui: Opens the Gui and passes it the filepath of
 * of the image and name of the show or movie
 *****************************************************************************/
static void OpenGui(char * filepath, char * media_name )
{
    system("/home/eece435l/EECE437/Individual_Project/build-character_lookup_gui-Desktop_Qt_5_9_1_GCC_64bit-Debug/character_lookup_gui");
}
