#include <Carbon/Carbon.h>
#include <dlfcn.h>  /* dlsym */


#define ERROR_FILE "/tmp/my_set_pasteboard"


void error(const char* fmt, ...) {
    va_list ap;
    FILE *f = fopen(ERROR_FILE, "a");

    va_start(ap, fmt); 
    vfprintf(f, fmt, ap);
    va_end(ap);

    fclose(f);
}


/* got this from ``reattach-to-user-namespace`` */
bool reattach_user_namespace() {
    static const char fn[] = "_vprocmgr_move_subset_to_user";
    void *(*f)();
    if (!(f = (void *(*)()) dlsym(RTLD_NEXT, fn))) {
        return false;
    }
    
    void *r;
    static const char bg[] = "Background";
    void *(*func)(uid_t, const char *, uint64_t) = f;
    r = func(getuid(), bg, 0);

    return true;
}


/* This is simple a copy of the os x pasteboard example.
 *
 * It's legacy code, maybe I should change this to Cocoa objective-c API.
 */
void setPasteboard(PasteboardRef pasteboard, const char* data, size_t len) {
    OSStatus err = noErr;
    PasteboardSyncFlags syncFlags;
    CFDataRef textData = NULL;
    int stat = 0;

    if (!reattach_user_namespace()) {
        error("reattach fail\n");
    }

    if (!pasteboard) {
        err = PasteboardCreate(kPasteboardClipboard, &pasteboard);
        require_noerr(err, CantCreatePasteboard);
    }

    err = PasteboardClear(pasteboard);
    require_noerr(err, CantClearPasteboard);

    syncFlags = PasteboardSynchronize(pasteboard);
    require_action(!(syncFlags&kPasteboardModified),
                   PasteboardNotSynchedAfterClear,
                   err = badPasteboardSyncErr);
    require_action((syncFlags&kPasteboardClientIsOwner),
                   ClientNotPasteboardOwner,
                   err = notPasteboardOwnerErr);


    textData = CFDataCreate(kCFAllocatorDefault,
                            (UInt8*)data, len);
    require_action(textData != NULL, CantCreateTextData, err = memFullErr);

    err = PasteboardPutItemFlavor(
            pasteboard, (PasteboardItemID)1, CFSTR("public.utf8-plain-text"),
            textData, 0);
    require_noerr(err, CantPutTextData);

    stat++;
CantCreatePasteboard:
    stat++;
CantPutTextData:
    stat++;
CantCreateTextData:
    stat++;
CantGetDataFromTextObject:
    stat++;
CantSetPromiseKeeper:
    stat++;
ClientNotPasteboardOwner:
    stat++;
PasteboardNotSynchedAfterClear:
    stat++;
CantClearPasteboard:
    stat++;

    if (err != noErr) {
        error("%s\n", GetMacOSStatusErrorString(err));
        error("%s\n", GetMacOSStatusCommentString(err));
        error("%d\n", stat);
    }
}
