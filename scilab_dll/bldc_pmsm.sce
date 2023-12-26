functions1 = ["SciHandleInit";];
link("SCIBLDCINTERRUPT.dll", functions1, "c");  
function ret=SciHandleInit()
  ret = call("SciHandleInit", "out", [1 1], 1, "d");
endfunction

functions2 = ["SciReqInt_BLDC";];
link("SCIBLDCINTERRUPT.dll", functions2, "c");  
function ret=SciReqInt_BLDC()
  ret = call("SciReqInt_BLDC", "out", [1 1], 1, "d");
endfunction

functions3 = ["SciGetBLDC_PWM_U";];
link("SCIBLDCINTERRUPT.dll", functions3, "c");  
function ret=SciGetBLDC_PWM_U()
  ret = call("SciGetBLDC_PWM_U", "out", [1 1], 1, "d");
endfunction

functions4 = ["SciGetBLDC_PWM_V";];
link("SCIBLDCINTERRUPT.dll", functions4, "c");  
function ret=SciGetBLDC_PWM_V();
  ret = call("SciGetBLDC_PWM_V", "out", [1 1], 1, "d");
endfunction

functions5 = ["SciGetBLDC_PWM_W";];
link("SCIBLDCINTERRUPT.dll", functions5, "c");  
function ret=SciGetBLDC_PWM_W();
  ret = call("SciGetBLDC_PWM_W", "out", [1 1], 1, "d");
endfunction

functions6 = ["SciSetBLDCData";];
link("SCIBLDCINTERRUPT.dll", functions6, "c");  
function ret=SciSetBLDCData(pos, vdc, iu, iw, omega);
  ret = call("SciSetBLDCData", pos, 1, "d", vdc, 2, "d", iu, 3, "d", iw, 4, "d", omega, 5, "d", "out", [1 1], 1, "d");
endfunction
