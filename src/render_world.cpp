#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"


Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray, Hit& hit)
{
    // TODO // IN PROGRESS
    Object* closest_object = NULL;
    double min_t = std::numeric_limits<double>::infinity(); // Set min_t to a large value
    // For each object in objects
    for (unsigned int objects_index = 0; objects_index < objects.size(); objects_index++) {

      std::vector<Hit> list_of_hits;          // create an empty list of hits

      // use object.intersect to fill the hits
      objects.at(objects_index)->Intersection(ray, list_of_hits);

      // For eacht h in list of hits
      for (unsigned int hit_index = 0; hit_index < list_of_hits.size(); hit_index++) {
        // if h is closest so far ( with smallest t, that is larger than small_t)
        if (list_of_hits.at(hit_index).t < min_t && list_of_hits.at(hit_index).t < small_t) {

          closest_object = objects.at(objects_index); // Set the object as the closest_object
          hit = list_of_hits.at(hit_index);                         // Set hit to h
          min_t = list_of_hits.at(hit_index).t;                 // Update min_t

        }


      }

    }

    return closest_object;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    Ray ray; // TODO: set up the initial view ray here
    // Notes from Lab 9
    // end_point: camera poisition (from camera class)
    // direction: a unit vector from the camera position to the world position of the pixel.
    ray.endpoint = camera.position;                                                           // camera poisition (from camera class
    ray.direction = (camera.World_Position(pixel_index) - camera.position).normalized();      // vector that has been normalized
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    // TODO
    vec3 color;

    vec3 dummy;           // dummy variable for now
    Hit hit;
    Object *obj = Closest_Intersection(ray, hit);

    // determine the color here
    if (obj != NULL) {
      color=obj->material_shader->Shade_Surface(ray,dummy,dummy,1);
    } else {
      color=background_shader->Shade_Surface(ray, dummy, dummy, 1);

    }

    return color;
}
