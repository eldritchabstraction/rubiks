/*
 * rubik.cpp
 *
 *  Created on: Jul 28, 2017
 *      Author: eldr
 */

#include <vector>
#include <string>
#include <iostream>

using namespace std;
/*
 * rotating mappings:
 *
 * - the below are the indices of the cube, if they are rotated e_face::right, a CW 90 degree rotation will
 *   be achieved, a rotation to the e_face::left produces a CCW 90 rotation
 * - a rotation to the e_face::right means (for example):
 *      - the colour of pane 1 is assigned to pane 3
 *      - the colour of pane 3 is assigned to pane 7
 *      - the colour of pane 7 is assigned to pane 9
 *      - the colour of pane 9 is assigned to pane 1
 */
const vector< vector <int> > U = { { 1, 3, 9, 7}, { 2, 6, 8, 4}, {10,37,28,19}, {11,38,29,20}, {12,39,30,21} };
const vector< vector <int> > R = { {28,30,36,34}, {29,33,35,31}, { 9,37,54,27}, { 6,40,51,24}, { 3,43,48,21} };
const vector< vector <int> > L = { {10,12,18,16}, {11,15,17,13}, { 1,19,46,45}, { 4,22,49,42}, { 7,25,52,39} };
const vector< vector <int> > D = { {46,48,54,52}, {47,51,53,49}, {16,25,34,43}, {17,26,35,44}, {18,27,36,45} };
const vector< vector <int> > F = { {19,21,27,25}, {20,24,26,22}, { 7,28,48,18}, { 8,31,47,15}, { 9,34,46,12} };
const vector< vector <int> > B = { {37,39,45,43}, {38,42,44,40}, { 3,10,52,36}, { 2,13,53,33}, { 1,16,54,30} };

enum class e_colour
{
    red     = 9,
    blue    = 18,
    white   = 27,
    green   = 36,
    yellow  = 45,
    orange  = 54
};

enum class e_face
{
    up,
    down,
    left,
    right,
    front,
    back
};

struct Pane
{
    Pane(e_colour colour, int uid): colour(colour), uid(uid){};
    e_colour colour;
    int uid;
    friend ostream& operator<< (ostream& stream, const Pane& pane);
};

class Cube
{
public:
    Cube();

    void print(void);

    void rotate(e_face face, bool cw);
private:
    vector<Pane> panes;
};


void Cube::rotate(e_face face, bool cw)
{

    vector< vector<int> > mapping;
    if (face == e_face::up)
        mapping = U;
    else if (face == e_face::down)
        mapping = D;
    else if (face == e_face::left)
        mapping = L;
    else if (face == e_face::right)
        mapping = R;
    else if (face == e_face::front)
        mapping = F;
    else if (face == e_face::back)
        mapping = B;

    if (cw)
    {
        for (auto field : mapping)
        {
            auto temp = panes[field[3]].colour;
            panes[field[3]].colour = panes[field[2]].colour;
            panes[field[2]].colour = panes[field[1]].colour;
            panes[field[1]].colour = panes[field[0]].colour;
            panes[field[0]].colour = temp;
        }
    }
    else
    {
        for (auto field : mapping)
        {
            auto temp = panes[field[0]].colour;
            panes[field[0]].colour = panes[field[1]].colour;
            panes[field[1]].colour = panes[field[2]].colour;
            panes[field[2]].colour = panes[field[3]].colour;
            panes[field[3]].colour = temp;
        }
    }
}

Cube::Cube()
{
    // initialize colours
    for (int i = 0; i < 55; i++)
    {
        if (i == 0)
            panes.push_back(Pane(e_colour::red, i));
        else if (i <= (int)e_colour::red)
            panes.push_back(Pane(e_colour::red, i));
        else if (i <= (int)e_colour::blue)
            panes.push_back(Pane(e_colour::blue, i));
        else if (i <= (int)e_colour::white)
            panes.push_back(Pane(e_colour::white, i));
        else if (i <= (int)e_colour::green)
            panes.push_back(Pane(e_colour::green, i));
        else if (i <= (int)e_colour::yellow)
            panes.push_back(Pane(e_colour::yellow, i));
        else if (i <= (int)e_colour::orange)
            panes.push_back(Pane(e_colour::orange, i));
    }
}

ostream& operator<<(ostream& stream, const Pane& pane)
{
    if (pane.colour == e_colour::blue)
        stream << "B ";
    else if (pane.colour == e_colour::orange)
        stream << "O ";
    else if (pane.colour == e_colour::yellow)
        stream << "Y ";
    else if (pane.colour == e_colour::red)
        stream << "R ";
    else if (pane.colour == e_colour::white)
        stream << "W ";
    else if (pane.colour == e_colour::green)
        stream << "G ";

    return stream;
 }

void Cube::print(void)
{
    const string space = "      ";

    // print the up face

    for (int i = 1; i <= 9; i++)
    {
        if ((i - 1) % 3 == 0)
            cout << space;
        cout << panes[i];
        if (i % 3 == 0)
            cout << endl;

    }

    // print out everything in the "middle"
    // for each line
    for (int i = 0; i < 3; i++)
    {
        // for each face
        for (int j = 0; j < 4; j++)
        {
            // start with 10 + 3*i, then add 7 * j
            cout << panes[10 + 3*i + 9*j];
            cout << panes[11 + 3*i + 9*j];
            cout << panes[12 + 3*i + 9*j];
        }
        cout << endl;
    }

    // print the down face
    for (int i = 46; i <= 54; i++)
    {
        if ((i - 1) % 3 == 0)
            cout << space;
        cout << panes[i];
        if (i % 3 == 0)
            cout << endl;
    }
    cout << endl;
}

int main (void)
{
    Cube cube;
    cube.print();
    cube.rotate(e_face::front, 1);
    cube.print();
    cube.rotate(e_face::right, 1);
    cube.print();
    cube.rotate(e_face::right, 0);
    cube.print();
    cube.rotate(e_face::front, 0);
    cube.print();
}
