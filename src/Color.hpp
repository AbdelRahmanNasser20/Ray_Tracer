// really basic type for unsigned byte colors
#pragma once

#include "Vec3.hpp"
const float INVGAMMA = 1.f / 2.2f;

// intentionally a POD (plain old data) type
// can have constructors & member functions, but nothing virtual
struct Color {
	unsigned char r, g, b;		// public access to color data

	// constructor from Vec3
	Color(Vec3 v = Vec3()) {
        
        // clamp values between 0 and 1
        v[0] = std::max(0.f, std::min(1.f, v[0]));
        v[1] = std::max(0.f, std::min(1.f, v[1]));
        v[2] = std::max(0.f, std::min(1.f, v[2]));

        // apply gamma correction
        v[0] = pow(v[0], INVGAMMA);
        v[1] = pow(v[1], INVGAMMA);
        v[2] = pow(v[2], INVGAMMA);
        
		r = (unsigned char)(255.f * v[0]);
        g = (unsigned char)(255.f * v[1]);
        b = (unsigned char)(255.f * v[2]);
	}

};

