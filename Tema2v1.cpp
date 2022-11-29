#include "lab_m1/Tema2v1/Tema2v1.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;



#define distRed 0.15
#define distBlue 0.05
#define epsilon 0.0001
#define dist_npc_car1 0.10
#define SpeedNFC 20 
#define SpeedPlayerMAX 5
#define NR_Vertices_Circle 11
#define PI 3.1415

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

struct Square
{
    Square(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4) : v1(v1), v2(v2), v3(v3), v4(v4) {};
    glm::vec3 v1, v2, v3, v4;
};


Tema2v1::Tema2v1()
{
}


Tema2v1::~Tema2v1()
{
}


void Tema2v1::Init()
{
    renderCameraTarget = false;

    rotateCarMatrix = glm::mat4(1);
    
    resolution = window->GetResolution();
    
    left = -5;
    right = 5;
    buttom = -5;
    top = 5;
    
    fov = RADIANS(60);

    cameraSpeed = 0;

    glm::vec3 color = glm::vec3(0.167, 0.172, 0.1686);
    vector<VertexFormat> track_vertices
    {

        VertexFormat(glm::vec3(-1.92, 0, 0.68), color), // A
        VertexFormat(glm::vec3(-1.89, 0, 0.79), color), // B
        VertexFormat(glm::vec3(-1.82, 0, 0.86), color), // C
        VertexFormat(glm::vec3(-1.75, 0, 0.91), color), // D
        VertexFormat(glm::vec3(-1.69, 0, 0.94), color), // E
        VertexFormat(glm::vec3(-1.61, 0, 0.95), color), // F
        VertexFormat(glm::vec3(-1.53, 0, 0.95), color), // G
        VertexFormat(glm::vec3(-1.44, 0, 0.95), color), // H
        VertexFormat(glm::vec3(-1.36, 0, 0.96), color), // I
        VertexFormat(glm::vec3(-1.27, 0, 0.97), color), // J
        VertexFormat(glm::vec3(-1.19, 0, 0.97), color), // K
        VertexFormat(glm::vec3(-1.1, 0, 0.97), color), // L
        VertexFormat(glm::vec3(-1.05, 0, 0.94), color), // M
        VertexFormat(glm::vec3(-1.01, 0, 0.9), color), // N
        VertexFormat(glm::vec3(-0.97, 0, 0.85), color), // O
        VertexFormat(glm::vec3(-0.95, 0, 0.76), color), // P
        VertexFormat(glm::vec3(-0.94, 0, 0.68), color), // Q
        VertexFormat(glm::vec3(-0.94, 0, 0.61), color), // R
        VertexFormat(glm::vec3(-0.92, 0, 0.54), color), // S
        VertexFormat(glm::vec3(-0.9, 0, 0.52), color), // S5
        VertexFormat(glm::vec3(-0.85, 0, 0.51), color), // T
        VertexFormat(glm::vec3(-0.82, 0, 0.5), color), // T5
        VertexFormat(glm::vec3(-0.77, 0, 0.51), color), // U
        VertexFormat(glm::vec3(-0.7, 0, 0.5), color), // V
        VertexFormat(glm::vec3(-0.65, 0, 0.5), color), // W
        VertexFormat(glm::vec3(-0.58, 0, 0.5), color), // Z
        VertexFormat(glm::vec3(-0.53, 0, 0.5), color), // U5
        VertexFormat(glm::vec3(-0.5, 0, 0.51), color), // A1
        VertexFormat(glm::vec3(-0.48, 0, 0.54), color), // V5
        VertexFormat(glm::vec3(-0.46, 0, 0.56), color), // B1
        VertexFormat(glm::vec3(-0.45, 0, 0.62), color), // C1
        VertexFormat(glm::vec3(-0.45, 0, 0.7), color), // D1
        VertexFormat(glm::vec3(-0.46, 0, 0.75), color), // E1
        VertexFormat(glm::vec3(-0.46, 0, 0.8), color), // F1
        VertexFormat(glm::vec3(-0.46, 0, 0.85), color), // G1
        VertexFormat(glm::vec3(-0.46, 0, 0.89), color), // H1
        VertexFormat(glm::vec3(-0.44, 0, 0.94), color), // I1
        VertexFormat(glm::vec3(-0.41, 0, 0.97), color), // J1
        VertexFormat(glm::vec3(-0.36, 0, 0.98), color), // K1
        VertexFormat(glm::vec3(-0.28, 0, 0.99), color), // M1
        VertexFormat(glm::vec3(-0.25, 0, 1), color), // N1
        VertexFormat(glm::vec3(-0.2, 0, 1), color), // O1
        VertexFormat(glm::vec3(-0.16, 0, 1), color), // P1
        VertexFormat(glm::vec3(-0.12, 0, 1), color), // Q1
        VertexFormat(glm::vec3(-0.07, 0, 1.01), color), // R1
        VertexFormat(glm::vec3(0, 0, 1), color), // S1
        VertexFormat(glm::vec3(0.06, 0, 1), color), // T1
        VertexFormat(glm::vec3(0.13, 0, 1), color), // U1
        VertexFormat(glm::vec3(0.2, 0, 1), color), // V1
        VertexFormat(glm::vec3(0.26, 0, 1), color), // W1
        VertexFormat(glm::vec3(0.3, 0, 1), color), // Z1
        VertexFormat(glm::vec3(0.33, 0, 0.99), color), // E5
        VertexFormat(glm::vec3(0.34, 0, 0.99), color), // F5
        VertexFormat(glm::vec3(0.35, 0, 0.98), color), // G5
        VertexFormat(glm::vec3(0.36, 0, 0.96), color), // A2
        VertexFormat(glm::vec3(0.36, 0, 0.94), color), // H5
        VertexFormat(glm::vec3(0.37, 0, 0.91), color), // B2
        VertexFormat(glm::vec3(0.37, 0, 0.86), color), // C2
        VertexFormat(glm::vec3(0.37, 0, 0.8), color), // D2
        VertexFormat(glm::vec3(0.37, 0, 0.7), color), // E2
        VertexFormat(glm::vec3(0.36, 0, 0.64), color), // F2
        VertexFormat(glm::vec3(0.36, 0, 0.56), color), // G2
        VertexFormat(glm::vec3(0.36, 0, 0.51), color), // H2
        VertexFormat(glm::vec3(0.37, 0, 0.44), color), // I2
        VertexFormat(glm::vec3(0.37, 0, 0.38), color), // J2
        VertexFormat(glm::vec3(0.37, 0, 0.32), color), // K2
        VertexFormat(glm::vec3(0.37, 0, 0.25), color), // L2
        VertexFormat(glm::vec3(0.38, 0, 0.16), color), // M2
        VertexFormat(glm::vec3(0.38, 0, 0.11), color), // N2
        VertexFormat(glm::vec3(0.37, 0, 0.05), color), // O2
        VertexFormat(glm::vec3(0.37, 0, -0.02), color), // P2
        VertexFormat(glm::vec3(0.37, 0, -0.08), color), // Q2
        VertexFormat(glm::vec3(0.33, 0, -0.14), color), // R2
        VertexFormat(glm::vec3(0.26, 0, -0.17), color), // S2
        VertexFormat(glm::vec3(0.2, 0, -0.2), color), // T2
        VertexFormat(glm::vec3(0.11, 0, -0.19), color), // U2
        VertexFormat(glm::vec3(0.03, 0, -0.15), color), // V2
        VertexFormat(glm::vec3(0, 0, -0.1), color), // W2
        VertexFormat(glm::vec3(-0.06, 0, -0.05), color), // Z2
        VertexFormat(glm::vec3(-0.13, 0, 0.01), color), // A3
        VertexFormat(glm::vec3(-0.19, 0, 0.05), color), // B3
        VertexFormat(glm::vec3(-0.26, 0, 0.09), color), // C3
        VertexFormat(glm::vec3(-0.31, 0, 0.09), color), // D3
        VertexFormat(glm::vec3(-0.37, 0, 0.1), color), // E3
        VertexFormat(glm::vec3(-0.45, 0, 0.1), color), // F3
        VertexFormat(glm::vec3(-0.53, 0, 0.09), color), // G3
        VertexFormat(glm::vec3(-0.6, 0, 0.09), color), // H3
        VertexFormat(glm::vec3(-0.67, 0, 0.09), color), // I3
        VertexFormat(glm::vec3(-0.74, 0, 0.08), color), // J3
        VertexFormat(glm::vec3(-0.82, 0, 0.09), color), // K3
        VertexFormat(glm::vec3(-0.88, 0, 0.08), color), // L3
        VertexFormat(glm::vec3(-0.94, 0, 0.09), color), // M3
        VertexFormat(glm::vec3(-1, 0, 0.09), color), // N3
        VertexFormat(glm::vec3(-1.07, 0, 0.08), color), // O3
        VertexFormat(glm::vec3(-1.12, 0, 0.08), color), // P3
        VertexFormat(glm::vec3(-1.18, 0, 0.03), color), // Q3
        VertexFormat(glm::vec3(-1.2, 0, 0), color), // R3
        VertexFormat(glm::vec3(-1.2, 0, -0.08), color), // S3
        VertexFormat(glm::vec3(-1.2, 0, -0.15), color), // T3
        VertexFormat(glm::vec3(-1.2, 0, -0.2), color), // U3
        VertexFormat(glm::vec3(-1.2, 0, -0.27), color), // V3
        VertexFormat(glm::vec3(-1.2, 0, -0.33), color), // W3
        VertexFormat(glm::vec3(-1.2, 0, -0.4), color), // Z3
        VertexFormat(glm::vec3(-1.19, 0, -0.46), color), // A4
        VertexFormat(glm::vec3(-1.19, 0, -0.52), color), // B4
        VertexFormat(glm::vec3(-1.23, 0, -0.56), color), // C4
        VertexFormat(glm::vec3(-1.29, 0, -0.58), color), // D4
        VertexFormat(glm::vec3(-1.36, 0, -0.58), color), // E4
        VertexFormat(glm::vec3(-1.41, 0, -0.57), color), // F4
        VertexFormat(glm::vec3(-1.47, 0, -0.52), color), // G4
        VertexFormat(glm::vec3(-1.5, 0, -0.46), color), // H4
        VertexFormat(glm::vec3(-1.55, 0, -0.4), color), // I4
        VertexFormat(glm::vec3(-1.58, 0, -0.34), color), // J4
        VertexFormat(glm::vec3(-1.6, 0, -0.28), color), // K4
        VertexFormat(glm::vec3(-1.6, 0, -0.2), color), // L4
        VertexFormat(glm::vec3(-1.59, 0, -0.16), color), // I5
        VertexFormat(glm::vec3(-1.58, 0, -0.11), color), // M4
        VertexFormat(glm::vec3(-1.57, 0, -0.07), color), // J5
        VertexFormat(glm::vec3(-1.57, 0, -0.04), color), // N4
        VertexFormat(glm::vec3(-1.57, 0, 0.01), color), // K5
        VertexFormat(glm::vec3(-1.57, 0, 0.05), color), // O4
        VertexFormat(glm::vec3(-1.58, 0, 0.08), color), // L5
        VertexFormat(glm::vec3(-1.59, 0, 0.11), color), // P4
        VertexFormat(glm::vec3(-1.62, 0, 0.12), color), // M5
        VertexFormat(glm::vec3(-1.64, 0, 0.13), color), // Q4
        VertexFormat(glm::vec3(-1.68, 0, 0.15), color), // N5
        VertexFormat(glm::vec3(-1.71, 0, 0.16), color), // R4
        VertexFormat(glm::vec3(-1.74, 0, 0.17), color), // O5
        VertexFormat(glm::vec3(-1.76, 0, 0.18), color), // S4
        VertexFormat(glm::vec3(-1.79, 0, 0.18), color), // T4
        VertexFormat(glm::vec3(-1.83, 0, 0.19), color), // P5
        VertexFormat(glm::vec3(-1.87, 0, 0.2), color), // U4
        VertexFormat(glm::vec3(-1.93, 0, 0.22), color), // V4
        VertexFormat(glm::vec3(-1.96, 0, 0.27), color), // W4
        VertexFormat(glm::vec3(-1.99, 0, 0.33), color), // Z4
        VertexFormat(glm::vec3(-2, 0, 0.4), color), // A5
        VertexFormat(glm::vec3(-1.98, 0, 0.46), color), // B5
        VertexFormat(glm::vec3(-1.96, 0, 0.54), color), // C5
        VertexFormat(glm::vec3(-1.94, 0, 0.61), color), // D5
        VertexFormat(glm::vec3(-1.93, 0, 0.65), color), // Q5

    };
    
    vector<Segment> segments_track, segments_red, segments_blue;
    for (int i = 0; i < track_vertices.size() - 1; i++)
    {
        segments_track.push_back(Segment(track_vertices.at(i), track_vertices.at(i + 1)));
    }
    segments_track.push_back(Segment(track_vertices.at(track_vertices.size() - 1), track_vertices.at(0)));
    
    
    glm::vec3 up = glm::vec3(0, 1, 0);
    for (Segment seg : segments_track)
    {
        glm::vec3 D = seg.p2.position - seg.p1.position;

        glm::vec3 P = glm::normalize(glm::cross(D, up));


        glm::vec3 poz_R = seg.p1.position + glm::vec3(P.x * distRed, P.y * distRed, P.z * distRed);
        glm::vec3 poz_A = seg.p1.position - glm::vec3(P.x * distBlue, P.y * distBlue, P.z * distBlue);
        glm::vec3 poz_car1 = seg.p1.position + glm::vec3(P.x * dist_npc_car1, P.y * dist_npc_car1, P.z * dist_npc_car1);
        red_and_blue_vertices_track.push_back(VertexFormat(poz_R, color));
        red_and_blue_vertices_track.push_back(VertexFormat(poz_A, color));
        points_npc_car.push_back(poz_car1);
    }

    fractiune_npc = 0;
    indice_last_point_npc = 0;

    vector<unsigned int> indices;
    int i = 0;
    for (int j = 0; j < track_vertices.size() - 1; j++)
    {
        indices.push_back(i);
        indices.push_back(++i);
        indices.push_back(++i);
        indices.push_back(i - 1);
        indices.push_back(i + 1);
        indices.push_back(i);
    }

    {
        indices.push_back(i);
        indices.push_back(++i);
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(1);
        indices.push_back(0);
    }
    glm::vec3 culoare_masinuta = glm::vec3(0, 0, 1);
    vector<VertexFormat> car_vertices
    {
        VertexFormat(glm::vec3(-1,-1,-2),culoare_masinuta), // A 0
        VertexFormat(glm::vec3(1,-1,-2),culoare_masinuta), // B 1
        VertexFormat(glm::vec3(-1,1,-2),culoare_masinuta), // C 2
        VertexFormat(glm::vec3(1, 1,-2),culoare_masinuta), // D 3
        VertexFormat(glm::vec3(1,-1,2),culoare_masinuta), // E 4 
        VertexFormat(glm::vec3(1,1,2),culoare_masinuta), // F 5 
        VertexFormat(glm::vec3(-1,-1,2),culoare_masinuta), // G 6
        VertexFormat(glm::vec3(-1,1,2),culoare_masinuta) // H 7
    };
    vector<glm::vec3> culori_masinute_npc;
    for (int i = 0; i < 8; i++)
    {
        culoare_masinuta = glm::vec3(rand() % 101 / 100.0, rand() % 101 / 100.0, rand() % 101 / 100.0);
        culori_masinute_npc.push_back(culoare_masinuta);
    }
    vector<VertexFormat> car_npc_vertices
    {

        VertexFormat(glm::vec3(-1,-1,-2), culori_masinute_npc.at(0)), // A 0
        VertexFormat(glm::vec3(1,-1,-2), culori_masinute_npc.at(1)), // B 1
        VertexFormat(glm::vec3(-1,1,-2), culori_masinute_npc.at(2)), // C 2
        VertexFormat(glm::vec3(1, 1,-2), culori_masinute_npc.at(3)), // D 3
        VertexFormat(glm::vec3(1,-1,2), culori_masinute_npc.at(4)), // E 4 
        VertexFormat(glm::vec3(1,1,2), culori_masinute_npc.at(5)), // F 5 
        VertexFormat(glm::vec3(-1,-1,2), culori_masinute_npc.at(6)), // G 6
        VertexFormat(glm::vec3(-1,1,2), culori_masinute_npc.at(7)) // H 7
    };
    glm::vec3 brown = glm::vec3(0.4, 0.26, 0.13);
    vector<VertexFormat> trunk_vertices
    {
        VertexFormat(glm::vec3(-1,-1,-2),brown), // A 0
        VertexFormat(glm::vec3(1,-1,-2),brown), // B 1
        VertexFormat(glm::vec3(-1,1,-2),brown), // C 2
        VertexFormat(glm::vec3(1, 1,-2),brown), // D 3
        VertexFormat(glm::vec3(1,-1,2),brown), // E 4 
        VertexFormat(glm::vec3(1,1,2),brown), // F 5 
        VertexFormat(glm::vec3(-1,-1,2),brown), // G 6
        VertexFormat(glm::vec3(-1,1,2),brown) // H 7
    };

    

    vector<unsigned int> car_indices
    {
        0, 1, 2,  // ABC
        2, 1, 3,  // CBD
        3, 4, 1, // DEB
        3, 5, 4,  // DFE
        7, 5, 4,  //HFE
        7, 5, 6, //HFG
        2, 6, 0, //CGA
        2, 7, 6, //CHG
        2, 3, 5, //CDF
        2, 5, 7, //CFH
        0, 1, 4, //AEB
        0, 4, 6  //AGE
    };

    meshes["trunk"] = new Mesh("trunk");
    meshes["trunk"]->SetDrawMode(GL_TRIANGLES);
    meshes["trunk"]->InitFromData(trunk_vertices, car_indices);
    meshes["npc_car"] = new Mesh("npc_car");
    meshes["npc_car"]->SetDrawMode(GL_TRIANGLES);
    meshes["npc_car"]->InitFromData(car_npc_vertices, car_indices);

    meshes["pista"] = new Mesh("pista");
    meshes["pista"]->SetDrawMode(GL_TRIANGLES);
    meshes["pista"]->InitFromData(red_and_blue_vertices_track, indices);

    meshes["car"] = new Mesh("car");
    meshes["car"]->SetDrawMode(GL_TRIANGLES);
    meshes["car"]->InitFromData(car_vertices, car_indices);

    glm::vec3 green_leaf = glm::vec3(0.216, 0.376, 0.024);
    float Raza = 3;
    vector<VertexFormat> tree_vertices;
    for (int alfa = 0; alfa < NR_Vertices_Circle; alfa++)
    {
        for (int beta = 0; beta < NR_Vertices_Circle; beta++)
        {
            glm::vec3 poz = glm::vec3(Raza * cos(double(alfa)/NR_Vertices_Circle * (2 * PI)) * cos(double(beta)/NR_Vertices_Circle * (2 * PI)), Raza * sin(double(alfa) / NR_Vertices_Circle * (2 * PI)), Raza * cos(double(alfa) / NR_Vertices_Circle * (2 * PI)) * sin(double(beta) / NR_Vertices_Circle * (2 * PI)));
            tree_vertices.push_back(VertexFormat(poz, green_leaf));
        }
    }
    vector<unsigned int> tree_indices;
    for (int x = 0; x < pow(NR_Vertices_Circle, 2); x++)
    {
        for (int y = 0; y < pow(NR_Vertices_Circle, 2); y++)
        {
            for (int z = 0; z < pow(NR_Vertices_Circle, 2); z++)
            {
                if (x != y && x != z && y != z && glm::distance(glm::vec3(x, y, z), glm::vec3(0, 0, 0)) == Raza);
                {
                    tree_indices.push_back(x);
                    tree_indices.push_back(y);
                    tree_indices.push_back(z);
                }
            }
        }
    }

    meshes["tree"] = new Mesh("tree");
    meshes["tree"]->SetDrawMode(GL_TRIANGLES);
    meshes["tree"]->InitFromData(tree_vertices, tree_indices);

    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);

    median = glm::vec3(-0.8, 0, 0.2);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Scale(10, 10, 10);
    modelMatrix *= transform3D::Translate(-median.x, -median.y, -median.z);
    //modelMatrix *= transform3D::Translate(0, 0.1, 0);
    glm::vec4 start_camera = glm::vec4(track_vertices.at(0).position.x, track_vertices.at(0).position.y, track_vertices.at(0).position.z,1);
    start_camera = modelMatrix * start_camera;


    glm::vec4 orientare_camera = glm::vec4(track_vertices.at(2).position.x, track_vertices.at(2).position.y, track_vertices.at(2).position.z, 1);
    orientare_camera = modelMatrix * orientare_camera;
    camera = new my_camera::Camera();
    camera->Set(glm::vec3(start_camera) + glm::vec3(0,0.5,0), glm::vec3(orientare_camera) + glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));

    poz_obiect = camera->GetTargetPosition() * glm::vec3(1, 0, 1);
    float initial_rotation_target = acos(glm::dot(camera->forward, glm::vec3(0, 0, -1)));
    rotateCarMatrix *= transform3D::RotateOY(-initial_rotation_target);
    
}


