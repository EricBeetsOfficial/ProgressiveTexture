#include <PlatformBase.h>

#if defined (SUPPORT_OPENGL_UNIFIED) || defined(SUPPORT_OPENGL_CORE)
# if defined (UNITY_WIN)
#  include <gl3w/gl3w.h>
# elif defined (UNITY_ANDROID) || defined (UNITY_WEBGL)
# include <GLES2/gl2.h>
# elif defined (UNITY_IOS) || defined(UNITY_TVOS)
#	include <OpenGLES/ES2/gl.h>
# elif defined (UNITY_OSX)
#	include <OpenGL/gl3.h>
# elif defined (UNITY_LINUX)
#	define GL_GLEXT_PROTOTYPES
#	include <GL/gl.h>
# else
#	error Unknown platform
# endif
#endif

#if defined (SUPPORT_D3D11)
# include <d3d11.h>
#endif

#if defined (SUPPORT_D3D12)
# include <d3d12.h>
#endif

#if defined (SUPPORT_METAL)
// Need to be included in the .mm file
// # import <Metal/Metal.h>
#endif

#if defined (SUPPORT_VULKAN)
//# include <vulkan/vulkan.h>
#endif
