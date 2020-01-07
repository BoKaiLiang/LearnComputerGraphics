#include "mat.h"

#include "math.h"

// Matrix 3x3 operations
mat3_t mat3_identity()
{   
    mat3_t m;
    m.vec[0] = vec3_init(1.0f, 0.0f, 0.0f);
    m.vec[1] = vec3_init(0.0f, 1.0f, 0.0f);
    m.vec[2] = vec3_init(0.0f, 0.0f, 1.0f);

    return m;
}

mat3_t mat3_from_vec3(vec3_t col0, vec3_t col1, vec3_t col2)
{
    mat3_t m;
    m.vec[0] = vec3_init(col0.x, col0.y, col0.z);
    m.vec[1] = vec3_init(col1.x, col1.y, col1.z);
    m.vec[2] = vec3_init(col2.x, col2.y, col2.z);

    return m;
}

mat3_t mat3_from_mat4(mat4_t mat)
{
    mat3_t m;
    
    m.vec[0] = vec3_init(mat.vec[0].x, mat.vec[0].y, mat.vec[0].z);
    m.vec[1] = vec3_init(mat.vec[1].x, mat.vec[1].y, mat.vec[1].z);
    m.vec[2] = vec3_init(mat.vec[2].x, mat.vec[2].y, mat.vec[2].z);

    return m;
}

vec3_t mat3_mul_vec3(mat3_t mat, vec3_t vec)
{
    float product[3];
    for (int i = 0; i < 3; i++)
    {
        float x = mat.mat[0][i] * vec.x;
        float y = mat.mat[1][i] * vec.y;
        float z = mat.mat[2][i] * vec.z;
        product[i] = x * y * z;
    }

    return vec3_init(product[0], product[1], product[2]);
}

mat3_t mat3_mul_mat3(mat3_t mat1, mat3_t mat2)
{
    mat3_t m;

    m.mat[0][0] = mat1.mat[0][0] * mat2.mat[0][0] + mat1.mat[1][0] * mat2.mat[0][1] + mat1.mat[2][0] * mat2.mat[0][2];
    m.mat[0][1] = mat1.mat[0][1] * mat2.mat[0][0] + mat1.mat[1][1] * mat2.mat[0][1] + mat1.mat[2][1] * mat2.mat[0][2];
    m.mat[0][2] = mat1.mat[0][2] * mat2.mat[0][0] + mat1.mat[1][2] * mat2.mat[0][1] + mat1.mat[2][2] * mat2.mat[0][2];

    m.mat[1][0] = mat1.mat[0][0] * mat2.mat[1][0] + mat1.mat[1][0] * mat2.mat[1][1] + mat1.mat[2][0] * mat2.mat[1][2];
    m.mat[1][1] = mat1.mat[0][1] * mat2.mat[1][1] + mat1.mat[1][1] * mat2.mat[1][1] + mat1.mat[2][1] * mat2.mat[1][2];
    m.mat[1][2] = mat1.mat[0][2] * mat2.mat[1][2] + mat1.mat[1][2] * mat2.mat[1][1] + mat1.mat[2][2] * mat2.mat[1][2];

    m.mat[2][0] = mat1.mat[0][0] * mat2.mat[2][0] + mat1.mat[1][0] * mat2.mat[2][1] + mat1.mat[2][0] * mat2.mat[2][2];
    m.mat[2][1] = mat1.mat[0][1] * mat2.mat[2][1] + mat1.mat[1][1] * mat2.mat[2][1] + mat1.mat[2][1] * mat2.mat[2][2];
    m.mat[2][2] = mat1.mat[0][2] * mat2.mat[2][2] + mat1.mat[1][2] * mat2.mat[2][1] + mat1.mat[2][2] * mat2.mat[2][2];

    return m;
}

// Matrix 4x4 operations
mat4_t mat4_identity()
{
    mat4_t m;
    m.vec[0] = vec4_init(1.0f, 0.0f, 0.0f, 0.0f);
    m.vec[1] = vec4_init(0.0f, 1.0f, 0.0f, 0.0f);
    m.vec[2] = vec4_init(0.0f, 0.0f, 1.0f, 0.0f);
    m.vec[3] = vec4_init(0.0f, 0.0f, 0.0f, 1.0f);

    return m;
}