void Tema2v1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.529, 0.808, 0.922, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    resolution = window->GetResolution();
   
    vector<VertexFormat> grass_vertices
    {
        VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0,1,0)),
        VertexFormat(glm::vec3(0, 0, resolution.y), glm::vec3(0,1,0)),
        VertexFormat(glm::vec3(resolution.x, 0, resolution.y), glm::vec3(0,1,0)),
        VertexFormat(glm::vec3(resolution.x, 0, 0), glm::vec3(0,1,0))
    };
    vector<unsigned int> grass_indices
    {
        0,2,1,0,3,2
    };
    meshes["grass"] = new Mesh("grass");
    meshes["grass"]->SetDrawMode(GL_TRIANGLES);
    meshes["grass"]->InitFromData(grass_vertices, grass_indices);
    
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

}


void Tema2v1::Update(float deltaTimeSeconds)
{

   
    RenderMesh(meshes["grass"], shaders["VertexColor"], transform3D::Translate(-resolution.x / 2, -0.5, -resolution.y / 2));
  
    RenderMesh(meshes["pista"], shaders["VertexColor"], modelMatrix);

        
    glm::mat4 modelMatrix_car;
    modelMatrix_car = transform3D::Translate(poz_obiect.x, 0, poz_obiect.z); 
    
    modelMatrix_car *= transform3D::Translate(0, 0.1005, 0);
    modelMatrix_car *= rotateCarMatrix; 
    modelMatrix_car *= transform3D::Scale(0.1, 0.1, 0.1);
    RenderMesh(meshes["car"], shaders["VertexColor"],modelMatrix_car);

    glm::mat4 modelMatrixCarNPC = modelMatrix;
    int size = points_npc_car.size();
    bool ultim = false;
    if (indice_last_point_npc + 1 == size - 1)
    {
        indice_last_point_npc = 0;
        ultim = true;
    }
    glm::vec3 dir = points_npc_car.at(indice_last_point_npc + 1) - points_npc_car.at(indice_last_point_npc);
    fractiune_npc += deltaTimeSeconds * SpeedNFC ;
    if (fractiune_npc >= 1)
    {
        fractiune_npc = 0;
        indice_last_point_npc++;
    }
    float translateX_NPC = 0;
    float translateZ_NPC = 0;
    float rotate_car_npc = glm::acos(glm::dot(glm::normalize(dir), glm::vec3(0, 0, 1)));
    if (ultim)
    {
        float translateX_NPC = points_npc_car.at(size - 1).x * (1 - fractiune_npc) + fractiune_npc * points_npc_car.at(0).x;
        float translateZ_NPC = points_npc_car.at(size - 1).z * (1 - fractiune_npc) + fractiune_npc * points_npc_car.at(0).z;
        ultim = false;
        if (points_npc_car.at(size - 1).z < median.z)
        {
            rotate_car_npc *= -1;
        }
    }
    else
    {
        translateX_NPC = points_npc_car.at(indice_last_point_npc).x * (1 - fractiune_npc) + fractiune_npc * points_npc_car.at(indice_last_point_npc + 1).x;
        translateZ_NPC = points_npc_car.at(indice_last_point_npc).z * (1 - fractiune_npc) + fractiune_npc * points_npc_car.at(indice_last_point_npc + 1).z;
        if (points_npc_car.at(indice_last_point_npc).z < median.z)
        {
            rotate_car_npc *= -1;
        }
    }
    
    modelMatrixCarNPC *= transform3D::Translate(translateX_NPC, 0, translateZ_NPC);
    
    
    modelMatrixCarNPC *= transform3D::RotateOY(rotate_car_npc);
    modelMatrixCarNPC *= transform3D::Translate(0, 0.01005, 0);
    modelMatrixCarNPC *= transform3D::Scale(0.01, 0.01, 0.01);
    RenderMesh(meshes["npc_car"], shaders["VertexColor"], modelMatrixCarNPC);

    glm::mat4 modelMatrixTree =glm::mat4(1);
    glm::vec3 pos = modelMatrix * glm::vec4(red_and_blue_vertices_track.at(0).position,1);
    //modelMatrixTree *= transform3D::Translate(0, -2, 0)
    
    modelMatrixTree *= transform3D::Scale(0.1, 0.1, 0.1);
    modelMatrixTree *= transform3D::Translate(pos.x, 2, pos.z);  
    RenderMesh(meshes["tree"], shaders["VertexColor"], modelMatrixTree);
    modelMatrixTree *= transform3D::Translate(0, -3, 0);
    modelMatrixTree *= transform3D::RotateOX(PI / 2);
    //modelMatrixTree *= transform3D::Scale()
    RenderMesh(meshes["trunk"], shaders["VertexColor"], modelMatrixTree);

    
}


