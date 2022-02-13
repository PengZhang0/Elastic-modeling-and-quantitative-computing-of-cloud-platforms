#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 5000

#define UP 12
#define DOWN 60
#define INCREASE 300
#define DECREASE 20

#define LENGTH 50 	//任务请求数量 
#define HIGH 15 	//虚拟机个数 

#define LEFTTIMES 1	//下边缘宽度 
#define RIGHTTIMES 3	//上边缘宽度 

double A[N][N] = {0.0};
double B[N][N] = {0.0};

double a[N][N] = {0};
double x[N] = {0};
double y[N] = {0};

int size = HIGH * LENGTH;


void SafeAlways(int x, int y){
	int ratiox;
	int ratioy;
    ratiox = ratioy = LENGTH*(x-1)+1+y;
	A[ratiox][ratioy] = x * DECREASE + INCREASE;
	A[ratiox][ratioy-1] = -INCREASE;
    A[ratiox][ratioy+1] = - x * DECREASE;
    
    printf("SA:|  %.2lf  |  %.2lf  |  %.2lf \n",A[ratiox][ratioy],A[ratiox][ratioy-1],A[ratiox][ratioy+1]);
};

void DownsideUnsafe(int x, int y){
    int ratiox;
    int ratioy;
    ratiox = ratioy = LENGTH*(x-1)+1+y;
    A[ratiox][ratioy] = y*DECREASE + INCREASE + DOWN;
    A[ratiox][ratioy-1] = -INCREASE;
    A[ratiox][ratioy+1] = -y*DECREASE;
    A[ratiox][ratioy+LENGTH] = -DOWN;

    printf("DU:|  %.2lf  |  %.2lf  |  %.2lf  |  %.2lf \n",A[ratiox][ratioy],A[ratiox][ratioy-1],A[ratiox][ratioy+1],A[ratiox][ratioy+LENGTH]);
};

void DownsideUnsafeRightEdge(int x, int y){
    int ratiox;
    int ratioy;
    ratiox = ratioy = LENGTH*(x-1)+1+y;
    A[ratiox][ratioy] = y*DECREASE + INCREASE;
    A[ratiox][ratioy-1] = -INCREASE;
    A[ratiox][ratioy+1] = -y*DECREASE;
    A[ratiox][ratioy+LENGTH] = -DOWN;
    
    printf("DURE:|  %.2lf  |  %.2lf  |  %.2lf  |  %.2lf \n",A[ratiox][ratioy],A[ratiox][ratioy-1],A[ratiox][ratioy+1],A[ratiox][ratioy+LENGTH]);
};

void DownsideUnsafeLeftEdge(int x, int y){
    int ratiox;
    int ratioy;
    ratiox = ratioy = LENGTH*(x-1)+1+y;
    A[ratiox][ratioy] = INCREASE + DOWN;
    A[ratiox][ratioy+1] = -DECREASE;
    //Only one job in this situation, so nevermind the valune of y is, the DECREASE probability is one times ONLY.
    A[ratiox][ratioy+LENGTH] = -DOWN;
    
    printf("DULE:|  %.2lf  |  %.2lf  |  %.2lf  |  %.2lf \n",A[ratiox][ratioy],A[ratiox][ratioy+1],A[ratiox][ratioy+LENGTH]);
    //printf("---%d---%d---%d---%d\n",A[ratiox][ratioy],A[ratiox][ratioy-1],A[ratiox][ratioy+1],A[ratiox][ratioy+13]);
    
};

void UpsideUnsafeLeftEdge(int x, int y){
    int ratiox;
    int ratioy;
    ratiox = ratioy = LENGTH*(x-1)+1+y;
    A[ratiox][ratioy] = DECREASE*x + INCREASE;
    A[ratiox][ratioy-1] = -INCREASE;
    A[ratiox][ratioy+1] = -DECREASE*x;
    A[ratiox][ratioy-LENGTH] = -UP;
    
    //printf("---%d---%d---%d---%d\n",A[ratiox][ratioy],A[ratiox][ratioy-1],A[ratiox][ratioy+1],A[ratiox][ratioy-13]);
    
    
};

