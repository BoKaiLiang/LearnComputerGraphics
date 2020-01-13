#include "mesh.h"

#define LINE_BUFFER_SIZE 256


mesh_t* mesh_load(const char* fpath) {

    mesh_t* mesh = NULL;

    vec3_t *positions = NULL;
    vec2_t *texcoords = NULL;
    vec3_t *normals = NULL;
    int *position_indices = NULL;
    int *texcoord_indices = NULL;
    int *normal_indices = NULL;

    // DESERIALIZE OBJ FILE //
    char line[LINE_BUFFER_SIZE];
    FILE* file = fopen(fpath, "rb");
    assert(NULL != file);

    while (true) {
        int items = 0;
        if (NULL == fgets(line, LINE_BUFFER_SIZE, file)) {
            break;
        }
        else if (0 == strncmp(line, "v ", 2)) {
            vec3_t pos;
            items = sscanf(line, "v %f %f %f", &pos.x, &pos.y, &pos.z);
            assert(items == 3);
            dyarray_push(positions, pos);
        }
        else if (0 == strncmp(line, "vt ", 3)) {
            vec2_t uv;
            items = sscanf(line, "vt %f %f", &uv.x, &uv.y);
            assert(items == 2);
            dyarray_push(texcoords, uv);
        }
        else if (0 == strncmp(line, "vn ", 3)) {
            vec3_t norm;
            items = sscanf(line, "vn %f %f %f", &norm.x, &norm.y, &norm.z);
            assert(items == 3);
            dyarray_push(normals, norm);
        }
        else if (0 == strncmp(line, "f ", 2)) {
            int i;
            int pos_indices[3], uv_indices[3], n_indices[3];
            items = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                           &pos_indices[0], &uv_indices[0], &n_indices[0],
                           &pos_indices[1], &uv_indices[1], &n_indices[1],
                           &pos_indices[2], &uv_indices[2], &n_indices[2]);
            assert(items == 9);
            for (i = 0; i < 3; i++) {
                dyarray_push(position_indices, pos_indices[i] - 1);
                dyarray_push(texcoord_indices, uv_indices[i] - 1);
                dyarray_push(normal_indices, n_indices[i] - 1);
            }
        }
    }

    // MAP DATA TO MESH STRUCTURE //
    int num_positions = dyarray_count(position_indices);
    int num_texcoords = dyarray_count(texcoord_indices);
    int num_normals = dyarray_count(normal_indices);

    mesh = malloc(sizeof(mesh_t));

    mesh->positions = malloc(sizeof(vec3_t) * num_positions);
    mesh->texcoords = malloc(sizeof(vec3_t) * num_texcoords);
    mesh->normals = malloc(sizeof(vec3_t) * num_normals);
    
    for (int i = 0; i < num_positions; i++) {
        int position_index = position_indices[i];
        int texcoord_index = texcoord_indices[i];
        int normal_index = normal_indices[i];
        mesh->positions[i] = positions[position_index];
        mesh->texcoords[i] = texcoords[texcoord_index];
        mesh->normals[i] = normals[normal_index];
    }

    mesh->num_normals = num_normals;
    mesh->num_positions = num_positions;
    mesh->num_texcoords = num_texcoords;

    // dyarray_release(positions);
    // dyarray_release(texcoords);
    // dyarray_release(normals);
    // dyarray_release(position_indices);
    // dyarray_release(texcoord_indices);
    // dyarray_release(normal_indices);

    return mesh;
}

void mesh_release(mesh_t* mesh) {
    if (mesh != NULL) {
        free(mesh->positions);
        free(mesh->texcoords);
        free(mesh->normals);
    }
}