function Vv = MatGetBLDC_PWM_V()
    pwm = 0;
    pwm_ptr = libpointer('doublePtr', pwm);
    calllib('SCIBLDCINTERRUPT','SciGetBLDC_PWM_V', pwm_ptr);
    Vv = pwm_ptr.value;
end