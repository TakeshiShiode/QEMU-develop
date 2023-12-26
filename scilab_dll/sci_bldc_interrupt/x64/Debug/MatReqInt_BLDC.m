function result = MatReqInt_BLDC()
    req= 0;
    req_ptr = libpointer('doublePtr',req);
    calllib('SCIBLDCINTERRUPT','SciReqInt_BLDC', req_ptr);
    result = req_ptr.value;
end