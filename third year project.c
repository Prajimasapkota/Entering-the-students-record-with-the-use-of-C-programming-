#include<stdio.h>
#include<string.h>
#include<conio.h>
#include <stdlib.h>
// defining functions//
void addrecord();
void addbulk();
void liststudents();
void searchstudents();
void edit(int num);
void del(int num);
void viewmarksheet(int num);




struct record{
		int roll;
	char name[30];
	int math;
	int science;
	int english;
	int nepali;
	int social;
	float per;
};
	
int main(){
	int choice=0;
	
	printf("*****************************************************************************************\n");
	while(choice!=5){
		printf("1.Add a record\n");
		printf("2.Add Bulk Records\n");
		printf("3.List students\n");
		printf("4.Search students\n");
		printf("5.Quit\n\n");
		printf("What is your choice?:" );
		scanf("%d",&choice);
	
			switch(choice){
		case 1:
			addrecord();
		
			break;
		case 2:
			
			addbulk();
			
			break;
		case 3:
			
			liststudents();
			
			break;
		case 4:
		
			searchstudents();
			break;
		case 5:
			exit(0);
		default:
			fflush(stdin);
			printf("Bye Bye !!");
			printf("\n******************************************************************************************\n");
			break;
			
			
		printf("\n******************************************************************************************\n");
	}

	}
	return 0;
	
}
void addrecord(){
	//I've considered the variable to be single for storing only one record//
	struct record single;
	FILE* fp;
	
	fp=fopen("record.dat","ab");

	
	getchar();
	printf("\nEnter name : ");
	scanf("%[^\n]s", single.name);
	// printf(" checking name  %s", &single.nameroll.name);
	printf("\nEnter Roll : ");
	scanf("%d",&single.roll);
	printf("\nEnter marks in Mathematics: ");
	scanf("%d",&single.math);
	printf("\nEnter marks in Science: ");
	scanf("%d",&single.science);
	printf("\n Enter marks in English: ");
	scanf("%d",&single.english);
	printf("\nEnter marks in Nepali: ");
	scanf("%d",&single.nepali);
	printf("\nEner marks in Social: ");
	scanf("%d",&single.social);
	single.per=((single.english +single.math + single.nepali +single.science +single.social )/5.0);

	getchar();
	fwrite(&single,sizeof(single),1,fp);

	fclose(fp);

}
void liststudents(){
	FILE* fp;
	struct record los;
	// printf("\nRoll \t\t\t\t Name");
	fp=fopen("record.dat","rb");
	rewind(fp);
	if(fp==NULL){
		printf("\n the file doesnot exist");
	}
	else
	{
		printf("\nRoll\t\tName\n");
 
		while(fread(&los,sizeof(los),1,fp)){
			printf("%d\t\t%-30s\n",los.roll,los.name);
		}
		printf("\n***********************************************************************************\n");
	}
	fclose(fp);
}	
void addbulk(){
	int num,i;
	struct record *bulk;
	FILE* fp;
	fp=fopen("record.dat","ab");
	
	printf("How many students?: ");
	scanf("%d",&num);
	bulk=(struct record*)calloc(num,sizeof(struct record));
	
	for(i=0;i<num;i++){
		
		printf("\nEnter information for student %d\n",i+1);
		getchar();
		printf("\nEnter name : ");
		scanf("%[^\n]s", bulk[i].name);
		// printf(" checking name  %s", &single.nameroll.name);
		printf("\nEnter Roll : ");
		scanf("%d",&bulk[i].roll);
		printf("\nEnter marks in Mathematics: ");
		scanf("%d",&bulk[i].math);
		printf("\nEnter marks in Science: ");
		scanf("%d",&bulk[i].science);
		printf("\n Enter marks in English: ");
		scanf("%d",&bulk[i].english);
		printf("\nEnter marks in Nepali: ");
		scanf("%d",&bulk[i].nepali);
		printf("\nEner marks in Social: ");
		scanf("%d",&bulk[i].social);
		bulk[i].per=((bulk[i].english +bulk[i].math + bulk[i].nepali +bulk[i].science +bulk[i].social )/5.0);
		fwrite(&bulk[i],sizeof(struct record),1,fp);
	}
	printf("\n***********************************************************************\n");
	fclose(fp);
}
void searchstudents(){
	struct record s1;
	FILE* fp;
	int num,choice;
	
	fp=fopen("record.dat","rb");
	printf("\n****************************************************************************\n");
	printf("Enter Roll No: ");
	scanf("%d",&num);
	printf("\n****************************************************************************\n");
	while(fread(&s1,sizeof(s1),1,fp)){
			if(s1.roll==num){
				printf("\nRecord Found:\n");
				printf("Student Name : %s",s1.name);
				printf("\n*****************************************************************\n");
				printf("1.Edit Record\n");
				printf("2.Delete Record\n");
				printf("3.View Marksheet\n");
				printf("4.Quit\n");
				printf("What is your choice? :");
				scanf("%d",&choice);
				switch(choice){
					case 1: 
						edit(num);
						break;
					case 2:
						del(num);
						break;
					case 3:
						viewmarksheet(num);
						break;
					case 4:
						break;
				}
				
			}
			
	}	
	fclose(fp);	
}
void viewmarksheet(int num){
	struct record s1;
	FILE* fp;
	fp=fopen("record.dat","rb");
	if(fp==NULL){
		fprintf(stderr,"Can't open file\n");
	}
	

	while(fread(&s1,sizeof(s1),1,fp)){
		if(s1.roll==num){
			printf("\nST.XAVIER'S COLLEGE\n");
			printf("*************************************************************************\n");
			printf("|\tName: %-30s				|\n",s1.name);
			printf("|\tRoll : %-10d						|",num);
			printf("\n*************************************************************************\n");
			printf("|\tS.N \t|\tSubjects\t\t|\tMarks\t\t|");
			printf("\n*************************************************************************\n");
			printf("|\t1.\t|\tMathematics\t\t|\t%3d\t\t|\n",s1.math);
			printf("|\t2.\t|\tEnglish\t\t\t|\t%3d\t\t|\n",s1.english);
			printf("|\t3.\t|\tNepali\t\t\t|\t%3d\t\t|\n",s1.nepali);
			printf("|\t4.\t|\tScience\t\t\t|\t%3d\t\t|\n",s1.science);
			printf("|\t5.\t|\tSocial\t\t\t|\t%3d\t\t|",s1.social);
			printf("\n*************************************************************************\n");
			printf("|\t\t|\tPercentage\t\t|\t%.2f\t\t|\n",s1.per);
			if(s1.per<=59.99){
				printf("|\t\t|\tDivison\t\t\t|\tThird\t\t|");
			}else if(s1.per<=69.99 && s1.per>=60){
				printf("|\t\t|\tDivison\t\t\t|\tSecond\t\t|");
			}else if(s1.per<=79.99 && s1.per>=70){
				printf("|\t\t|\tDivison\t\t\t|\tFirst\t\t|");
			}else{
				printf("|\t\t|\tDivison\t\t\t|\tDistinction\t|");
			}
			printf("\n*************************************************************************\n");
			printf("END OF RESULT\n");
			printf("\n*************************************************************************\n");
		}
	}
	fclose(fp);
	getch();
		
	
}
void edit(int num){
	struct record s1;
	FILE* fp,*fp1;
	int found=0;
	
	fp=fopen("record.dat","rb");
	fp1=fopen("tempo.dat","wb");
	while(fread(&s1,sizeof(s1),1,fp)){
			if(s1.roll==num){
				found=1;
				getchar();
				printf("\nEnter name : ");
				scanf("%[^\n]s", s1.name);
				// printf(" checking name  %s", &single.nameroll.name);
				printf("\nEnter Roll : ");
				scanf("%d",&s1.roll);
				printf("\nEnter marks in Mathematics: ");
				scanf("%d",&s1.math);
				printf("\nEnter marks in Science: ");
				scanf("%d",&s1.science);
				printf("\n Enter marks in English: ");
				scanf("%d",&s1.english);
				printf("\nEnter marks in Nepali: ");
				scanf("%d",&s1.nepali);
				printf("\nEner marks in Social: ");
				scanf("%d",&s1.social);
				s1.per=((s1.english +s1.math + s1.nepali +s1.science +s1.social )/5.0);
				getchar();
			}	
		fwrite(&s1,sizeof(s1),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	if(found){
		fp1=fopen("tempo.dat","rb");
		fp=fopen("record.dat","wb");
		
		while(fread(&s1,sizeof(s1),1,fp1)){
			fwrite(&s1,sizeof(s1),1,fp);	
		}
		fclose(fp);
		fclose(fp1);
		printf("\n***********************************************************************\n");
		printf("Record Updated !");
		printf("\n*************************************************************************\n");
	}else{
		printf("\nRecord not found\n");
	}
}
void del(int num){
	struct record s1;
	FILE* fp,*fp1;
	int found=0;
	
	fp=fopen("record.dat","rb");
	fp1=fopen("tempo.dat","wb");
	while(fread(&s1,sizeof(s1),1,fp)){
			if(s1.roll==num){
				found=1;
			}else{	
				fwrite(&s1,sizeof(s1),1,fp1);
			}	

	}
	fclose(fp);
	fclose(fp1);
	if(found){
		fp1=fopen("tempo.dat","rb");
		fp=fopen("record.dat","wb");
		
		while(fread(&s1,sizeof(s1),1,fp1)){
			fwrite(&s1,sizeof(s1),1,fp);	
		}
		fclose(fp);
		fclose(fp1);
	}else{
		printf("\nRecord not found\n");
	}
}
	
	

						
			
			

