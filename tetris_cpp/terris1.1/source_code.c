/*tips:1.pay attention to ������lock & unlock ���߼�  
**Task:1.Thread operation��3.shape�Ѿ�����ײ������ж�ʱ����ƶ��� 2.������Ϸ���û��˳�����Ϸʧ�ܣ��󷵻���Ϣ����
**GUI design:  
*/
/************************************************************�0�2 
�0�2 FileName: tetris-thread_modify.c
�0�2 Author:�0�2Gary Gao�0�2�0�2�0�2�0�2�0�2�0�2 Version :1.1�0�2�0�2�0�2�0�2�0�2�0�2�0�2�0�2�0�2 Date:2010/2/14
�0�2 Description:�0�2�0�2�0�2Ubuntu�汾�Ķ���˹����0�2�0�2 
  History:2009.11.04 ������������(version:1.0)
	  2009.11.10 ������̣߳�ʵ��Block�Զ��ƶ�(version:1.1)�0�2�0�2 
***********************************************************/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  
#include <curses.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


#define SHAPE_ROW 4
#define SHAPE_COLUMN 4
#define ATTR 2     //ATTR1:�洢��ǰ��λ�õ���ʾ�ַ�  ATTR2:�жϴ�λ���Ƿ�Ϊ���̶����ĵ�Ԫ
#define ATTR1	0	
#define ATTR2   1

#define ROW 20
#define COLUMN 14

#define TRUE 1
#define FALSE 0

typedef int TYPE;
typedef int BOOL;
typedef int POSITION;
typedef int DIRECTION;
typedef int SCORE;

typedef struct ShapeType{
	char mode;                  			//ģʽ�ַ�
	char shape[SHAPE_ROW][SHAPE_COLUMN];		//Shape for all ,square 
	int x,y;  		    			//����
	int type ;                		 	 //type �ܹ���7��
}ShapeType,*pType;

typedef struct
{
	char name[15];
	long score;	
	char grade[2];            //HIGHIEST A+,A,B+,B,C+,C,D+,D,E+,E LOWEST
}User,*pUser;

void initfun();
void Display(pUser user);
pUser initUser();
pType initShape(TYPE type,char mode,pType instance);
BOOL DrawShape(pType instance,POSITION x,POSITION y);
TYPE DestroyShape(pType instance);
int randType(int num);
//�ƶ�����
void *keypressed(void *arg);
void Move(pType instance,const int keyvalue);
void MoveDown(pType instance);
void MoveLeft(pType instance);
void MoveRight(pType instance);
void turn_90_Degree(pType instance);
void line_down(POSITION Frmline,POSITION Toline);
int check_and_remove(pType instance);
BOOL isAbleToDrawSh(POSITION ToX,POSITION ToY,pType instance,DIRECTION dre);
BOOL isAtBoundary(pType instance,DIRECTION dre);
void to_fix_Shape(pType instance);
void gainScore(pUser user,int gainscore);


//#define DEBUG         			 //define for debug
//������Ϸ����
char space[ROW][COLUMN][ATTR];
ShapeType instance,next_instance;
pUser user;
pthread_t auto_thread;
pthread_mutex_t mutex;        //Protect variable of main thread or auto_thread.
int keyval = 1;	
BOOL new_shape = FALSE; 			//flag to check if it is needed to draw new shape

