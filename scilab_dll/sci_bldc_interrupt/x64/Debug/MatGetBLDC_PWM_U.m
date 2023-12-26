function Vu = MatGetBLDC_PWM_U()
    pwm = 0;
    pwm_ptr = libpointer('doublePtr', pwm);
    calllib('SCIBLDCINTERRUPT','SciGetBLDC_PWM_U', pwm_ptr);
    Vu = pwm_ptr.value;
end