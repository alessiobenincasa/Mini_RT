/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:24:32 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/18 15:33:30 by albeninc         ###   ########.fr       */
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
int tuple_equals(t_tuple a, t_tuple b) {
    return equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z) && equal(a.w, b.w);
}

t_tuple negate_tuple(t_tuple t)
{
    t_tuple result = {-t.x, -t.y, -t.z, -t.w};
    return (result);
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
    
    // Si le vecteur est nul, retourner le vecteur lui-même
    if (magnitude == 0.0) {
        return v;
    }
    
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
    return (t_color){0, 0, 0}; // Return black as a default/fallback color}
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

t_matrix multiply_matrices(t_matrix a, t_matrix b) {
    if (a.cols != b.rows) {
        printf("Error: Matrices cannot be multiplied due to incompatible dimensions.\n");
        return create_matrix(0, 0, NULL);
    }
    
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


/*
int main() {
    // Elements for matrix A
    float elementsA[16] = {
        1, 2, 3, 4,
        2, 4, 4, 2,
        8, 6, 4, 1,
        0, 0, 0, 1
    };
    // Elements for matrix B
    float elementsB[4] = {
        1, 2, 3, 1,
    };

    // Create matrices A and B
    t_matrix A = create_matrix(4, 4, elementsA);
    t_matrix B = create_matrix(4, 1, elementsB);
    t_matrix C = multiply_matrices(A, B);
    

    printf("Result of A multiplied by B:\n");
    for (int i = 0; i < C.rows; i++) {
        for (int j = 0; j < C.cols; j++) {
            printf("%8.2f", C.elements[i * C.cols + j]);
        }
        printf("\n");
    }

    // Free the matrices when done
    free_matrix(&A);
    free_matrix(&B);
    free_matrix(&C);
    return 0;
}

*/