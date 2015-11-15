#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct activity{
	char type[20];
	char name[20];
	int startYear;
	int startMonth;
	int startDay;
	int startHour;
	int dueYear;
	int dueMonth;
	int dueDay;
	int dueHour;
	int duration;
	int priority;
	int handled;
	int startTimeValue;
	int dueTimeValue;
	int waittime;
	int turntime;
}Event;

int monthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int periodStartYear, periodStartMonth, periodStartDay, periodStartHour, periodStartMinute;			
int periodEndYear, periodEndMonth, periodEndDay, periodEndHour, periodEndMinute;
void SJF(Event *event,int eventCounter,int duryear, int timetable[duryear][12][31][24]){
//printf("sjf\n");
	int i,j,k,l,m,timetablevalue,tmptime;
	int shortestEvent = -1;
	int handling = -1; // nothing handling
	for(i=0;i<duryear;i++){
		for(j=0;j<12;j++){
			for(k=0;k<31;k++){
				for(l=0;l<24;l++){
					shortestEvent = -1;
					tmptime = i*1000000+(j+1)*10000+(k+1)*100+l+1;	
					if(timetable[i][j][k][l] != -1)//valid day?
						continue;
					if(handling == -1){// nothing handling, find something to do
						// find one available activity
						for(m=0;m<eventCounter;m++){
							if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0)
								continue;
							if(event[m].startTimeValue < tmptime && event[m].handled<event[m].duration){
							//start before this date and not finished
								shortestEvent = m;
								break;
							}
						}
						if(shortestEvent == -1)//have nothing to do
							continue;	// go to next hour

						for(m=0;m<eventCounter;m++){// find the earliest coming event	
							if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0)
								continue;		
							if(event[m].startTimeValue<tmptime && event[m].handled<event[m].duration && event[m].duration<event[shortestEvent].duration)
								shortestEvent = m;
						}
						handling = shortestEvent;
						timetable[i][j][k][l] = handling;
						event[handling].handled++;
	 					if(event[handling].handled == event[handling].duration)
							handling = -1;
					}	
					else{//something handling, continue
						timetable[i][j][k][l] = handling;
						event[handling].handled++;
						if(event[handling].handled == event[handling].duration)
							handling = -1;
					}
				}							
			}
		}
	}
}
void SRT(Event *event,int eventCounter,int duryear, int timetable[duryear][12][31][24]){
//printf("srt\n");
	int i,j,k,l,m,timetablevalue,tmptime;
	int shortestEvent = -1;
	int handling = -1; // nothing handling
	for(i=0;i<duryear;i++){
		for(j=0;j<12;j++){
			for(k=0;k<31;k++){
				for(l=0;l<24;l++){
					shortestEvent = -1;
					tmptime = i*1000000+(j+1)*10000+(k+1)*100+l+1;	
					if(timetable[i][j][k][l] != -1)//valid day?
						continue;
					if(handling == -1){// nothing handling, find something to do
						// find one available activity
						for(m=0;m<eventCounter;m++){
							if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0)
								continue;
							if(event[m].startTimeValue < tmptime && event[m].handled<event[m].duration){
							//start before this date and not finished
								shortestEvent = m;
								break;
							}
						}
						if(shortestEvent == -1)//have nothing to do
							continue;	// go to next hour

						for(m=0;m<eventCounter;m++){// find the earliest coming event	
							if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0)
								continue;		
							if(event[m].startTimeValue<tmptime && event[m].handled<event[m].duration && (event[m].duration-event[m].handled)<(event[shortestEvent].duration-event[shortestEvent].handled))
								shortestEvent = m;
						}
						handling = shortestEvent;
						timetable[i][j][k][l] = handling;
						event[handling].handled++;
	 					if(event[handling].handled == event[handling].duration)
							handling = -1;
					}	
					else{//something handling, continue
						timetable[i][j][k][l] = handling;
						event[handling].handled++;
						if(event[handling].handled == event[handling].duration)
							handling = -1;
					}
				}							
			}
		}
	}
}
void PRN(Event *event,int eventCounter,int duryear, int timetable[duryear][12][31][24]){
//printf("prn\n without preemption");
	int i,j,k,l,m,timetablevalue,tmptime;
	int highestEvent = -1;
	int handling = -1; // nothing handling
	for(i=0;i<duryear;i++){
		for(j=0;j<12;j++){
			for(k=0;k<31;k++){
				for(l=0;l<24;l++){
					highestEvent = -1;
					tmptime = i*1000000+(j+1)*10000+(k+1)*100+l+1;	
					if(timetable[i][j][k][l] != -1)//valid day?
						continue;
					if(handling == -1){// nothing handling, find something to do
						// find one available activity
						for(m=0;m<eventCounter;m++){
							if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0)
								continue;
							if(event[m].startTimeValue < tmptime && event[m].handled<event[m].duration){
							//start before this date and not finished
								highestEvent = m;
								break;
							}
						}
						if(highestEvent == -1)//have nothing to do
							continue;	// go to next hour

						for(m=0;m<eventCounter;m++){// find the earliest coming event	
							if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0)
								continue;		
							if(event[m].startTimeValue<tmptime && event[m].handled<event[m].duration && event[m].priority<event[highestEvent].priority)
								highestEvent = m;
						}
						handling = highestEvent;
						timetable[i][j][k][l] = handling;
						event[handling].handled++;
	 					if(event[handling].handled == event[handling].duration)
							handling = -1;
					}	
					else{//something handling, continue
						timetable[i][j][k][l] = handling;
						event[handling].handled++;
						if(event[handling].handled == event[handling].duration)
							handling = -1;
					}
				}							
			}
		}
	}
}
void PRP(Event *event,int eventCounter,int duryear, int timetable[duryear][12][31][24]){
//printf("prp\n");
	int i,j,k,l,m,timetablevalue,tmptime;
	int highestEvent = -1;
	for(i=0;i<duryear;i++){
		for(j=0;j<12;j++){
			for(k=0;k<31;k++){
				for(l=0;l<24;l++){
					highestEvent = -1;
					tmptime = i*1000000+(j+1)*10000+(k+1)*100+l+1;	
					if(timetable[i][j][k][l] != -1)//valid day?
						continue;
					// find one available activity
					for(m=0;m<eventCounter;m++){
						if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0)
							continue;
						if(event[m].startTimeValue < tmptime && event[m].handled<event[m].duration){
						//start before this date and not finished
							highestEvent = m;
							break;
						}
					}
					if(highestEvent == -1)//have nothing to do
						continue;	// go to next hour
					for(m=0;m<eventCounter;m++){// find the earliest coming event	
						if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0)
							continue;		
						if(event[m].startTimeValue<tmptime && event[m].handled<event[m].duration && event[m].priority<event[highestEvent].priority)
							highestEvent = m;
					}
					timetable[i][j][k][l] = highestEvent;
					event[highestEvent].handled++;	
				}							
			}
		}
	}	
}
void RRX(Event *event,int eventCounter,int duryear, int timetable[duryear][12][31][24], int qtm){
//printf("rrx %d\n",qtm);
	int eventQ[eventCounter];
	int Qcounter = 0;
	int Qpointer = 0;
	int tmpQp = 0;
	int eventcnt = 0;
	int i,j,k,l,m,timetablevalue,tmptime;
	for(i=0;i<eventCounter;i++)
		eventQ[i]=-1;
	for(i=0;i<duryear;i++){
		for(j=0;j<12;j++){
			for(k=0;k<31;k++){
				for(l=0;l<24;l++){
					tmptime = i*1000000+(j+1)*10000+(k+1)*100+l;
					for(m=0;m<eventCounter;m++){//what event start from today? add to Q
						if(event[m].startTimeValue == tmptime && strcmp(event[m].type,"Class")!=0 && strcmp(event[m].name,"Sleep")!=0){
							Qcounter++;
							for(tmpQp = Qcounter;tmpQp>Qpointer;tmpQp--){
								eventQ[tmpQp] = eventQ[tmpQp-1];
							}
							eventQ[Qpointer] = m;
							//printf("-----put %d in %d-------\n",m,Qpointer);
							Qpointer++;
						}//if
					}//for	
					if(eventQ[Qpointer]==-1){
						Qpointer++;
						if(Qpointer>Qcounter)
							Qpointer = 0;
					}
					
					//printf("%d-%d:%d %d \n",j,k,l,timetable[i][j][k][l]);
					if(timetable[i][j][k][l] != -1){//valid day(==-1)? do something 	
						continue;	
					}
					if(eventcnt == 0){//nothing is being handled! find something to do!
						tmpQp = Qpointer;
						while(1){
							
							if(eventQ[Qpointer] == -1)
								break;
							if(event[eventQ[Qpointer]].duration>event[eventQ[Qpointer]].handled){
								//if this event on Qpointer is ok, do it!
								timetable[i][j][k][l] = eventQ[Qpointer];
								event[eventQ[Qpointer]].handled++;
								eventcnt++;
								if(eventcnt == qtm||event[eventQ[Qpointer]].handled == event[eventQ[Qpointer]].duration){// finish this qtm, go away~
									Qpointer++;
									eventcnt = 0;
									if(Qpointer > Qcounter)
										Qpointer = 0;
								}
								break; 
							}
							Qpointer++;
							if(Qpointer > Qcounter)
								Qpointer = 0;
							if(Qpointer == tmpQp)//wraparound but not find something todo
								break;
						}//while	
					}//if
					else{//something not finish its qtm, continue to do it
						timetable[i][j][k][l] = eventQ[Qpointer];
						event[eventQ[Qpointer]].handled++;
						eventcnt++;
						if(eventcnt == qtm||event[eventQ[Qpointer]].handled == event[eventQ[Qpointer]].duration){
							Qpointer++;
							eventcnt = 0;
							if(Qpointer > Qcounter)
								Qpointer = 0;
						}//if
					}//else
				}//l							
			}//k
		}//j
	}//i
}//function

