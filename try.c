#include <stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1 // controll appearance of engine temp
typedef enum{  //define ON & OFF
	OFF,
	ON
}bool;
typedef struct{  //struct of 6 variables of engine
	bool engine_state;
	bool AC_state;
	bool temp_controller_state;
	int speed;
	int room_temp;
	int engine_temp;
}ENG;

void (*ptr_state)(ENG *)= NULL; // pointer to 2 functions main_menu and sensors_set_menu according to engine state

void print_state(ENG *); // function print 6 variables of engine take pointer to ENG structure
void main_menu(ENG *);   // display 3 choose turn on/off - quit and take action take pointer to ENG structure
void Sensors_set_menu(ENG *);  // display 4 choose turn off-color-room/engine temp - state take pointer to ENG structure

void start(ENG *ptr){  //set pointer to funcion to point to the correct function based on engine state and call the function
	ptr_state = ptr->engine_state? Sensors_set_menu: main_menu;
	(*ptr_state)(ptr);
}
int main(){  //create structure
	ENG engine={OFF,OFF,OFF,0,0,0};
	start(&engine);
	return 0;
}
void main_menu(ENG *engine){  //change value of engine state based on choose of user to turn on / off
	char input;
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	fflush(stdout);
	scanf(" %c",&input);
	switch(input){
		case 'a':
		case 'A':
		    printf("Turn on the vehicle engine\n\n");
		    engine->engine_state = ON;
		    start(engine);
		    break;
		case 'b':
		case 'B':
		    printf("Turn off the vehicle engine\n\n");
		    engine->engine_state = OFF;
		    start(engine);
		    break;
		case 'c':
		case 'C':
		    printf("Quit the system\n");
		    break;
		default:
			printf("this input is not allowed\n");
			start(engine);
	}
}

void Sensors_set_menu(ENG *engine){ //change parameters of engine structure based on values entered from user
	char input;
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
	#if WITH_ENGINE_TEMP_CONTROLLER
		printf("d. Set the engine temperature\n");
	#endif
	fflush(stdout);
	scanf(" %c",&input);
	switch(input){
		case 'a':
		case 'A':
			printf("Turn off the vehicle engine\n\n");
			engine->engine_state = OFF;
			start(engine);  // change pointer to function value and display new display
			break;
		case 'b':
		case 'B':
			char color;
			printf("enter required color: ");
			fflush(stdout);
			scanf(" %c",&color);
			switch(color){
				case 'G':
				case 'g':
					engine->speed = 100;
					break;
				case 'O':
				case 'o':
					engine->speed = 30;
					break;
				case 'R':
				case 'r':
					engine->speed = 0;
					break;
			}
			print_state(engine);
			start(engine);
			break;
		case 'c':
		case 'C':
			int t;
			printf("enter the room temperature: ");
			fflush(stdout);
			scanf("%d",&t);
			if(t<10 || t>30){
				engine->AC_state = ON;
				engine->room_temp = 20;
			}
			else engine->AC_state = OFF;
			print_state(engine);
			start(engine);
			break;
	#if WITH_ENGINE_TEMP_CONTROLLER
		case 'd':
		case 'D':
			int e_t;
			printf("enter engine temperature: ");
			fflush(stdout);
			scanf("%d",&e_t);
			if(e_t<100 || e_t>150){
				engine->engine_temp = 125;
				engine->temp_controller_state = ON;
			}else engine->temp_controller_state = OFF;
			print_state(engine);
			start(engine);
			break;
	#endif
		default:
			printf("this input is not allowed\n");
			start(engine);
	}
}
void print_state(ENG *engine){

	if(engine->speed==30){
		engine->AC_state = ON;
		engine->room_temp = ((float)5/4)*(engine->room_temp) + 1;
#if WITH_ENGINE_TEMP_CONTROLLER
		engine->temp_controller_state = ON;
		engine->engine_temp = ((float)5/4)*(engine->engine_temp) + 1;
#endif
	}
	printf("%s",engine->engine_state?"Engine is ON\n":"Engine is OFF\n");
	printf("%s",engine->AC_state?"AC is ON\n":"AC is OFF\n");
	printf("vehicle speed: %d Km/Hr\n",engine->speed);
	printf("Room Temperature: %d c\n",engine->room_temp);
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("%s",engine->temp_controller_state?"Engine Temperature Controller State is ON\n":"Engine Temperature Controller State is OFF\n");
	printf("Engine Temperature: %d c\n",engine->engine_temp);
#endif
	puts("\n");
}