int main()
{	
	int res;                          //����߳��Ƿ������ı�־
	
	BOOL GameFlg = TRUE ;            //��¼�Ƿ������Ϸ	
	int radm,gainscore;		//radm:random number
	char ch_mode[] = "GARYTBX";           //���ģʽ�ַ�			  		   
	
	initfun();	                      //��ʼ��
	pthread_mutex_lock(&mutex);	      //lock
	radm = time(NULL);
	initShape(randType(radm),ch_mode[randType(radm*radm)-1],&next_instance); 
	while(GameFlg != FALSE && keyval != 'q'){
		instance = next_instance;
		if(isAbleToDrawSh(0,COLUMN/2-2,&instance,0) == TRUE){								
			DrawShape(&instance,0,COLUMN/2-2);
			pthread_mutex_unlock(&mutex);		//unlock	
		}
		else
			GameFlg = FALSE;	                //׼���˳���Ϸ
		radm = time(NULL);           //��ȡʱ�䣬��Ϊ�����������seed		
		initShape(randType(radm+radm),ch_mode[randType(radm*radm+radm)-1],&next_instance);
		new_shape = FALSE;				//����״�Ѿ�������������ΪFALSE		
		Display(user);										
		while( GameFlg != FALSE && new_shape != TRUE && keyval != 'q'){			
			pthread_mutex_lock(&mutex);										
			//Check whether instance->shape can move down 
			//if not ,call to_fix_Shape(pType instance)						
			if(isAbleToDrawSh(instance.x+1,instance.y,&instance,KEY_DOWN) == FALSE){
				//Block�ײ����Ѿ����ĵ�Ԫ�Ӵ�������1s�������ƶ�ʱ��
				pthread_mutex_unlock(&mutex);
				usleep(800000);//sleep:0.8s
				pthread_mutex_lock(&mutex);

				if(isAbleToDrawSh(instance.x+1,instance.y,&instance,KEY_DOWN) == FALSE){
					to_fix_Shape(&instance);
					// check if can gain score				
					if((gainscore = check_and_remove(&instance)) > 0)
						gainScore(user,gainscore);
					new_shape = TRUE;			//��Ҫ����״				
					Display(user);	
					break;	
				}					
			}				
			//ÿ��1�����Զ�����һ��									
			pthread_mutex_unlock(&mutex);                    //unlock
			usleep(800000);//sleep:0.8s
			pthread_mutex_lock(&mutex);			//lock
			MoveDown(&instance);			
			Display(user);					
			pthread_mutex_unlock(&mutex);                    //unlock
					
		}					
	}
	//finish last work	
	res = pthread_cancel(auto_thread);          
	if(res != 0){
		perror("Thread cancel failed");
		getch();
		endwin();
		exit(EXIT_FAILURE);
	}	
	pthread_mutex_destroy(&mutex);			          
	endwin();                              //finish curses library and go back to normal state	
	//Game over,print user information.
	printf("\n\n            Game Over.\n");
	printf("         Player name: %s   \n",user->name);
	printf("         Score:       %ld,    Grade:%c%c\n\n",user->score,user->grade[0],user->grade[1]);
		
	exit(EXIT_SUCCESS);
}

void *keypressed(void *arg)
{
	int res;
	//set thread can be cancelled
	res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);       
	if(res != 0){
		perror("Thread pthread_setcancelstate failed");
		getch();
		endwin();
		exit(EXIT_FAILURE);
	}
	//set thread can be cancelled as long as it is required.
	res = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);   
	if(res != 0){
		perror("Thread pthread_setcanceltype failed");
		getch();
		endwin();
		exit(EXIT_FAILURE);
	}
	while(1){
		
		keyval = getch();   //   get   the   key   you   input   		
		pthread_mutex_lock(&mutex);			//lock
		Move(&instance,keyval);		
		Display(user);						
		pthread_mutex_unlock(&mutex);			//unlock	
	}
	pthread_exit(NULL);
}


void initfun(){
	int i,j,res;
	
	user = initUser();     
	if(user == NULL)
		printf("Error:Player has not been initialized!");
	
	initscr();
	noecho();
	//intrflush(stdscr,FALSE);        //3��ע�͵��ĺ���δ������ʲôӰ��
	keypad(stdscr,TRUE);	
	refresh(); 
	
	for(i = 0 ;i < ROW;i++){
		for(j = 0 ; j < COLUMN;j++){
			space[i][j][ATTR1] = ' ';     //white space;
			space[i][j][ATTR2] = 'N';     //��Ԫ��̶�����־λ N:unfixed Y:fixed		
		}
	}
	res = pthread_mutex_init(&mutex,NULL);	
	if(res != 0){
		perror("Thread mutex initialization failed");
		getch();
		endwin();
		exit(EXIT_FAILURE);
	}	
	res = pthread_create(&auto_thread,NULL,keypressed,(void *)NULL);
	if(res != 0){
		perror("Thread creation failed");
	  	getch();
		endwin();
		exit(EXIT_FAILURE);
	}				
}

