# Generated by Django 4.1.3 on 2022-11-27 21:19

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('website', '0002_alter_patient_dr_code'),
    ]

    operations = [
        migrations.AddField(
            model_name='diagnosis',
            name='dr_code',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='website.doctor'),
        ),
        migrations.AddField(
            model_name='diagnosis',
            name='dr_name',
            field=models.CharField(max_length=100, null=True),
        ),
        migrations.AlterField(
            model_name='bill',
            name='dr_code',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='website.doctor'),
        ),
        migrations.AlterField(
            model_name='bill',
            name='pat_code',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='website.patient'),
        ),
        migrations.AlterField(
            model_name='diagnosis',
            name='pat_code',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='website.patient'),
        ),
        migrations.AlterField(
            model_name='staff',
            name='dr_code',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='website.doctor'),
        ),
    ]