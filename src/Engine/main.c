/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:24:32 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/20 15:39:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


t_tuple vector(double x, double y, double z)
{
    return (t_tuple){x, y, z, 0.0};
}

t_tuple tuple(double x, double y, double z, double w)
{
    t_tuple t = {x, y, z, w};
    return t;
}

t_tuple point(double x, double y, double z)
{
    t_tuple t = {x, y, z, 1.0};
    return t;
}

int equal(double a, double b)
{
    return (fabs(a - b) < EPSILON);
}

t_tuple add_tuples(t_tuple a, t_tuple b)
{
    t_tuple result = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    return result;
}

t_tuple substract_tuples(t_tuple a, t_tuple b)
{
    t_tuple result = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    return result;
}
int tuple_equals(t_tuple a, t_tuple b)
{
    return equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z) && equal(a.w, b.w);
}

t_tuple negate_tuple(t_tuple t)
{
    t_tuple result = {-t.x, -t.y, -t.z, -t.w};
    return (result);
}
t_vector tuple_to_vector(t_tuple t)
{
    t_vector v = {t.x, t.y, t.z};
    return v;
}


t_tuple multiply_tuple_scalar(t_tuple a, double scalar)
{
    t_tuple result = {a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar};
    return (result);
}

t_tuple divide_tuple_scalar(t_tuple a, double scalar)
{
    t_tuple result = {a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar};
    return (result);
}

t_tuple normalize(t_tuple v) 
{
    double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    
    if (magnitude == 0.0)
        return v;
    
    t_tuple normalized_vector;
    normalized_vector.x = v.x / magnitude;
    normalized_vector.y = v.y / magnitude;
    normalized_vector.z = v.z / magnitude;
    
    return normalized_vector;
}

double magnitude (t_tuple t)
{ 
    return (sqrt(t.x * t.x + t.y * t.y + t.z * t.z));
}

