#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

#include <vector>
#include <map>

// struct funcmap
// {
//     char key;
//     void T::*func();
// };
void wait(int seconds)
{
    int const ligma = 100;
    for (int i = 0; i < (seconds*ligma); i++)
    {
        for (int j = 0; j < (seconds*ligma); j++)
        {
            printf("");
        }
    }
}

enum Colour
{
    RED, 
    BLUE,
    GREEN, 
    WHITE,
    BLACK,
    YELLOW
};

class obj //is it possible to have a function that maps a character key to a function from a child class? even if the function is void?
{
    protected:
        int x;
        int y;
        char sym;
        string name;
        bool nameset = false;
        enum Colour colour;

        //arraylist<funcmap> actions = arraylist<funcmap>();
        //vector<char> keys = vector<char>();
        //vector<void> actions = vector<void>();
        //map<char, T> actions = map<char, T::((void) *func())>();

    public:
        obj()
        {
            name = "";
            x = 0;
            y = 0;
            sym = '0';
            colour = WHITE;
        }
        obj(string name, int x = 0, int y = 0, char sym = '0', enum Colour colour = WHITE)
        {
            nameset = true;
            this->name = name;
            this->x = x;
            this->y = y;
            this->sym = sym;
            this->colour = colour;
        }

        int getx()
        {
            return x;
        }

        int gety()
        {
            return y;
        }

        char getsym()
        {
            return sym;
        }

        string getname()
        {
            return name;
        }

        Colour getcolour()
        {
            return colour;
        }


        void setx(int x)
        {
            this->x = x;
        }

        void sety(int y)
        {
            this->y = y;
        }

        void setsym(char sym)
        {
            this->sym = sym;
        }

        void setcolour(Colour colour)
        {
            this->colour = colour;
        }

        void setname(string name)
        {
            if (!nameset)
            {
                nameset = true; //name can only be set once and never changed again. this is to provide an immutable identifier per object
                this->name = name;
            }
        }

        // template <class T>
        // void setaction(char key, void (*func)()) //hopefully will work
        // {
        //     // struct funcmap current = {key, (*func)};
        //     // actions.push_back(current);
        //     // actions[key] = (*func)();
        //     keys.push_back(key);
        //     actions.push_back((*func)());

        // }
};

//this is a class that will allow you to bundle objects together, to form larger ones. it is also meant to make moving multiple objects at the same time simpler.
//will also include file reading capabilities to make bundle creation simpler.
class bundle
{
    vector<obj> parts;
    int offset;
    public:
        bundle(string name, int amount = 1)
        {
            if (amount <= 0)
            {
                amount = 1;
            }
            offset = 0;
            string tempname;
            char buffer[100];
            for (int i = 0; i < amount; i++)
            {
                obj part = obj();
                parts.push_back(part);
                tempname = name + itoa(offset, buffer, 10);//strcat(name, itoa(offset, buffer, 10));
                // string str(tempname);
                parts[i].setname(tempname);
                offset += 1;
            }
        }
        bundle(string name, string filename)
        {
            offset = 0;
            string tempname;
            char buffer[100];

            FILE *fptr;
            fptr = fopen(filename.c_str(), "r");
            char blueprint[100];
            int x = 0;
            int y = 0;
            int i = 0;
            while(fgets(blueprint, 100, fptr))
            {
                while (blueprint[i] != '\n')
                {
                    obj part = obj();
                    part.setx(x);
                    part.sety(y);
                    part.setsym(blueprint[i]);
                    tempname = name + itoa(offset, buffer, 10);
                    part.setname(tempname);
                    parts.push_back(part);
                    x += 1;
                    offset += 1;
                    i += 1;
                }
                x = 0;
                y += 1;
                i = 0;
            }
        }
        bundle()
        {
            
        }


        vector<obj> getparts()
        {
            return parts;
        }
        obj getpart(int index = 0)
        {
            return parts[index];
        }
        void removepart(int index)
        {
            parts.erase(parts.begin() + index);
        }

        int getx(int index = 0)
        {
            return parts[index].getx();
        }

        int gety(int index = 0)
        {
            return parts[index].gety();
        }