mat4_t mat4_from_vec4(vec4_t col0, vec4_t col1, vec4_t col2, vec4_t col3)
{
    mat4_t m;
    m.vec[0] = vec4_init(col0.x, col0.y, col0.z, col0.w);
    m.vec[1] = vec4_init(col1.x, col1.y, col1.z, col1.w);
    m.vec[2] = vec4_init(col2.x, col2.y, col2.z, col2.w);
    m.vec[3] = vec4_init(col3.x, col3.y, col3.z, col3.w);

    return m;
}

mat4_t mat4_from_mat3(mat3_t mat)
{
    mat4_t m;
    
    m.vec[0] = vec4_init(mat.vec[0].x, mat.vec[0].y, mat.vec[0].z, 0.0f);
    m.vec[1] = vec4_init(mat.vec[1].x, mat.vec[1].y, mat.vec[1].z, 0.0f);
    m.vec[2] = vec4_init(mat.vec[2].x, mat.vec[2].y, mat.vec[2].z, 0.0f);
    m.vec[3] = vec4_init(0.0f, 0.0f, 0.0f, 0.0f);

    return m;
}

vec4_t mat4_mul_vec4(mat4_t mat, vec4_t vec)
{
    float product[4];
    for (int i = 0; i < 4; i++)
    {
        float x = mat.mat[0][i] * vec.x;
        float y = mat.mat[1][i] * vec.y;
        float z = mat.mat[2][i] * vec.z;
        float w = mat.mat[3][i] * vec.w;
        product[i] = x * y * z * w;
    }

    return vec4_init(product[0], product[1], product[2], product[3]);
}

mat4_t mat4_mul_mat4(mat4_t mat1, mat4_t mat2)
{
    mat4_t m;

    m.mat[0][0] = mat1.mat[0][0] * mat2.mat[0][0] + mat1.mat[1][0] * mat2.mat[0][1] + mat1.mat[2][0] * mat2.mat[0][2] + mat1.mat[3][0] * mat2.mat[0][3];
    m.mat[0][1] = mat1.mat[0][1] * mat2.mat[0][0] + mat1.mat[1][1] * mat2.mat[0][1] + mat1.mat[2][1] * mat2.mat[0][2] + mat1.mat[3][1] * mat2.mat[0][3];
    m.mat[0][2] = mat1.mat[0][2] * mat2.mat[0][0] + mat1.mat[1][2] * mat2.mat[0][1] + mat1.mat[2][2] * mat2.mat[0][2] + mat1.mat[3][2] * mat2.mat[0][3];
    m.mat[0][3] = mat1.mat[0][3] * mat2.mat[0][0] + mat1.mat[1][3] * mat2.mat[0][1] + mat1.mat[2][3] * mat2.mat[0][2] + mat1.mat[3][3] * mat2.mat[0][3];

    m.mat[1][0] = mat1.mat[0][0] * mat2.mat[1][0] + mat1.mat[1][0] * mat2.mat[1][1] + mat1.mat[2][0] * mat2.mat[1][2] + mat1.mat[3][0] * mat2.mat[1][3];
    m.mat[1][1] = mat1.mat[0][1] * mat2.mat[1][0] + mat1.mat[1][1] * mat2.mat[1][1] + mat1.mat[2][1] * mat2.mat[1][2] + mat1.mat[3][1] * mat2.mat[1][3];
    m.mat[1][2] = mat1.mat[0][2] * mat2.mat[1][0] + mat1.mat[1][2] * mat2.mat[1][1] + mat1.mat[2][2] * mat2.mat[1][2] + mat1.mat[3][2] * mat2.mat[1][3];
    m.mat[1][3] = mat1.mat[0][3] * mat2.mat[1][0] + mat1.mat[1][3] * mat2.mat[1][1] + mat1.mat[2][3] * mat2.mat[1][2] + mat1.mat[3][3] * mat2.mat[1][3];

    m.mat[2][0] = mat1.mat[0][0] * mat2.mat[2][0] + mat1.mat[1][0] * mat2.mat[2][1] + mat1.mat[2][0] * mat2.mat[2][2] + mat1.mat[3][0] * mat2.mat[2][3];
    m.mat[2][1] = mat1.mat[0][1] * mat2.mat[2][0] + mat1.mat[1][1] * mat2.mat[2][1] + mat1.mat[2][1] * mat2.mat[2][2] + mat1.mat[3][1] * mat2.mat[2][3];
    m.mat[2][2] = mat1.mat[0][2] * mat2.mat[2][0] + mat1.mat[1][2] * mat2.mat[2][1] + mat1.mat[2][2] * mat2.mat[2][2] + mat1.mat[3][2] * mat2.mat[2][3];
    m.mat[2][3] = mat1.mat[0][3] * mat2.mat[2][0] + mat1.mat[1][3] * mat2.mat[2][1] + mat1.mat[2][3] * mat2.mat[2][2] + mat1.mat[3][3] * mat2.mat[2][3];

    m.mat[3][0] = mat1.mat[0][0] * mat2.mat[3][0] + mat1.mat[1][0] * mat2.mat[3][1] + mat1.mat[2][0] * mat2.mat[3][2] + mat1.mat[3][0] * mat2.mat[3][3];
    m.mat[3][1] = mat1.mat[0][1] * mat2.mat[3][0] + mat1.mat[1][1] * mat2.mat[3][1] + mat1.mat[2][1] * mat2.mat[3][2] + mat1.mat[3][1] * mat2.mat[3][3];
    m.mat[3][2] = mat1.mat[0][2] * mat2.mat[3][0] + mat1.mat[1][2] * mat2.mat[3][1] + mat1.mat[2][2] * mat2.mat[3][2] + mat1.mat[3][2] * mat2.mat[3][3];
    m.mat[3][3] = mat1.mat[0][3] * mat2.mat[3][0] + mat1.mat[1][3] * mat2.mat[3][1] + mat1.mat[2][3] * mat2.mat[3][2] + mat1.mat[3][3] * mat2.mat[3][3];

    return m;
}


