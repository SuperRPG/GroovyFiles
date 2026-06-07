#ifndef _SDLUTILS_H_
#define _SDLUTILS_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <fmt/core.h>
#include "def.h"

struct resouce_t
{
public:
   std::string name;
   SDL_Texture* texture;
};

struct resources_t
{
public:
   ~resources_t()
   {
      for (auto& resource : m_res_list)
      {
         SDL_DestroyTexture(resource.texture);
      }
   }

   inline void add(resouce_t resource)
   {
      m_res_list.push_back(resource);
   }

   SDL_Texture* find(const std::string& name)
   {
      for (auto& resource : m_res_list)
      {
         if (resource.name.compare(name) == 0)
         {
            return resource.texture;
         }
      }

      return NULL;
   }
private:
   std::list<resouce_t> m_res_list{};
};

class IWindow;

struct config_t
{
public:
   config_t(const std::vector<std::string>& res_list);
   ~config_t();
   
   inline SDL_Texture* findTexture(const std::string& name)
   {
      return resources.find(name);
   }

   inline void PushWindow(IWindow* window)
   {
      windows.push_back(window);
   }

   inline void PopWindow()
   {
      windows.pop_back();
   }

   SDL_Renderer* renderer;
   TTF_Font* font;
   TTF_Font* monoFont;
   SDL_Window* window;
   SDL_Joystick* joystick;
   int char_width;
   std::vector<IWindow*> windows;
private:   
   resources_t resources{};  
};

namespace SDLUtils
{

   // Init SDL
   bool init(config_t* config);

   // Close SDL
   void close(config_t* config);

   // Load a texture
   SDL_Texture* loadTexture(config_t* config, const std::string &p_path);

   // Load a TTF font
   TTF_Font *loadFont(const std::string &p_path, const int p_size);

   // Horizontal alignment
   typedef enum T_ALIGN_H {
      T_ALIGN_LEFT = 0,
      T_ALIGN_RIGHT,
      T_ALIGN_CENTER
   } T_ALIGN_H;

   // Vertical alignment
   typedef enum T_ALIGN_V {
      T_ALIGN_TOP = 0,
      T_ALIGN_BOTTOM,
      T_ALIGN_MIDDLE
   } T_ALIGN_V;

   // Render a texture on the screen
   void renderTexture(config_t* config, SDL_Texture * p_texture, const int p_x, const int p_y, const T_ALIGN_H p_alignH = T_ALIGN_LEFT, const T_ALIGN_V p_alignV = T_ALIGN_TOP, const SDL_RendererFlip p_flip = SDL_FLIP_NONE, const SDL_Rect *p_clip = NULL);

   // Render text on the screen
   // Return: width of the texture
   int renderText(config_t* config, const std::string &p_text, TTF_Font *p_font, const int p_x, const int p_y, const SDL_Color &p_fg, const SDL_Color &p_bg, const T_ALIGN_H p_alignH = T_ALIGN_LEFT, const T_ALIGN_V p_alignV = T_ALIGN_TOP, const int p_maxWidth = -1, const T_ALIGN_H p_alignHClip = T_ALIGN_LEFT);

   // Render text on the screen, with clip scrolling
   // Return: width of the texture
   int renderTextScrolling(config_t* config, const std::string &p_text, TTF_Font *p_font, const int p_x, const int p_y, const SDL_Color &p_fg, const SDL_Color &p_bg, const T_ALIGN_H p_alignH, const T_ALIGN_V p_alignV, const int p_maxWidth, const int p_clipX);

   // Render text and return the texture
   SDL_Texture *renderText(config_t* config, const std::string &p_text, TTF_Font *p_font, const SDL_Color &p_fg, const SDL_Color &p_bg);

   // Width of one character in monospace font
   int getCharWidthMono(config_t* config);

}

#endif
