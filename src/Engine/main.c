/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:24:32 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/19 03:58:03 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sphere g_sphere;
t_plane g_plane;
t_light g_light;
t_cylinder g_cylinder;
 /*
void render_scene(t_vars *vars, t_sphere *sphere, t_plane *plane, t_light *light)
{
    int y = 0;
    int x;
    while (y < HEIGHT) {
        x = 0;
        while (x < WIDTH) {
            t_ray ray = {
                .origin = {0, 0, 0},
                .direction = normalize((t_vector){
                    x - WIDTH / 2,
                    y - HEIGHT / 2,
                    -WIDTH / (2 * tan(M_PI / 6))
                })
            };
            
            float t_sphere_value = intersect_ray_sphere(ray, *sphere);
            float t_plane_value = intersect_ray_plane(ray, *plane);
            int color = create_trgb(0, 0, 0, 255);

            if (t_sphere_value < INFINITY && (t_sphere_value < t_plane_value || t_plane_value == INFINITY)) {
                t_vector intersection_point = vector_add(ray.origin, vector_scale(ray.direction, t_sphere_value));
                t_vector normal = normalize(vector_sub(intersection_point, sphere->center));
                t_vector light_dir = normalize(vector_sub(light->position, intersection_point));
                double diff = fmax(dot(normal, light_dir), 0.0) * light->intensity;
                color = adjust_color_by_light(sphere->color, diff);
            } else if (t_plane_value != INFINITY) {
                color = create_trgb(0, plane->color[0], plane->color[1], plane->color[2]);
            }

            my_mlx_pixel_put(vars, x, y, color);
            x++;
        }
        y++;
    }
}
*/
/*
int key_hook(int keycode, t_vars *vars) 
{
    if (keycode == 'w') {
        g_sphere.diameter = fmax(1, g_sphere.diameter + 1);
    } else if (keycode == 's') {
        g_sphere.diameter = fmin(100, g_sphere.diameter - 1);
    }

    render_scene(vars, &g_sphere, &g_plane, &g_light);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
    return 0;
}
*/

/*
int main(void)
{
    t_vars vars;
    g_sphere = (t_sphere){
        .center = {0, 0, -20},
        .diameter = 10.0,
        .color = {255, 0, 0}
    };

    g_plane = (t_plane){
        .point = {0.0, -5.0, 0.0},
        .normal = {0.0, 1.0, 0.0},
        .color = {0, 255, 0}
    };

    g_light = (t_light){
        .position = {-20.0, 20.0, 20.0},
        .intensity = 0.7,
        .color = {255, 255, 255}
    };

     g_cylinder = (t_cylinder){
        .center = {2.0, 0.0, -15.0}, // Example position
        .direction = {0.0, 1.0, 0.0}, // Example orientation (aligned with Y axis)
        .diameter = 3.0,
        .height = 10.0,
        .color = {0, 0, 255} // Blue
    };

    vars.camera.fov = 90;
    
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniRT - bitch");
    vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
    //mlx_key_hook(vars.win, key_hook, &vars);
    render_cylinder_basic(&vars, g_cylinder, g_light);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
    mlx_loop(vars.mlx);

    return 0;
}

*/

t_color color(float red, float green, float blue)
{
    t_color c;
    c.red = red;
    c.green = green;
    c.blue = blue;
    return c;
}

t_color add_colors(t_color c1, t_color c2)
{
    return color(c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue);
}

t_color subtract_colors(t_color c1, t_color c2)
{
    return color(c1.red - c2.red, c1.green - c2.green, c1.blue - c2.blue);
}

t_color multiply_color_scalar(t_color c, float scalar)
{
    return color(c.red * scalar, c.green * scalar, c.blue * scalar);
}

t_color hadarmard_product(t_color c, t_color b)
{
    return color(c.red * b.red, c.green * b.green, c.blue * b.blue);
}


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

t_color pixel_at(t_canvas c, int x, int y)
{
    if (x >= 0 && x < c.width && y >= 0 && y < c.height)
        return c.pixels[y * c.width + x];
    return (t_color){0, 0, 0};
}

t_matrix create_matrix(int rows, int cols, float elements[])
{
    t_matrix m;
    m.rows = rows;
    m.cols = cols;
    m.elements = (float*)malloc(rows * cols * sizeof(float));
    if (elements != NULL)
        ft_memcpy(m.elements, elements, rows * cols * sizeof(float));
    else
        ft_memset(m.elements, 0, rows * cols * sizeof(float));
    return (m);
}

