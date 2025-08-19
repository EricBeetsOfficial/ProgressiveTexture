#include <PlatformBase.h>

#if (SUPPORT_OPENGL_UNIFIED) || (SUPPORT_OPENGL_CORE)
# if (UNITY_WIN)
#  include <gl3w/gl3w.h>
# elif (UNITY_ANDROID) || (UNITY_WEBGL)
# include <GLES2/gl2.h>
# elif (UNITY_IOS) || (UNITY_TVOS)
#	include <OpenGLES/ES2/gl.h>
# elif (UNITY_OSX)
#	include <OpenGL/gl3.h>
# elif (UNITY_LINUX)
#	define GL_GLEXT_PROTOTYPES
#	include <GL/gl.h>
# else
#	error Unknown platform
# endif
#endif

#if (SUPPORT_D3D11)
# include <d3d11.h>
#endif

#if (SUPPORT_D3D12)
# include <d3d12.h>
#endif

#if (SUPPORT_METAL)
// Need to be included in the .mm file
# import <Metal/Metal.h>
#endif

#if (SUPPORT_VULKAN)
# include <vulkan/vulkan.h>
#endif
