#import django url
from django.urls import path
import website.views as views

urlpatterns = [
    path('', views.index, name='index'),
    path('doctors', views.doctors, name='doctors'),
    path('/patients', views.patients, name='patients'),
    path('/diagnosis', views.diagnosis, name='diagnosis'),
    path('/bills', views.bills, name='bills'),
    path('/staff', views.staff, name='staff'),
]