        char getsym(int index = 0)
        {
            return parts[index].getsym();
        }

        void offsetallx(int newx)
        {
            // int oldx = parts[0].getx();
            // parts[0].setx(newx);
            for (int i = 0; i < parts.size(); i++)
            {
                parts[i].setx(parts[i].getx() + newx);
            }
        }
        void offsetally(int newy)
        {
            // int oldy = parts[0].gety();
            // parts[0].sety(newy);
            for (int i = 0; i < parts.size(); i++)
            {
                parts[i].sety(parts[i].gety() + newy);
            }
        }
        void offsetx(int index, int newx)
        {
            setx(index, getx(index) + newx);
        }
        void offsety(int index, int newy)
        {
            sety(index, gety(index) + newy);
        }
        

        void setallx(int newx)
        {
            for (int i = 0; i < parts.size(); i++)
            {
                parts[i].setx(newx);
            }
        }
        void setally(int newy)
        {
            for (int i = 0; i < parts.size(); i++)
            {
                parts[i].sety(newy);
            }
        }
        void setallsym(char newsym)
        {
            for (int i = 0; i < parts.size(); i++)
            {
                parts[i].setsym(newsym);
            }
        }

        void setallcolour(enum Colour colour)
        {
            for (int i = 0; i < parts.size(); i++)
            {
                parts[i].setcolour(colour);
            }
        }

        void setrangex(int start, int end, int x)
        {
            if (start < 0 || end > parts.size() || start > end)
            {
                return;
            }
            for (int i = start; i < end; i++)
            {
                setx(i, x);
            }
        }
        void setrangey(int start, int end, int y)
        {
            if (start < 0 || end > parts.size() || start > end)
            {
                return;
            }
            for (int i = start; i < end; i++)
            {
                sety(i, y);
            }
        }
        void setrangesym(int start, int end, char sym)
        {
            if (start < 0 || end > parts.size() || start > end)
            {
                return;
            }
            for (int i = start; i < end; i++)
            {
                setsym(i, sym);
            }
        }
        void setrangecolour(int start, int end, enum Colour colour)
        {
            if (start < 0 || end > parts.size() || start > end)
            {
                return;
            }
            for (int i = start; i < end; i++)
            {
                setcolour(i, colour);
            }
        }
        void setoffsetrangex(int start, int end, int x)
        {
            if (start < 0 || end > parts.size() || start > end)
            {
                return;
            }
            for (int i = start; i < end; i++)
            {
                offsetx(i, x);
            }
        }
        void setoffsetrangey(int start, int end, int y)
        {
            if (start < 0 || end > parts.size() || start > end)
            {
                return;
            }
            for (int i = start; i < end; i++)
            {
                offsety(i, y);
            }
        }

        void setx(int index, int x)
        {
            parts[index].setx(x);
        }
        void sety(int index, int y)
        {
            parts[index].sety(y);
        }
        void setsym(int index, char sym)
        {
            parts[index].setsym(sym);
        }
        void setcolour(int index, enum Colour colour)
        {
            parts[index].setcolour(colour);
        }

};

class sbundle: public bundle
{
    public:
        sbundle(string name, int amount = 1): bundle(name, amount)
        {
            //makespecial();
        }
        sbundle(string name, string filename) :bundle(name, filename)
        {
            //makespecial();
        }
        sbundle() : bundle()
        {

        }
        void makespecial()
        {
            enum Colour specialcolour = YELLOW;
            bool special = false;
            int offset = 0;
            int cury = 0;
            for (int i = 0; i < getparts().size(); i++)
            {
                if (gety(i) != cury)
                {
                    offset = 0;
                }
                cury = gety(i);
                if (getpart(i).getsym() == '<')
                {
                    //temp.setallcolour(specialcolour); //test works
                    special = true;
                    offset += 1;
                    continue;
                }
                else if (getpart(i).getsym() == '>')
                {
                    special = false;
                    offset += 1;
                    continue;
                }
                // else if (temp.getpart(i).getsym() == '\n') //not executing, probably because '\n' is not being saved. instead detect changes in the y value
                // {
                //     temp.setallcolour(specialcolour); //test works
                //     x = 0;
                //     continue;
                // }
                
                if (special)
                {
                    setcolour(i, specialcolour);
                }
                setx(i, getpart(i).getx() - offset);
    
            }
            for (int i = 0; i < getparts().size(); i++)
            {
                if (getpart(i).getsym() == '<' || getpart(i).getsym() == '>')
                {
                    //temp.setallcolour(specialcolour); test works
                    //temp.setsym(i, '\0');
                    removepart(i);
                }
    
            }
        }
};

