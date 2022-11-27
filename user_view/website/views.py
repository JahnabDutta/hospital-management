from django.shortcuts import render
from .models import Doctor, Patient, Diagnosis, Bill, Staff

# Create your views here.
def index(request):
    return render(request, 'index.html')

def doctors(request):
    doctors = Doctor.objects.all()
    return render(request, 'doctors.html', {'doctors': doctors})

def patients(request):
    patients = Patient.objects.all()
    return render(request, 'patients.html', {'patients': patients})

def diagnosis(request):
    diagnosis = Diagnosis.objects.all()
    return render(request, 'diagnosis.html', {'diagnosis': diagnosis})

def bills(request):
    bills = Bill.objects.all()
    return render(request, 'bills.html', {'bills': bills})

def staff(request):
    staff = Staff.objects.all()
    return render(request, 'staff.html', {'staff': staff})