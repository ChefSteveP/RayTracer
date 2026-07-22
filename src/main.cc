
#include "common.h"
#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"

#include <iostream>
#include <vector>
//cmake -B build // config
//cmake --build build //compile

int main() {

    //render
    camera cam;

    hittable_list obj_list;

    obj_list.add(std::make_shared<Sphere>(point3(0,0,-1), 0.5));
    obj_list.add(std::make_shared<Sphere>(point3(1,0,-2), 0.5));
    obj_list.add(std::make_shared<Sphere>(point3(-1,-0.5,-2), 0.5));
    obj_list.add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));

    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 256;
    cam.render(obj_list);

}