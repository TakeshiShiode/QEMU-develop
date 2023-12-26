function Vw = MatGetBLDC_PWM_W()
    pwm = 0;
    pwm_ptr = libpointer('doublePtr', pwm);
    calllib('SCIBLDCINTERRUPT','SciGetBLDC_PWM_W', pwm_ptr);
    Vw = pwm_ptr.value;
end