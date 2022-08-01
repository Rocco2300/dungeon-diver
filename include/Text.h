#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

class Text : public sf::Drawable, public sf::Transformable
{
private:
   std::map<char, int> specialCharMap = {
      {'.', 10},
      {':', 11},
      {',', 12},
      {';', 13},
      {'\'', 14},
      {'\"', 15},
      {'(', 16},
      {')', 17},
      {'!', 18},
      {'?', 19},
      {'+', 20},
      {'-', 21},
      {'*', 22},
      {'/', 23},
      {'=', 24}
   };

private:
   sf::Vector2f pos;
   sf::Vector2f size;
   sf::Texture* texture;
   sf::VertexArray vertices;

   int width;
   int height;
   int letterSpacing;

   std::string text;
public: 
   Text();
   Text(sf::Texture& texture, int width, int height, std::string str);

   inline sf::Vector2f getSize() { return size; }

   void setSpacing(int spacing);
   void setString(std::string str);
   void setPosition(sf::Vector2f pos);
   void setTexture(sf::Texture& texture);
   void setCharacterSize(int width, int height);

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
   sf::Vector2i getTextureIndex(char c);
};