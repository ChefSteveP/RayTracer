#pragma once
#include "common.h"
#include "hittable.h"

class camera {

    public:
        double aspect_ratio = 16.0/9.0;
        int image_width = 256;

        void render(const hittable& world){
            initalize();
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

                // SL.push(Sphere(point3(1,0,-2), 0.5));
            for (int j = 0; j < image_height; j++){
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++){
                    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    auto ray_direction = pixel_center - center;
                    ray r ( center, ray_direction );

                    color pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);
                }
            }
            std::clog << "\rDone.                 \n";
        }

    private:

        int image_height;
        point3 center;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;

        void initalize(){
            
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height; 

            //camera 
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/image_height);
            center = point3(0,0,0); // position

            //viewport vectors
            auto viewport_u = vec3(viewport_width, 0,0);
            auto viewport_v = vec3(0,-viewport_height, 0);

            pixel_delta_u = viewport_u/image_width;
            pixel_delta_v = viewport_v/image_height;

            auto viewport_upper_left = center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); //move to center of pixel

        }
        color ray_color(const ray& r, const hittable& hl) {
            
            hit_record hr;
            if( hl.hit(r, interval(0.0, infinity), hr)){
                return 0.5 + (0.5 * hr.normal);
            }
            
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y()) + 0.5;
            return lerp(color(1.0, 1.0, 1.0), color(0.2, 0.3, 0.7), a);
        }

};