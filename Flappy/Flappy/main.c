//
//  main.c
//  Flappy
//
//  Created by NISCHITHA on 01/04/23.
//

#include <stdio.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdlib.h>
#include <string.h>





int check=1;            //to display the front page only once
int i=0;
int count=140;          //to keep track of how many pixel positions the beams moved left
int coll=0;                 //collision detection variable
GLfloat c1,c2;              //to generate random color for bird
GLfloat ba[1000][8]={{0},{0}};//bottom array for bottom beams
GLfloat ta[1000][8]={{0},{0}};//top array for top beams
GLfloat u=100.0,v=100.0;      //initial position of bird

//calculating raster values for bird in byte
GLubyte rasters[218] = {
   0x0f,0xff,0xff,0xff,0xff,0xf0,
   0x0f,0xff,0xff,0xff,0xff,0xf0,
   0x0c,0x00,0xc0,0x00,0x00,0x30,
   0x0c,0x00,0xc0,0x00,0x00,0x30,
   0x0c,0x00,0xc0,0x00,0x00,0x30,
   0x0c,0x00,0xc0,0x00,0x00,0x30,
   0x0c,0x00,0xc0,0x00,0x00,0x30,
   0x0c,0x00,0xc0,0x00,0x00,0x30,
   0x0f,0xff,0xc0,0x00,0x00,0x30,
   0x0f,0xff,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xc0,0x00,0x00,0x30,
   0x00,0x00,0xff,0xff,0xff,0xf0,
   0x00,0x00,0xff,0xff,0xff,0xf0,
   0x00,0x00,0x00,0x30,0x00,0x3f,
   0x00,0x00,0x00,0x30,0x00,0x3f,
   0x00,0x00,0x00,0x30,0xf0,0x3f,
   0x00,0x00,0x00,0x30,0xf0,0x3f,
   0x00,0x00,0x00,0x30,0xf0,0x3f,
   0x00,0x00,0x00,0x30,0xf0,0x3f,
   0x00,0x00,0x00,0x30,0x00,0x3f,
   0x00,0x00,0x00,0x30,0x00,0x30,
   0x00,0x00,0x00,0x30,0x00,0x30,
   0x00,0x00,0x00,0x30,0x00,0x30,
   0x00,0x00,0x00,0x30,0x00,0x30,
   0x00,0x00,0x00,0x3f,0xff,0xf0,
   0x00,0x00,0x00,0x3f,0xff,0xf0
};

void myinit();
void display();
void back_ground();
void game_end(int coll);
void front();

void front()
{
        char str1[]="FLAPPY BIRD";
        char str2[]="876543210";
        char str3[]="Nachiketha K C     4NM20CS113";
        char str4[]="Nischitha Shetty   4NM20CS122";
        myinit();
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(230.0f, 260.0f);
        for(int i=0;i<strlen(str1);i++)
        {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)str1[i]);
        }

        glColor3f(0.5f, 0.0f, 0.0f);
        glRasterPos2f(230.0f, 110.0f);
        for(int i=0;i<strlen(str3);i++)
        {
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)str3[i]);
        }

        glColor3f(0.5f, 0.0f, 0.0f);
        glRasterPos2f(230.0f, 85.0f);
        for(int i=0;i<strlen(str4);i++)
        {
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)str4[i]);
        }
        check=0;
        glFlush();

        for(int i=0;i<=8;i++)
        {

                glColor3f(1.0f, 0.0f, 0.0f);
                glRasterPos2f(270.0f, 190.0f);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)str2[i]);
                glFlush();
                for(int j=0;j<500000000;j++);
                glColor3f(0.0f, 0.9f, 0.9f);
                glRasterPos2f(270.0f, 190.0f);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)str2[i]);
                for(int j=0;j<500000000;j++);
                glFlush();
        }
}


void mouse(int btn,int state,int x,int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        v=v+50;           //on clicking MOUSE RIGHT BUTTON,bird moves up by 5 px

        if(v>380)
                v=380;
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
        v=v-50;
}
void keyboard (unsigned char key, int x, int y)    //CONTROLS OF THE KEYBOARD
{


    switch (key)
    {


        case 'w':
            v=v+50;
        break;

        case 's':
            v=v-50;
        break;

        case 'a':
            
        break;
            

        case 'q':

            exit(0);
            
        break;

    }
}

void game_end(int coll)         //printing the score and terminating
{
        char string1[20]="GAME OVER";
        char string2[20]="YOUR SCORE IS : ";
        int len1 = strlen(string1);

        if(coll==0){string2[17]=48;}
        int rev=0,var;
        while(coll!=0)
        {
                var=coll%10;
                rev=var+rev*10;
                coll=coll/10;
        }

        for(int i=0;rev!=0;i++)
        {
                var=rev%10;
                string2[17+i]=var+48;
                rev=rev/10;
        }
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0,1.0,1.0,1.0);

        glColor3f(0.0f, 0.0f, 1.0f);
        glRasterPos2f(240.0f, 230.0f);

        for (int i = 0; i < len1; i++)
        {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)string1[i]);
        }

        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(215.0f, 190.0f);

        for (int i = 0; i <= 19; i++)
        {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)string2[i]);
        }

        glFlush();
        for(int l=0;l<1000000000;l++);    //holding the screen for a while and then terminate
        exit(0);

}

