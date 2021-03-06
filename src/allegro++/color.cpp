#include <allegro++/color.h>

namespace AllegroPP {
   Color::Color(int r, int g, int b, float a){
      _r = Math::clamp(r, 0, 255);
      _g = Math::clamp(g, 0, 255);
      _b = Math::clamp(b, 0, 255);
      _a = Math::clamp(a, 0.0f, 1.0f);
   }
   
   Color::Color(int hex){
      _r = Math::clamp((hex & 0xFF0000)/0x010000, 0, 0xFF);
      _g = Math::clamp((hex & 0x00FF00)/0x000100, 0, 0xFF);
      _b = Math::clamp((hex & 0x0000FF)/0x000001, 0, 0xFF);
      _a = 1.0f - Math::clamp((float)(hex & 0xFF000000)/0xFF000000, 0.0f, 1.0f);
   }
   
   Color::Color(ALLEGRO_COLOR color){
      _r = (int)(color.r * 255);
      _g = (int)(color.g * 255);
      _b = (int)(color.b * 255);
      _a = color.a;
   }

   Color::Color(bool notColor){
      Color(0, 0, 0);
      this->notColor = notColor;
   }

   Color Color::operator*(double k){
      return Color(this->_r*k, this->_g*k, this->_b*k);
   }

   Color Color::operator/(double k){
      return Color(this->_r/k, this->_g/k, this->_b/k);
   }

   Color Color::operator+(const Color& c){
      return Color(this->_r+c._r, this->_g+c._g, this->_b+c._b);
   }
   
   Color Color::operator =(unsigned hex){
      Color c;
      c._r = Math::clamp((hex & 0xFF0000)/0x010000, 0, 0xFF);
      c._g = Math::clamp((hex & 0x00FF00)/0x000100, 0, 0xFF);
      c._b = Math::clamp((hex & 0x0000FF)/0x000001, 0, 0xFF);
      c._a = 1.0f - Math::clamp((float)(hex & 0xFF000000)/0xFF000000, 0.0f, 1.0f);
      
      return c;
   }
   
   void Color::setAlpha(float alpha){
      _a = alpha;
   }

   Color Color::mix(const Color& c){
      return Color(Math::clamp(this->_r, 0, c._r), Math::clamp(this->_g, 0, c._g), Math::clamp(this->_b, 0, c._b));
   }

   Color Color::blend(const Color& c){
      return Color((this->_r + c._r)/2, (this->_g + c._g)/2, (this->_b + c._b)/2);
   }
   
   std::ostream& operator<<(std::ostream& os, const Color& c){
      os << "Color(" << c._r << "," << c._g << "," << c._b << "," << c._a << ")";
      return os;
   }
   
   std::string Color::toHex() const{
      std::stringstream ss;
      ss << std::hex << ((int)(_a*0xFF) * 0x01000000 + _r * 0x010000 + _g * 0x000100 + _b);
      return ss.str();
   }

   ALLEGRO_COLOR Color::toAllegro(){
      if(_a != 1)
         return al_map_rgba(_r, _g, _b, _a*255);
      else
         return al_map_rgb(_r, _g, _b);
   }
   
}