#pragma once
#include "utility.h"
#include "ray.h"

class material;

struct hit_record {
	point3 p;
	vec3 normal;
	shared_ptr<material> mat_ptr;
	double t;
	
	bool outer_face;

	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		outer_face = dot(r.direction(), outward_normal) < 0.;
		normal = outer_face ? outward_normal : -outward_normal;
	}
};

class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;

};