void Tema2v1::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2v1::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

bool exist_in_zone(glm::vec3 point1, glm::vec3 point2, glm::vec3 position)
{
    
    if (position.x > point1.x &&
        position.x < point2.x &&
        position.z < point1.z &&
        position.z > point2.z)
    {
       
        return true;
    }
   
    return false;
}

bool exist_in_triangles(Square square, glm::vec3 pos)
{
    // pt p1 p2 p3 si p2 p3 p4

    glm::vec3 p1p2 = square.v2 - square.v1;
    glm::vec3 p1p3 = square.v3 - square.v1;
    
    glm::vec3 res = glm::cross(p1p2, p1p3);
    float area = glm::sqrt(glm::dot(res,res)) / 2;

    glm::vec3 Pp1 = square.v1 - pos;
    glm::vec3 Pp2 = square.v2 - pos;
    res = glm::cross(Pp1, Pp2);
    float area1 = glm::sqrt(glm::dot(res,res)) / 2;

    glm::vec3 Pp3 = square.v3 - pos;
    res = glm::cross(Pp1, Pp3);
    float area2 = glm::sqrt(glm::dot(res, res)) / 2;
    

    res = glm::cross(Pp2, Pp3);
    float area3 = glm::sqrt(glm::dot(res, res)) / 2;
    if ( glm::fabs(area - area1 - area2 - area3) <= epsilon)
    {
       
        return true;
    }

    glm::vec3 p2p3 = square.v3 - square.v2;
    glm::vec3 p2p4 = square.v4 - square.v2;
    res = glm::cross(p2p3, p2p4);
    area = glm::sqrt(glm::dot(res, res)) / 2;

    glm::vec3 Pp4 = square.v4 - pos;
     Pp2 = square.v2 - pos;
     res = glm::cross(Pp4, Pp2);
    area1 = glm::sqrt(glm::dot(res, res)) / 2;

     Pp3 = square.v3 - pos;
     res = glm::cross(Pp2, Pp3);
    area2 = glm::sqrt(glm::dot(res, res)) / 2;

    res = glm::cross(Pp4, Pp3);
  area3 = glm::sqrt(glm::dot(res, res)) / 2;
    if (glm::fabs(area - area1 - area2 - area3) <= epsilon)
    {
        return true;
    }


    return false;

}


