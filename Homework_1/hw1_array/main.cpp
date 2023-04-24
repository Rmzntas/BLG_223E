/* @Author
Name: Ramazan Taş
Date: 23.04.2023 */


#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <chrono>


using namespace std;

void add_row_to_array(string**,int,string,string,string,string,string,string,string,string,string,string,string,string);  // adding new row to selected index
void push_array (string** , int, int); 
bool perform_operation(char, string**, int, int[], int[]);
void print_menu();
void printDetails(string**,int);
void list_departments(string**, int, int [], int []);
void select_dep(string** , int , int [], int[]);
void select_uni_dep(string** , int, int [], int []);
 
void add_row_to_array(string** arr,int index, string department, string faculty, string university, string discount, string city, string language,string score_last, string range_last ,string score_first, string range_first, string range_average, string score_average){
    arr[index][0] = department;
    arr[index][1] = faculty;
    arr[index][2] = university;
    arr[index][3] = discount;
    arr[index][4] = city;
    arr[index][5] = language;
    arr[index][6] = score_last;
    arr[index][7] = range_last;
    arr[index][8] = score_first;
    arr[index][9] = range_first;
    arr[index][10]=  range_average;
    arr[index][11]=  score_average;
}

void push_array (string** arr, int num_all, int first_index){   //parameters (array,num_of_all,temp(first index))
    for(int k = num_all; k > first_index; k--){
        for(int j =0; j < 12; j++){
            arr[k][j] = arr[k-1][j];        //pushing 1, it is starting from last element
        }
    }
}

void list_departments(string** arr,int num_dep ,int num_uni[],int dep_index[]){  //list all departments
    
    auto start_dep_listing = chrono::high_resolution_clock::now();

    for (int i=0; i<num_dep ; i++){
        int k = dep_index[i];
        cout<< "Department: " << arr[k][0] << endl;
        cout<< "Number of University Department: "<< num_uni[i] << endl;
        cout<< "-----------------"<<endl;
    }

    auto end_dep_listing = chrono::high_resolution_clock::now();
    auto time_dep_listing = chrono::duration_cast< chrono::milliseconds>(end_dep_listing - start_dep_listing);
    //cout << "Listing departments time: " << time_dep_listing.count() << " milliseconds" << std::endl;

}

void printDetails(string** arr,int i){      //print details of universities
    cout << "Faculty: " << arr[i][1] << endl;
    cout << "Discount: " << arr[i][3] << endl;
    cout << "City: " << arr[i][4] << endl;
    cout << "Language: " << arr[i][5] << endl;
    cout << "Score Last: " << arr[i][6] << endl;
    cout << "Range Last: " << arr[i][7] << endl;
    cout << "Score First: " << arr[i][8] << endl;
    cout << "Range First: " << arr[i][9] << endl;
    cout << "Score Average: " << arr[i][10] << endl;
    cout << "Range Average: " << arr[i][11] << endl;
    cout << "----------------" << endl;
}

void select_dep(string** arr, int num_dep, int num_uni[],int dep_index[]){

    auto start_select_dep = chrono::high_resolution_clock::now();

    int number;
    do{   // loop until giving number between 0 and department number
        cout<< "To review a department, enter a number between 0 and the department number: ";
        cin >> number;
    }while ( number < 0 || number >= num_dep);

    cout<<"Department: "<<arr[dep_index[number]][0]<<endl;

    for(int i= dep_index[number] ; i < dep_index[number] + num_uni[number] ;i++){
        cout<<i-dep_index[number]+1<<": "<<arr[i][2]<<endl;
        printDetails(arr,i);
    }

    auto end_select_dep = chrono::high_resolution_clock::now();
    auto time_select_dep = chrono::duration_cast< chrono::microseconds>(end_select_dep - start_select_dep);
    //cout << "Selecting department: " << time_select_dep.count() << " microseconds" << std::endl;
}

void select_uni_dep(string** arr,int num_dep,int num_uni[],int dep_index[]){

    auto start_select_unidep = chrono::high_resolution_clock::now();

    int num1,num2;
    do{   // loop until giving number between 0 and department number
        cout<< "To review a department, enter a number between 0 and the department number: ";
        cin >> num1;
    }while ( num1 < 0 || num1 >= num_dep);

    cout<<"Department: "<<arr[dep_index[num1]][0]<<endl<<endl;

    do{   // loop until giving number between 0 and department number
        cout<< "To review a department, enter a number between 0 and the department number: ";
        cin >> num2;
    }while ( num2 < 0 || num2 >= num_uni[num1]);

    cout<<arr[dep_index[num1]+num2][2]<<endl;
    printDetails(arr,dep_index[num1]+num2);

    auto end_select_unidep = chrono::high_resolution_clock::now();
    auto time_select_unidep = chrono::duration_cast< chrono::microseconds>(end_select_unidep - start_select_unidep);
    //cout << "Selected university time: " << time_select_unidep.count() << " microseconds" << std::endl;
}

