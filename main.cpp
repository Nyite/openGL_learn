#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>

void error_cb(int err_code, const char* description)
{
    std::cout << "GLFW error " << err_code << ": " << description << std::endl;
    throw(description);
}

struct Cell
{
    bool isMine;
    bool opened;
    bool flaged;
    int neighbours_cnt;
};

const int CellW = 50;
const int CellH = 50;

const int FieldW = 10;
const int FieldH = 15;
const int Mines = 20;

const float x_scale_factor = 2.0f / FieldH;
const float y_scale_factor = 2.0f / FieldW;

const int AppW = CellW * FieldW;
const int AppH = CellH * FieldH;

Cell field[FieldH][FieldW] {};

// 7-segment number renderer
void draw_cell_number(int num)
{
    glLineWidth(7);
    glBegin(GL_LINES);

        glColor3f(0.1f, 0.3f, 0.1f);

        if (num != 5 && num != 6)                         { glVertex3f(0.6f, 0.7f, 0.0f); glVertex3f(0.6f, 0.5f, 0.0f); } // top-right
        if (num != 2)                                     { glVertex3f(0.6f, 0.5f, 0.0f); glVertex3f(0.6f, 0.3f, 0.0f); } // bot-right
        if (num != 1 && num != 4 && num != 7)             { glVertex3f(0.6f, 0.3f, 0.0f); glVertex3f(0.4f, 0.3f, 0.0f); } // bot
        if (num == 0 || num == 2 || num == 6 || num == 8) { glVertex3f(0.4f, 0.3f, 0.0f); glVertex3f(0.4f, 0.5f, 0.0f); } // bot-left
        if (num != 1 && num != 2 && num != 3 && num != 7) { glVertex3f(0.4f, 0.5f, 0.0f); glVertex3f(0.4f, 0.7f, 0.0f); } // top-left
        if (num != 1 && num != 4)                         { glVertex3f(0.6f, 0.7f, 0.0f); glVertex3f(0.4f, 0.7f, 0.0f); } // top
        if (num != 0 && num != 1 && num != 7)             { glVertex3f(0.6f, 0.5f, 0.0f); glVertex3f(0.4f, 0.5f, 0.0f); } // middle

    glEnd();
}

void draw_cell(Cell cell)
{
    glBegin(GL_TRIANGLE_STRIP);
        
        glColor3f(0.6f, 0.6f, 0.6f);
        glVertex3f(1.0f, 0.0f, 0.0f);

        glColor3f(0.9f, 0.9f, 0.9f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);

    glEnd();

    if (cell.isMine)
    {
        glBegin(GL_TRIANGLE_FAN);

            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.25f, 0.25f, 0.0f);
            glVertex3f(0.25f, 0.75f, 0.0f);
            glVertex3f(0.75f, 0.75f, 0.0f);
            glVertex3f(0.75f, 0.25f, 0.0f);

        glEnd();
    }
    else if (cell.neighbours_cnt != 0)
    {
        draw_cell_number(cell.neighbours_cnt);
    }
}

void set_mine_at(int row, int col)
{
    field[row][col].isMine = true;
    for (int i = row - 1; i <= row + 1; ++i)
        for (int j = col - 1; j <= col + 1; ++j)
        {
            if ((i == row && j == col) || i >= FieldH || j >= FieldW || i < 0 || j < 0)
                continue;
            ++field[i][j].neighbours_cnt;
        }
}

void game_init()
{
    srand(time(NULL));
    for (int i = 0; i < Mines; ++i)
    {
        int row = rand() % FieldH;
        int col = rand() % FieldW;

        if (field[row][col].isMine) --i;
        else set_mine_at(row, col);
    }
}

void draw_field()
{
    glPushMatrix();
    glScalef(x_scale_factor, y_scale_factor, 1.0f);

    for (int i = 0; i < FieldH; ++i)
        for (int j = 0; j < FieldW; ++j)
        {
            glPushMatrix();

            glTranslatef(float(i), float(j), 0.0f);
            draw_cell(field[i][j]);

            glPopMatrix();
        }
    glPopMatrix();
}

int main(void)
{
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(AppH, AppW, "Сапёр", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    

    game_init();
    glTranslatef(-1.0f, -1.0f, 0.0f); // Move (0, 0) to bottom-right
   /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw_field();

        glfwSwapBuffers(window);
        glfwPollEvents();
        // usleep(1000); 
    }

    glfwTerminate();
    return 0;
}
