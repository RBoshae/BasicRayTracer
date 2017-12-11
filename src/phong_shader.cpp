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

    vec3 tmpd = vec3(0,0,0);                 // Used for diffuse color
    vec3 light_color = vec3(0,0,0);
    vec3 L = vec3(0,0,0);

    // TODO: determine the color
    // std::cout << "world.lights" << world.lights[1]<< '\n';

    // Redundant normalization
    //same_side_normal = same_side_normal/pow(dot(same_side_normal,same_side_normal),.5);

    //light color is the (color of the light)/(distance to the light)2

    for (unsigned int i = 0; i < world.lights.size(); i++){

      // vec3 light_color = world.lights.at(i)->color/(pow(dot(world.lights.at(i)->position - intersection_point, intersection_point),2));

      light_color = world.lights.at(i)->Emitted_Light(ray)/(world.lights.at(i)->position - intersection_point).magnitude_squared();

      // std::cout << "light color " << light_color << '\n';

      L = (world.lights.at(i)->position - intersection_point).normalized();

      // std::cout << "L " << L << '\n';
      // std::cout << "same_side_normal " << same_side_normal << '\n';
      // std::cout << "same_side_normal.normalized() " << same_side_normal.normalized() << '\n';

      tmpd += std::max( 0.0, dot( same_side_normal.normalized(), L )) * color_diffuse * light_color;

        // std::cout << "dot( same_side_normal.normalized(), L ) " << dot( same_side_normal.normalized(), L ) << std::endl << std::endl;
      // std::cout << "tmpd " << tmpd << std::endl << std::endl;
    }

    //max(dot(L,N),0)∗color_diffuse∗light_color

    color = world.ambient_color*world.ambient_intensity*color_ambient + tmpd;

    return color;
}