void Display(pUser user)
{
	//1.display space 2.information of the player.                                      
	int i,j;
	POSITION x_base = 2,y_base = 2;
	time_t tim = time(NULL);
	clear();
	box(stdscr,'|','-'); 
	mvprintw(1,2,"%s","Made by Gary Gao  ");
	mvprintw(1,24,"%s",ctime(&tim));				
	mvprintw(x_base,y_base,"%s","******************************************************************");	
	move(x_base,y_base);
	for(i = 0;i<ROW;i++){
		for(j = 0 ;j <COLUMN;j++){				
			//printf(" %c ",space[i][j][ATTR1]);
			mvprintw(x_base+i+1,y_base+1+(j-1)*2,"%c",space[i][j][ATTR1]); 
		}		
	}
	for(i = 0 ; i < ROW;i++){
		mvprintw(x_base+i+1,y_base+1+(COLUMN-2)*2+1,"%c",'|');
	}
	// display of next instance.shape.
	mvprintw(x_base+1,y_base+COLUMN*2+10,"%s","~~~~~~~~~~~~~~");	
	for(i = 0; i <SHAPE_ROW;i++){
		for(j = 0 ;j< SHAPE_COLUMN; j++)
			mvprintw(x_base+3+i,y_base+COLUMN*2+14+(j-1)*3,"%c",next_instance.shape[i][j]);	
	}	
	mvprintw(x_base+7,y_base+COLUMN*2+10,"%s","~~~~~~~~~~~~~~");	
	//User information
	mvprintw(x_base+9,y_base+COLUMN*2+10,"%s","******************");
	mvprintw(x_base+10,y_base+COLUMN*2+10,"NAME:  %s",user->name);
	mvprintw(x_base+11,y_base+COLUMN*2+10,"SCORE: %ld",user->score);
	mvprintw(x_base+12,y_base+COLUMN*2+10,"GRADE: %s",user->grade);
	mvprintw(x_base+13,y_base+COLUMN*2+10,"%s","******************");
	//Prompt
	mvprintw(x_base+15,y_base+COLUMN*2+10,"%s","******************");
	mvprintw(x_base+16,y_base+COLUMN*2+10,"%s","KEYBOARD:");
	mvprintw(x_base+18,y_base+COLUMN*2+10,"%s","q : QUIT");
	mvprintw(x_base+19,y_base+COLUMN*2+10,"%s","UP DOWN LEFT RIGHT");	
	mvprintw(x_base+20,y_base+COLUMN*2+10,"%s","******************");			
	refresh();
}
	
pUser initUser()
{	
	pUser user;
	user = (pUser) malloc(sizeof(User));
	user->score = 0;
	user->grade[0] = 'E';
	user->grade[1] = ' ';	
	
	strcpy(user->name,"");
	while(strlen(user->name) <= 2){
		printf("\nPlease enter your name(NOT A LETTER!):");
		fgets(user->name,15,stdin);    
	}        
	return user;	
}


