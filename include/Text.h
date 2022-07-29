#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "AssetManager.h"

class Text : public sf::Drawable
{
private:
   sf::Vector2f pos;
   sf::Texture* texture;
   sf::VertexArray vertices;

   std::string text;
public: 
   Text();
   Text(std::string str);

   void setString(std::string str);
   void setPosition(sf::Vector2f pos);


   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};