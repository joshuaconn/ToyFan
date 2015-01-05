#include "color.h"

color3f black   = { 0.0 , 0.0 , 0.0 };
color3f white   = { 1.0 , 1.0 , 1.0 };
color3f red     = { 1.0 , 0.0 , 0.0 };
color3f green   = { 0.0 , 0.5 , 0.0 };
color3f lime    = { 0.0 , 1.0 , 0.0 };
color3f blue    = { 0.0 , 0.0 , 1.0 };
color3f cyan    = { 0.0 , 1.0 , 1.0 };
color3f magenta = { 1.0 , 0.0 , 1.0 };
color3f yellow  = { 1.0 , 1.0 , 0.0 };
color3f gray    = { 0.5 , 0.5 , 0.5 };
color3f orange  = { 1.0 , 0.5 , 0.0 };
color3f purple  = { 0.3 , 0.0 , 0.3 };
color3f brown   = { 0.4 , 0.2 , 0.0 };
color3f beige   = { 0.8 , 0.6 , 0.3 };
color3f pink    = { 1.0 , 0.5 , 1.0 };
color3f burgundy= { 0.4 , 0.0 , 0.1 };
color3f teal    = { 0.0, 0.5 , 0.5 };

color3f mix(color3f c1, color3f c2) {
	c1.r = (c1.r+c2.r)/2;
	c1.g = (c1.g+c2.g)/2;
	c1.b = (c1.b+c2.b)/2;
	return c1;
}

color3f mix(color3f c1, color3f c2, float perc_c1){
	float perc_c2 = (1.0-perc_c1);
	c1.r = c1.r*perc_c1+c2.r*perc_c2;
	c1.g = c1.g*perc_c1+c2.g*perc_c2;
	c1.b = c1.b*perc_c1+c2.b*perc_c2;
	return c1;
}
