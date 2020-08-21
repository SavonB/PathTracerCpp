#include "utility.h"
vec3 random_in_unit_sphere() {
	while (true) {
		auto p = vec3::random_vec(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

vec3 random_vector_lambertian() {
	auto a = random_double(0, 2 * pi);
	auto z = random_double(-1, 1);
	auto r = sqrt(1 - z * z);
	return vec3(r * cos(a), r * sin(a), z);

}

vec3 random_in_unit_disk() {
	while (true) {
		auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