pType initShape(TYPE type,char mode,pType instance)
{
	//������״,��ʼ��������״SHAPE_ROW��SHAPE_COLUMN����
	int i,j;
	for(i = 0 ;i< SHAPE_ROW;i++){
		for(j = 0;j<SHAPE_COLUMN;j++)
			instance->shape[i][j] = ' ';
			
	}
	instance->type = type;
	instance->mode = mode;
	#ifdef DEBUG
	mvprintw(1,30,"TYPE:%d MODE:%c  instance->mode:%c",type,mode,instance->mode);
	refresh();
	getch();		
	#endif
	
	switch(type){			
		case 1:
		     	 {
				for(i = 0 ;i < 4;i++ ){
					instance->shape[i][1] = mode;
				}
				break;
		       	 }		
		case 2:{ 	// S shape 1
				instance->shape[2][0] = mode;
				instance->shape[1][1] = mode;
				instance->shape[2][1] = mode;
				instance->shape[1][2] = mode;		
				break;
			}
		case 3: {       //S shape 2
				instance->shape[1][0] = mode;
				instance->shape[1][1] = mode;
				instance->shape[2][1] = mode;
				instance->shape[2][2] = mode;						
				break;
			}
		case 4:{ 	//square
				for(i = 0 ;i < 2;i++){
					for(j = 0 ; j < 2;j++)
						instance->shape[i][j] = mode;	
				}
				break;
			}
		case 5:{	// T shape
				instance->shape[1][0] = mode;
				instance->shape[0][1] = mode;
				instance->shape[1][1] = mode;
				instance->shape[1][2] = mode;		
				break;
			}
		case 6: {
				instance->shape[0][1] = mode;
				instance->shape[1][1] = mode;
				instance->shape[2][1] = mode;
				instance->shape[0][2] = mode;		
				break;
			}
		case 7: {
				instance->shape[0][0] = mode;
				instance->shape[0][1] = mode;
				instance->shape[1][1] = mode;
				instance->shape[2][1] = mode;		
				break;
			}
		default: printf("\nError! in initialize Shape!\n");
	}
	
	
	#ifdef DEBUG	
	for(i = 0 ;i < SHAPE_ROW;i++){
		for(j = 0;j < SHAPE_COLUMN;j++){			
			mvprintw(i+10,(j-1)*2+10," %c ",instance->shape[i][j]);
		}			
	}	
	refresh();
	getch();
	#endif	
}

BOOL DrawShape(pType instance,POSITION x,POSITION y)
{	
	//�ƶ���״��λ�þ��൱�����µ�λ���ػ�����״
	//Ҫ��x,y�����ػ���	
	BOOL flag = TRUE;		
	instance->x = x;    // ������������
	instance->y = y;   
	
	#ifdef DEBUG
	mvprintw(12,40,"In DrawShape():X:%d,Y:%d",instance->x,instance->y);
	refresh();
	getch();
	#endif
	int i,j;
	
	for(i = 0 ;i <SHAPE_ROW;i++){
		for(j = 0 ;j < SHAPE_COLUMN ; j++){
			if(instance->shape[i][j] == instance->mode){				
				space[x+i][y+j][ATTR1] = instance->mode;	
			}		
		}
	}
	#ifdef DEBUG
	refresh();
	getch();	
	#endif	
	return flag;
}

TYPE DestroyShape(pType instance)
{
	int i,j;
	POSITION xp,yp;
	xp = instance->x;
	yp = instance->y;

	for(i = 0;i < SHAPE_ROW;i++){
		for(j = 0;j < SHAPE_COLUMN; j++){
			if(space[xp+i][yp+j][ATTR1] == instance->shape[i][j])
				space[xp+i][yp+j][ATTR1] = ' ';			
		}	
	}	
	return instance->type;
}

int randType(int num)
{	//����1��7֮��������
	int radm;
	int rn;
	srand((unsigned)num);
	rn = rand();
	radm = rn%7 + 1;
	return radm;	
}

void Move(pType instance,const int keyvalue)
{
	switch(keyvalue){	
		case KEY_UP     : turn_90_Degree(instance);     break;		
		case KEY_DOWN 	: MoveDown(instance);		break;
		case KEY_LEFT	: MoveLeft(instance);		break;
		case KEY_RIGHT	: MoveRight(instance);		break;
		default:break;	
	}	
}


void MoveDown(pType instance)
{	
	POSITION x,y;
	x = instance->x;
	y = instance->y;
	
	if(isAbleToDrawSh(x+1,y,instance,KEY_DOWN) == TRUE){    //check condition				
		DestroyShape(instance);
		DrawShape(instance,x+1,y);
	}
	
}

void MoveLeft(pType instance)
{	
	POSITION x,y;
	x = instance->x;
	y = instance->y;
	
	if(isAbleToDrawSh(x,y-1,instance,KEY_LEFT) == TRUE){    //check condition		
		DestroyShape(instance);
		DrawShape(instance,x,y-1);	
	}
	
}