double dot(t_tuple a, t_tuple b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

t_vector cross(t_tuple v, t_tuple w)
{   
    t_vector result;
    
    result.x = v.y * w.z - v.z * w.y;
    result.y = v.z * w.x - v.x * w.z;
    result.z = v.x * w.y - v.y * w.x;
    return (result);
}


t_projectile tick(t_environnement env, t_projectile proj)
{
    t_tuple position = add_tuples(proj.position, proj.velocity);
    t_tuple velocity = add_tuples(add_tuples(proj.velocity, env.gravity), env.wind);
    return (t_projectile){position, velocity};
}

t_canvas canvas(int width, int height)
{
    t_canvas c;
    int i = 0;
    c.width = width;
    c.height = height;
    c.pixels = (t_color*)malloc(width * height * sizeof(t_color));
    
    while (i < width * height)
    {
        c.pixels[i] = (t_color){0, 0, 0};
        i++;
    }
    
    return c;
}

void write_pixel(t_canvas* c, int x, int y, t_color color)
{
    if (x >= 0 && x < c->width && y >= 0 && y < c->height) {
        c->pixels[y * c->width + x] = color;
    }
}

t_ray ray(t_tuple origin, t_tuple direction)
{
    t_ray r;
    r.origin = origin;
    r.direction = direction;
    return r;
}

t_tuple position(t_ray r, double t)
{
    t_tuple distance = multiply_tuple_scalar(r.direction, t);
    return add_tuples(r.origin, distance);
}

t_sphere sphere()
{
    t_sphere s;
    s.center = point(0, 0, 0);
    s.radius = 1;
    s.transform = identity_matrix();
    s.material = material();
    return s;
}

void set_transform(t_sphere *s, t_matrix t)
{
    if (s != NULL)
        s->transform = t;
}

t_intersections intersect(t_sphere *s, t_ray r)
{
    t_matrix inverse_transform = inverse(s->transform);

    
    t_ray transformed_ray = transform(r, inverse_transform);


    t_tuple sphere_to_ray = substract_tuples(transformed_ray.origin, s->center);

    double a = dot(transformed_ray.direction, transformed_ray.direction);
    double b = 2.0 * dot(transformed_ray.direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - (s->radius * s->radius);

    double discriminant = b * b - 4 * a * c;

    t_intersections xs;
    if (discriminant < 0) {
    xs.count = 0;
    xs.intersections = NULL;
    } else {
        xs.count = (discriminant == 0) ? 2 : 2;
        xs.intersections = malloc(xs.count * sizeof(t_intersection));
        if (xs.intersections == NULL) exit(EXIT_FAILURE);

        double root = sqrt(discriminant);

        double t1 = (-b - root) / (2 * a);
        double t2 = (-b + root) / (2 * a);

        if (t1 > t2) {
            double temp = t1;
            t1 = t2;
            t2 = temp;
        }

        xs.intersections[0].t = t1;
        xs.intersections[0].sphere = s;

        if (discriminant == 0) {
            xs.intersections[1].t = t1;
        } else {
            xs.intersections[1].t = t2;
        }
        xs.intersections[1].sphere = s;
    }
    return xs;
}



t_intersection intersection(double t, t_sphere *object)
{
    t_intersection i;
    i.t = t;
    i.sphere = object;
    return i;
}

t_intersections intersections(int count, t_intersection *inter_arr)
{
    t_intersections xs;
    int i = 0;
    xs.count = count;
    xs.intersections = (t_intersection *)malloc(sizeof(t_intersection) * count);
    while (i < count)
    {
        xs.intersections[i] = inter_arr[i];
        i++;
    }
    return xs;
}

t_intersection *hit(t_intersections *intersections)
{
    int i = 0;
    t_intersection *hit = NULL;
    while (i < intersections->count)
    {
        if (intersections->intersections[i].t >= 0)
        {
            if (hit == NULL || intersections->intersections[i].t < hit->t)
                hit = &(intersections->intersections[i]);
        }
        i++;
    }
    return hit;
}
void matrix_set(t_matrix *m, int row, int col, float value)\
{
    int index = row * m->cols + col;
    m->elements[index] = value;
}

float matrix_get(t_matrix *m, int row, int col)
{
    int index = row * m->cols + col;
    return m->elements[index];
}

t_ray transform(t_ray ray, t_matrix m)
{
    t_ray transformed_ray;
    transformed_ray.origin = multiply_matrix_tuple(m, ray.origin);
    transformed_ray.direction = multiply_matrix_tuple(m, ray.direction);
    return transformed_ray;
}

t_tuple    normal_at(t_sphere sphere, t_tuple p)
{
    t_tuple object_point = multiply_matrix_tuple(inverse(sphere.transform), p);\
    t_tuple object_normal = substract_tuples(object_point, (t_tuple){sphere.center.x, sphere.center.y, sphere.center.z, 1});
    t_tuple world_normal = multiply_matrix_tuple(transpose_matrix(inverse(sphere.transform)), object_normal);
    
    world_normal.w = 0;
    return (normalize(world_normal));
}

t_tuple reflect(t_tuple incident, t_tuple normal)
{
    t_tuple result;
    float dot_product = dot(incident, normal);
    result.x = incident.x - 2 * dot_product * normal.x;
    result.y = incident.y - 2 * dot_product * normal.y;
    result.z = incident.z - 2 * dot_product * normal.z;
    result.w  = 0;
    return result;
}
t_light point_light(t_vector position, double intensity, int color[3])
{
    t_light light;
    light.position = position;
    light.intensity = intensity;
    light.color[0] = color[0];
    light.color[1] = color[1];
    light.color[2] = color[2];
    return light;
}

t_material material()
{
    t_material m;
    m.color[0] = 1;
    m.color[1] = 1;
    m.color[2] = 1;
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.shininess = 200.0;
    return m;
}



void render_sphere(t_vars *vars)
{
    int x = 0; 
    int y = 0;
    int canvas_pixel = 1200;
    double wall_size = 0.3;
    t_sphere s = sphere();
    double pixel_size = wall_size / canvas_pixel;
    double wall_z = -4.5;
    double half = wall_size / 2.0;
    int color = 0x00FF0000; 

    while (y < canvas_pixel)
    {
        double world_y = half - pixel_size * y - (wall_size / 2.0 - canvas_pixel / 2.0 * pixel_size);
        x = 0;
        while (x < canvas_pixel)
        {
            double world_x = -half + pixel_size * x + (wall_size / 2.0 - canvas_pixel / 2.0 * pixel_size);
            t_tuple pixel_position = {world_x, world_y, wall_z, 1};
            t_tuple ray_direction = normalize(substract_tuples(pixel_position, (t_tuple){0, 0, -5, 1}));
            t_ray r = ray((t_tuple){0, 0, -5, 1}, ray_direction);
            t_intersections result = intersect(&s, r);
            t_intersection *intersection = hit(&result);
            if (intersection != NULL)
                my_mlx_pixel_put(vars, x, y, color);
            x++;
        }
        y++;
    }
}


int main() {
    t_vars  vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniLibX - Sphere Rendering");
    vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bits_per_pixel, &vars.img.line_length,
                                     &vars.img.endian);

    render_sphere(&vars);

    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
    mlx_loop(vars.mlx);
    return (0);
}