float get_element(t_matrix m, int row, int col)
{
    if (row >= 0 && row < m.rows && col >= 0 && col < m.cols)
        return (m.elements[row * m.cols + col]);
    return (0.0f);
}
int matrices_equal(t_matrix a, t_matrix b)
{
    int i = 0;
    
    if (a.rows != b.rows || a.cols != b.cols)
        return 0;
    while (i < a.rows * a.cols)
    {
        if (fabs(a.elements[i] - b.elements[i]) > EPSILON)
            return (0);
        i++;
    }
    return(1);
}

t_matrix multiply_matrices(t_matrix a, t_matrix b)
{
    if (a.cols != b.rows)
        return create_matrix(0, 0, NULL);
    
    t_matrix c = create_matrix(a.rows, b.cols, NULL);
    int i = 0;

    while (i < a.rows) {
        int j = 0;
        while (j < b.cols) {
            float sum = 0;
            int k = 0;
            while (k < a.cols) {
                sum += a.elements[i * a.cols + k] * b.elements[k * b.cols + j];
                k++;
            }
            c.elements[i * c.cols + j] = sum;
            j++;
        }
        i++;
    }
    
    return c;
}

t_tuple multiply_matrix_tuple(t_matrix m, t_tuple t)
{
    float elements[4] = {t.x, t.y, t.z, t.w};
    t_matrix result = multiply_matrices(m, create_matrix(4, 1, elements));
    return tuple(result.elements[0], result.elements[1], result.elements[2], result.elements[3]);
}

void free_matrix(t_matrix* m)
{
    free(m->elements);
    m->elements = NULL;
}

