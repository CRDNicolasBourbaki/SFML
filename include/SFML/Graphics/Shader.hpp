////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2015 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_SHADER_HPP
#define SFML_SHADER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/GlResource.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <map>
#include <string>


namespace sf
{
class InputStream;
class Texture;

////////////////////////////////////////////////////////////
/// \brief Shader class (vertex and fragment)
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API Shader : GlResource, NonCopyable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Types of shaders
    ///
    ////////////////////////////////////////////////////////////
    enum Type
    {
        Vertex,  ///< Vertex shader
        Fragment ///< Fragment (pixel) shader
    };

    ////////////////////////////////////////////////////////////
    /// \brief Special type that can be passed to setParameter,
    ///        and that represents the texture of the object being drawn
    ///
    /// \see setParameter(const std::string&, CurrentTextureType)
    ///
    ////////////////////////////////////////////////////////////
    struct CurrentTextureType {};

    ////////////////////////////////////////////////////////////
    /// \brief Represents the texture of the object being drawn
    ///
    /// \see setParameter(const std::string&, CurrentTextureType)
    ///
    ////////////////////////////////////////////////////////////
    static CurrentTextureType CurrentTexture;

	
	////////////////////////////////////////////////////////////
	/// \brief Matrix type, used to set uniforms in GLSL
	///
	////////////////////////////////////////////////////////////
    template <std::size_t Columns, std::size_t Rows>
    struct Matrix
    {
        explicit Matrix(const float* pointer) :
        pointer(pointer)
        {
        }

        const float* pointer;
    };

	////////////////////////////////////////////////////////////
	/// \brief 4D vector type, used to set uniforms in GLSL
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	struct Vector4
	{
		Vector4() :
		x(0),
		y(0),
		z(0),
		w(0)
		{
		}

		Vector4(T X, T Y, T Z, T W) :
		x(X),
		y(Y),
		z(Z),
		w(W)
		{
		}

		template <typename U>
		explicit Vector4(const Vector4<U>& other) :
		x(static_cast<T>(other.x)),
		y(static_cast<T>(other.y)),
		z(static_cast<T>(other.z)),
		w(static_cast<T>(other.w))
		{
		}

		T x, y, z, w;
	};


    typedef Matrix<3, 3> Mat3;
    typedef Matrix<4, 4> Mat4;

	typedef Vector2<float> Vec2;
	typedef Vector2<int>   Ivec2;
	typedef Vector2<bool>  Bvec2;

	typedef Vector3<float> Vec3;
	typedef Vector3<int>   Ivec3;
	typedef Vector3<bool>  Bvec3;

	typedef Vector4<float> Vec4;
	typedef Vector4<int>   Ivec4;
	typedef Vector4<bool>  Bvec4;

public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor creates an invalid shader.
    ///
    ////////////////////////////////////////////////////////////
    Shader();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Shader();

