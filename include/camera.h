#pragma once
#include "common.h"
#include "hittable.h"

class camera {

    public:
        double aspect_ratio = 16.0/9.0;
        int image_width = 256;
        int samples_per_pixel = 10;

        void render(const hittable& world){
            initalize();
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

                // SL.push(Sphere(point3(1,0,-2), 0.5));
            for (int j = 0; j < image_height; j++){
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++){
                    color pixel_color(0,0,0);
                    for (int s = 0; s < samples_per_pixel; s++){
                        ray r = get_ray(i,j);
                        pixel_color += ray_color(r, world);
                    }
                    write_color(std::cout, pixels_per_sampler_scale * pixel_color);
                }
            }
            std::clog << "\rDone.                 \n";
        }

    private:

        int image_height;
        double pixels_per_sampler_scale;
        point3 center;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;

        void initalize(){
            
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height; 
            pixels_per_sampler_scale = 1.0 / samples_per_pixel;
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

        ray get_ray(int i, int j) const {

            auto offset = sample_square();
            auto pixel_sample = pixel00_loc 
                              + ((i + offset.x()) * pixel_delta_u)
                              + ((j + offset.y()) * pixel_delta_v);
            
            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;
            return ray(ray_origin, ray_direction);
        }

        vec3 sample_square() const {
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
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