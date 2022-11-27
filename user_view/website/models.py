from django.db import models
import random
import string

GENDER = (
    ('M', 'male'),
    ('F', 'female'),
    ('O', 'other'),
)

def generate_random_code():
    # generate random alphanumeric code
    return ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(6))

def generate_random_number():
    # generate a random 6 digit number
    return random.randint(100000, 999999)
 
# Create your models here.
class Doctor(models.Model):
    dr_code = models.CharField(max_length=10, primary_key=True, unique=True,default = generate_random_code)
    name = models.CharField(max_length=100, blank=False)
    gender  = models.CharField(max_length=10, blank=False,choices=GENDER)
    address = models.CharField(max_length=1000, null = True)
    designation = models.CharField(max_length=100)

    def __str__(self):
        return self.dr_code
    #meta
    class Meta:
        ordering = ['dr_code']
        verbose_name = 'Doctor'
        verbose_name_plural = 'Doctors'

class Patient(models.Model):
    pat_code = models.CharField(max_length=10, primary_key=True, unique=True,default = generate_random_code)
    name = models.CharField(max_length=100, blank=False)
    gender = models.CharField(max_length=10, blank=False,choices=GENDER)
    address = models.CharField(max_length=1000, null = True)
    age = models.IntegerField()
    phone = models.CharField(max_length=12,null = True)
    dr_code = models.ForeignKey(Doctor, on_delete=models.CASCADE, null = True, blank = True,)


#bill - billNo, patient code, doctor name, date, amount

class Bill(models.Model):
    bill_no = models.CharField(max_length=20, primary_key=True, unique=True,default = generate_random_number)
    pat_code = models.ForeignKey(Patient, on_delete=models.CASCADE, null = True,blank=True)
    pat_name = models.CharField(max_length=100, null = True)
    dr_code = models.ForeignKey(Doctor, on_delete=models.CASCADE, null = True,blank=True)
    dr_name = models.CharField(max_length=100,null = True)
    date = models.DateField()
    amount = models.IntegerField()

    def __str__(self):
        return self.bill_no
    #meta
    class Meta:
        ordering = ['bill_no']
        verbose_name = 'Bill'
        verbose_name_plural = 'Bills'



# staff staff_id, name, dept, gender, address, dr_code

class Staff(models.Model):
    staff_id = models.CharField(max_length=10, primary_key=True, unique=True,default = generate_random_code)
    name = models.CharField(max_length=100, blank=False)
    department = models.CharField(max_length=100, blank=False)
    gender = models.CharField(max_length=10, blank  = False,choices= GENDER)
    address = models.CharField(max_length=1000, null = True)
    dr_code = models.ForeignKey(Doctor, on_delete=models.CASCADE, null = True, blank = True)

    def __str__(self):
        return self.staff_id
    #meta
    class Meta:
        ordering = ['staff_id']
        verbose_name = 'Staff'
        verbose_name_plural = 'Staffs'

# diagnosis dianosis_number, patient code, patient name, diagnosis, date, remark, other

class Diagnosis(models.Model):
    diagnosis_number = models.CharField(max_length=20, primary_key=True, unique=True,default = generate_random_number)
    pat_code = models.ForeignKey(Patient, on_delete=models.CASCADE, null = True,blank= True)
    pat_name = models.CharField(max_length=100, null = True)
    diagnosis = models.CharField(max_length=1000, null = True)
    date = models.DateField()
    remark = models.CharField(max_length=1000, null = True)
    other = models.CharField(max_length=1000, null = True)

    def __str__(self):
        return self.diagnosis_number
    #meta
    class Meta:
        ordering = ['diagnosis_number']
        verbose_name = 'Diagnosis'
        verbose_name_plural = 'Diagnosis'