void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "L: List All Departments" << endl;
    cout << "D: Select a Department" << endl;
    cout << "U: Select a Department and University" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {L,D,U,E}: ";
}

bool perform_operation(char choice, string** arr ,int num_dep, int num_uni[], int dep_index[])
{
    bool terminate = false;

    switch (choice)
    {
    case 'l':
    case 'L':
        list_departments(arr,num_dep,num_uni,dep_index);
        print_menu();
        cin >> choice;
        terminate = perform_operation(choice, arr, num_dep, num_uni, dep_index );
        break;
    
    case 'd':
    case 'D':
        cout<<endl;
        select_dep(arr,num_dep,num_uni,dep_index);
        print_menu();
        cin >> choice;
        terminate = perform_operation(choice, arr, num_dep, num_uni, dep_index );
        break;

    case 'u':
    case 'U':
        cout<<endl;
        select_uni_dep(arr, num_dep, num_uni, dep_index);
        print_menu();
        cin >> choice;
        terminate = perform_operation(choice, arr, num_dep, num_uni, dep_index );
        break;

    case 'e':
    case 'E':
        terminate = true;
        break;

    default:
        cout << "ERROR: You have entered an invalid choice" << endl << endl;
        print_menu();
        cin >> choice;
        terminate = perform_operation(choice, arr, num_dep, num_uni,dep_index );
        break;
    }
    return terminate;
}

