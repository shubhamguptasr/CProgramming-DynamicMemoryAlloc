#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int ID;
    char firstName[15];
    char lastName[15];
    int prjGrade1;
    int prjGrade2;
    float finalGrade;
} student;

//function prototypes
student **create_class_list(char *filename, int *sizePtr);
int find(int idNo, student **list, int size);
void input_grades(char *filename, student **list, int size);
void compute_final_course_grades(student **list, int size);
void output_final_course_grades(char *filename, student **list, int size);
void print_list(student **list, int size);
void withdraw(int idNo, student **list, int *sizePtr);
void destroy_list(student **list, int *sizePtr);


int main()
{
    char studentList[50],studentGrade[50],studentOutput[50];
    int size;
    int id;

    student **list = NULL; //initialize pointer variable

    printf("Enter the input filename: ");
    scanf("%s",studentList); //asks user for classlist file

    list = create_class_list(studentList, &size); //class list

    printf("Enter the grades filename: ");
    scanf("%s",studentGrade); //asks user for grade file
    input_grades(studentGrade,list,size);

    compute_final_course_grades(list,size); //class list and size

    printf("Enter the output filename: ");
    scanf("%s",studentOutput); //asks user for output file
    output_final_course_grades(studentOutput,list,size);

    print_list(list,size); //refers to class list and size

    while(1){ //used while loop to invoke withdraw unit 0 is inputted
        printf("Enter id to withdraw (0 to exit): ");
        scanf("%d", &id);
        if(id==0)
        break;

        withdraw(id,list,&size);
        print_list(list,size);
        }
        destroy_list(list,&size);

    return 0;
}

student **create_class_list(char *filename, int *sizePtr){
    FILE *inputFile = fopen(filename, "r"); //opens file for reading
    int i;
    int n;

    student **stu = NULL; //set a new stu array to null
    if(inputFile==NULL){
        printf("Could not open file %s", filename);
        exit(1);
    }

    fscanf(inputFile, "%d", &n); //reads the integer (aka # of students)
    *sizePtr = n; //points to the integer value (# of students)

    stu = (student**)malloc(n*(sizeof(student*))); //memory allocation for # of students

    for(i=0;i<n;i++){
        stu[i]= (student*)malloc(sizeof(student)); //memory allocation for current student
        fscanf(inputFile, "%d %s %s", &stu[i]->ID, stu[i]->firstName, stu[i]->lastName); //intializes student structure

        stu[i]->prjGrade1 =0; //initializes grades to 0
        stu[i]->prjGrade2 =0;
        stu[i]->finalGrade =0;
    }
    fclose(inputFile);
    return stu;
    free(stu);
}

void input_grades(char *filename,student **list, int size){

    FILE *inputFile = fopen(filename, "r"); //opens file to read
    int index;
    int id;

    int grade1, grade2;

    if(inputFile==NULL){ //checks if inputfile has the value of null (DNE)
        printf("Could not open file %s", filename);
        exit(1);
    }

    while(fscanf(inputFile, "%d", &id)==1){ //keeps reading
        fscanf(inputFile, "%d %d", &grade1, &grade2); //gets grades for proj&2
        index = find(id,list,size); //finds the position of the current id

        if(index != -1){
            list[index]->prjGrade1 = grade1; //sets the correct grades
            list[index]->prjGrade2 = grade2;
        }
    }
    fclose(inputFile);
}

int find(int idNo, student **list, int size){

    int i;
    for(i=0;i<size;i++){
        if(list[i]->ID==idNo){ //searches for idNo
            return i; //returns index position in the list
        }
    }
        return -1; //returns -1 if not found
    }

void compute_final_course_grades(student **list, int size){

    int i;
    for(i=0;i<size;i++){ //computes each student grades in list
        list[i]->finalGrade = (list[i]->prjGrade1 + list[i]->prjGrade2)/2.0; //adds the projects
    }
}

void output_final_course_grades(char *filename, student **list, int size){

    FILE *outputFile = fopen(filename, "w"); //opens file to write

    int i;

    if(outputFile==NULL){ //checks if outputfile is null
        printf("Could not open %s file",filename);
        return;
    }
    fprintf(outputFile,"%d\n",size); //prints size on output file
    for(i=0;i<size;i++){ //loops and prints the id and grade
        fprintf(outputFile, "%d %.2f\n",list[i]->ID,list[i]->finalGrade);
    }
    fclose(outputFile);
}

void print_list(student **list, int size){

    int i;

    printf("Student list \n");
    for(i=0;i<size;i++){ //prints the list
        printf("ID:%d, StudentName: %s %s, Grade Prj1:%d , Grade Prj2:%d, Final:%.2f\n",list[i]->ID, list[i]->firstName, list[i]->lastName, list[i]->prjGrade1, list[i]->prjGrade2, list[i]->finalGrade);
    }
}

void withdraw(int idNo, student **list, int *sizePtr){

    int i;
    int search = 0;

    for(i=0;i<*sizePtr;i++){ //similar to find fnct (finds if ID == idNo)
        if(list[i]->ID==idNo){
            search = 1; //sets flag if found
            break;
        }
    }
    if(search){
        free(list[i]); //frees memory of student being withdrawn from [i] location
        for(i=i+1;i<*sizePtr;i++){//shifts pointer to next student
            list[i-1]=list[i]; //stores in the new list
        }
        (*sizePtr)=(*sizePtr)-1; //reduces the size of list
        printf("ID: %d removed\n", idNo);
    }else
    printf("ID: %d DNE\n",idNo);
}

void destroy_list(student **list, int *sizePtr){

    int i;
    for(i=0;i<*sizePtr;i++){
        free(list[i]); //frees memory of each student
    }
    *sizePtr=0; //sets size to 0
    free(list); //frees memory of list
}