void MoveRight(pType instance)
{	
	POSITION x,y;
	x = instance->x;
	y = instance->y;	
	if(isAbleToDrawSh(x,y+1,instance,KEY_RIGHT) == TRUE){	  //check condition		
		DestroyShape(instance);
		DrawShape(instance,x,y+1);	
	}	
}


void turn_90_Degree(pType instance)
{
	//��״��ת������tips:1.�ж��Ƿ��ܹ���ת(�߽����ײ) 2.��ת������,Χ��������ת  3.check boundary
	BOOL isAbleToRotate = TRUE;
	BOOL left_bound,right_bound,bottom_bound;   		
	POSITION xp,yp;	
	int i,j;
	//�м��������飬���������תʱ���м�ֵ	
	char tmp[SHAPE_ROW][SHAPE_COLUMN] = 
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};	//16		
	
	xp = instance->x;
	yp = instance->y;	
	switch(instance->type){
		case 1:{
				if(instance->shape[1][0] == instance->mode){    //TYPE 1.1
					//check if cannot rotate  						
					bottom_bound = (xp >= ROW-3);			
					if(bottom_bound)
						isAbleToRotate = FALSE; 
					//Rotate	
					tmp[0][1]=instance->mode;
					tmp[1][1]=instance->mode;
					tmp[2][1]=instance->mode;
					tmp[3][1]=instance->mode;					
				}else{						//TYPE 1.2
					left_bound  = (yp == -1);
					right_bound = (yp >= COLUMN-3);
					if(left_bound || right_bound)
						isAbleToRotate = FALSE;
					//Rotate
					tmp[1][0]=instance->mode;
					tmp[1][1]=instance->mode;
					tmp[1][2]=instance->mode;
					tmp[1][3]=instance->mode;
				}
				if(isAbleToRotate == TRUE){			//check if cannot rotate
					for(i = 0; i < 4; i++){
						for(j = 0;j <4 ; j++){
							if(space[xp + i][yp + j][ATTR2] =='Y' 
									&& tmp[i][j] == instance->mode){
								
								isAbleToRotate = FALSE;
								break;	
							}
						}
						if(isAbleToRotate == FALSE) break;
					}						
		
				}
				break;				
			}
		case 2:
		case 3:
		case 5:
		case 6:
		case 7:{	//��ʱ����ת,��2��1,2,3��Ϊ�м�Գ���,��Columnת��
				//        1 2 3
				//	1 x x x
				//      2 x x x
				//	3 x x x
				//				
				left_bound = (yp == -1);
				right_bound = (yp == COLUMN - 2);
				bottom_bound = (xp == ROW - 2);
				if(left_bound || right_bound || bottom_bound)	
					isAbleToRotate = FALSE;
				else if(!left_bound && !right_bound && !bottom_bound){
					//rotate to tmp[][]
					for(i = 1;i <= 3;i++){
						for(j = 1; j <= 3;j++){ 
							tmp[i-1][j-1] = instance->shape[j-1+(2-j)*2][i-1];
						}
					}						
					//check if cannot rotate
					for(i = 0; i < 3; i++){
						for(j = 0;j <3 ; j++){
							if(space[xp + i][yp + j][ATTR2] =='Y' 
									&& tmp[i][j] == instance->mode){
								
								isAbleToRotate = FALSE;
								break;	
							}
						}
						if(isAbleToRotate == FALSE) break;
					}									
				}
				break;				
			}
		case 4: isAbleToRotate == FALSE;   //square does not need rotate    
		default:break;
	}
	if(isAbleToRotate == TRUE){	
		DestroyShape(instance);             //Destroy the shape in space[x][y][0]
		for(i = 0;i < SHAPE_ROW;i++){
			for(j = 0;j < SHAPE_COLUMN; j++)
			instance->shape[i][j] = tmp[i][j];
		}
		DrawShape(instance,xp,yp);	 //draw the shape
	}

	#ifdef DEBUG
	for(i = 0 ; i < SHAPE_ROW ; i++){
		for(j = 0 ; j < SHAPE_COLUMN; j++)
			mvprintw(i+10,(j-1)*2+20,"%c",instance->shape[i][j]);
	}
	mvprintw(1,60,"Type:%d",instance->type);
	refresh();
	getchar();
	#endif
	
}

