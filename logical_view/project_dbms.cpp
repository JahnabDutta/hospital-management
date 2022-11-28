//Command to Compile: g++ project_dbms.cpp -o project_dbms.exe -lmysql
#include <iostream>
#include <windows.h>
#include <mysql.h>

using namespace std;

MYSQL *conn;



void display(const char *a)
{
    int displaystatus = mysql_query(conn, a);
    if (displaystatus != 0) {
            cout<<"Error while displaying table: "<<mysql_error(conn)<<endl;
    }
    else{
        
        // if(DEBUG_MODE == 1)
        // {
        //     printf("Displaying Result\n");
        // }
        MYSQL_RES *results = mysql_store_result(conn);
        MYSQL_ROW record;
        MYSQL_FIELD *fields;
        int num_fields = mysql_num_fields(results);
        fields = mysql_fetch_fields(results);
        for(int i = 0; i < num_fields; i++)
        {
            cout<<fields[i].name<<" ";
        }
        cout<<endl;
        while ((record = mysql_fetch_row(results)))
        {
            for(int i = 0; i < num_fields; i++)
            {
                char *val = record[i];
                cout<<record[i]<<" ";
            }
            cout<<endl;
        }
        mysql_free_result(results);
    }
    // return 0;
}


int main()
{
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }

    // mysql_real_connect(Connection Instance, Username, Password, Database, Port, Unix Socket, Client Flag)
    if (mysql_real_connect(conn, "localhost", "user01", "123", "project_dbms", 3306, NULL, 0)) {
        cout<<"Connected Successfully!"<<endl;

        // declaring variables

        char tableName1[256] = "doctor";
        char tableName2[256] = "patient";
        char tableName3[256] = "bill";
        char tableName4[256] = "staff";
        char tableName5[256] = "diagnosis";
        char query1[1024],query2[256],query3[256],query4[256],query5[256],query6[256],query7[256];
        char query8[1024],query9[1024],query10[1024];

        // creating table 
        snprintf(query1, 1024, "CREATE TABLE `%s` (`dr_code` int primary key AUTO_INCREMENT,`dr_name` varchar(100) not null,`gender` varchar(10) not null, CONSTRAINT `check_gender` CHECK (gender IN ('M', 'Male', 'F', 'Female' , 'O' , 'Other')), `address` varchar(1000) null, `designation` varchar(1000));", tableName1); 

        int createTableStatus = mysql_query(conn, query1);
        if (createTableStatus != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }

        // creating table 
        snprintf(query2, 1024, "CREATE TABLE `%s`(`pat_code` int primary key AUTO_INCREMENT,`name` varchar(100) not null,`gender` varchar(10) not null,CONSTRAINT `check_gender` CHECK (gender IN ('M', 'Male', 'F', 'Female' , 'O' , 'Other')),`address` varchar(1000) null,`age` int,`phone` varchar(12) null,`dr_code` int, FOREIGN KEY (`dr_code`) REFERENCES `doctor`(`dr_code`));", tableName2); 

        createTableStatus = mysql_query(conn, query2);
        if (createTableStatus != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }

        // creating table 
        snprintf(query3, 1024, "CREATE TABLE `%s`(`bill_no` int primary key AUTO_INCREMENT,`pat_code` int NULL ,`pat_name` varchar(100) null,`dr_code` int null ,`dr_name` varchar(100) null,`date` DATETIME,`amount` int, foreign key (`pat_code`) references `patient`(`pat_code`),FOREIGN KEY (`dr_code`) references `doctor`(`dr_code`));", tableName3); 

        createTableStatus = mysql_query(conn, query3);
        if (createTableStatus != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }

        // creating table 
        snprintf(query4, 1024, "CREATE TABLE `%s`(`staff_id` int primary key AUTO_INCREMENT,`name` varchar(100) not null,`department` varchar(100) not null,`gender` varchar(10) not null,CONSTRAINT `check_gender` CHECK (gender IN ('M', 'Male', 'F', 'Female' , 'O' , 'Other')),`address` varchar(100) null,`dr_code` int null, foreign key (`dr_code`) references `doctor`(`dr_code`));", tableName4); 

        createTableStatus = mysql_query(conn, query4);
        if (createTableStatus != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }

        // creating table 
        snprintf(query5, 1024, "CREATE TABLE `%s`(`diagnosis_number` int primary key AUTO_INCREMENT,`pat_code` int NULL ,`pat_name` varchar(100) null,`diagnosis` varchar(1000) null,`date` DATETIME,`remark` varchar(1000) null,`dr_code` int null,`other` varchar(1000) null,foreign key (`pat_code`) references patient(pat_code), foreign key (`dr_code`) references doctor(dr_code));", tableName5); 

        createTableStatus = mysql_query(conn, query5);
        if (createTableStatus != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }

        // creating trigger to add dr_code in patient table after every insert in diagnosis table
        snprintf(query6, 1024, "CREATE TRIGGER `update_dr_code` AFTER INSERT ON `diagnosis` FOR EACH ROW UPDATE patient SET patient.dr_code = new.other WHERE patient.pat_code = new.pat_code;"); 
        int createTriggerStatus = mysql_query(conn, query6);
        if (createTriggerStatus != 0) {
            cout<<"Error while creating trigger: "<<mysql_error(conn)<<endl;
        }

        // trigger to create instance of bill after every insert in diagnosis table
        snprintf(query7, 1024, "CREATE TRIGGER `create_bill` AFTER INSERT ON `diagnosis` FOR EACH ROW INSERT INTO bill (`pat_code`, `pat_name`, `dr_code`, `dr_name`, `date`, `amount`) values (new.pat_code, new.pat_name, new.dr_code, (select name from doctor where doctor.dr_code = new.dr_code), new.date, (SELECT RAND()*1000));"); 
        createTriggerStatus = mysql_query(conn, query7);
        if (createTriggerStatus != 0) {
            cout<<"Error while creating trigger: "<<mysql_error(conn)<<endl;
        }

        // QUERIES

        // All the patients a doctor with given name = A is examining
        const char* query01 = "SELECT patient.pat_code, patient.name, patient.gender, patient.age from patient cross join doctor where doctor.dr_code = patient.dr_code and doctor.dr_name = 'A';";
        cout << "All the patients a doctor with given name = A is examining" << endl;
        display(query01);
        cout << endl; 

        // Staff details working under supervision of a doctor
        const char* query02 = "Select staff.staff_id, staff.name from staff cross join doctor where doctor.dr_code = staff.dr_code and doctor.dr_name = 'A';";
        cout << "Staff details working under supervision of a doctor" << endl;
        display(query02);
        cout << endl; 

        // List of doctors from a specific department
        const char* query03 = "select doctor.dr_name from doctor cross join staff where staff.department = 'Bhs';";
        cout << "List of doctors from a specific department" << endl;
        display(query03);
        cout << endl; 

        // Diagnostic remarks for particular Patient
        const char* query04 = "SELECT diagnosis.diagnosis, diagnosis.remark, doctor.dr_name from diagnosis, doctor where diagnosis.pat_name = 'XYZ' and diagnosis.dr_code = doctor.dr_code;";
        cout << "Diagnostic remarks for particular Patient" << endl;
        display(query04);
        cout << endl; 

        // Total amount a patient has to pay 
        const char* query05 = "select sum(bill.amount) from bill cross join patient where patient.pat_code = bill.pat_code and patient.name = 'ABC';";
        cout << "Total amount a patient has to pay " << endl;
        display(query05);
        cout << endl; 
   
    } else {
        cout<<"Error while connecting!"<<endl;
    }
    return 0;
}