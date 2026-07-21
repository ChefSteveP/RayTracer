#pragma once

#include "hittable.h"

#include <vector>

class hittable_list: public hittable {

    public: 
        std::vector<std::shared_ptr<hittable>> objects;

        hittable_list() {}
        hittable_list(std::shared_ptr<hittable> object) {
            add(object);
        }

        void add(std::shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        bool hit(const ray&r, double ray_tmin, double ray_tmax, hit_record& rec) const override{

            hit_record temp_rec;
            bool hit_anything = false;
            double closest_point = ray_tmax;

            for(const auto& object: objects){
                //search until the closest point seen so far
                if(object->hit(r, ray_tmin, closest_point, temp_rec)) {
                    hit_anything = true;
                    closest_point = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;

        }
        
};