void line_down(POSITION FrmLine,POSITION ToLine) 
{
	//Premise:Toline��Ϊ��,Action��ʹFrmline�����Ƶ�Toline��	
	int i,j;
	int height = ToLine - FrmLine;	// > 0
	//POSITION top_filled_line = FrmLine;    //��space�б��̶�����������һ��
	//int height = 1;
	POSITION top_filled_line = 0;
	for(i = FrmLine; i >= top_filled_line;i--){	
		for(j = 0 ; j < COLUMN; j++){
			space[i+height][j][ATTR2] = space[i][j][ATTR2];	
			//���ƶ��Ѿ��̶����ĵ�Ԫ
			if( !(space[i][j][ATTR1] != ' ' && space[i][j][ATTR2] == 'N'))
				space[i+height][j][ATTR1] = space[i][j][ATTR1];						
		}
	}	
	//�������distance��������մ���
	for(i = top_filled_line ;i <= top_filled_line+height-1;i++){
		for(j = 0;j < COLUMN;j++){
			//�����û��instance->shape�ĵ�Ԫ
			if(!(space[i][j][ATTR1] != ' ' && space[i][j][ATTR2] == 'N')){
				space[i][j][ATTR2] == 'N';
				space[i][j][ATTR1] == ' ';
			}
		}
	}		
}

int check_and_remove(pType instance)
{
	int i,j;
	BOOL flag[SHAPE_ROW];                      //remove flag(TRUE:can be removed)
	int num_of_remove = 0;
	
	for(i = 0; i < SHAPE_ROW;i++){
		flag[i] = TRUE;
		//check to see if this line can be removed.
		for(j = 0; j < COLUMN ;j++){
			if(space[instance->x+i][j][ATTR2] != 'Y')
				flag[i] = FALSE;
		}		
	}			
	for(i = 0 ;i < SHAPE_ROW;i++){
		if(flag[i] == TRUE){
			//line_down(POSITION Frmline,POSITION Toline)
			line_down(instance->x+i-1,instance->x+i);      // remove successfully!
			num_of_remove++;
		}
	}	
	return num_of_remove;    
} 	

/*
**Collision logic
*/

BOOL isAbleToDrawSh(POSITION ToX,POSITION ToY,pType instance,DIRECTION dre)
{
	
	//����dre�������»���shape������
	//1.��״�ı߽�û�нӴ����߿�                  
	//2.instance->shape ��Ҫ���Ƶĵ�Ԫ��δ���̶����
		
	//POSITION xp,yp;
	//xp = instance->x;
	//yp = instance->y;	
	int i,j;	
	//CHECK BOUNDARY
	if( isAtBoundary(instance,dre) == TRUE)
		return FALSE;
	for(i = 0;i < SHAPE_ROW;i++){
		for(j = 0 ;j< SHAPE_COLUMN;j++){
			if(instance->shape[i][j] == instance->mode && space[ToX+i][ToY+j][ATTR2] == 'Y')
				return FALSE;
		}
	}
	return TRUE;   //������� 1.�ж��ܷ��ƶ��ĺ��� 2.��Ϸ������־
}


