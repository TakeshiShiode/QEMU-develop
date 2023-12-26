R = 0.453;
Ld = 0.0009447;
Lq = 0.0009447;
qsi = 0.006198;
P = 7;
J = 0.00025;
D = 0.00075;
V = 24;

result = MatHandleInit();
MatSetBLDCData(0,0,0,0,0);

function  result = MatHandleInit()
    ret = 0;
    ret_ptr = libpointer('doublePtr', ret);
    loadlibrary('SCIBLDCINTERRUPT','sci_bldc_interrupt.h')
    calllib('SCIBLDCINTERRUPT','SciHandleInit',ret_ptr);
    result = ret_ptr.value;
end
