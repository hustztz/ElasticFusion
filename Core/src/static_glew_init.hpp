/*
Function to get, find, or initialize Pangolin context and initialize glew
*/

#if !defined(__STATIC_GLEW_INIT_HPP__)
#define __STATIC_GLEW_INIT_HPP__
#define GLEW_STATIC
#include <pangolin/pangolin.h>
#include <pangolin/gl/gl.h>
#include <pangolin/gl/glplatform.h>
#include <pangolin/display/display_internal.h>
#include <string>

static inline void staticGlewInit(std::string name = "Main")
{
    // GetCurrentContext
    pangolin::PangolinGl* context = pangolin::GetCurrentContext();
    if (context == NULL)
    {
        // Find Context
        context = pangolin::FindContext(name);
        if (context == NULL)
        {
            // Create new
            std::shared_ptr<pangolin::PangolinGl> newcontext(new pangolin::PangolinGl());
            AddNewContext(name, newcontext);
            context = newcontext.get();
            std::cout << "Pangolin Context" << name << "created." << std::endl;
        }
        else
        {
            std::cout << "Pangolin Context" << name << "already exists." << std::endl;
        }
        // Make Current Context
        context->MakeCurrent();

        //  Initialize GLEW
        glewExperimental = GL_TRUE; // GL_FALSE; 
        GLenum error = glGetError();

        if (error != GL_NO_ERROR)
        {
            std::cout << "OpenGL Error: " << error << std::endl;
        }

        GLenum glewinit = glewInit();
        if (glewinit != GLEW_OK) {
            std::cout << "Glew Error: " << glewGetErrorString(glewinit) << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cout << "Pangolin Current Context exists." << std::endl;
    }
}

#endif /* !__STATIC_GLEW_INIT_HPP__ */