BOOL isAtBoundary(pType instance,DIRECTION dre)
{	
	int i;
	BOOL flag = FALSE;
	POSITION xp,yp;
	xp = instance->x;
	yp = instance->y;
	switch(dre){
		case 0: flag = FALSE;break;
		case KEY_LEFT:{	//Check space's left boundary
				if(yp == -1){
					flag = TRUE;
					break;
				}
				else if(yp == 0){
					//Check instance->shape's left boundary
					for(i = 0 ;i < SHAPE_ROW;i++){  
						if(instance->shape[i][0] == instance->mode){
							flag = TRUE;	
							break;
						}
					}
				}											
				break;
		}
		case KEY_RIGHT:{	//Check space's right boundary
				if(yp == COLUMN-2){             
					flag = TRUE;
					break;
				}
				else if(yp == COLUMN-4){	//Check instance->shape[SHAPE_COLUMN-1] 									
					for(i = 0;i <SHAPE_ROW;i++){					
						if(instance->shape[i][SHAPE_COLUMN-1] == instance->mode){
							flag = TRUE;	
							break;	
						}
					}					
				}
				else if(yp == COLUMN-3){       //Check instance->shape[SHAPE_COLUMN-2]
					for(i = 0;i <SHAPE_ROW;i++){					
						if(instance->shape[i][SHAPE_COLUMN-2] == instance->mode){
							flag = TRUE;	
							break;
						}
					}						
				}
				break;
	        }
		case KEY_DOWN:{
				if(xp == ROW-2){
					flag = TRUE;
					break;
				}
				else if(xp == ROW-3){					
					for(i = 0 ;i < SHAPE_COLUMN; i++){
						if(instance->shape[SHAPE_ROW-2][i] == instance->mode){
							flag = TRUE;
							break;
						}
					}				
				}		
				else if(xp == ROW-4){
					for(i = 0;i < SHAPE_COLUMN; i++)
						if(instance->shape[SHAPE_ROW-1][i] == instance->mode){
							flag = TRUE;
							break;
						}
				}							
				break;
		}
		default :break;
	}
	return flag;
}


void to_fix_Shape(pType instance)
{
	//instance->shape ��ʱ�Ѿ����ɼ������䡣	
	//��instance->shape���óɹ̶�״̬����׼��������һ��ʵ����	
	int i,j;
	POSITION xp,yp;
	xp = instance->x;
	yp = instance->y;

	for(i = 0; i < SHAPE_ROW; i++){
		for(j = 0;j< SHAPE_COLUMN;j++){
			if(instance->shape[i][j] == instance->mode){
				//check fix position (x,y)
				space[xp+i][yp+j][ATTR2] = 'Y';	
			}			
		}
	}
	//�������Ѿ��̶���ʵ��instance����Ϣ
	instance->type = -1;
	instance->mode = '?';		
}



void gainScore(pUser user,int gainscore)
{
	//����ͳ�ƺ���
	//ÿ����һ�м�2�֣����м�10�֣����м�40�֣����м�120�֡�
	int point;
	switch( gainscore ){
		case 1:point = 2;break;
		case 2:point = 10;break;
		case 3:point = 40;break;
		case 4:point = 120;break;
	}
	user->score += point;
	long score = user->score;	
	// GRADE:E 10 E+ 20 D 40 D+ 80 C 160 C+ 320 B 640 B+ 1280 A 2560 A+ 5120		
	if(score >= 10 && score < 20){		//E+
		user->grade[1] = '+';
	}	
	else if(score >= 20 && score < 40){		//D
		user->grade[0] = 'D';
		user->grade[1] = ' ';
	}	
	else if(score >= 40 && score < 80){		//D+
		user->grade[0] = 'D';
		user->grade[1] = '+';
	}	
	else if(score >= 80 && score < 160){		//C
		user->grade[0] = 'C';
		user->grade[1] = ' ';
	}	
	else if(score >= 160 && score < 320){	//C+
		user->grade[0] = 'C';
		user->grade[1] = '+';
	}
	else if(score >= 320 && score < 640){	//B
		user->grade[0] = 'B';
		user->grade[1] = ' ';
	}
	else if(score >= 640 && score < 1280){	//B+
		user->grade[0] = 'B';
		user->grade[1] = '+';	
	}
	else if(score >= 1280 && score < 2560){	//A
		user->grade[0] = 'A';
		user->grade[1] = ' ';			
	}
	else if(score >= 2560 && score < 5120){	//A+
		user->grade[0] = 'A';
		user->grade[1] = '+';		
	}
}