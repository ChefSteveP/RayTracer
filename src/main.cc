#include "vec3.h"
#include "ray.h"
#include "color.h"
#include <iostream>
#include <vector>
//cmake -B build // config
//cmake --build build //compile

class Sphere{

public:
    Sphere(point3 center, double radius){
        m_center = center;
        m_radius = radius;
    }
    inline double getRadius() const {return m_radius;}
    inline point3 getCenter() const {return m_center;}

private:
    point3 m_center;
    double m_radius;
};


class SphereList{

    public:
    SphereList(){}
    
    void push(Sphere s){
        m_list.push_back(s);
    }
    const Sphere* pop(){
        if (!m_list.empty()) {
            Sphere s = m_list.back();
            m_list.pop_back();
            return &s;
        }
        else {
            return nullptr;
        }
    }
    std::vector<Sphere> getList() {return m_list;}

    private:
    std::vector<Sphere> m_list;
};

double hit_sphere(const point3& center, double radius, const ray& r){
    vec3 d = r.direction();
    vec3 o_to_c = center - r.origin();
    double a = dot(d,d);
    
    double b = -2.0 * (dot(d, o_to_c));
    double c = dot(o_to_c, o_to_c) - (radius * radius);
    double discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - std::sqrt(discriminant) ) / (2.0*a);
    }
}

color ray_color(const ray& r, SphereList& sl) {
    
    auto list = sl.getList();
    // Sphere s = list[0];
    for (int i=0; i < list.size(); ++i){

        auto s = list[i];
        double t = hit_sphere(s.getCenter(), s.getRadius(), r);
        if (t > 0) {
            vec3 N = unit_vector(r.at(t)-s.getCenter());
            return 0.5 + (0.5 * N);
            // return color(1.0, 0.0, 1.0);
        }
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y()) + 0.5;
    return lerp(color(1.0, 1.0, 1.0), color(0.2, 0.3, 0.7), a);
}


int main() {
    //image

    auto aspect_ratio = 16.0/9.0;

    int image_width = 256;
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height; 

    //camera 
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0,0,0); // position

    //viewport vectors
    auto viewport_u = vec3(viewport_width, 0,0);
    auto viewport_v = vec3(0,-viewport_height, 0);

    auto pixel_delta_u = viewport_u/image_width;
    auto pixel_delta_v = viewport_v/image_height;

    auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); //move to center of pixel

 
    //render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    SphereList SL;
    SL.push(Sphere(point3(0,0,-1), 0.5));
    SL.push(Sphere(point3(1,0,-2), 0.5));
    for (int j = 0; j < image_height; j++){
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++){
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r ( camera_center, ray_direction );

            color pixel_color = ray_color(r, SL);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
    return 0;

}