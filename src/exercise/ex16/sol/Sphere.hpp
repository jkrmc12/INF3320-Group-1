#ifndef _SPHERE_HPP__
#define _SPHERE_HPP__

#include "RayTracerState.hpp"
#include "SceneObject.hpp"
#include "SceneObjectEffect.hpp"

#include <glm/glm.hpp>

/**
  * The sphere is a scene object that is easy to work with. We have
  * simple analytical formulations for both the intersection with a ray and
  * for computation of the normal at any point
  */
class Sphere : public SceneObject {
public:
	Sphere(glm::vec3 center, float radius, SceneObjectEffect* effect) {
		this->p = center;
		this->r = radius;
		this->effect = effect;
	}

	/**
	  * Computes the ray-sphere intersection
	  */
	float intersect(const Ray& r) {
		const glm::vec3 d = r.getDirection();
		const glm::vec3 p0 = r.getOrigin();
		float a = glm::dot(d, d);
		float b = 2.0f*glm::dot(d, (p0-p));
		float c = glm::dot(p0-p, p0-p)-this->r*this->r;

		//skip

		float dist = (b*b)-4*a*c;
		if(dist < 0)
			return -1.0f;
		
		float t0 = (-b+glm::sqrt(dist))/(2*a);
		float t1 = (-b-glm::sqrt(dist))/(2*a);	

		if(t0*t1 < 0)
			return glm::max(t0,t1);
		else if(t0 >= 0 && t1 >= 0)
			return glm::min(t0,t1);	

		//unskip
			
		//No intersections
		return -1.0f;
	}
	
	/**
	  * Computes normal for an intersection point on a sphere
	  */
	const glm::vec3 computeNormal(const Ray& r, const float& t) {
		glm::vec3 n = glm::normalize(((r.getOrigin() + t * r.getDirection()) - p) / this->r);
		return n;
	}

	glm::vec3 rayTrace(Ray &ray, const float& t, RayTracerState& state) {
		glm::vec3 normal = computeNormal(ray, t);
		return effect->rayTrace(ray, t, normal, state);
	}

protected:
	glm::vec3 p; //< center of sphere
	float r;   //< sphere radius
};

#endif