void FCFS(Event *event,int eventCounter,int duryear, int timetable[duryear][12][31][24]){
	int i,j,k,l,m,timetablevalue,tmptime;
	int earliestEvent = -1;
	int handling = -1; // nothing handling
	for(i=0;i<duryear;i++){
		for(j=0;j<12;j++){
			for(k=0;k<31;k++){
				for(l=0;l<24;l++){
					earliestEvent = -1;
					tmptime = i*1000000+(j+1)*10000+(k+1)*100+l+1;	
					if(timetable[i][j][k][l] != -1)//valid day?
						continue;
					if(handling == -1){// nothing handling, find something to do
						// find one available activity
						for(m=0;m<eventCounter;m++){
							if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0)
								continue;
							if(event[m].startTimeValue < tmptime && event[m].handled<event[m].duration){
							//start before this date and not finished
								earliestEvent = m;
								break;
							}
						}
						if(earliestEvent == -1)//have nothing to do
							continue;	// go to next hour

						for(m=0;m<eventCounter;m++){// find the earliest coming event	
							if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0)
								continue;		
							if(event[m].startTimeValue<event[earliestEvent].startTimeValue && event[m].handled<event[m].duration)
								earliestEvent = m;
						}
						handling = earliestEvent;
						timetable[i][j][k][l] = handling;
						event[handling].handled++;
	 					if(event[handling].handled == event[handling].duration)
							handling = -1;
					}	
					else{//something handling, continue
						timetable[i][j][k][l] = handling;
						event[handling].handled++;
						if(event[handling].handled == event[handling].duration)
							handling = -1;
					}
				}							
			}
		}
	}