int main(){
    
    //array will made after file is open
    int num_of_dep = 0;   //number of department
    int num_of_all = 0;   //number of rows
    int roww = -1 ;       //number of row -1 for header row      // Column is constant 12
    const int dep =0;       
    const int uni =2;
    
    /**   array index for column
     * 
     * 0 -> Department Name
     * 1 -> Faculty Name
     * 2 -> University Name
     * 3 -> Discount
     * 4 -> City
     * 5 -> Language
     * 6 -> Last score
     * 7 -> Last rank
     * 8 -> firt score
     * 9 -> first rank
     * 10 -> average rank
     * 11-> average score
    */

    ifstream inFile;

    inFile.open("hw1.csv");
    if(!inFile.is_open()){
        cout << "ERROR: The File Cannot be Opened" << endl;
        return EXIT_FAILURE;
    }
    string discount;
    string city;
    string language;
    string scoreLast;
    string rangeLast;
    string scoreFirst;
    string rangeFirst;
    string averageRange;
    string averageScore;
    string departmentName;
    string facultyName;
    string uniName;
    string row;
    string delimiter = ";"; // If you need change the delimiter
    string afterDelimiter;
    bool header = true;

    while (!inFile.eof())   // getting number of rows in array
    {
        getline(inFile, row, '\n');
        roww++;
    }

    //creating 2D array by dynamicly
    string** Array = new string *[roww];
    for (int i = 0; i < roww; i++) {
        Array[i] = new string[12];
    }

    auto start_filling = chrono::high_resolution_clock::now();

    inFile.clear();     //for reading file again
    inFile.seekg(0);    //for reading file again

    while(!inFile.eof()){
        int i = 0 ;
        getline(inFile, row, '\n');
        
        size_t pos = 0;
        string token;
        while ((pos = row.find(delimiter)) != string::npos) {
            token = row.substr(0, pos);  // token variable is the string before the delimiter
            afterDelimiter = row.substr(row.find(";") + 1); 
            if(token != " "){
                if(i == 0) departmentName=token;
                else if(i==1) facultyName = token;
                else if(i==2) uniName = token;
                else if(i==3) discount = token;
                else if(i==4) city = token;
                else if(i==5) language = token;
                else if(i==6) scoreLast = (token);
                else if(i==7) rangeLast = (token);
                else if(i==8) scoreFirst = (token);
                else if(i==9) rangeFirst = (token);
                else if(i==10) {averageRange = (token);
                    averageScore = afterDelimiter; // since the substr() function takes the string before the delimiter averageScore attribute cannot be get from this function

                } 
            }
            row.erase(0, pos + delimiter.length());
            i++;
        }
        if(header == false){

            if(num_of_all == 0){        // if Array is Empty
                add_row_to_array(Array,0,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);
                num_of_dep++;
                num_of_all++;
            }
            else if (num_of_all == 1){   //if there is only 1 row
                if( (Array[0][dep] == departmentName) & ( Array [0][uni] == uniName ||  uniName > Array [0][uni] )){  //department names ara same and uni name same or bigger
                    
                    add_row_to_array(Array,1,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);
                    num_of_all++;
                }
                else if((departmentName == Array[0][dep]) & (Array[0][uni] > uniName)){         // if department name is same and university name is smaller
                    
                    push_array(Array,num_of_all,0);
                    add_row_to_array(Array,0,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);
                    num_of_all++;
                }
                else if( departmentName > Array [0][dep]){   // if department name is bigger
                    
                    add_row_to_array(Array,1,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);
                    num_of_all++;
                    num_of_dep++;
                }
                else{  // departmentName < Array [0][0]     // if department name is smaller
                    
                    push_array(Array,num_of_all,0);
                    add_row_to_array(Array,0,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);

                    
                    num_of_all++;
                    num_of_dep++;
                }  
            }
            else{       // number of row more than 1
                int temp = 0;
                bool flag =true;                    // for not increasing wrong
                
                while(temp != num_of_all-1){        // while temp is not in the last row

                    if (departmentName < Array[temp][dep]){     // if department name is smaller
                        push_array(Array,num_of_all,temp);
                        add_row_to_array(Array,temp,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);
                        num_of_all++;                 
                        if(flag){
                            num_of_dep++;
                        }
                        flag = true;
                        break;
                    }
                    else if (departmentName == Array [temp][dep]){   // if department name is same
                        
                        if (uniName < Array[temp][uni]){             // and if uni name is samller
                            push_array(Array,num_of_all,temp);
                            add_row_to_array(Array,temp,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);

                            num_of_all++;
                            break;
                        }
                        else if(uniName == Array[temp][uni]){       //and if uni name is same
                            push_array(Array,num_of_all,temp);
                            add_row_to_array(Array,temp,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);

                            num_of_all++;
                            break;
                        }
                        else{   //uniName > Array[temp][uni]        //and uni name is bigger
                            temp++;  // sıradakine geçiş
                            flag = false;
                        }
                    }
                    else{       // departmentName > Array[temp][dep]
                        temp++;
                    }
                }
                if (temp == num_of_all-1){                      // temp is at the last row

                    if(departmentName < Array[temp][dep]){      //if department name is smaller
                        
                        push_array(Array,num_of_all,temp);
                        add_row_to_array(Array,temp,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);
                        num_of_all++;
                        if(flag){
                            num_of_dep++;
                        }
                    }
                    else if(departmentName > Array[temp][dep]){     //if department name is bigger
                        
                        add_row_to_array(Array,num_of_all,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);
                        num_of_all++;
                        num_of_dep++;
                    }
                    else{       //department == Array[temp][dep]        // if department name is same
                        
                        if (uniName > Array[temp][uni]){                //and if uni name is bigger
                            add_row_to_array(Array,num_of_all,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);
                            num_of_all++;
                        }
                        else if(uniName == Array[temp][uni]){           //and if uni name is same
                            add_row_to_array(Array,num_of_all,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);
                            num_of_all++;
                        }
                        else{       // uni name < array[temp][uni]      //and if uni name is smaller
                            push_array(Array,num_of_all,temp);
                            add_row_to_array(Array,temp,departmentName,facultyName,uniName,discount,city,language,scoreLast,rangeLast,scoreFirst,rangeFirst,averageRange,averageScore);
                            num_of_all++;
                        }
                    }
                }
            }
        }
        header = false;
    }

    auto end_filling = chrono::high_resolution_clock::now();
    auto time_filling = chrono::duration_cast <chrono::milliseconds>(end_filling - start_filling);
    //cout << "Filling Time: " << time_filling.count() << " milliseconds" << std::endl;

    inFile.close();

            // calculating there is have many universities in each department
    
    int num_of_uni[num_of_dep];     //uni number for each department
    int dep_index[num_of_dep];      //index of each department
    int univer = 1;                 
    int temp_department=0;          

    dep_index[0]=0;             // index of first dep


            //calculating how many university each department have

    for (int j = 0; j < num_of_all-1; j++){
            
        if (Array[j][dep] == Array[j+1][dep]){    
            univer++;
            if ( j==num_of_all-2){      // in the last iteration
                num_of_uni[temp_department] = univer;
            }
        }
        else{
            num_of_uni[temp_department]=univer;
            temp_department++;
            univer=1;
            dep_index[temp_department]=j+1;
            if ( j==num_of_all-2){      // in the last iteration
                num_of_uni[temp_department] = univer;
            }
        }
    }
       
    bool end = false;
    char choice;

    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice, Array, num_of_dep, num_of_uni, dep_index); 
    }

    auto start_deallocating = chrono::high_resolution_clock::now();

    for (int i = 0; i < roww; i++) {  //deallocation
        delete[] Array[i];
    }
    delete[] Array;

    auto end_deallocating = chrono::high_resolution_clock::now();
    auto time_deallocating = chrono::duration_cast< chrono::milliseconds>(end_deallocating - start_deallocating);
    //cout << "Deallocating Time: " << time_deallocating.count() << " millseconds" << std::endl;
    
    return 0;
}
