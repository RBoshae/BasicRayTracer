#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    // std::cout << "x1 " << x1 << std::endl;
    // std::cout << "normal " << normal << std::endl;

    double denominator;

    if ((denominator = dot(normal,ray.direction)) != 0) {
      Hit hit;

      if((hit.t = -dot(normal,(ray.endpoint - x1))/(denominator)) >=0) {
        hit.object = this;
        if(hit.t >= 0) {
          hit.ray_exiting = false;
          hits.push_back(hit);
          return true;
        }
      } else if(-dot(normal,(ray.endpoint-x1)) != 0) {
        // infinite hits
        //std::cout << "Unhandled case in plane.cpp\n";
        return false;
      } else {
        return false;
      }

    }
    return false;
}

vec3 Plane::
Normal(const vec3& point) const
{

    return normal;
}


// to test code: ./ray_tracer -i tests/00.txt -s tests/00.png