// fcfs finish here, in the timetable[][][][], -2 is time that not available(out of range or april 32nd.etc), -1 is time available but not used, the >-1 value is the index of event[] that has been allocated in the time slot

}
int main(int argc, char *argv[]){
	//declare the time period
	extern int monthDay[12];
	extern int periodStartYear, periodStartMonth, periodStartDay, periodStartHour, periodStartMinute;			
	extern int periodEndYear, periodEndMonth, periodEndDay, periodEndHour, periodEndMinute;
	FILE *fp, *tmpfp, *dest;
	int intbuf,qtm;
	qtm = 0;
	//type of scheduler
	char* scheduleType = (char*)malloc(10);
	//current number of array slot
	int eventSize = 80;
	//declare the event array, can be expanded its size twice to contain all events
	Event *event = (Event*)calloc(eventSize, sizeof(*event));
	//printf("allocate calloc space + %d",sizeof(*event));
	int i, j,k,l,m,havevalidday;
	int pid = 0;
	// initialize all the data in event array (may not needed)
	for (i=0; i<eventSize;i++){											
		strcpy(event[i].type, "");
		strcpy(event[i].name, "");
		event[i].startYear = 0;
		event[i].startMonth = 0;
		event[i].startDay = 0;
		event[i].startHour = 0;
		event[i].dueYear = 0;
		event[i].dueMonth = 0;
		event[i].dueDay = 0;
		event[i].dueHour = 0;
		event[i].duration = 0;
		event[i].priority = 0;
		event[i].handled = 0;
		event[i].startTimeValue = 0;
		event[i].dueTimeValue = 0;
	}

	printf("   ~~WELCOME TO ASKS~~\n\n");
	//declare the buffer to contain the input string
	char input[100]; 														
	printf("Please enter:\n");
	fgets(input, 100, stdin);
	//initialize the period of schedule
	char* tmp;
	char* tmpforrr;
	tmp = strtok(input, " ");
	tmp = strtok(NULL, "-");
	periodStartYear = atoi(tmp);
	tmp = strtok(NULL, "-");
	periodStartMonth = atoi(tmp);
	tmp = strtok(NULL, " ");
	periodStartDay = atoi(tmp);
	tmp = strtok(NULL, ":");
	periodStartHour = atoi(tmp);
	tmp = strtok(NULL, " ");
	periodStartMinute = atoi(tmp);
	tmp = strtok(NULL, "-");
	periodEndYear = atoi(tmp);
	tmp = strtok(NULL, "-");
	periodEndMonth = atoi(tmp);
	tmp = strtok(NULL, " ");
	periodEndDay = atoi(tmp);
	tmp = strtok(NULL, ":");
	periodEndHour = atoi(tmp);
	tmp = strtok(NULL, " ");
	periodEndMinute = atoi(tmp);

	// time table array
	int duryear = periodEndYear-periodStartYear+1;
	int timetable [duryear][12][31][24];

	int max = (periodEndYear-periodStartYear)*1000000+periodEndMonth*10000+periodEndDay*100+periodEndHour;
	int min = periodStartMonth*10000+periodStartDay*100+periodStartHour;
	int dayAmount = 0;
	// initialization
	int tmptime;
	for(i=0;i<duryear;i++){
		for(j=0;j<12;j++){
			for(k=0;k<31;k++){
				havevalidday = 0;
				for(l=0;l<24;l++){
					tmptime = i*1000000+(j+1)*10000+(k+1)*100+l;			
					if(tmptime<min||tmptime>max)
						timetable[i][j][k][l] = -2; //day do not need, disable
					else
						timetable[i][j][k][l] = -1; //valid day, give -1
					if(k>monthDay[j]-1)
						timetable[i][j][k][l] = -2; //day do not exist, disable
					if(timetable[i][j][k][l] == -1)
						havevalidday = 1;
				}	
				if(havevalidday == 1)
					dayAmount++;								
			}
		}
	}
	int timetablebyday[dayAmount][24];
// for counting the number of used array slot to decide whether there is need to expand the array
	int eventCounter = 0;
	//initialize the formal input event and put them into correct Event data type.
	while(1){
		printf("Please enter:\n");
		char input[100];
		fgets(input, 100, stdin);

		//decide whether this is the end of input
		if (input[0]=='a'&&input[1]=='d'&&input[2]=='d'){
			//initialize the type of event
			tmp = strtok(input, " ");
			for (i=3; i<strlen(tmp)+1; i++){
				*(tmp+i-3) = *(tmp+i);
			}
			strcpy(event[eventCounter].type, tmp);
			//printf("%s\n",event[eventCounter].type);

			//initialize the name of event
			tmp = strtok(NULL, " ");
			strcpy(event[eventCounter].name, tmp);
			//printf("%s\n",event[eventCounter].name);

			if (strcmp(event[eventCounter].type, "Project") != 0){
				//initialize the year of start time of this event
				tmp = strtok(NULL, "-");
				event[eventCounter].startYear = atoi(tmp);
				//printf("%d\n",event[eventCounter].startYear);

				//initialize the month of start time of this event
				tmp = strtok(NULL, "-");
				event[eventCounter].startMonth = atoi(tmp);
				//printf("%d\n",event[eventCounter].startMonth);

				//initialize the day of start time of this event
				tmp = strtok(NULL, " ");
				event[eventCounter].startDay = atoi(tmp);
				//printf("%d\n",event[eventCounter].startDay);

				//initialize the hour of start time of this event
				tmp = strtok(NULL, ":");
				event[eventCounter].startHour = atoi(tmp);
				//printf("%d\n",event[eventCounter].startHour);
				tmp = strtok(NULL, " ");
			}
	        
			//test whether the event is project or assignment
			if (strcmp(event[eventCounter].type, "Project") == 0 || strcmp(event[eventCounter].type, "Assignment") == 0){
				//initialize the year of due time of this event
				tmp = strtok(NULL, "-");
				event[eventCounter].dueYear = atoi(tmp);

				//initialize the month of due time of this event
				tmp = strtok(NULL, "-");
				event[eventCounter].dueMonth = atoi(tmp);

				//initialize the day of due time of this event
				tmp = strtok(NULL, " ");
				event[eventCounter].dueDay = atoi(tmp);

				//initialize the hour of due time of this event
				tmp = strtok(NULL, ":");
				event[eventCounter].dueHour = atoi(tmp);
				tmp = strtok(NULL, " ");
				int minute = atoi(tmp);
				if (minute > 0){
					event[eventCounter].dueHour++;
				}
			}

			//initialize the duration
			tmp = strtok(NULL, " ");
			event[eventCounter].duration = atoi(tmp);
			//printf("%d\n",event[eventCounter].duration);

			tmp = strtok(NULL, " ");
			event[eventCounter].priority = atoi(tmp);
			//printf("%d\n",event[eventCounter].priority);

			//expand dynamic array to contain more event (may need more tests)	
			eventCounter++;
			if (eventCounter == eventSize){
				Event *tmpEvent = (Event*)calloc(eventSize, 80);
				memcpy(tmpEvent, event, eventSize*80);
				eventSize *= 2;
				event = (Event*)calloc(eventSize, 80);
				memcpy(event, tmpEvent, eventSize*40);
				free(tmpEvent);
			}
		}else if(strcmp(strtok(input, "-"), "runASKS ") == 0){
			tmp = strtok(NULL, "|");
			strcpy(scheduleType, tmp);
		//	printf("---%s---\n",scheduleType);
			tmp = strtok(NULL, " ");
			tmp = strtok(NULL, " ");
			tmp = strtok(NULL, " ");
			tmp[strlen(tmp)-2] = '\0';
			fp = fopen("report.dat", "wt");
			tmpfp = fopen("analysis.dat","wt");
			break;
		}		
		//printf("%d\n", eventCounter); //testing code
	}//end of input module

	// put all class and sleep into the timetable
	int theYear;
	int theMonth;
	int theDay;
	int theHour;
	int timetablevalue;
	int periodStartTimeValue = periodStartMonth*10000+periodStartDay*100+periodStartHour;
	int periodEndTimeValue = duryear*1000000+periodEndMonth*10000+periodEndDay*100+periodEndHour;
	for(m=0;m<eventCounter;m++){
		theYear = event[m].startYear - periodStartYear;
		theMonth = event[m].startMonth;
		theDay = event[m].startDay;
		theHour = event[m].startHour;
		if((event[m].startYear+event[m].startMonth+event[m].startDay+event[m].startHour)!=0){
			// if start time has been input, calculate the starttimevalue
			event[m].startTimeValue = theYear*1000000+theMonth*10000+theDay*100+theHour;
		}
		else{// if start time not input, set it to the start of the period and calculate
			event[m].startYear = periodStartYear;
			event[m].startMonth = periodStartMonth;
			event[m].startDay = periodStartDay;
			event[m].startHour = periodStartHour;
			theYear = event[m].startYear - periodStartYear;
			theMonth = event[m].startMonth;
			theDay = event[m].startDay;
			theHour = event[m].startHour;
			event[m].startTimeValue = theYear*1000000+theMonth*10000+theDay*100+theHour;
		}
		if((event[m].dueYear+event[m].dueMonth+event[m].dueDay+event[m].dueHour)!=0)
			// calculate duetimevalue
			event[m].dueTimeValue = (event[m].dueYear-periodStartYear)*1000000+event[m].dueMonth*10000+event[m].dueDay*100+event[m].dueHour;
	//	printf("%d %d %d %d\n",event[m].startYear,event[m].startMonth,event[m].startDay,event[m].startHour);
	//	printf("%d %d\n ",event[m].startTimeValue,event[m].dueTimeValue);
		if(strcmp(event[m].type,"Class")==0||strcmp(event[m].name,"Sleep")==0){// for class and sleep
			if(event[m].startTimeValue<periodStartTimeValue){
				//printf("%s %d %d\n",event[m].name,event[m].startTimeValue,periodStartTimeValue);
				continue;
			}
			//printf("%s %s \n",event[m].type,event[m].name);	
			for(i=theYear;i<duryear;i++){//year
				for(j=0;j<12;j++){//month
					for(k=0;k<31;k++){//day
						for(l=0;l<24;l++){//hour
							timetablevalue = (i)*1000000+(j+1)*10000+(k+1)*100+l+1;//time in this round of loop
							if(timetablevalue > event[m].startTimeValue &&timetable[i][j][k][l] == -1){
								event[m].handled++;
// 啊啊啊腰疼疼疼疼						//printf("handled\n");
								timetable[i][j][k][l] = m;
								if(event[m].handled == event[m].duration){
								//	printf("%d %d %d %d %s\n",i+1,j+1,k+1,l+1,event[m].type);
									break; 
								}
							}//if
							if(event[m].handled == event[m].duration){
								break; 
							}
						}//l	
						if(event[m].handled == event[m].duration){
							break; 
						}						
						}//k
					if(event[m].handled == event[m].duration){
						break; 
					}
					}//j
				if(event[m].handled == event[m].duration){
					break; 
				}
			}//i
		}
	}
	//printf("%s\n",scheduleType);
	if(strcmp(scheduleType, "FCFS ") == 0){
	//	printf("fcfs\n");
		FCFS(event,eventCounter,duryear,timetable);
		scheduleType = "First Come First Serve";
	}
	else if(strcmp(scheduleType, "SJF ") == 0){
	//	printf("sjf\n");
		SJF(event,eventCounter,duryear,timetable);
		scheduleType = "Short Job First";
	}
	else if(strcmp(scheduleType, "SRT ") == 0){
	//	printf("srt\n");
		SRT(event,eventCounter,duryear,timetable);
		scheduleType = "Shortest Remaining Time";
	}
	else if(strcmp(scheduleType, "PR p ") == 0){
	//	printf("pr p\n");
		PRP(event,eventCounter,duryear,timetable);
		scheduleType = "priority with preemption";
	}
	else if(strcmp(scheduleType, "PR n ") == 0){
	//	printf("pr n\n");
		PRN(event,eventCounter,duryear,timetable);
		scheduleType = "priority without preemption";
	}
	else {
		tmpforrr = strtok(scheduleType, " ");
		if(strcmp(tmpforrr,"RR ")){
			qtm = atoi(strtok(NULL," "));
		RRX(event,eventCounter,duryear,timetable,qtm);
		scheduleType = "Round Robin with quantum of ";
		}
	}

	/*for(i=0;i<duryear;i++){
		for(j=0;j<12;j++){
	//	printf("month %d\n",j+1);
			for(k=0;k<31;k++){
		//	printf("day %d\n",k+1);
				for(l=0;l<24;l++){
						if(timetable[i][j][k][l] != -2)
						printf("%d ",timetable[i][j][k][l]);
				}
		//	printf("\n");							
			}
		}
	}
	printf("\n-----\n");
	*/
	
	//prepare for multi-process
	int fd[2];					
	if(pipe(fd)<0){
		printf("pipe creation error!\n");
		exit(1);		
	}
	pid = fork();
	if(pid == 0){//child for output...
		//printf("outer child %d %d\n",getpid(),getppid());
		close(fd[1]);
		for(i=0;i<dayAmount;i++){
			for(j=0;j<24;j++){
				if(i==0&&j<periodStartHour)
					timetablebyday[i][j] = -2;
				else
					if(i==dayAmount-1&&j>periodEndHour)
					timetablebyday[i][j] = -2;
				
					else{
						read(fd[0],&intbuf,sizeof(int));
						timetablebyday[i][j] = intbuf;
						//printf(" %d",timetablebyday[i][j]);
					}
			}						
		}
		pid = fork();
		if(pid == 0){//child of child for output
		//printf("inner child %d %d\n",getpid(),getppid());
			fprintf(fp, "Alex Timetable\n");
			fprintf(fp, "%d-%02d-%02d %02d:%02d to %d-%02d-%02d %02d:%02d\n", periodStartYear, periodStartMonth, periodStartDay,periodStartHour, periodStartMinute, periodEndYear, periodEndMonth, periodEndDay, periodEndHour, periodEndMinute);
			fprintf(fp, "time\t");
			for(i=0;i<duryear;i++){
				for(j=0;j<12;j++){
					for(k=0;k<31;k++){
						havevalidday = 0;
						for(l=0;l<24;l++){
							if(timetable[i][j][k][l] != -2)
								havevalidday = 1;
						}
							
						if(havevalidday == 1)
							fprintf(fp,"%d-%02d-%02d\t",i+periodStartYear,j+1,k+1);	
					}//k
				}//j
			}//i	
			fprintf(fp,"\n");
			for(i=0;i<24;i++){
				fprintf(fp,"%02d:00\t",i);
				for(j=0;j<dayAmount;j++){
					if(timetablebyday[j][i] == -1)
						fprintf(fp,"N/A\t\t");
					else if(timetablebyday[j][i] > -1)
						fprintf(fp,"%s  \t",event[timetablebyday[j][i]].name);
					else
						fprintf(fp,"invalid time\t");
				}
				fprintf(fp,"\n");
			}
			fclose(fp);				
			exit(0);
		}
		else{//parent of child for analysis
		//printf("child parent %d %d\n",getpid(),getppid());
			fprintf(tmpfp,"\n\n**Summary of assignments allocation**\n\n");
			fprintf(tmpfp,"Algorithms used: %s",scheduleType);
			if(qtm != 0)
				fprintf(tmpfp,"%d",qtm);
			fprintf(tmpfp,"\n");			
			int cnt=0;
			for(i=0;i<eventCounter;i++){
				if(event[i].duration == event[i].handled)
					cnt++;
			}
			int turntime = 0;
			int tmpturntime = 0;
			int tmpwaittime = 0;
			int waittime = 0;
			fprintf(tmpfp,"There are %d assignments scheduled. Details are as follows\n",cnt);
			fprintf(tmpfp,"ASSIGNMENT\tSTART\t\t\tEND\t\t\tTURNAROUND TIME\n");
			fprintf(tmpfp,"===========================================================================\n");
			//finished calculate turnaround time and wait time
			for(m=0;m<eventCounter;m++){
				tmpturntime = 0;
				tmpwaittime = 0;
				if(event[m].duration != event[m].handled)// not finished
					continue;//pass	
				event[m].handled = 0;
				for(i=0;i<duryear;i++){//year
				for(j=0;j<12;j++){//month
					for(k=0;k<31;k++){//day
						for(l=0;l<24;l++){//hour
							if(timetable[i][j][k][l]==-2)
								continue;
							timetablevalue = (i)*1000000+(j+1)*10000+(k+1)*100+l;//time in this round of loop
							if(event[m].startTimeValue<timetablevalue+1){
								tmpwaittime++;
								tmpturntime++;
							}
							if(timetable[i][j][k][l] == m){
								if(event[m].handled==0){
									event[m].startYear = i+periodStartYear;
									event[m].startMonth = j+1;
									event[m].startDay = k+1;
									event[m].startHour = l;
								}
								event[m].handled++;							
								tmpwaittime--;
								if(event[m].handled == event[m].duration){
									fprintf(tmpfp,"%s\t%d-%02d-%02d %02d:00\t%d-%02d-%02d %02d:00\t%dHrs\t\n",event[m].name,event[m].startYear,event[m].startMonth,event[m].startDay,event[m].startHour,i+periodStartYear,j+1,k+1,l,tmpturntime);
									turntime = turntime + tmpturntime;
									waittime = waittime + tmpwaittime;
									break; 
								}
							}
						}//l	
						if(event[m].handled == event[m].duration){
							break; 
						}						
						}//k
					if(event[m].handled == event[m].duration){
						break; 
					}
					}//j
				if(event[m].handled == event[m].duration){
					break; 
				}
				}//i				
			}
			fprintf(tmpfp,"  -end-\n");
			fprintf(tmpfp,"\n===========================================================================\n");
			fprintf(tmpfp,"**PERFORMANCE\n\n");
			fprintf(tmpfp,"AVERAGE TURNAROUND TIME FOR ASSIGNMENTS: %d HRS\n",turntime/cnt);
			fprintf(tmpfp,"AVERAGE WAITINGTIME FOR ASSIGNMENTS: %d HRS\n",waittime/cnt);
			fprintf(tmpfp,"\n**Outstanding/Rejected List**\n\n");
			m=0;
			for(i=0;i<eventCounter;i++)
				if(event[i].duration!=event[i].handled){
					m++;
					fprintf(tmpfp,"%s %s\n",event[i].type,event[i].name);
				}

			fprintf(tmpfp,"There are %d events rejected.\n\n\n",m);
			fclose(tmpfp);
			//remove("analysis.dat");
			waitpid();
			exit(0);
		}
	}
	else{//parent
		close(fd[0]);
		//printf("parent %d %d\n",getpid(),getppid());
		for(i=0;i<duryear;i++){
			for(j=0;j<12;j++){
				for(k=0;k<31;k++){
					for(l=0;l<24;l++){
						if(timetable[i][j][k][l] != -2){
							intbuf = timetable[i][j][k][l];		
						//	printf(" %d \n ",intbuf);
							write(fd[1],&intbuf,sizeof(int));
						}
					}					
				}
			}	
		}
		waitpid();
		sleep(1);
		fp = fopen("report.dat", "r");
		tmpfp = fopen("analysis.dat","r");
		dest = fopen(tmp,"a+");
		char byte;

		while (!feof(fp)) {
 			fread(&byte, sizeof(char), 1, fp);
 			fwrite(&byte, sizeof(char), 1, dest);
		}
		close(fp);
		while (!feof(tmpfp)) {
 			fread(&byte, sizeof(char), 1, tmpfp);
 			fwrite(&byte, sizeof(char), 1, dest);
		}
		close(tmpfp);
		close(dest);
		remove("report.dat");
		remove("analysis.dat");
		exit(0);
	}		
}


