/* vim: set filetype=c: */
#ifndef PASTEBOARD_H__3E4DFD467FC84B468A098D04CC2177E7
#define PASTEBOARD_H__3E4DFD467FC84B468A098D04CC2177E7

#include <stddef.h>  /* size_t */

#ifdef __APPLE__
    typedef struct Pasteboard* PasteboardRef;
#else
    typedef void *PasteboardRef;
#endif



void setPasteboard(PasteboardRef pasteboard, const char* data, size_t len);


#endif /* PASTEBOARD_H__3E4DFD467FC84B468A098D04CC2177E7 */
