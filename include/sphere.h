
#pragma once

#include <vector>
#include "ray.h"
#include "hittable.h"

class Sphere : public hittable {

public:
    Sphere(const point3& center, double radius)
        : m_center(center), m_radius(std::fmax(0,radius)) {}

    inline double getRadius() const {return m_radius;}
    inline point3 getCenter() const {return m_center;}

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override{
        vec3 d = r.direction();
        vec3 o_to_c = m_center - r.origin();
        double a = dot(d,d);
        
        double b = -2.0 * (dot(d, o_to_c));
        double c = dot(o_to_c, o_to_c) - (m_radius * m_radius);
        double discriminant = (b * b) - (4 * a * c);
        if (discriminant < 0) {
            return false;
        } 
            
        auto root = (-b - std::sqrt(discriminant) ) / (2.0*a);
        
        if (root <= ray_tmin || root >= ray_tmax){
            root = (-b + std::sqrt(discriminant) ) / (2.0*a);
            if (root <= ray_tmin || root >= ray_tmax) {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - m_center) / m_radius;

        return true;
    }


private:
    point3 m_center;
    double m_radius;
};


class SphereList{

    public:
    SphereList() = default;
    
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