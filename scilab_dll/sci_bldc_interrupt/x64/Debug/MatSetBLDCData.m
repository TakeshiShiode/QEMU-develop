function MatSetBLDCData(theta, vdc, Iu, Iw, omega)
    theta_ptr = libpointer('doublePtr', theta);
    vdc_ptr   = libpointer('doublePtr', vdc);
    Iu_ptr    = libpointer('doublePtr', Iu);
    Iw_ptr    = libpointer('doublePtr', Iw);
    omega_ptr = libpointer('doublePtr', omega);
    ret = 0;
    ret_ptr   = libpointer('doublePtr', ret);
    calllib('SCIBLDCINTERRUPT','SciSetBLDCData', theta_ptr, vdc_ptr, Iu_ptr, Iw_ptr, omega_ptr, ret_ptr);
end