void UpsideUnsafe(int x, int y){
    int ratiox;
    int ratioy;
    ratiox = ratioy = LENGTH*(x-1)+1+y;
    A[ratiox][ratioy] = DECREASE*x + INCREASE + UP;
    A[ratiox][ratioy-1] = -INCREASE;
    A[ratiox][ratioy+1] = -DECREASE*x;
    A[ratiox][ratioy-LENGTH] = -UP;
    
    //printf("---%d---%d---%d---%d\n",A[ratiox][ratioy],A[ratiox][ratioy-1],A[ratiox][ratioy+1],A[ratiox][ratioy-13]);
    
    
};

void UpsideUnsafeRightEdge(int x, int y){
    int ratiox;
    int ratioy;
    ratiox = ratioy = LENGTH*(x-1)+1+y;
    A[ratiox][ratioy] = DECREASE*x + UP;
    A[ratiox][ratioy-1] = -INCREASE;
    A[ratiox][ratioy-LENGTH] = -UP;
    
    //printf("---%d---%d---%d---%d\n",A[ratiox][ratioy],A[ratiox][ratioy-1],A[ratiox][ratioy+1],A[ratiox][ratioy-13]);
    

};

void Judge(){
    
    int x=0, y=0;
	//the location of each point in the system;
    
	int i =0;
	int j = 0;
	for( i = HIGH-1; i >= 0; i --){
		for(j = 0; j < LENGTH; j ++){
			x = i+1;
			y = j;
            //next judgement of the value of y lead to the part two "SafeAlways"
			if( (y >= LEFTTIMES*(x+1)+1) && (y <= RIGHTTIMES*(x-1))){ 
				//printf("%d ", y);
				//printf("%d,%d\t",x,y);
				SafeAlways(x, y);
			}
            //next part is part one "DownsideUnafe"
            if(y <= LEFTTIMES*(x+1)-1 && y != 0){
                //printf("%d ",y);
                //printf("--->>%d,%d\t",x,y);
                DownsideUnsafe(x,y);
            }
            //next part also belongs to part one but the extreme area of Part one's Right Edege
            if(y == LEFTTIMES*(x+1)){
                //printf("\n");
                //printf("***>>%d,%d\n",x,y);
                //printf("%d ",y);
                DownsideUnsafeRightEdge(x,y);
            }
            //Part one's Left Edege except for the point (1,0) wich will be changed at last
            if(y == 0){
                //printf("\n");
                //printf("###>>%d,%d		",x,y);
                //printf("%d ",y);
                DownsideUnsafeLeftEdge(x,y);
            }    
            if((y > RIGHTTIMES*(x-1)) && (y <= RIGHTTIMES*x)){
                //printf("\n");
                //printf("$$$>>%d,%d		",x,y);
                //printf("%d ",y);
                UpsideUnsafeLeftEdge(x,y);
                
            }
            if(y > RIGHTTIMES*x) {
                //printf("\n");
                //printf("%%%d,%d		",x,y);
                //printf("%d ",y);
                UpsideUnsafe(x,y);
            }
            if(y == LENGTH-1){
                //printf("\n");
                //printf("^^^%d,%d		",x,y);
                //printf("%d ",y);
                //UpsideUnsafeRightEdge(x,y);
                
            }
		}
		printf("\n");
	}
};

void ShapeTopandDownandFourCornerEdge(){
    int x = 0;
    int y = 0;
    
    int i,j;
    
    //Handle with the Matrix[x,y]'s last line to get A[1][1->Length] to A[Length][1->Length];
    for (i = 0; i<LENGTH; i++) {
        x = 1;
        y = i;
        if((y >= LEFTTIMES*(x+1)+1) && (y <= RIGHTTIMES * x)){
        	printf("-->%d,%d \n",x,y) ;
            SafeAlways(x,y);
        }
        if (y < LEFTTIMES*(x+1)+1) {
            printf("++>%d,%d ",x,y) ;
			DownsideUnsafeRightEdge(x,y);
        }
        if (y > RIGHTTIMES * x) {
            int ratiox;
            int ratioy;
            ratiox = ratioy = 1+y;
            A[ratiox][ratioy] =  1 * DECREASE + INCREASE + UP;
            A[ratiox][ratioy-1] = -INCREASE;
            A[ratiox][ratioy+1] = -  1 * DECREASE;
        }
    }
    
    //Handle with the Matrix[x,y]'s last line to get A[1][1->Length] to A[Length][1->Length];
    for (j = 0; j<LENGTH; j++) {
        x = HIGH;
        y = i;
        if ((y > LEFTTIMES * x) && (y <= RIGHTTIMES * (x-1))) {
            SafeAlways(x,y);
        }
        if (y <= LEFTTIMES * x) {
            int ratiox;
            int ratioy;
            ratiox = ratioy = (HIGH-1)*13+1+y;
            A[ratiox][ratioy] = y*DECREASE + INCREASE + DOWN;
            A[ratiox][ratioy-1] = -INCREASE;
            A[ratiox][ratioy+1] = -y*DECREASE;
        }
        if (y > RIGHTTIMES*(x-1)) {
            UpsideUnsafeLeftEdge(x,y);
        }
    }
    
    //Handle with the Four Corner points of the Matrix[x,y];
    //point[1,0]
    
    A[1][1] = INCREASE;
    A[1][1+LENGTH] = -DOWN;
    A[1][2] = -DECREASE;
    
    //point[1,LENGTH-1]

    A[LENGTH][LENGTH] = UP + DECREASE;
    A[LENGTH][LENGTH-1] = -INCREASE;
    
    //point[High,0]
    
    A[(HIGH-1)*13+1][(HIGH-1)*13+1] = INCREASE + DOWN;
    A[(HIGH-1)*13+1][(HIGH-1)*13+1+1] = -DECREASE;
    
    //point[High,LENGTH]
    
    A[HIGH*LENGTH][HIGH*LENGTH] = HIGH*DECREASE;
    A[HIGH*LENGTH][HIGH*LENGTH-1] = -INCREASE;
    A[HIGH*LENGTH][(HIGH-1)*LENGTH] = -UP;
    
}

