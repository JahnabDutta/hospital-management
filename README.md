# Hospital Management System

## Introduction
The following project contains simulation on a Database management system of a hospital on 3 levels-
1. User level (A web application for the doctors and staff to look at the data)
2. Logical Level (Actual Running of the SQL queries and their optimzation and performance)
3. Physical Level (Simulation of actual database and its performance via hashing and indexing)

### General Instructions
clone the repository and run the following commands in the terminal
```git clone https://github.com/JahnabDutta/hospital-management.git```

## User Level
The user level is a web application which is built using Django. The web application is hosted on a local server.

### Techstack
1. Django
2. HTML
3. CSS
4. Bootstrap

### Requirements
1. Python 3.6 or above

### How to run
1. Install virtualenv using ```pip install virtualenv```
2. Create a virtual environment using ```virtualenv venv```
3. Activate the virtual environment using ```source venv/bin/activate```
4. Install the requirements using ```pip install -r requirements.txt```
5. Navigate to the directory ```cd user_level```
6. Run the following commads
```python manage.py makemigrations```
```python manage.py migrate```
```python manage.py runserver```
7. Open the link in the browser

## Logical Level
The logical level is a query level simulation of the database management system of a hospital. The queries are run on a sample dataset and the performance is measured.

### Techstack
1. c++
2. SQL

### Requirements
1. gcc c++ compiler

### How to run
1. Navigate to the directory ```cd logical_level```
2. Run the following commands
```g++ -o hospital_project hospital_project.cpp```
```./hospital_project```

## Physical Level
The physical level is a simulation of the doctors table management system of a hospital. The queries are run on a sample dataset and the performance is measured.

### Techstack
1. c++

### Requirements
1. gcc c++ compiler

### How to run
1. Navigate to the directory ```cd physical_level```
2. Run the following commands
```g++ -o doctors doctors.cpp```
```./doctors```

Upon prompt, enter the commands to view the simulation in action.

## Contributors
1. Jahnab Dutta (B20CS091)
2. Nitya Anand Shah (B20CS039)
3. Niharika Manhar (B20CS038)





 