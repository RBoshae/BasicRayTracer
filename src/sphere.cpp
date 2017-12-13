#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
  // TODO // Complete
  double discriminant;
  vec3 w = ray.direction;
  vec3 u = ray.endpoint;
  vec3 v = u - this->center;

  // Compute discriminant
  discriminant = pow(dot(w,v),2) - (dot(w,w)*(dot(v,v) - radius*radius));
  //  discriminant = pow(dot(w,v),2) - (dot(w,w)*(dot(v,v) - pow(this->radius,2)));
  //  discriminant = pow(dot(ray.direction , ray.endpoint),2) - (dot(w,w)*(dot(v,v) - pow(this->radius,2)));

  // Set up both hits
  Hit enter_hit;
  Hit exit_hit;

  if (discriminant < 0) {

    return false;

  } else if (discriminant > 0) {

    enter_hit.t = (-1.0*dot(w,v) + pow(discriminant, .5))/dot(w,w);
    exit_hit.t  = (-1.0*dot(w,v) - pow(discriminant, .5))/ dot(w,w);

    enter_hit.object = this;
    enter_hit.ray_exiting = false;
    hits.push_back(enter_hit);

    exit_hit.object = this;
    exit_hit.ray_exiting = true;
    hits.push_back(exit_hit);

    return true;

  } else {

    enter_hit.t = (-1.0*dot(w,v) + pow(discriminant, .5))/dot(w,w);

    enter_hit.object = this;
    enter_hit.ray_exiting = false;
    hits.push_back(enter_hit);

    return true;

  }

  return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    // The normal of a sphere is the vector from the center of the sphere to the point
    normal = center - point;

    normal =normal.normalized(); // normalize the normal.

    return normal;
}
