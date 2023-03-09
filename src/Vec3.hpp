// 3D vector class
#pragma once

//////////////////////////////////////////////////////////////////////
// 3D vector
class Vec3 {
private: // private data
    float data[3];                          // array data

public: // constructor (also can use default copy constructor)
    Vec3(float x_ = 0, float y_ = 0, float z_ = 0) { 
        data[0] = x_; data[1] = y_; data[2] = z_;
    };

public:
    // access as an array vec[i] rather than vec.data[i]
    float operator[](int i) const;
    float &operator[](int i);
};