    ////////////////////////////////////////////////////////////
    /// \brief Load either the vertex or fragment shader from a file
    ///
    /// This function loads a single shader, either vertex or
    /// fragment, identified by the second argument.
    /// The source must be a text file containing a valid
    /// shader in GLSL language. GLSL is a C-like language
    /// dedicated to OpenGL shaders; you'll probably need to
    /// read a good documentation for it before writing your
    /// own shaders.
    ///
    /// \param filename Path of the vertex or fragment shader file to load
    /// \param type     Type of shader (vertex or fragment)
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromMemory, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromFile(const std::string& filename, Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Load both the vertex and fragment shaders from files
    ///
    /// This function loads both the vertex and the fragment
    /// shaders. If one of them fails to load, the shader is left
    /// empty (the valid shader is unloaded).
    /// The sources must be text files containing valid shaders
    /// in GLSL language. GLSL is a C-like language dedicated to
    /// OpenGL shaders; you'll probably need to read a good documentation
    /// for it before writing your own shaders.
    ///
    /// \param vertexShaderFilename   Path of the vertex shader file to load
    /// \param fragmentShaderFilename Path of the fragment shader file to load
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromMemory, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromFile(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);

    ////////////////////////////////////////////////////////////
    /// \brief Load either the vertex or fragment shader from a source code in memory
    ///
    /// This function loads a single shader, either vertex or
    /// fragment, identified by the second argument.
    /// The source code must be a valid shader in GLSL language.
    /// GLSL is a C-like language dedicated to OpenGL shaders;
    /// you'll probably need to read a good documentation for
    /// it before writing your own shaders.
    ///
    /// \param shader String containing the source code of the shader
    /// \param type   Type of shader (vertex or fragment)
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromFile, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromMemory(const std::string& shader, Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Load both the vertex and fragment shaders from source codes in memory
    ///
    /// This function loads both the vertex and the fragment
    /// shaders. If one of them fails to load, the shader is left
    /// empty (the valid shader is unloaded).
    /// The sources must be valid shaders in GLSL language. GLSL is
    /// a C-like language dedicated to OpenGL shaders; you'll
    /// probably need to read a good documentation for it before
    /// writing your own shaders.
    ///
    /// \param vertexShader   String containing the source code of the vertex shader
    /// \param fragmentShader String containing the source code of the fragment shader
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromFile, loadFromStream
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromMemory(const std::string& vertexShader, const std::string& fragmentShader);

    ////////////////////////////////////////////////////////////
    /// \brief Load either the vertex or fragment shader from a custom stream
    ///
    /// This function loads a single shader, either vertex or
    /// fragment, identified by the second argument.
    /// The source code must be a valid shader in GLSL language.
    /// GLSL is a C-like language dedicated to OpenGL shaders;
    /// you'll probably need to read a good documentation for it
    /// before writing your own shaders.
    ///
    /// \param stream Source stream to read from
    /// \param type   Type of shader (vertex or fragment)
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromFile, loadFromMemory
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromStream(InputStream& stream, Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Load both the vertex and fragment shaders from custom streams
    ///
    /// This function loads both the vertex and the fragment
    /// shaders. If one of them fails to load, the shader is left
    /// empty (the valid shader is unloaded).
    /// The source codes must be valid shaders in GLSL language.
    /// GLSL is a C-like language dedicated to OpenGL shaders;
    /// you'll probably need to read a good documentation for
    /// it before writing your own shaders.
    ///
    /// \param vertexShaderStream   Source stream to read the vertex shader from
    /// \param fragmentShaderStream Source stream to read the fragment shader from
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see loadFromFile, loadFromMemory
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromStream(InputStream& vertexShaderStream, InputStream& fragmentShaderStream);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for float uniform
	///
	/// \param name Name of the uniform variable in GLSL
	/// \param x    Value of the float scalar
	///
	////////////////////////////////////////////////////////////
    void setUniformFloat(const std::string& name, float x);
	
	////////////////////////////////////////////////////////////
	/// \brief Specify value for vec2 uniform
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param vector Value of the vec2 vector
	///
	////////////////////////////////////////////////////////////
	void setUniformVec2(const std::string& name, const Vec2& vector);
	
	////////////////////////////////////////////////////////////
	/// \brief Specify value for vec3 uniform
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param vector Value of the vec3 vector
	///
	////////////////////////////////////////////////////////////
	void setUniformVec3(const std::string& name, const Vec3& vector);
	
	////////////////////////////////////////////////////////////
	/// \brief Specify value for vec4 uniform
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param vector Value of the vec4 vector
	///
	////////////////////////////////////////////////////////////
	void setUniformVec4(const std::string& name, const Vec4& vector);

	////////////////////////////////////////////////////////////
	/// \brief Change a color parameter of the shader
	///
	/// \a name is the name of the variable to change in the shader.
	/// The corresponding parameter in the shader must be a 4x1 vector
	/// (vec4 GLSL type).
	///
	/// It is important to note that the components of the color are
	/// normalized before being passed to the shader. Therefore,
	/// they are converted from range [0 .. 255] to range [0 .. 1].
	/// For example, a sf::Color(255, 127, 0, 255) will be transformed
	/// to a vec4(1.0, 0.5, 0.0, 1.0) in the shader.
	///
	/// Example:
	/// \code
	/// uniform vec4 color; // this is the variable in the shader
	/// \endcode
	/// \code
	/// shader.setParameter("color", sf::Color(255, 128, 0, 255));
	/// \endcode
	///
	/// \param name  Name of the parameter in the shader
	/// \param color Color to assign
	///
	////////////////////////////////////////////////////////////
	void setUniformVec4(const std::string& name, const Color& color);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for int uniform
	///
	/// \param name Name of the uniform variable in GLSL
	/// \param x    Value of the int scalar
	///
	////////////////////////////////////////////////////////////
    void setUniformInt(const std::string& name, int x);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for ivec2 uniform
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param vector Value of the ivec2 vector
	///
	////////////////////////////////////////////////////////////
	void setUniformIvec2(const std::string& name, const Ivec2& vector);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for ivec3 uniform
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param vector Value of the ivec3 vector
	///
	////////////////////////////////////////////////////////////
	void setUniformIvec3(const std::string& name, const Ivec3& vector);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for ivec4 uniform
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param vector Value of the ivec4 vector
	///
	////////////////////////////////////////////////////////////
    void setUniformIvec4(const std::string& name, const Ivec4& vector);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for bool uniform
	///
	/// \param name Name of the uniform variable in GLSL
	/// \param x    Value of the bool scalar
	///
	////////////////////////////////////////////////////////////
	void setUniformBool(const std::string& name, bool x);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for bvec2 uniform
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param vector Value of the bvec2 vector
	///
	////////////////////////////////////////////////////////////
    void setUniformBvec2(const std::string& name, const Bvec2& vector);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for bvec3 uniform
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param vector Value of the bvec3 vector
	///
	////////////////////////////////////////////////////////////
	void setUniformBvec3(const std::string& name, const Bvec3& vector);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for bvec4 uniform
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param vector Value of the bvec4 vector
	///
	////////////////////////////////////////////////////////////
    void setUniformBvec4(const std::string& name, const Bvec4& vector);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for mat3 matrix
	///
	/// \param name    Name of the uniform variable in GLSL
	/// \param pointer Pointer to the 9 values of the 3x3 matrix
	///
	////////////////////////////////////////////////////////////
	void setUniformMat3(const std::string& name, const float* pointer);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for mat3 matrix
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param matrix Value of the mat3 matrix
	///
	////////////////////////////////////////////////////////////
	void setUniformMat3(const std::string& name, const Mat3& matrix);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for mat3 matrix
	///
	/// \param name    Name of the uniform variable in GLSL
	/// \param pointer Pointer to the 16 values of the 4x4 matrix
	///
	////////////////////////////////////////////////////////////
	void setUniformMat4(const std::string& name, const float* pointer);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for mat4 matrix
	///
	/// \param name   Name of the uniform variable in GLSL
	/// \param matrix Value of the mat4 matrix
	///
	////////////////////////////////////////////////////////////
	void setUniformMat4(const std::string& name, const Mat4& matrix);

	////////////////////////////////////////////////////////////
	/// \brief Specify value for mat4 uniform as SFML transform
	///
	/// \a name is the name of the uniform variable to change in the.
	/// shader. The corresponding GLSL type is a 4x4 matrix (mat4).
	///
	/// Example:
	/// \code
	/// uniform mat4 matrix; // this is the variable in the shader
	/// \endcode
	/// \code
	/// sf::Transform transform;
	/// transform.translate(5, 10);
	/// shader.setUniformMat4("matrix", transform);
	/// \endcode
	///
	/// \param name      Name of the parameter in the shader
	/// \param transform Transform to assign
	///
	////////////////////////////////////////////////////////////
	void setUniformMat4(const std::string& name, const Transform& transform);

	////////////////////////////////////////////////////////////
	/// \brief Specify values for float[] array uniform
	///
	/// \param name       Name of the uniform variable in GLSL
	/// \param valueArray Pointer to array of float values
	/// \param length     Number of elements in the array
	///
	////////////////////////////////////////////////////////////
    void setUniformFloatArray(const std::string& name, const float* valueArray, std::size_t length);

	////////////////////////////////////////////////////////////
	/// \brief Specify values for vec2[] array uniform
	///
	/// \param name       Name of the uniform variable in GLSL
	/// \param valueArray Pointer to array of vec2 values
	/// \param length     Number of elements in the array
	///
	////////////////////////////////////////////////////////////
	void setUniformVec2Array(const std::string& name, const Vector2f* vectorArray, std::size_t length);

	////////////////////////////////////////////////////////////
	/// \brief Specify values for vec3[] array uniform
	///
	/// \param name       Name of the uniform variable in GLSL
	/// \param valueArray Pointer to array of vec3 values
	/// \param length     Number of elements in the array
	///
	////////////////////////////////////////////////////////////
	void setUniformVec3Array(const std::string& name, const Vector3f* vectorArray, std::size_t length);

	////////////////////////////////////////////////////////////
	/// \brief Specify values for vec4[] array uniform
	///
	/// \param name       Name of the uniform variable in GLSL
	/// \param valueArray Pointer to array of vec4 values
	/// \param length     Number of elements in the array
	///
	////////////////////////////////////////////////////////////
	void setUniformVec4Array(const std::string& name, const Vec4* vectorArray, std::size_t length);

	////////////////////////////////////////////////////////////
	/// \brief Specify values for mat3[] array uniform
	///
	/// \param name        Name of the uniform variable in GLSL
	/// \param matrixArray Pointer to array of mat3 values
	/// \param length      Number of elements in the array
	///
	////////////////////////////////////////////////////////////
    void setUniformMat3Array(const std::string& name, const Mat3* matrixArray, std::size_t length);

	////////////////////////////////////////////////////////////
	/// \brief Specify values for mat4[] array uniform
	///
	/// \param name        Name of the uniform variable in GLSL
	/// \param matrixArray Pointer to array of mat4 values
	/// \param length      Number of elements in the array
	///
	////////////////////////////////////////////////////////////
	void setUniformMat4Array(const std::string& name, const Mat4* matrixArray, std::size_t length);


    ////////////////////////////////////////////////////////////
    /// \brief Change a texture parameter of the shader
    ///
    /// \a name is the name of the variable to change in the shader.
    /// The corresponding parameter in the shader must be a 2D texture
    /// (sampler2D GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform sampler2D the_texture; // this is the variable in the shader
    /// \endcode
    /// \code
    /// sf::Texture texture;
    /// ...
    /// shader.setParameter("the_texture", texture);
    /// \endcode
    /// It is important to note that \a texture must remain alive as long
    /// as the shader uses it, no copy is made internally.
    ///
    /// To use the texture of the object being draw, which cannot be
    /// known in advance, you can pass the special value
    /// sf::Shader::CurrentTexture:
    /// \code
    /// shader.setParameter("the_texture", sf::Shader::CurrentTexture).
    /// \endcode
    ///
    /// \param name    Name of the texture in the shader
    /// \param texture Texture to assign
    ///
    ////////////////////////////////////////////////////////////
    void setUniformSampler2D(const std::string& name, const Texture& texture);

    ////////////////////////////////////////////////////////////
    /// \brief Change a texture parameter of the shader
    ///
    /// This overload maps a shader texture variable to the
    /// texture of the object being drawn, which cannot be
    /// known in advance. The second argument must be
    /// sf::Shader::CurrentTexture.
    /// The corresponding parameter in the shader must be a 2D texture
    /// (sampler2D GLSL type).
    ///
    /// Example:
    /// \code
    /// uniform sampler2D current; // this is the variable in the shader
    /// \endcode
    /// \code
    /// shader.setUniformSampler2D("current", sf::Shader::CurrentTexture);
    /// \endcode
    ///
    /// \param name Name of the texture in the shader
    ///
    ////////////////////////////////////////////////////////////
    void setUniformSampler2D(const std::string& name, CurrentTextureType);

	////////////////////////////////////////////////////////////
	/// \brief Change a float parameter of the shader
	///
	/// \deprecated Use setUniformFloat() instead.
	///
	////////////////////////////////////////////////////////////
	void setParameter(const std::string& name, float x);

	////////////////////////////////////////////////////////////
	/// \brief Change a 2-components vector parameter of the shader
	///
	/// \deprecated Use setUniformVec2() instead.
	///
	////////////////////////////////////////////////////////////
	void setParameter(const std::string& name, float x, float y);

	////////////////////////////////////////////////////////////
	/// \brief Change a 3-components vector parameter of the shader
	///
	/// \deprecated Use setUniformVec3() instead.
	///
	////////////////////////////////////////////////////////////
	void setParameter(const std::string& name, float x, float y, float z);

	////////////////////////////////////////////////////////////
	/// \brief Change a 4-components vector parameter of the shader
	///
	/// \deprecated Use setUniformVec4() instead.
	///
	////////////////////////////////////////////////////////////
	void setParameter(const std::string& name, float x, float y, float z, float w);

	////////////////////////////////////////////////////////////
	/// \brief Change a 2-components vector parameter of the shader
	///
	/// \deprecated Use setUniformVec2() instead.
	///
	////////////////////////////////////////////////////////////
	void setParameter(const std::string& name, const Vector2f& vector);

	////////////////////////////////////////////////////////////
	/// \brief Change a 3-components vector parameter of the shader
	///
	/// \deprecated Use setUniformVec3() instead.
	///
	////////////////////////////////////////////////////////////
	void setParameter(const std::string& name, const Vector3f& vector);

	////////////////////////////////////////////////////////////
	/// \brief Change a color parameter of the shader
	///
	/// \deprecated Use setUniformVec4() instead.
	///
	////////////////////////////////////////////////////////////
	void setParameter(const std::string& name, const Color& color);

	////////////////////////////////////////////////////////////
	/// \brief Change a matrix parameter of the shader
	///
	/// \deprecated Use setUniformMat4() instead.
	///
	////////////////////////////////////////////////////////////
	void setParameter(const std::string& name, const Transform& transform);

	////////////////////////////////////////////////////////////
	/// \brief Change a texture parameter of the shader
	///
	/// \deprecated Use setUniformSampler2D() instead.
	///
	////////////////////////////////////////////////////////////
	void setParameter(const std::string& name, const Texture& texture);

	////////////////////////////////////////////////////////////
	/// \brief Change a texture parameter of the shader
	///
	/// \deprecated Use setUniformSampler2D() instead.
	///
	////////////////////////////////////////////////////////////
	void setParameter(const std::string& name, CurrentTextureType);

    ////////////////////////////////////////////////////////////
    /// \brief Get the underlying OpenGL handle of the shader.
    ///
    /// You shouldn't need to use this function, unless you have
    /// very specific stuff to implement that SFML doesn't support,
    /// or implement a temporary workaround until a bug is fixed.
    ///
    /// \return OpenGL handle of the shader or 0 if not yet loaded
    ///
    ////////////////////////////////////////////////////////////
    unsigned int getNativeHandle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Bind a shader for rendering
    ///
    /// This function is not part of the graphics API, it mustn't be
    /// used when drawing SFML entities. It must be used only if you
    /// mix sf::Shader with OpenGL code.
    ///
    /// \code
    /// sf::Shader s1, s2;
    /// ...
    /// sf::Shader::bind(&s1);
    /// // draw OpenGL stuff that use s1...
    /// sf::Shader::bind(&s2);
    /// // draw OpenGL stuff that use s2...
    /// sf::Shader::bind(NULL);
    /// // draw OpenGL stuff that use no shader...
    /// \endcode
    ///
    /// \param shader Shader to bind, can be null to use no shader
    ///
    ////////////////////////////////////////////////////////////
    static void bind(const Shader* shader);

    ////////////////////////////////////////////////////////////
    /// \brief Tell whether or not the system supports shaders
    ///
    /// This function should always be called before using
    /// the shader features. If it returns false, then
    /// any attempt to use sf::Shader will fail.
    ///
    /// Note: The first call to this function, whether by your
    /// code or SFML will result in a context switch.
    ///
    /// \return True if shaders are supported, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool isAvailable();

private:

    ////////////////////////////////////////////////////////////
    /// \brief Compile the shader(s) and create the program
    ///
    /// If one of the arguments is NULL, the corresponding shader
    /// is not created.
    ///
    /// \param vertexShaderCode   Source code of the vertex shader
    /// \param fragmentShaderCode Source code of the fragment shader
    ///
    /// \return True on success, false if any error happened
    ///
    ////////////////////////////////////////////////////////////
    bool compile(const char* vertexShaderCode, const char* fragmentShaderCode);

    ////////////////////////////////////////////////////////////
    /// \brief Bind all the textures used by the shader
    ///
    /// This function each texture to a different unit, and
    /// updates the corresponding variables in the shader accordingly.
    ///
    ////////////////////////////////////////////////////////////
    void bindTextures() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the location ID of a shader parameter
    ///
    /// \param name Name of the parameter to search
    ///
    /// \return Location ID of the parameter, or -1 if not found
    ///
    ////////////////////////////////////////////////////////////
    int getParamLocation(const std::string& name);

	////////////////////////////////////////////////////////////
	/// \brief Sets uniforms using a function object (code reuse)
	///
	/// \param name Name of the uniform variable
	/// \param functor Function object setting the uniform
	///
	////////////////////////////////////////////////////////////
	template <typename F>
    void setUniformImpl(const std::string& name, F functor);

    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::map<int, const Texture*> TextureTable;
    typedef std::map<std::string, int> ParamTable;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    unsigned int m_shaderProgram;  ///< OpenGL identifier for the program
    int          m_currentTexture; ///< Location of the current texture in the shader
    TextureTable m_textures;       ///< Texture variables in the shader, mapped to their location
    ParamTable   m_params;         ///< Parameters location cache
};

} // namespace sf


#endif // SFML_SHADER_HPP


////////////////////////////////////////////////////////////
/// \class sf::Shader
/// \ingroup graphics
///
/// Shaders are programs written using a specific language,
/// executed directly by the graphics card and allowing
/// to apply real-time operations to the rendered entities.
///
/// There are two kinds of shaders:
/// \li Vertex shaders, that process vertices
/// \li Fragment (pixel) shaders, that process pixels
///
/// A sf::Shader can be composed of either a vertex shader
/// alone, a fragment shader alone, or both combined
/// (see the variants of the load functions).
///
/// Shaders are written in GLSL, which is a C-like
/// language dedicated to OpenGL shaders. You'll probably
/// need to learn its basics before writing your own shaders
/// for SFML.
///
/// Like any C/C++ program, a GLSL shader has its own variables
/// that you can set from your C++ application. sf::Shader
/// handles different types of variables:
/// \li scalars: float, int, bool
/// \li vectors (2, 3 or 4 components)
/// \li matrices (3x3 or 4x4)
/// \li samplers (textures)
/// 
/// Some SFML-specific types are also accepted:
/// \li sf::Color as a 4D vector (vec4)
/// \li sf::Transform as matrices (either mat3 or mat4)
///
/// The value of the variables can be changed at any time
/// with the various setUniform*() functions:
/// \code
/// shader.setUniformFloat("offset", 2.f);
/// shader.setUniformVec3("point", 0.5f, 0.8f, 0.3f);
/// shader.setUniformVec4("color", sf::Color(128, 50, 255));
/// shader.setUniformMat4("matrix", transform); // transform is a sf::Transform
/// shader.setUniformSampler2D("overlay", texture); // texture is a sf::Texture
/// shader.setUniformSampler2D("texture", sf::Shader::CurrentTexture);
/// \endcode
///
/// The old setParameter() overloads are deprecated and should be replaced
/// with their setUniform*() equivalents.
///
/// The special Shader::CurrentTexture argument maps the
/// given texture variable to the current texture of the
/// object being drawn (which cannot be known in advance).
///
/// To apply a shader to a drawable, you must pass it as an
/// additional parameter to the Draw function:
/// \code
/// window.draw(sprite, &shader);
/// \endcode
///
/// ... which is in fact just a shortcut for this:
/// \code
/// sf::RenderStates states;
/// states.shader = &shader;
/// window.draw(sprite, states);
/// \endcode
///
/// In the code above we pass a pointer to the shader, because it may
/// be null (which means "no shader").
///
/// Shaders can be used on any drawable, but some combinations are
/// not interesting. For example, using a vertex shader on a sf::Sprite
/// is limited because there are only 4 vertices, the sprite would
/// have to be subdivided in order to apply wave effects.
/// Another bad example is a fragment shader with sf::Text: the texture
/// of the text is not the actual text that you see on screen, it is
/// a big texture containing all the characters of the font in an
/// arbitrary order; thus, texture lookups on pixels other than the
/// current one may not give you the expected result.
///
/// Shaders can also be used to apply global post-effects to the
/// current contents of the target (like the old sf::PostFx class
/// in SFML 1). This can be done in two different ways:
/// \li draw everything to a sf::RenderTexture, then draw it to
///     the main target using the shader
/// \li draw everything directly to the main target, then use
///     sf::Texture::update(Window&) to copy its contents to a texture
///     and draw it to the main target using the shader
///
/// The first technique is more optimized because it doesn't involve
/// retrieving the target's pixels to system memory, but the
/// second one doesn't impact the rendering process and can be
/// easily inserted anywhere without impacting all the code.
///
/// Like sf::Texture that can be used as a raw OpenGL texture,
/// sf::Shader can also be used directly as a raw shader for
/// custom OpenGL geometry.
/// \code
/// sf::Shader::bind(&shader);
/// ... render OpenGL geometry ...
/// sf::Shader::bind(NULL);
/// \endcode
///
////////////////////////////////////////////////////////////