t_matrix identity_matrix(void)
{
    float elements[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    return create_matrix(4, 4, elements);
}

t_matrix transpose_matrix(t_matrix matrix)
{
    t_matrix transposed;
    transposed.rows = matrix.cols;
    transposed.cols = matrix.rows;
    transposed.elements = (float *)malloc(sizeof(float) * transposed.rows * transposed.cols);
    if (transposed.elements == NULL)
    {
        perror("Memory allocation error for transposed matrix");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < matrix.rows)
    {
        int j = 0;
        while (j < matrix.cols)
        {

            int originalIndex = i * matrix.cols + j;
            int transposedIndex = j * transposed.cols + i;
            transposed.elements[transposedIndex] = matrix.elements[originalIndex];
            j++;
        }
        i++;
    }
    
    return (transposed);
}


t_matrix submatrix(t_matrix matrix, int remove_row, int remove_col)
{
    t_matrix sub;
    sub.rows = matrix.rows - 1;
    sub.cols = matrix.cols - 1;
    sub.elements = malloc(sub.rows * sub.cols * sizeof(float));

    if (!sub.elements) 
        exit(EXIT_FAILURE);
    int i = 0, sub_i = 0;
    while (i < matrix.rows)
    {
        if (i != remove_row)
        {
            int j = 0, sub_j = 0;
            while (j < matrix.cols)
            {
                if (j != remove_col)
                {
                    sub.elements[sub_i * sub.cols + sub_j] = matrix.elements[i * matrix.cols + j];
                    sub_j++;
                }
                j++;
            }
            sub_i++;
        }
        i++;
    }
    
    return sub;
}

float minor(t_matrix matrix, int row, int col)
{
    t_matrix sub = submatrix(matrix, row, col);
    float det = determinant(sub);
    free(sub.elements);
    return det;
}
float cofactor(t_matrix matrix, int row, int col)
{
    float min = minor(matrix, row, col);
    if ((row + col) % 2 == 0)
        return min;
    
    else
        return -min;
}

float determinant(t_matrix M)
{
    if (M.rows != M.cols)
        exit(EXIT_FAILURE);
    
    float det = 0;
    if (M.rows == 2)
        det = M.elements[0] * M.elements[3] - M.elements[1] * M.elements[2];
    else 
    {
        int column = 0;
        while (column < M.cols)
        {
            det += M.elements[column] * cofactor(M, 0, column);
            column++;
        }
    }
    return det;
}

t_matrix inverse(t_matrix A)
{
    float det = determinant(A);
    if (det == 0)
        exit(EXIT_FAILURE);

    t_matrix B = { .rows = A.rows, .cols = A.cols, .elements = malloc(A.rows * A.cols * sizeof(float)) };
    int i = 0;
    while (i < A.rows)
    {
        int j = 0;
        while (j < A.cols)
        {
            float cof = cofactor(A, i, j);
            B.elements[j * B.cols + i] = cof / det;
            j++;
        }
        i++;
    }
    return B;
}

int is_invertible(t_matrix A)
{
    return determinant(A) != 0;
}
t_matrix translation(float x, float y, float z)
{
    t_matrix transform = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    if (!transform.elements)
        exit(EXIT_FAILURE);
    
    int index = 0;
    float elements[] = {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };
    while (index < 16) 
    {
        transform.elements[index] = elements[index];
        index++;
    }
    return transform;
}

t_matrix scaling(float x, float y, float z)
{
    int i = 0;
    t_matrix scale = {4, 4, malloc(16 * sizeof(float))};
    if (!scale.elements)
        exit(EXIT_FAILURE);
    while (i < 16)
    {
        scale.elements[i] = 0;
        i++;
    }
    scale.elements[0] = x;
    scale.elements[5] = y;
    scale.elements[10] = z;
    scale.elements[15] = 1.0;
    return scale;
}
t_matrix rotation_x(float radians)
{
    t_matrix result = {4, 4, malloc(16 * sizeof(float))};
    if (!result.elements)
        exit(EXIT_FAILURE);
        
    int i = 0;
    while (i < 16) {
        result.elements[i] = 0;
        i++;
    }
    result.elements[0] = 1;
    result.elements[5] = cos(radians);
    result.elements[6] = -sin(radians);
    result.elements[9] = sin(radians);
    result.elements[10] = cos(radians);
    result.elements[15] = 1;
    return result;
}
t_matrix rotation_y(float radians)
{
    int i = 0;
    t_matrix result = {4, 4, malloc(16 * sizeof(float))};
    if (!result.elements)
        exit(EXIT_FAILURE);

    while (i < 16)
    {
        result.elements[i] = 0;
        i++;
    }
    result.elements[0] = cos(radians);
    result.elements[2] = sin(radians);
    result.elements[5] = 1;
    result.elements[8] = -sin(radians);
    result.elements[10] = cos(radians);
    result.elements[15] = 1;

    return result;
}

t_matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
    t_matrix result = {4, 4, malloc(16 * sizeof(float))};
    int i = 0;
    if (!result.elements)
        exit(EXIT_FAILURE);
        
    while (i < 16)
    {
        result.elements[i] = 0;
        i++;
    }
    result.elements[0] = 1;
    result.elements[5] = 1;
    result.elements[10] = 1;
    result.elements[15] = 1;


    result.elements[1] = xy; 
    result.elements[2] = xz;
    result.elements[4] = yx;
    result.elements[6] = yz;
    result.elements[8] = zx;
    result.elements[9] = zy;

    return result;
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

t_intersections intersections(int count, t_intersection *intersectionsArray)
{
    t_intersections xs;
    int i = 0;
    xs.count = count;
    xs.intersections = (t_intersection *)malloc(sizeof(t_intersection) * count);
    while (i < count)
    {
        xs.intersections[i] = intersectionsArray[i];
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

void render_sphere(t_vars *vars) {
    int x, y;
    int canvas_pixel = 500;
    double wall_size = -1.0;
    t_sphere s = sphere();
    double pixel_size = wall_size / canvas_pixel;
    double wall_z = -3;
    double half = wall_size / 2.0;
    int color = 0x00FF0000; 

    for (y = 0; y < canvas_pixel; y++) {
        double world_y = half - pixel_size * y - (wall_size / 2.0 - canvas_pixel / 2.0 * pixel_size);
        for (x = 0; x < canvas_pixel; x++) {
            double world_x = -half + pixel_size * x + (wall_size / 2.0 - canvas_pixel / 2.0 * pixel_size);
            t_tuple pixel_position = {world_x, world_y, wall_z, 1};
            t_tuple ray_direction = normalize(substract_tuples(pixel_position, (t_tuple){0, 0, -5, 1}));
            t_ray r = ray((t_tuple){0, 0, -5, 1}, ray_direction);
            t_intersections result = intersect(&s, r);
            t_intersection *intersection = hit(&result);
            if (intersection != NULL) {
                my_mlx_pixel_put(vars, x, y, color);
            }
        }
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