//Program to Show the working of Cohen-Sutherland Line-Clipping Algorithm

#include <iostream>
#include <graphics.h>

using namespace std;

//Variable Declarations
static int ABOVE = 8,
           BELOW = 4,
           RIGHT = 2,
           LEFT = 1;
int xh,yh,xl,yl;

//GetCode function
int getCode(int x,int y)
{
    int code = 0;
    if(y > yh)
        code |= ABOVE;
    if(y < yl)
        code |= BELOW;
    if(x > xh)
        code |= RIGHT;
    if(x < xl)
        code |= LEFT;
    return code;
}

//main()
int main()
{
    int x1,y1,x2,y2;
    char choice;
    int gd,gm;
    gd = DETECT;
    initgraph(&gd,&gm,NULL);

    setcolor(BLUE);
    cout<<"\nEnter window co-ordinates : \n";
    cin>>xl>>yl>>xh>>yh;
    rectangle(xl,yl,xh,yh);

loop:
    setcolor(BLUE);
    cout<<"\nEnter co-ordinates of line : \n";
    cin>>x1>>y1>>x2>>y2;
    line(x1,y1,x2,y2);

    int outCode1,outCode2;
    outCode1 = getCode(x1,y1);
    outCode2 = getCode(x2,y2);

    bool accept;
    float m;

    while(1)
    {
        m = (float)(y2-y1)/(x2-x1);

        //Both points inside. Accept line
        if(outCode1 == 0 && outCode2 == 0)
        {
            accept = true;
            break;
        }

        //AND of both codes != 0. Line is outside, Reject line
        else if((outCode1 & outCode2) != 0)
        {
            accept = false;
            break;
        }
        else
        {
            int x,y;
            int temp;

            //Decide if point1 is inside, if not, calculate intersection
            if(outCode1==0)
                temp = outCode2;
            else
                temp = outCode1;

            //Line clips top edge
            if(temp & ABOVE)
            {
                x = int(x1+ (yh-y1)/m);
                y = yh;
            }

            //Line clips bottom edge
            else if(temp & BELOW)
            {
                x = int(x1+ (yl-y1)/m);
                y = yl;
            }

            //Line clips left edge
            else if(temp & LEFT)
            {
                x = xl;
                y = int(y1+ m*(xl-x1));
            }

            //Line clips right edge
            else if(temp & RIGHT)
            {
                x = xh;
                y = (int)(y1 + m*(xh-x1));
            }

            //Check which point we had selected earlier as temp, and replace its co-ordinates
            if(temp == outCode1)
            {
                x1 = x;
                y1 = y;
                outCode1 = getCode(x1,y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                outCode2 = getCode(x2,y2);
            }
        }
    }

    setcolor(WHITE);
    if(accept)
        line(x1,y1,x2,y2);

    cout<<"\nDo you want to continue (y/n) ? ";
    cin>>choice;
    if(choice == 'y' || choice == 'Y')
        goto loop;

    //delay(15000);
    closegraph();
    return 0;
}
