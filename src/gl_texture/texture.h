/* SDL library needed! Make sure you have installed it! */
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/* OpenGL library needed! Make sure you have installed it! */
#include <GL/glut.h>

/* Data type redefinition */
typedef GLuint textureIDtype;

/* CLASS: Texture Loading */
class Texture
{
public:
    /* Default constructor */
    Texture() : level(0), border(0)
    { // Do nothing here
    }

    /* Load image and bind texture */
    Texture(const char* image_path)
    { // Constructor
        surface = IMG_Load(image_path);

        // Make room for our texture
        glGenTextures(1, &id);
        // Tell OpenGL which texture to edit and map the image to the texture
        glBindTexture(GL_TEXTURE_2D, id);

        // Specify a two-dimensional texture image
        // Learn more about this function:
        // https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
        glTexImage2D(GL_TEXTURE_2D, // Specifies the target texture of the active texture unit
                     level,  // Specifies the level-of-detail number. Here the basic level is needed
                     GL_RGB, // Specifies the internal format of the texture
                     surface->w, // Image width
                     surface->h, // Image height
                     border, // The border width of the image
                     GL_RGB, // GL_RGB, because pixels are stored in RGB format
                     GL_UNSIGNED_BYTE, // TYPE (Specifies the data type of the texel data) = GL_UNSIGNED_BYTE
                     surface->pixels); // The pixel data of this texture
    }

    /* Reload image and rebind this texture */
    void reload(const char* image_path)
    { // Constructor
        surface = IMG_Load(image_path);

        // Regenerate the texture
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, surface->w, surface->h, 
                     border, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
    }

    /* Read the value of texture id */
    textureIDtype getID()
    { // Return a private member
        return id;
    }

private:

    /* The ID of this texture 
    ** The most IMPORTANT member! */
    textureIDtype id;

    /* Specifies the level-of-detail number.
    ** Level 0 is the base image level. 
    ** Level n is the nth mipmap reduction image. 
    ** DEFAULT: 0 */
    GLint level;

    /* The border width of texture
    ** DEFAULT: 0 */
    GLint border;

    /* Specify a pointer to the image data in memory. */
    SDL_Surface *surface;
};