// Transformations

/*
   1  0  0  x
   0  1  0  y
   0  0  1  z
   0  0  0  1
*/
mat4_t mat4_translate(mat4_t origin, float x, float y, float z)
{
    mat4_t translate = mat4_identity();

    translate.mat[3][0] = x;
    translate.mat[3][1] = y;
    translate.mat[3][2] = z;

    return mat4_mul_mat4(origin, translate);
}

/*
    s = sin(angle), c = cos(angle)
    x = norm.x, y = norm.y, z = norm.z

    x*x*(1-c)+c     x*y*(1-c)-z*s   x*z*(1-c)+y*s   0
    y*x*(1-c)+z*s   y*y*(1-c)+c     y*z*(1-c)-x*s   0
    z*x*(1-c)-y*s   z*y*(1-c)+x*s   z*z*(1-c)+c     0
                0               0           0       1
*/
mat4_t mat4_rotate(mat4_t origin, vec3_t axis, float angle)
{
    mat4_t rotate = mat4_identity();

    vec3_t n = vec3_norm(axis);
    float x = n.x, y = n.y, z = n.z;
    float s = sinf(angle), c = cosf(angle);

    rotate.mat[0][0] = x * x * (1 - c) + c;
    rotate.mat[0][1] = y * x * (1 - c) + z * s;
    rotate.mat[0][2] = z * x * (1 - c) - y * s;

    rotate.mat[1][0] = x * y * (1 - c) - z * s;
    rotate.mat[1][1] = y * y * (1 - c) + c;
    rotate.mat[1][2] = z * y * (1 - c) + x * s;

    rotate.mat[2][0] = x * z * (1 - c) + y * s;
    rotate.mat[2][1] = y * z * (1 - c) - x * s;
    rotate.mat[2][2] = z * z * (1 - c) + c;

    return mat4_mul_mat4(origin, rotate);
}

/*
    x  0  0  0
    0  y  0  0
    0  0  z  0
    0  0  0  1
*/
mat4_t mat4_scale(mat4_t origin, float x, float y, float z)
{
    mat4_t scale = mat4_identity();

    scale.mat[0][0] = x;
    scale.mat[1][1] = y;
    scale.mat[2][2] = z;

    return mat4_mul_mat4(origin, scale);
}