void myinit()
{

        glPixelStorei (GL_UNPACK_ALIGNMENT, 1);//to unpack the pixels in rasters array.
        glClearColor(0.0,0.9,0.9,1.0);
        glColor3f(1.0,0.0,1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0,600.0,0.0,400.0);
        glMatrixMode(GL_MODELVIEW);
}

void obstacles()
{
        //after 140 px left move of beam, new beam is created
        if(count==140)//count keeps track of how many pixels does beams have moved left. when 140 px,generates new top and bottom beams.
        {


            
            glFlush();
            glutSwapBuffers();
            

                ba[i][0]=585.0;
                ba[i][1]=0.0;
                ba[i][2]=585.0;
                ba[i][3]=rand()%200;
                ba[i][4]=600.0;
                ba[i][5]=ba[i][3];
                ba[i][6]=600.0;
                ba[i][7]=0.0;

                ta[i][0]=585.0;
                ta[i][1]=400.0;
                ta[i][2]=585.0;
                ta[i][3]=400.0-ba[i][3]-140.0;
                ta[i][4]=600.0;
                ta[i][5]=ta[i][3];
                ta[i][6]=600.0;
                ta[i][7]=400.0;
            i++;
            count=0;
        }
        //clearing the color buffer and displaying
        glClear(GL_COLOR_BUFFER_BIT);
        count++;

        for(int m=0;m<i;m++)//displays beams
        {
                if(ba[m][0]==0 && ta[m][0]==0)continue;
                glColor3f(1.0,0.0,0.0);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//to fill color for bottom  beams
                glBegin(GL_POLYGON);
                        glVertex2f(ba[m][0]--,ba[m][1]);
                        glVertex2f(ba[m][2]--,ba[m][3]);
                        glVertex2f(ba[m][4]--,ba[m][5]);
                        glVertex2f(ba[m][6]--,ba[m][7]);
                glEnd();

                glColor3f(1.0,0.0,0.0);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//to fill color for top beams
                glBegin(GL_POLYGON);
                        glVertex2f(ta[m][0]--,ta[m][1]);
                        glVertex2f(ta[m][2]--,400-ta[m][3]);
                        glVertex2f(ta[m][4]--,400-ta[m][5]);
                        glVertex2f(ta[m][6]--,ta[m][7]);
                glEnd();

                 glColor3f(c1,c2,0.0);                          //to display bird
                 glRasterPos2i (u,v);                           //to set position of bird
                 glBitmap (48, 36, 0.0, 0.0, 0.0, 0.0, rasters);//width =48 px height=36 px rasters=px array
        }

        glFlush();

        if(ta[coll][4]==99)coll++;

        //collistion theorem for top obstacles
        if( u<=(ta[coll][2]+15) && (u+48)>=ta[coll][2] && v<=(ba[coll][3]+400+ta[coll][3]) && (36+v)>=(140+ba[coll][3]))
        {
               // game_end(coll);
        }

        //collision theorm for bottom obstacles
        if( u<=(ba[coll][0]+15) && (u+48)>=ba[coll][0] && v<=(ba[coll][1]+ba[coll][3]) && (36+v)>=ba[coll][1])
        {
                //game_end(coll);
        }

}

void display(void)
{
        if(check==1)front();
        int k=0;
        glClear(GL_COLOR_BUFFER_BIT);

//        v--;//on not clicking the mouse button,to move bird down.
  //        if(v==0)//if touches base,terminates
//                game_end(coll);
    
            obstacles();
}



int main(int argc,char** argv)
{
    int m,level;
    printf("-----------------\n|   FLAPPY BIRD |\n-----------------\n******************************\n* Enter the level :\t\t*\n*-------------------\t\t*\n*Level 1: EASY\t\t*\n*Level 2: MEDIUM \t*\n*Level 3: HARD\t\t*\n******************************\n\nENTER YOUR CHOICE :");
    scanf("%d",&level);
    
    //Level Defination.
    if(level==1)
        m=1000;
    else if(level==2)
        m=6000;
    else if(level==3)
        m=8000;
    
        c1= (GLfloat)rand() / RAND_MAX;//random colors for bird
        c2= (GLfloat)rand() / RAND_MAX;
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(600,400);
        glutInitWindowPosition(0,0);
        glutCreateWindow("Flappy Bird");
        myinit();
        glutDisplayFunc(display);
        //glEnable(GL_DEPTH_TEST);
        glutIdleFunc(display);
        glutMouseFunc(mouse);
        glutKeyboardFunc(keyboard);
        glutMainLoop();

}


