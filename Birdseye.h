void crossProduct(float a[], float b[], float c[]) {
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
    return;
}
float getMagnitude(float a[]) {
    return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}
void makeUnit(float a[]) {
    float mag = getMagnitude(a);
    a[0] /= mag;
    a[1] /= mag;
    a[2] /= mag;
}
void multiplyMatrix(GLfloat M[][4], GLfloat P[4][1], GLfloat res[4][1]) {
    for(int i=0;i<4;i++)res[i][0]=0;
    for (int i = 0;i < 4;i++) {
        for (int j = 0;j < 1;j++) {
            for (int k = 0;k < 4;k++) {
                res[i][j] = res[i][j] + M[i][k] * P[k][j];
            }
        }
    }
}
void moveForward(GLfloat look[],GLfloat eye[]) {
    GLfloat dv[3];
    for(int i=0; i<3; i++) dv[i] = look[i] - eye[i];
    GLfloat magnitude = getMagnitude(dv);
    for(int i=0; i<3; i++) {
        look[i]+=dv[i]/magnitude;
        eye[i]+=dv[i]/magnitude;
    }
}
void moveBackward(GLfloat look[],GLfloat eye[]) {
    GLfloat dv[3];
    for(int i=0; i<3; i++) dv[i] = look[i] - eye[i];
    GLfloat magnitude = getMagnitude(dv);
    for(int i=0; i<3; i++) {
        look[i]-=dv[i]/magnitude;
        eye[i]-=dv[i]/magnitude;
    }
}

//Zoom in using field of view angle in y direction.


void getUVN(GLfloat eye[],GLfloat look[],GLfloat up[], GLfloat U[], GLfloat V[], GLfloat N[]) {
    for(int i=0; i<3; i++) N[i] = eye[i] - look[i];
    crossProduct(up,N,U);
    crossProduct(N,U,V);

    makeUnit(U);
    makeUnit(V);
    makeUnit(N);
}
void transformToVCS(GLfloat eye[], GLfloat look[], GLfloat up[], GLfloat P_[]) {
    GLfloat P[4][1];
    for(int i=0; i<3; i++)P[i][0] = P_[i];
    P[3][0] = 1;
    GLfloat U[3],V[3],N[3];
    getUVN(eye,look,up,U,V,N);
   // show(U);
    //show(V);
   // show(N);
    GLfloat R[4][4];
    GLfloat T[4][4];

    for (int i = 0; i < 3; i++)R[0][i] = U[i];
    for (int i = 0; i < 3; i++)R[1][i] = V[i];
    for (int i = 0; i < 3; i++)R[2][i] = N[i];
    R[0][3] = R[1][3] = R[2][3] = R[3][0] = R[3][1] = R[3][2] = 0;
    R[3][3] = 1;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            T[i][j] = (i == j);
        }
        if(i<3)T[i][3]= -eye[i];
    }
    GLfloat tmp[4][1];
    multiplyMatrix(T,P,tmp);
    multiplyMatrix(R,tmp,P);
    for(int i=0; i<3; i++) {
        P[i][0]/=P[3][0];
        P_[i] = P[i][0];
    }
}
void transformToWCS(GLfloat eye[], GLfloat look[],GLfloat up[],GLfloat P_[]) {
    GLfloat P[4][1];
    for(int i=0; i<3; i++)P[i][0] = P_[i];
    P[3][0] = 1;

    GLfloat U[3],V[3],N[3];

    getUVN(eye,look,up,U,V,N);
    GLfloat R[4][4];
    GLfloat T[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            T[i][j] = (i == j);
        }
        if(i<3)T[i][3]= eye[i];
    }

    for (int i = 0; i < 3; i++)R[i][0] = U[i];
    for (int i = 0; i < 3; i++)R[i][1] = V[i];
    for (int i = 0; i < 3; i++)R[i][2] = N[i];
    R[0][3] = R[1][3] = R[2][3] = R[3][0] = R[3][1] = R[3][2] = 0;
    R[3][3] = 1;
    GLfloat tmp[4][1];
    multiplyMatrix(R, P, tmp);
    multiplyMatrix(T, tmp, P);
    for(int i=0; i<3; i++) {
        P[i][0]/=P[3][0];
        P_[i] = P[i][0];
    }
}
void Yaw(GLfloat eye[], GLfloat look[], GLfloat up[],GLfloat &theta,bool clockwise = true) {
    //std::cout<<clockwise<<' '<<theta<<std::endl;
    /*if(clockwise && theta>=179)return;
    if(!clockwise && theta<=1)return;*/
    if(clockwise)theta++;
    else theta--;
    int neg = 1;
    if(clockwise==false)neg=-1;
    GLfloat new_eye[3]= {look[0],look[1],look[2]};
    transformToVCS(eye,look,up,new_eye);
    GLfloat new_x = new_eye[0]*cos(PI/180.0)+neg*new_eye[2]*sin(PI/180.0);
    GLfloat new_z = -neg*new_eye[0]*sin(PI/180.0)+new_eye[2]*cos(PI/180.0);
    new_eye[0] = new_x;
    new_eye[2] = new_z;
    transformToWCS(eye,look,up,new_eye);
    for(int i=0; i<3; i++)look[i] = new_eye[i];
}

void Pitch(GLfloat eye[], GLfloat look[], GLfloat up[],GLfloat &theta,bool clockwise = true) {
    /*if(clockwise && theta>=179)return;
    if(!clockwise && theta<=1)return;*/
    if(clockwise)theta++;
    else theta--;
    int neg = 1;
    if(clockwise==false)neg=-1;
    GLfloat new_eye[3]= {look[0],look[1],look[2]};
    transformToVCS(eye,look,up,new_eye);
    GLfloat new_y =      new_eye[1]*cos(PI/180.0)- neg* new_eye[2]*sin(PI/180.0);
    GLfloat new_z = neg* new_eye[1]*sin(PI/180.0)+      new_eye[2]*cos(PI/180.0);
    new_eye[1] = new_y;
    new_eye[2] = new_z;
    transformToWCS(eye,look,up,new_eye);
    for(int i=0; i<3; i++)look[i] = new_eye[i];
}

void Roll(GLfloat eye[], GLfloat look[], GLfloat up[],GLfloat &theta,bool clockwise = true) {
    if(clockwise)theta++;
    else theta--;
    int neg = 1;
    if(clockwise==false)neg=-1;
    GLfloat U[3],V[3],N[3];
    for(int i=0; i<3; i++) N[i] = eye[i] - look[i];
    crossProduct(up,N,U);
    crossProduct(N,U,V);
    GLfloat new_eye[3]= {V[0],V[1],V[2]};
    transformToVCS(eye,look,up,new_eye);
    GLfloat new_x =      new_eye[0]*cos(PI/180.0)- neg* new_eye[1]*sin(PI/180.0);
    GLfloat new_y = neg* new_eye[0]*sin(PI/180.0)+      new_eye[1]*cos(PI/180.0);
    new_eye[0] = new_x;
    new_eye[1] = new_y;
    transformToWCS(eye,look,up,new_eye);
    makeUnit(new_eye);
    for(int i=0; i<3; i++)up[i] = new_eye[i];
    //printf("New Up: %.3f %.3f %.3f\n",up[0],up[1],up[2]);
}