void BeginningPrintInformation(){
    printf("\n");
    printf("**************************************************************************\n");
    printf("*********PLEASE PAY ATTENTION OF THE INFORMATION IN THIS TASK!!!!*********\n");
    printf("*********INFORMATION AND DATA USED IN THIS PROGRAM OF MMC TESTING*********\n");
	printf("The number of PRCESSORS is \"%d\";\nThe number of JOBS is \"%d\" of each working state;\n",HIGH,LENGTH);
	printf("****So the number of the elements in this Matrix is %d * %d = \"%d\"****\n",HIGH,LENGTH,HIGH*LENGTH);
}

void PrintMatrix(){
    int i, j;
    printf("\n*****The Matrix is:*****\n");
	for( i = 1; i < LENGTH*(HIGH)+1; i ++){
		for(j = 1; j < LENGTH*(HIGH)+1; j ++){
			
            printf("%-3.1f  ",A[i][j]);
            
			
		}
		printf("\n");
	}
}

void OutputMatrixToTxt(){
    
    int i, j;
    
    FILE* pf;        
	freopen("MatrixOfMMC.txt","w",stdout); 	  
	printf("The Matrix is:\n");
	for( i = 1; i < LENGTH*HIGH+1; i ++){
		for(j = 1; j < LENGTH*HIGH+1; j ++){
			
            printf("%-3.1f  ",A[i][j]);
            
			
		}
		printf("\n");
	}
    
	fclose(stdout);
}

void CopyMatrix(){
    int i,j;
    for (i=1; i<=HIGH*LENGTH; i++) {
        for (j=1; j<=HIGH*LENGTH; j++) {
            a[i-1][j-1] = A[i][j];
        }
    }
    for (int i = 0; i<size+1; i++) {
        a[size-1][i] = 1;
    }
    
    
}

void PrintMatrix1(){
    int i, j;
    printf("\n*****The Matrix is:*****\n");
	for( i = 0; i < size; i ++){
		for(j = 0; j < size; j ++){
			
            printf("%-3.1f  ",a[i][j]);
            
			
		}
		printf("\n");
	}
}
void DoolittleDivide()
{
    
    double temp=0.0;
    for(int i = 0; i < size; i++)
    {
        int t = i;
        while( a[t][i]*a[t][i] <= 0.000001 && t < size-1 )
			t++;
        
		if( t == size ){
            printf("not the only answer!!!!\n");
            exit(-1);
        }
		
        if(t != i )
            for(int j = 0; j < size + 1; j++){
                temp = a[i][j];
                a[i][j] = a[t][j];
                a[t][j] = temp;
            }
        /*
         This prat we do the first line like: A1j = U1j;Ai1 = Li1*U11 
         Swap the value of a[i][j] and a[t][j]
         */
        for(int j=i+1; j < size; j++)
            a[j][i] = a[j][i]/a[i][i];
         
        for(int j = i+1; j < size; j++)
            for(int k = i+1; k < size; k++)
                a[j][k] -= a[j][i] * a[i][k];       
        /*
         The new matrix has been created and stored into the original places.
         The L and U parts have been done.
         A = L * U;
         */
	}
}

