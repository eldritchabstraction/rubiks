/*
 * rubik.cpp
 *
 *  Created on: Jul 28, 2017
 *      Author: eldr
 */

#include <cmath>
#include <vector>
#include <string>
#include <iostream>

const double pi = std::acos(-1);

using namespace std;

// intentionally leaving out centre cubes for now
const vector<vector<int> > F_map = { { 1, 3, 9, 7}, { 2, 6, 8, 4} };
const vector<vector<int> > B_map = { {20,18,24,26}, {23,19,21,25} };
const vector<vector<int> > R_map = { { 3,20,26, 9}, {12,23,17, 6} };
const vector<vector<int> > L_map = { {18, 1, 7,24}, {10, 4,15,21} };
const vector<vector<int> > U_map = { {18,20, 3, 1}, {19,12, 2,10} };
const vector<vector<int> > D_map = { { 7, 9,26,24}, { 8,17,25,15} };

struct Orient
{
    Orient(int x, int y, int z): x(x), y(y), z(z) {};
    Orient(const Orient& orient)
    {
        x = orient.x;
        y = orient.y;
        z = orient.z;
    }

    void rotate_about_x(bool ccw);
    void rotate_about_y(bool ccw);
    void rotate_about_z(bool ccw);
    int x, y, z;
    friend ostream& operator<< (ostream& stream, const Orient& orient);
};

ostream& operator<<(ostream& stream, const Orient& orient)
{
    stream << "{" << orient.x << " " << orient.y << " " << orient.z << "}";
    return stream;
}

// to be consistent, use the right hand rule where thumb points at +axis
void Orient::rotate_about_x(bool ccw)
{
    Orient temp_orient(*this);

    x = temp_orient.x * 1 + temp_orient.y * 0                          + temp_orient.z * 0;
    y = temp_orient.x * 0 + temp_orient.y * cos((ccw ? 1 : -1) * pi/2) - temp_orient.z * sin((ccw ? 1 : -1) * pi/2);
    z = temp_orient.x * 0 + temp_orient.y * sin((ccw ? 1 : -1) * pi/2) + temp_orient.z * cos((ccw ? 1 : -1) * pi/2);
}

void Orient::rotate_about_y(bool ccw)
{
    Orient temp_orient(*this);

    x = temp_orient.x * cos((ccw ? 1 : -1) * pi/2)      + temp_orient.y * 0 + temp_orient.z * sin((ccw ? 1 : -1) * pi/2);
    y = temp_orient.x * 0                               + temp_orient.y * 1 + temp_orient.z * 0;
    z = -1 * temp_orient.x * sin((ccw ? 1 : -1) * pi/2) + temp_orient.y * 0 + temp_orient.z * cos((ccw ? 1 : -1) * pi/2);
}

void Orient::rotate_about_z(bool ccw)
{
    Orient temp_orient(*this);

    x = temp_orient.x * cos((ccw ? 1 : -1) * pi/2)   - temp_orient.y * sin((ccw ? 1 : -1) * pi/2) + temp_orient.z * 0;
    y = temp_orient.x * sin((ccw ? 1 : -1) * pi/2)   + temp_orient.y * cos((ccw ? 1 : -1) * pi/2) + temp_orient.z * 0;
    z = temp_orient.x * 0                            + temp_orient.y * 0                          + temp_orient.z * 1;
}

// not using enum class this time because I don't want to scope resolve a lot
enum e_colour
{
    blue,
    orange,
    white,
    red,
    yellow,
    green,
    none
};

struct Cublet
{
    Cublet(vector<e_colour> colours, const Orient& orient): colours(colours), orient(orient) {};

    friend ostream& operator<< (ostream& stream, const Cublet& cublet);
    vector<e_colour> colours;
    Orient orient;
};

ostream& operator<< (ostream& stream, const Cublet& cublet)
{
    for (int i = 0; i < 6; i++)
    {
        if (cublet.colours[i] == blue)
            cout << "blue ";
        else if (cublet.colours[i] == orange)
            cout << "orange ";
        else if (cublet.colours[i] == white)
            cout << "white ";
        else if (cublet.colours[i] == red)
            cout << "red ";
        else if (cublet.colours[i] == yellow)
            cout << "yellow ";
        else if (cublet.colours[i] == green)
            cout << "green ";
    }
    stream << cublet.orient;

    return stream;
}
class Cube
{
public:
    Cube();

    // uppercase means cw operation whereas lowercase means ccw operation
    void L(void) { rotate(L_map, true); }
    void l(void) { rotate(L_map, false); }

    void R(void) { rotate(R_map, true); }
    void r(void) { rotate(R_map, false); }

    void U(void) { rotate(U_map, true); }
    void u(void) { rotate(U_map, false); }

    void D(void) { rotate(D_map, true); }
    void d(void) { rotate(D_map, false); }

    void F(void) { rotate(F_map, true); }
    void f(void) { rotate(F_map, false); }

    void B(void) { rotate(B_map, true); }
    void b(void) { rotate(B_map, false); }

    void print(void);

private:
    void rotate(vector<vector<int> > mapping, bool cw);

    vector<Cublet> cublets;
};

