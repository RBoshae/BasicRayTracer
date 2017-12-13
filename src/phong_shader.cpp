#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"


vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color;

    vec3 diffuse_component = vec3(0,0,0);   // Used for diffuse color
    vec3 specular_component = vec3(0,0,0);   // Used for diffuse color
    vec3 light_color = vec3(0,0,0);
    vec3 L = vec3(0,0,0);
    vec3 reflectance_vector = vec3(0,0,0);
    vec3 C = vec3(0,0,0);

    // TODO: Shadows in Progress
    if(world.enable_shadows) {
      for (unsigned int i = 0; i < world.lights.size(); i++){

        // Contruct a ray from object to light
        Ray ray_from_object_to_light_source;
        ray_from_object_to_light_source.direction = (world.lights.at(i)->position - intersection_point).normalized();
        ray_from_object_to_light_source.endpoint = intersection_point + small_t*ray_from_object_to_light_source.direction;



        Hit intercepting_object_hit;

        Object* intercepting_object = world.Closest_Intersection(ray_from_object_to_light_source, intercepting_object_hit);

        double distance_between_object_and_light = (world.lights.at(i)->position - intersection_point ).magnitude();

        //double distance_between_object_and_hit = ray_from_object_to_light_source.Point(intercepting_object_hit.t).magnitude();

        double distance_between_object_and_hit = intercepting_object_hit.t;


        // if there is no interefering object between the starting object and the light source
        if (intercepting_object == nullptr || distance_between_object_and_light <= distance_between_object_and_hit /*(distance_between_object_and_light < ray_from_object_to_light_source.Point(intercepting_object_hit.t +small_t).magnitude()*/){
          //std::cout << small_t << "\n";

          // std::cout << "distance_from_light = " <<  distance_from_light << '\n';
          // std::cout << "intercepting_object.t = " <<  intercepting_object_hit.t << '\n';
          // std::cout << "intercepting_object_hit.t *(intercepting_object_hit.t *ray_from_object_to_light_source.direction).magnitude() = " <<  (intercepting_object_hit.t *ray_from_object_to_light_source.direction).magnitude() << '\n';

          //std::cout << "ray_from_object_to_light_source.Point(intercepting_object_hit.t) = " << ray_from_object_to_light_source.Point(intercepting_object_hit.t) << '\n';

          light_color = world.lights.at(i)->Emitted_Light(ray)/(world.lights.at(i)->position - intersection_point).magnitude_squared();

          L = (world.lights.at(i)->position - intersection_point).normalized();

          diffuse_component += std::max( 0.0, dot( same_side_normal.normalized(), L )) * color_diffuse * light_color;

          // calculating the reflectance value;
          reflectance_vector = (((dot(L,same_side_normal.normalized()) * same_side_normal * 2)-L));
          //reflectance_vector = L - (L-dot(L,same_side_normal)*same_side_normal.normalized())*2;
          reflectance_vector= reflectance_vector.normalized();

          // calculating the camera vector
          C = (ray.endpoint - intersection_point).normalized();
          // dot(r,v)

          specular_component += pow(std::max( 0.0, dot( C, reflectance_vector )), specular_power)  * light_color * color_specular;

        }
      }
      color = world.ambient_color*world.ambient_intensity*color_ambient + diffuse_component + specular_component;

      return color;
    } else { // shadows not enabled
      for (unsigned int i = 0; i < world.lights.size(); i++){

        light_color = world.lights.at(i)->Emitted_Light(ray)/(world.lights.at(i)->position - intersection_point).magnitude_squared();

        L = (world.lights.at(i)->position - intersection_point).normalized();

        diffuse_component += std::max( 0.0, dot( same_side_normal.normalized(), L )) * color_diffuse * light_color;

        // calculating the reflectance value;
        reflectance_vector = (((dot(L,same_side_normal.normalized()) * same_side_normal * 2)-L));
        //reflectance_vector = L - (L-dot(L,same_side_normal)*same_side_normal.normalized())*2;
        reflectance_vector= reflectance_vector.normalized();

        // calculating the camera vector
        C = (ray.endpoint - intersection_point).normalized();
        // dot(r,v)

        specular_component += pow(std::max( 0.0, dot( C, reflectance_vector )), specular_power)  * light_color * color_specular;

      }
      color = world.ambient_color*world.ambient_intensity*color_ambient + diffuse_component + specular_component;

      return color;
    }
}