void PrintResult()
{
	printf("**********************************************\n");
	printf("***************SHOW THE RESULT****************\n");
    //double ep=0.0; 
    for(int i = 0; i < size; i++)//￥ú”°Ω·π? 
    {
        printf("result(%d) = %.3f\t",i,y[i]);    
        //printf("X(%d) = %.6f\n",i,x[i]);
        //ep += (result[i] - x[i]) * (result[i] - x[i]);
    }
	printf("***************TIME COST HERE*****************");
    //printf("\nTIME COST : %d\n",finish - start); 
    printf("**************END OF THIS TEXT****************\n");
    //std::cout << sqrt(ep);
}

void CalculateResult()
{
    double SUM=0.0;
	//y[size-1] =1;
    /*
     The following part is calculating Ly = b to get the value of y
     */
    for(int i = 0; i < size; i++){ 
        SUM = 0.0;
        for(int j = 0; j < i; j++)
            SUM += y[j] * a[i][j];
            printf("%d\n",SUM); 
        y[i] = a[i][size] - SUM; 
        printf("y[%d] = %d\n",i,y[i]);
    }
	/*
     We have got the value of y in the last part;
     So now can easily got x for each i depends on Ux = y;
     */
    for(int i = size-1; i >= 0; i--){
        SUM = 0.0;
        for(int j = size-1; j > i; j--)
            SUM += x[j] * a[i][j];
        x[i] = (y[i] - SUM) / a[i][i]; 
        printf("x[%d] = %.6f\n",i,x[i]); 
    }

}

void OutputResult(){
    
    double sumofunder = 0;
    double sumofover = 0;
    double averageofn = 0;
    double averageofm = 0; 
    
    double p[HIGH+1][LENGTH+1] = {0};
    
    int d0 = 0;					//供给不足数组下标 
    int d1 = 0;					//攻击过度数组下表 
    int data_x[1][400]= {0};	//记录供给不足状态的横坐标 
    int data_y[1][400]= {0};	//记录供给不足状态的纵坐标 
    
    printf("\n#######\n");
    
    for (int i = HIGH; i >0; i--) {
        for (int j =0; j< LENGTH; j++) {
            p[i][j] = x[(i-1)*LENGTH+j];
            //printf("%.6f ", p[i][j]);
        }
        printf("\n");
    }
    
    for (int i =1; i <HIGH+1; i++) {
        for (int j=0; j<LENGTH; j++) {
            //供给不足 
            if (j > 3*i) {
            	data_x[0][d0] = i;
            	data_y[0][d0] = j;
            	d0++;
            	//printf("%d ",i);
                sumofunder += p[i][j];
                printf("++%.6f, i = %d, j = %d\n", p[i][j],i,j);
            }
            //供给过度 
            if (j<=i && i>1 ) {
            	d1++;
            	data_x[1][d1] = i;
            	data_y[1][d1] = j;
                sumofover += p[i][j];
                //printf("i = %d, j = %d d1 = %d\n",i,j,data_y[1][d1]);
                printf("--%.6f, i = %d, j = %d\n", p[i][j],i,j);
            }
            if (j>0) {
                averageofn += j*p[i][j];
            }
            
            averageofm += i*p[i][j];
            
        }
    }
    
    printf("\n");
    /* 
    for (int i =0; i <400; i++){
    	printf("%d ", data_x[1][i]);
	}
	printf("\n");
	for (int j =0; j <150; j++){
    	printf("%d ", data_y[1][j]);
	}*/
	
	
    printf("SUM OF UNDER =%.6f, SUM OF OVER =%.6f, SUM OF NORMAL =%.6f\n", sumofunder, sumofover, 1-sumofover-sumofunder);
    printf("\n");
    printf("AVERAGE NUMBER OF REQUESTS = %.6f, AVERAGE NUMBER OF RUNNING VMS = %.6f", averageofn, averageofm);
}

int main()
{
    //show the beginning information of the varalbes and 显示开始信息 
	BeginningPrintInformation();
    
	Judge();

    ShapeTopandDownandFourCornerEdge();

    CopyMatrix();
    //OutputMatrixToTxt();

    //PrintMatrix1();

    DoolittleDivide();
    CalculateResult();
    //PrintResult();
    OutputResult();
    
    printf("\n------END------\n\n");
    
    system("pause");
}

