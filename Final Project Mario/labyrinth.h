int dH = 10;
int dW = 10;

bool lab[100][100];
int L[100];
int R[100];
int X;
int Y;


void plotV0()
{
    lab[X][Y] = true;
    lab[X][Y+1] = true;
    X++;
}

void plotV()
{
    lab[X+1][Y] = true;
    lab[X+1][Y+1] = true;
}

void plotH()
{
    lab[X][Y+1] = true;
    lab[X+1][Y+1] = true;
}

void plotN()
{
    X = 0;
    Y = Y+2;
}

void generateLabyrinth()
{
    srand ( time(NULL) );
    //glfwEnable( GLFW_KEY_REPEAT );

    // Maze reset
    for( int x=0; x<2*dW; x++)
        for( int y=0; y<2*dH; y++)
            lab[x][y]=false;

    X=0;
    Y=0;
    L[0]=1;
    int E=dW;
    while (E)
    {
        L[E]=E;
        R[E]=E;
        E--;
        if (E) {plotH();}
        X+=2;
    }
    lab[X-2][Y+1]=true;
    plotN();
    plotV0();

    int H=dH;
    while(H>1)
    {
        H--;
        int C=dW;
        while(C>1)
        {
            C--;
            E=L[C-1];
            if( (C!=E)  && (random(0,1)>0.5) )
            {
                R[E]=R[C];
                L[R[C]]=E;
                R[C]=C-1;
                L[C-1]=C;
            }
            else
            {
                plotV();
            }

            E=L[C];
            if( (C!=E)  && (random(0,1)>0.5) )
            {
                R[E]=R[C];
                L[R[C]]=E;
                L[C]=C;
                R[C]=C;
                plotH();
            }

            lab[X+1][Y+1] = true;
            X = X+2;
        }

        plotN();
        plotV0();
    }


    int C=dW;
    while(C>1)
    {
        C--;
        E=L[C-1];
        if( (C!=E)  && ((C==R[C]) || (random(0,1)>0.5)) )
        {
            R[E]=R[C];
            L[R[C]]=E;
            R[C]=C-1;
            L[C-1]=C;
        }
        else
        {
            plotV();
        }

        E=L[C];
        R[E]=R[C];
        L[R[C]]=E;
        L[C]=C;
        R[C]=C;
        plotH();
        X=X+2;
    }



    glNewList(1,GL_COMPILE);
    glColor3f(1,1,1);
    glScalef(1,1,1.1);
    glNormal3f(0.0, 0.0, 1.0);
    for( int x=0; x<2*(dW)+1; x++)
        for( int y=0; y<2*(dH)+2; y++)
            if( lab[x][y] )
            {
                glPushMatrix();
                glTranslatef(x-dW+1,y-dH-0.5,0);
                glScalef(1,1,1);
                glColor4ub(0,0,255, 100);
                drawSolidCube(0,0,0,1);
                glPopMatrix();
            }
    glEndList();

}

#define isEmpty(x,y)    (!lab[(int)round(x)][(int)round(y)])
