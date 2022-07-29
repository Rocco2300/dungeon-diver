#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "AssetManager.h"

class Text : public sf::Drawable
{
private:
   sf::Texture* texture;
   sf::VertexArray vertices;

   std::string text;
public: 
   Text();
   Text(std::string str);

   void setString(std::string str);

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};