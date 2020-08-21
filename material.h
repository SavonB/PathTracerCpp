#pragma once
#include "utility.h"
struct hit_record;

class material {
public:
	virtual bool scatter(const ray& r_in, 
		const hit_record& rec, 
		color& attenuation, 
		ray& scattered) const = 0;

};

class lambertian : public material {
public:
    lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        vec3 scatter_direction = rec.normal + random_vector_lambertian();
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

public:
    color albedo;
};

class metal : public material {
public:
    metal(const color& a,double f) : albedo(a), fuzz(f<1?f:1) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
        ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.p, reflected+fuzz*random_vector_lambertian());
        attenuation = albedo;
        return(dot(scattered.direction(), rec.normal) > 0);
    }
public:
    color albedo;
    double fuzz;

};

class dielectric : public material {
public:
    dielectric(double ri) : ref_idx(ri) {}
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override{
        attenuation = color(1., 1., 1.);
        double etai_over_etat = rec.outer_face ? (1. / ref_idx) : ref_idx;

        vec3 unit_direction = unit_vector(r_in.direction());

        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        //ray is coming from the inside (handle total internal reflection)
        if (etai_over_etat * sin_theta > 1.) { 
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }
        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (random_double() < reflect_prob) {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }
        
        vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = ray(rec.p, refracted);
        return true;
    }
    double ref_idx;

};