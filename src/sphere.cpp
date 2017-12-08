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

    // std::cout << "pow(dot(w,v),2) " << pow(dot(w,v),2) << '\n';
    // std::cout << "(dot(w,w)*(dot(v,v) " << dot(w,w)*dot(v,v) << '\n';
    // std::cout << "pow(radius,2) " << pow(radius,2) << '\n';

    // Compute discriminant
    discriminant = pow(dot(w,v),2) - (dot(w,w)*(dot(v,v) - radius*radius));
    //discriminant = pow(dot(w,v),2) - (dot(w,w)*(dot(v,v) - pow(this->radius,2)));
    //discriminant = pow(dot(ray.direction , ray.endpoint),2) - (dot(w,w)*(dot(v,v) - pow(this->radius,2)));
    Hit hit;
    //std::cout << "discriminant " << discriminant<< '\n';

    if (discriminant >= 0){
      // std::cout << "discriminant " << discriminant<< '\n';
      // std::cout << "Greate than 0" << '\n';
      hit.t = (-1.0*dot(w,v) + pow(discriminant, .5))/dot(w,w);
      // std::cout<< hit.t;
      hit.object = this;

      if(hit.t >= 0) {
        hits.push_back(hit);

      }

      hit.t = (-1.0*dot(w,v) - pow(discriminant, .5))/ dot(w,w);
      if(hit.t >= 0) {
        hits.push_back(hit);
      }
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

    normal/=radius; // normalize the normal.

    return normal;
}