/*
    foward  = norm(eye - target)
    right   = norm(cross(foward, up))
    up      = cross(foward, right)
    pos     = -dot([right, up, foward], eye)

    right.x     right.y     right.z     -dot(right, eye)
    up.x        up.y        up.z        -dot(up, eye)
    foward.x    foward.y    foward.z    -dor(foward, eye)
           0           0           0                    1

*/
mat4_t mat4_lookat(vec3_t eye, vec3_t target, vec3_t world_up)
{
    vec3_t foward = vec3_norm(vec3_sub(eye, target));
    vec3_t right = vec3_norm(vec3_cross(vec3_norm(world_up), foward));
    vec3_t up = vec3_cross(foward, right);

    mat4_t translation = mat4_identity();
    mat4_t rotation = mat4_identity();

    rotation.mat[0][0] = right.x;
    rotation.mat[1][0] = right.y;
    rotation.mat[2][0] = right.z;

    rotation.mat[0][1] = up.x;
    rotation.mat[1][1] = up.y;
    rotation.mat[2][1] = up.z;

    rotation.mat[0][2] = foward.x;
    rotation.mat[1][2] = foward.y;
    rotation.mat[2][2] = foward.z;

    translation.mat[3][0] = -eye.x;
    translation.mat[3][1] = -eye.y;
    translation.mat[3][2] = -eye.z;

    return mat4_mul_mat4(rotation, translation);
}

/*
    2/(r-l)        0         0      -(r+l)/(r-l)
          0   2/(t-b)        0      -(t+b)/(t-b)
          0        0  -2/(f-n)      -(f+n)/(f-n)
          0        0         0                 1
*/
mat4_t mat4_ortho(float left, float right, float bottom, float top, float near, float far)
{
    mat4_t ortho = mat4_identity();

    ortho.mat[0][0] = 2 / (right - left);
    ortho.mat[1][1] = 2 / (top - bottom);
    ortho.mat[2][2] = -2 / (far - near);

    ortho.mat[3][0] = - (right + left) / (right - left);
    ortho.mat[3][1] = - (top + bottom) / (top - bottom);
    ortho.mat[3][2] = - (far + near) / (far - near);

    return ortho;
}

/*
    2n/(r-l)         0   (r+l)/(r-l)           0
           0  2n/(t-b)   (t+b)/(t-b)           0
           0         0  -(f+n)/(f-n)  -2fn/(f-n)
           0         0            -1           0
*/
mat4_t mat4_frustum(float left, float right, float bottom, float top, float near, float far)
{
    mat4_t frustum = mat4_identity();

    frustum.mat[0][0] = 2 * near / (right - left);
    frustum.mat[1][1] = 2 * near / (top - bottom);
    frustum.mat[2][0] = (right + left) / (right - left);
    frustum.mat[2][1] = (top + bottom) / (top - bottom);
    frustum.mat[2][2] = -(far + near) / (far - near);
    frustum.mat[2][3] = -1;
    frustum.mat[3][2] = -2 * far * near / (far - near);
    frustum.mat[3][3] = 0;

    return frustum;
}

/*
    left    = -right
    bottom  = -top

     1/r    0         0             0
       0  1/t         0             0
       0    0  -2/(f-n)  -(f+n)/(f-n)
       0    0         0             1
*/
mat4_t mat4_orthographics(float right, float top, float near, float far)
{
    mat4_t ortho = mat4_identity();

    ortho.mat[0][0] = 1 / right;
    ortho.mat[1][1] = 1 / top;
    ortho.mat[2][2] = -2 / (far - near);
    ortho.mat[3][2] = -(far + near) / (far - near);

    return ortho;
}

/*
     1/(aspect*tan(fovy/2))              0             0           0
                          0  1/tan(fovy/2)             0           0
                          0              0  -(f+n)/(f-n)  -2fn/(f-n)
                          0              0            -1           0
*/
mat4_t mat4_perspective(float fovy, float aspect, float near, float far)
{
    mat4_t persp = mat4_identity();

    persp.mat[0][0] = 1 / 1/(aspect * tanf(fovy / 2));
    persp.mat[1][1] = 1 / tanf(fovy / 2);
    persp.mat[2][2] = -(far + near) / (far - near);
    persp.mat[2][3] = -1;
    persp.mat[3][2] = -2 * far * near / (far - near);

    return persp;
}