void Tema2v1::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeedRotate = 2.0f;
        float acc = 3; 
        float dec_acc = -1;
        float acc_frana = -2.5;
        if (window->KeyHold(GLFW_KEY_W)) {
            cameraSpeed = glm::min(cameraSpeed + deltaTime * acc, (float)SpeedPlayerMAX);
            printf("W apasat\n");
        }
        else if (window->KeyHold(GLFW_KEY_S)) {

            cameraSpeed = glm::max(cameraSpeed + deltaTime * acc_frana, float(-SpeedPlayerMAX));
        }
        else
        {
            cameraSpeed = glm::max(cameraSpeed + deltaTime * dec_acc, 0.0f);
        }

        printf("vit = %f\n", cameraSpeed);

            glm::vec3 poz_obiect_viit = camera->GetTargetPosition() + glm::normalize(camera->forward) * cameraSpeed * deltaTime;
            bool in_zone;
            vector<Square> patrate;
            for (int i = 0; i < red_and_blue_vertices_track.size() - 3; i+= 2)
            {
                glm::vec4 v1 = glm::vec4(red_and_blue_vertices_track.at(i).position, 1);
                glm::vec4 v2 = glm::vec4(red_and_blue_vertices_track.at(i+1).position, 1);
                glm::vec4 v3 = glm::vec4(red_and_blue_vertices_track.at(i+2).position, 1);
                glm::vec4 v4 = glm::vec4(red_and_blue_vertices_track.at(i+3).position, 1);
                v1 = modelMatrix * v1 * glm::vec4(1,0, 1, 1);
                v2 = modelMatrix * v2 * glm::vec4(1, 0, 1, 1);
                v3 = modelMatrix * v3 * glm::vec4(1, 0, 1, 1);
                v4 = modelMatrix * v4 * glm::vec4(1, 0, 1, 1);
                glm::vec3 point1 = glm::vec3(
                    glm::min(glm::min(v1.x, v2.x), glm::min(v3.x, v4.x)),
                        0,
                    glm::max(glm::max(v1.z, v2.z), glm::max(v3.z, v4.z)));
                glm::vec3 point2 = glm::vec3(
                    glm::max(glm::max(v1.x, v2.x), glm::max(v3.x, v4.x)),
                    0,
                    glm::min(glm::min(v1.z, v2.z), glm::min(v3.z, v4.z)));

                  in_zone = exist_in_zone(point1, point2, poz_obiect_viit);
                  if (in_zone)
                  {
                      patrate.push_back(Square(v1, v2, v3, v4));
                  }
                
            }
            
            {
                int size = red_and_blue_vertices_track.size();
                glm::vec4 v1 = glm::vec4(red_and_blue_vertices_track.at(size-2).position, 1);
                glm::vec4 v2 = glm::vec4(red_and_blue_vertices_track.at(size - 1).position, 1);
                glm::vec4 v3 = glm::vec4(red_and_blue_vertices_track.at(0).position, 1);
                glm::vec4 v4 = glm::vec4(red_and_blue_vertices_track.at(1).position, 1);
                v1 = modelMatrix * v1  * glm::vec4(1,0, 1, 1);
                v2 = modelMatrix * v2 * glm::vec4(1, 0, 1, 1);
                v3 = modelMatrix * v3 * glm::vec4(1, 0, 1, 1);
                v4 = modelMatrix * v4 * glm::vec4(1, 0, 1, 1);
                glm::vec3 point1 = glm::vec3(
                    glm::min(v1.x, v2.x),
                    0,
                    glm::max(v1.z, v3.z));
                glm::vec3 point2 = glm::vec3(
                    glm::max(v3.x, v4.x),
                    0,
                    glm::min(v2.z, v4.z));

                in_zone = exist_in_zone(point1, point2, poz_obiect_viit);
                if (in_zone)
                {
                    patrate.push_back(Square(v1, v2,v3, v4));
                }

            }

            bool in_triangles = false;

            for (int i = 0; i < patrate.size() && !in_triangles; i++)
            {
                Square patrat = patrate.at(i);
                if (exist_in_triangles(patrat, poz_obiect_viit * glm::vec3(1, 0, 1)))
                {
                    in_triangles = true;
                }
            }
            // TODO(student): Translate the camera forward
            if (in_triangles)
            {
                camera->TranslateForward(cameraSpeed * deltaTime);


                poz_obiect = camera->GetTargetPosition();
            }
            else
            {
                printf("boule iesi pe camp cu ea la pascut\n");
                cameraSpeed = 0;
            }
        

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            //camera->TranslateRight(-cameraSpeed * deltaTime);
            camera->RotateThirdPerson_OY(cameraSpeedRotate * deltaTime);
            rotateCarMatrix *= transform3D::RotateOY( cameraSpeedRotate * deltaTime);
            
        }

        

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            //camera->TranslateRight(cameraSpeed * deltaTime);

            camera->RotateThirdPerson_OY(- cameraSpeedRotate * deltaTime);
            rotateCarMatrix *= transform3D::RotateOY(-cameraSpeedRotate * deltaTime);
        }
        /*
        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            camera->TranslateUpward(cameraSpeed * deltaTime);
        }
        */
    }
    else
    {
    float cameraSpeed = 2.0f;

    if (window->KeyHold(GLFW_KEY_W)) {
        // TODO(student): Translate the camera forward
        camera->TranslateForward(cameraSpeed * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        // TODO(student): Translate the camera to the left
        camera->TranslateRight(-cameraSpeed * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        // TODO(student): Translate the camera backward
        camera->TranslateForward(-cameraSpeed * deltaTime);

    }

    if (window->KeyHold(GLFW_KEY_D)) {
        // TODO(student): Translate the camera to the right
        camera->TranslateRight(cameraSpeed * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
        // TODO(student): Translate the camera downward
        camera->TranslateUpward(-cameraSpeed * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_E)) {
        // TODO(student): Translate the camera upward
        camera->TranslateUpward(cameraSpeed * deltaTime);
    }
 }

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.

    if (window->KeyHold(GLFW_KEY_I))
    {
        fov += deltaTime;
        projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);
    }

    if (window->KeyHold(GLFW_KEY_K))
    {
        fov -= deltaTime;
        projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);
    }

    if (window->KeyHold(GLFW_KEY_M))
    {
        right += deltaTime;
        left = -right;
        projectionMatrix = glm::ortho(left, right, buttom, top, 0.01f, 200.0f);
    }

    if (window->KeyHold(GLFW_KEY_N))
    {
        right -= deltaTime;
        left = -right;
        projectionMatrix = glm::ortho(left, right, buttom, top, 0.01f, 200.0f);
    }

    

}


void Tema2v1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections

    if (key == GLFW_KEY_O)
    {
        projectionMatrix = glm::ortho(left, right, buttom, top, 0.01f, 200.0f);
    }

    if (key == GLFW_KEY_P)
    {
        projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);
    }


}


void Tema2v1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2v1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
   
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.

            camera->RotateFirstPerson_OX(sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(sensivityOY * deltaX);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX(sensivityOX * deltaY);
            camera->RotateThirdPerson_OY(sensivityOY * deltaX);
        }
    }
    
    
}


void Tema2v1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2v1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2v1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2v1::OnWindowResize(int width, int height)
{
}

