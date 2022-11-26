#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/Tema2/transform3D.h"

using namespace std;
using namespace m1;


#define VITEZA 10

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

#define distRed 0.05
#define distBlue 0.05

Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    
   polygonMode = GL_FILL;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    angularStepOY_gen = 0;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
    
    glm::vec3 color = glm::vec3(0.5, 0.5, 0.5);
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

    renderCameraTarget = true;
    camera = new camera::Camera();
    camera->Set(track_vertices.at(0).position, track_vertices.at(2).position, glm::vec3(0, 1, 0));
    left = -5;
    right = 5;
    buttom = -5;
    top = 5;

    fov = RADIANS(60);

    translateX = track_vertices.at(2).position.x;
    translateY = track_vertices.at(2).position.y;
    translateZ = track_vertices.at(2).position.z;
    vector<Segment> segments_track, segments_red, segments_blue ;
    for (int i = 0; i < track_vertices.size() - 1; i++)
    {
        segments_track.push_back(Segment(track_vertices.at(i), track_vertices.at(i + 1)));
    }
    segments_track.push_back(Segment(track_vertices.at(track_vertices.size() - 1), track_vertices.at(0)));
    vector<VertexFormat> red_and_blue_vertices_track;

    glm::vec3 up = glm::vec3(0, 1, 0);
    for (Segment seg : segments_track)
    {
        glm::vec3 D = seg.p2.position - seg.p1.position;
        
        glm::vec3 P = glm::normalize(glm::cross(D, up));
       
        
        glm::vec3 poz_R = seg.p1.position +  glm::vec3(P.x*distRed, P.y*distRed, P.z*distRed);
        glm::vec3 poz_A = seg.p1.position - glm::vec3(P.x * distBlue, P.y * distBlue, P.z * distBlue);
        red_and_blue_vertices_track.push_back(VertexFormat(poz_R, color));
        red_and_blue_vertices_track.push_back(VertexFormat(poz_A, color));
    }

    vector<unsigned int> indices;
    int i = 0;
    for (int j = 0; j < track_vertices.size() - 1; j++ )
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

        
    meshes["pista"] = new Mesh("pista");
    meshes["pista"]->SetDrawMode(GL_TRIANGLES);
    meshes["pista"]->InitFromData(red_and_blue_vertices_track, indices);


}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
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

    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::RenderScene() {
    
    //modelMatrix *= transform3D::Translate(-2.5f, 0.5f, -1.5f);
    

    /*modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 0.5f, -1.5f);
    modelMatrix *= transform3D::RotateOY(angularStepOY_gen);
    modelMatrix *= transform3D::Translate(2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::RotateOX(angularStepOX);
    modelMatrix *= transform3D::RotateOY(angularStepOY);
    modelMatrix *= transform3D::RotateOZ(angularStepOZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
 */
    glm::vec3 median = glm::vec3(-0.8, 0, 0.2);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Scale(10, 10, 10);

    modelMatrix *= transform3D::Translate(-median.x, -median.y, -median.z);
    RenderMesh(meshes["pista"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    //modelMatrix *= transform3D::Translate(-median.x, -median.y, -median.z);
    modelMatrix *= transform3D::Scale(0.1, 0.1, 0.1);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-resolution.x/2, -0.5,-resolution.y/2 );
    RenderMesh(meshes["grass"], shaders["VertexColor"], modelMatrix);
    
   
}

void Tema2::Update(float deltaTimeSeconds)
{
   glLineWidth(3);
    glPointSize(5);
   glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    RenderScene();
    DrawCoordinateSystem();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // TODO(student): render the scene again, in the new viewport
    RenderScene();
   DrawCoordinateSystem();
    
}

void Tema2::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // TODO(student): Add transformation logic
    /*if (window->KeyHold(GLFW_KEY_S))
    {
        translateY -= 2 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_W))
    {
        translateY += 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D))
    {
        translateX += 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_A))
    {
        translateX -= 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_R))
    {
        translateZ -= 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_F))
    {
        translateZ += 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_1))
    {
        scaleX += 2 * deltaTime;
        scaleY += 2 * deltaTime;
        scaleZ += 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_2))
    {
        scaleX -= 2 * deltaTime;
        scaleY -= 2 * deltaTime;
        scaleZ -= 2 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_3))
    {
        angularStepOX += VITEZA * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_4))
    {
        angularStepOX -= VITEZA * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_5))
    {
        angularStepOY += VITEZA * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_6))
    {
        angularStepOY -= VITEZA * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_7))
    {
        angularStepOZ += VITEZA * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_8))
    {
        angularStepOZ -= VITEZA * deltaTime;
    }


    if (window->KeyHold(GLFW_KEY_M))
    {
        angularStepOY_gen -= VITEZA * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_N))
    {
        angularStepOY_gen += VITEZA * deltaTime;
    }

    */


}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
    /*
    // TODO(student): Add viewport movement and scaling logic

    if (key == GLFW_KEY_I)
    {
        miniViewportArea.y++;
    }

    if (key == GLFW_KEY_K)
    {
        miniViewportArea.y--;
    }

    if (key == GLFW_KEY_L)
    {
        miniViewportArea.x++;
    }

    if (key == GLFW_KEY_J)
    {
        miniViewportArea.x--;
    }

    if (key == GLFW_KEY_U)
    {
        float rap = (float)miniViewportArea.height / miniViewportArea.width;
        miniViewportArea.width -= 10;
        miniViewportArea.height = rap * miniViewportArea.width;
    }

    if (key == GLFW_KEY_O)
    {
        float rap = (float)miniViewportArea.height / miniViewportArea.width;
        miniViewportArea.width += 10;
        miniViewportArea.height = rap * miniViewportArea.width;
    }
    */
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