//should probably use c++ vectors now to make life easier
class grid
{
    //arraylist<obj> objs;
    protected:
        vector<obj> objs;
        int height;
        int length;
        char background;
        
        string setupcolour(obj target)
        {
            string colour;
            switch (target.getcolour())
            {
                case RED:
                    colour =  "\033[0;31m";
                    break;
                case BLUE:
                    colour =  "\033[0;34m";
                    break;
                case GREEN:
                    colour =  "\033[0;32m";
                    break;
                case WHITE:
                    colour =  "\033[0;37m";
                    break;
                case BLACK:
                    colour = "\033[0;30m";
                    break;
                case YELLOW:
                    colour = "\033[0;33m";
                    break;
                default: //WHITE
                    colour = "\033[0;37m";
                    break;
            }
            return colour;
        }

    public:
        grid(int length, int height, char background = ' ')
        {
            objs = vector<obj>();
            this->length = length;
            this->height = height;
            this->background = background;
        }

        int getlength()
        {
            return length;
        }
        int getheight()
        {
            return height;
        }
    
        vector<obj> getobjs()
        {
            return objs;
        }

        void addobj(obj myobj)
        {
            objs.push_back(myobj);
            //printf("object appended\n");
        }

        void removeobj(obj myobj)
        {
            for (int i = 0; i < objs.size(); i++)
            {
                if (myobj.getname() == objs[i].getname())
                {
                    objs.erase(objs.begin() + i);
                    break;
                }
            }
        }

        void updateobj(obj myobj)
        {
            for (int i = 0; i < objs.size(); i++)
            {
                if (myobj.getname() == objs[i].getname())
                {
                    objs[i] = myobj;
                    break;
                }
            }
        }

        void addbundle(bundle mybundle)
        {
            //printf("ah");
            for (int i = 0; i < mybundle.getparts().size(); i++)
            {
                //printf("yo");
                addobj(mybundle.getpart(i));
            }
        }
        void updatebundle(bundle mybundle)
        {
            for (int i = 0; i < mybundle.getparts().size(); i++)
            {
                updateobj(mybundle.getpart(i));
            }
        }
        void removebundle(bundle mybundle)
        {
            for (int i = 0; i < mybundle.getparts().size(); i++)
            {
                removeobj(mybundle.getpart(i));
            }
        }

        void changebackground(char newchar)
        {
            background = newchar;
        }

        //an issue with display is that each cell of the command prompt is rectangular, meaning the same width and length results in a longer 
        void display(int waittime = -1)
        {
            bool objfound = false;
            int curindex = 0;
            printf(" ");
            for (int i = 0; i < length; i++)
            {
                printf("-");
            }
            printf(" \n");
            for (int i = 0; i < height; i++)
            {
                printf("|");
                for (int j = 0; j < length; j++)
                {
                    for (int k = 0; k < objs.size(); k++)
                    {
                        if (objs[k].getx() == j && objs[k].gety() == i)
                        {
                            curindex = k;
                            objfound = true;
                            break;
                        }   
                    }
                    
                    if (objfound)
                    {
                        //printf("%s", setupcolour(objs[curindex]));
                        cout << setupcolour(objs[curindex]);
                        printf("%c", objs[curindex].getsym());
                        printf("\033[0m"); //reset
                    }
                    else
                    {
                        printf("%c", background);
                    }
                    objfound = false;
                    curindex = 0;
                }
                printf("|\n");
            }
            printf(" ");
            for (int i = 0; i < length; i++)
            {
                printf("-");
            }
            printf(" \n");
            if (waittime >= 0)
            {
                wait(waittime);
            }
            system("cls");
        }
};