#pragma once

#include <SFML/Graphics.hpp>

enum class ColorTypes {RGB, HSL, HSV, CMY};

sf::Color hsv2rgb(double H, double S, double V);
double Hue_2_RGB(double v1, double v2, double vH);



sf::Color getRGB(double r, double g, double b){
    return sf::Color(static_cast<sf::Uint8>(r*255), static_cast<sf::Uint8>(g*255), static_cast<sf::Uint8>(b*255));
}

sf::Color getHSL(double s, double h, double l){
    double var_1, var_2;
    if ( l < 0.5 ) 
        var_2 = l * ( 1. + s );
    else
        var_2 = ( l + s ) - ( s * l );

    var_1 = 2. * l - var_2;
    return sf::Color(static_cast<sf::Uint8>(Hue_2_RGB(var_1, var_2, h + (1/3.))*255.), static_cast<sf::Uint8>(Hue_2_RGB(var_1, var_2, h)*255.), static_cast<sf::Uint8>(Hue_2_RGB(var_1, var_2, h-(1/3.))*255.));
}

sf::Color getHSV(double s, double h, double v){
    if(s == 0.){
        return sf::Color(static_cast<sf::Uint8>((v)*255.), static_cast<sf::Uint8>((v)*255.), static_cast<sf::Uint8>((v)*255.));
    }
    double var_h = h*6;
    if(var_h == 6.) 
        var_h = 0.;
    int var_i = (int)var_h;
    double var_1 = v*(1.-s);
    double var_2 = v*(1.-s*(var_h - (double)var_i));
    double var_3 = v * ( 1. - s * ( 1. - ( var_h - (double)var_i)));

    if      ( var_i == 0 ) return sf::Color(static_cast<sf::Uint8>((v)*255.),        static_cast<sf::Uint8>((var_3)*255.),    static_cast<sf::Uint8>((var_1)*255.));
    else if ( var_i == 1 ) return sf::Color(static_cast<sf::Uint8>((var_2)*255.),    static_cast<sf::Uint8>((v)*255.),        static_cast<sf::Uint8>((var_1)*255.));
    else if ( var_i == 2 ) return sf::Color(static_cast<sf::Uint8>((var_1)*255.),    static_cast<sf::Uint8>((v)*255.),        static_cast<sf::Uint8>((var_3)*255.));
    else if ( var_i == 3 ) return sf::Color(static_cast<sf::Uint8>((var_1)*255.),    static_cast<sf::Uint8>((var_2)*255.),    static_cast<sf::Uint8>((v)*255.));
    else if ( var_i == 4 ) return sf::Color(static_cast<sf::Uint8>((var_3)*255.),    static_cast<sf::Uint8>((var_1)*255.),    static_cast<sf::Uint8>((v)*255.));
    else                   return sf::Color(static_cast<sf::Uint8>((v)*255.),        static_cast<sf::Uint8>((var_1)*255.),    static_cast<sf::Uint8>((var_2)*255.));
    
    // return hsv2rgb(h, s, v);
}

sf::Color getCMY(double c, double m, double y){
    return sf::Color(static_cast<sf::Uint8>((1-c)*255), static_cast<sf::Uint8>((1-m)*255), static_cast<sf::Uint8>((1-y)*255));
}


double Hue_2_RGB(double v1, double v2, double vH){
   if ( vH < 0. ) vH += 1.;
   if( vH > 1. ) vH -= 1.;
   if ( ( 6. * vH ) < 1. ) return ( v1 + ( v2 - v1 ) * 6. * vH );
   if ( ( 2. * vH ) < 1. ) return ( v2 );
   if ( ( 3. * vH ) < 2. ) return ( v1 + ( v2 - v1 ) * ( ( 2 / 3. ) - vH ) * 6. );
   return ( v1 );
}

sf::Color hsv2rgb(double H, double s, double v){
    double h=H*360;
    double      hh, p, q, t, ff;
    long        i;
    double r, g, b;
    if(s <= 0.0) {       // < is bogus, just shuts up warnings
        r = v;
        g = v;
        b = v;
        return sf::Color((sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b);     
    }
    hh = h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch(i) {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;

    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    default:
        r = v;
        g = p;
        b = q;
        break;
    }
    return sf::Color((sf::Uint8)r*255, (sf::Uint8)g*255, (sf::Uint8)b*255);     
}
