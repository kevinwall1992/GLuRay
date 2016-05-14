#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>

#include "defines.h"

#include "next_declarations.c"
#include "function_map.c"

#include "enum_tables.c"

char *getEnumString(GLenum value)
{
  int i;
  for(i= 0; i< sizeof(enum_translations)/ sizeof(EnumTranslation); i++)
    if(enum_translations[i].value== value)
      return enum_translations[i].name;
    
  return "Enum not found!";
}

void debugPrint(const char *format, ...)
{
#if DEBUG_GL
  va_list arguments;
  va_start (arguments, format);
  vfprintf (stderr, format, arguments);
  va_end (arguments);
#endif
}

void printGLError()
{
#if INTERCEPT_GL_ERRORS
  
  GLenum error= next_glGetError();
  while(error!= GL_NO_ERROR)
  {
    debugPrint("OpenGL Error: %s\n", getEnumString(error));
    error= next_glGetError();
  }
#endif
}

static void initializeInterception(void) __attribute__ ((__constructor__));

int is_initialized= 0;

static void initializeInterception(void)
{
  if(is_initialized)
    return;
  
    int i;
    for(i= 0; function_map[i].pointer!= NULL; i++)
      *(function_map[i].pointer)= dlsym(RTLD_NEXT, function_map[i].name);
    
    is_initialized= 1;
}

//http://stackoverflow.com/questions/15599026/how-can-i-intercept-dlsym-calls-using-ld-preload
extern void *_dl_sym(void *, const char *, void *);
extern void *dlsym(void *handle, const char *name)
{
  if (next_dlsym == NULL)
    next_dlsym= _dl_sym(RTLD_NEXT, "dlsym", dlsym);
  
  if (strcmp(name, "dlsym")== 0) 
    return (void *)dlsym;
  
  if(handle!= RTLD_NEXT && is_initialized)
  {
    int i;
    for(i= 0; function_map[i].pointer!= NULL; i++)
    {
      if(strcmp(name, function_map[i].name)== 0)
      {
        void *intercept_pointer= next_dlsym(RTLD_DEFAULT, name);
        
        return intercept_pointer;
      }
    } 
  }
 
  return next_dlsym(handle, name);
}


__GLXextFuncPtr (*next_glXGetProcAddressARB)(const GLubyte* procName) = NULL;
__GLXextFuncPtr glXGetProcAddressARB(const GLubyte* procName) {
  if(next_glXGetProcAddressARB== NULL)
  {
    next_glXGetProcAddressARB= dlsym(RTLD_NEXT, "glXGetProcAddressARB");
    if(next_glXGetProcAddressARB== NULL)
      next_glXGetProcAddressARB= dlsym(RTLD_NEXT, "glXGetProcAddress");
  }

  void *pointer= dlsym(RTLD_DEFAULT, procName);
  if(pointer== NULL)
    pointer= next_glXGetProcAddressARB(procName);
  return pointer;
}

__GLXextFuncPtr glXGetProcAddress(const GLubyte* procName) {
  return glXGetProcAddressARB(procName);
}

#include "intercepts.c"
#include "passthrough_intercepts.c"