Cube::Cube()
{
    // null cube, not to be used other than a offset
    cublets.push_back(Cublet({  none,   none,   none,   none,   none,   none    }, Orient({0,0,0})));

    // 1-3
    cublets.push_back(Cublet({  none,   blue,   red,    none,   white,  none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  none,   none,   red,    none,   white,  none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  green,  none,   red,    none,   white,  none    }, Orient({0,1,0})));

    // 4-6
    cublets.push_back(Cublet({  none,   blue,   none,   none,   white,  none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  none,   none,   none,   none,   white,  none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  none,   green,  none,   none,   white,  none    }, Orient({0,1,0})));

    // 7-9
    cublets.push_back(Cublet({  none,   blue,   none,   orange, white,  none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  none,   none,   none,   orange, white,  none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  green,  none,   none,   orange, white,  none    }, Orient({0,1,0})));

    // 10 - 12
    cublets.push_back(Cublet({  none,   blue,   red,    none,   none,   none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  none,   none,   red,    none,   none,   none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  green,  none,   red,    none,   none,   none    }, Orient({0,1,0})));

    // 13, 14
    cublets.push_back(Cublet({  none,   blue,   none,   none,   none,   none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  green,  none,   none,   none,   none,   none    }, Orient({0,1,0})));

    // 15 - 17
    cublets.push_back(Cublet({  none,   blue,   none,   orange, none,   none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  none,   none,   none,   orange, none,   none    }, Orient({0,1,0})));
    cublets.push_back(Cublet({  green,  none,   none,   orange, none,   none    }, Orient({0,1,0})));

    // 18 - 20
    cublets.push_back(Cublet({  none,   blue,   red,    none,   none,   yellow  }, Orient({0,1,0})));
    cublets.push_back(Cublet({  none,   none,   red,    none,   none,   yellow  }, Orient({0,1,0})));
    cublets.push_back(Cublet({  green,  none,   red,    none,   none,   yellow  }, Orient({0,1,0})));

    // 21 - 23
    cublets.push_back(Cublet({  none,   blue,   none,   none,   none,   yellow  }, Orient({0,1,0})));
    cublets.push_back(Cublet({  none,   none,   none,   none,   none,   yellow  }, Orient({0,1,0})));
    cublets.push_back(Cublet({  green,  none,   none,   none,   none,   yellow  }, Orient({0,1,0})));

    // 24 - 26
    cublets.push_back(Cublet({  none,   blue,   none,   orange, none,   yellow  }, Orient({0,1,0})));
    cublets.push_back(Cublet({  none,   none,   none,   orange, none,   yellow  }, Orient({0,1,0})));
    cublets.push_back(Cublet({  green,  none,   none,   orange, none,   yellow  }, Orient({0,1,0})));
}

void Cube::print(void)
{
    // I didn't want to zero index
    for (int i = 1; i < 27; i++)
    {
        cout << i << " " << cublets[i] << endl;
    }
}

void Cube::rotate(vector<vector<int> > mapping, bool cw)
{
    // take care of the orientation
    for (auto field : mapping)
    {
        if (mapping == F_map || mapping == B_map)
        {
            cublets[field[3]].orient.rotate_about_z((mapping == F_map ? !cw : cw));
            cublets[field[2]].orient.rotate_about_z((mapping == F_map ? !cw : cw));
            cublets[field[1]].orient.rotate_about_z((mapping == F_map ? !cw : cw));
            cublets[field[0]].orient.rotate_about_z((mapping == F_map ? !cw : cw));
        }
        else if (mapping == R_map || mapping == L_map)
        {
            cublets[field[3]].orient.rotate_about_x((mapping == R_map ? !cw : cw));
            cublets[field[2]].orient.rotate_about_x((mapping == R_map ? !cw : cw));
            cublets[field[1]].orient.rotate_about_x((mapping == R_map ? !cw : cw));
            cublets[field[0]].orient.rotate_about_x((mapping == R_map ? !cw : cw));
        }
        else if (mapping == U_map || mapping == D_map)
        {
            cublets[field[3]].orient.rotate_about_y((mapping == U_map ? !cw : cw));
            cublets[field[2]].orient.rotate_about_y((mapping == U_map ? !cw : cw));
            cublets[field[1]].orient.rotate_about_y((mapping == U_map ? !cw : cw));
            cublets[field[0]].orient.rotate_about_y((mapping == U_map ? !cw : cw));
        }
    }
    // take care of the positions
    if (cw)
    {
        for (auto field : mapping)
        {
            auto temp = cublets[field[3]];
            cublets[field[3]] = cublets[field[2]];
            cublets[field[2]] = cublets[field[1]];
            cublets[field[1]] = cublets[field[0]];
            cublets[field[0]] = temp;
        }
    }
    else
    {
        for (auto field : mapping)
        {
            auto temp = cublets[field[0]];
            cublets[field[0]] = cublets[field[1]];
            cublets[field[1]] = cublets[field[2]];
            cublets[field[2]] = cublets[field[3]];
            cublets[field[3]] = temp;
        }
    }
}

int main (void)
{
    Cube cube;

    cube.print();
    cube.F();
    cube.R();
    cube.L();
    cube.r();
    cube.U();
    cube.d();
    cube.B();

    cube.b();
    cube.D();
    cube.u();
    cube.R();
    cube.l();
    cube.r();
    cube.f();
    cube.print();
}
